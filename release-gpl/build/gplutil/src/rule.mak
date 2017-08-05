unexport EXTRA_AFLAGS
unexport EXTRA_CFLAGS
unexport EXTRA_LDFLAGS
unexport EXTRA_ARFLAGS
unexport SUBDIRS
unexport SUB_DIRS
unexport O_TARGET
unexport L_TARGET
unexport OBJS
unexport SUB_LIBA
unexport EXTRA_OBJS

REAL_OBJS:=$(patsubst %,$(O)%,$(OBJS))

REAL_MACROS:=$(patsubst %.o,$(O)%.macro,$(OBJS))

REAL_MLOG:=$(patsubst %.o,$(O)%.mlog,$(OBJS))
REAL_SYMBOL_CALLS:=$(patsubst %.o,$(O)%.call,$(OBJS))

ifneq ($(CC), $(HOSTCC))
SO_WHOLE_ARCHIVE_FLAG=$(patsubst %.a,$(STAGING_DIR)/lib/%.a,$(SUB_LIBA))
else
SO_WHOLE_ARCHIVE_FLAG=$(patsubst %.a,$(HOST_LIB_DIR)/%.a,$(SUB_LIBA))
endif

# Strip quotes and then whitespaces
qstrip=$(strip $(subst ",,$(1)))
#"))

.PHONY: clean cfile

ifeq ($(CC), $(HOSTCC))
CFLAGS += -m32
endif

ifeq ($(strip $(BR2_ENABLE_DEBUG)),y)
DBG_FLAGS = -g
CFLAGS += -O0 -ftrapv 
EXTRA_FLAG = -O0
else
CFLAGS += -s -Os -fomit-frame-pointer 
EXTRA_FLAG = -s -Os -fomit-frame-pointer  
SECURE_LDFLAGS = -pie
endif

ifeq ("$(VENDOR)", "ws860s")
CFLAGS += -lpthread -L$(STAGING_DIR)/lib
else ifeq ("$(VENDOR)", "ws860s_rom")
CFLAGS += -lpthread -L$(STAGING_DIR)/lib
else
CFLAGS += -L$(STAGING_DIR)/lib
endif

CFLAGS += -Wall  -DCONFIG_32BIT 
EXTRA_FLAG += -Wall -DCONFIG_32BIT 
CFLAGS += -Wl,-Map=$(O)$(PROGRAM_NAME).map
EXTRA_FLAG += -Wl,-Map=$(O)$(PROGRAM_NAME).map


#CFLAGS += -Werror -Wno-strict-aliasing 
EXTRA_FLAG += -Werror -Wno-strict-aliasing 

CFLAGS += $(if $(ALLOW_UNDEFINED), ,-Wl,-no-undefined)

CFLAGS += $(ATPFLAGS) $(LDFLAGS)

ifneq ($(filter shared,$(MAKECMDGOALS)),)
CFLAGS += -fPIC
endif

ifeq ($(strip $(BR2_ARCH)),"i386")
CFLAGS += -DSUPPORT_DESKTOP -DATP_DEBUG_CMS_PC_VERSION -D_GNU_SOURCE -fprofile-arcs -ftest-coverage -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
CPPFLAGS += -DSUPPORT_DESKTOP -DATP_DEBUG_CMS_PC_VERSION -fprofile-arcs -ftest-coverage -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
endif

ifeq ($(strip $(BR2_ENDIAN)),"LITTLE")
CFLAGS += -DCONFIG_CPU_LITTLE_ENDIAN
else
CFLAGS += -DCONFIG_CPU_BIG_ENDIAN
endif

CURR_DIR = $(shell pwd)
ifeq ($(strip $(ATP_UNIT_TEST)),yes)
CFLAGS += -DSUPPORT_UNIT_TEST
CPPFLAGS += -DSUPPORT_UNIT_TEST
endif

CFLAGS += $(if $(ATP_DEBUG),-DATP_DEBUG,-DATP_RELEASE)
CPPFLAGS += $(if $(ATP_DEBUG),-DATP_DEBUG,-DATP_RELEASE)

ifneq ($(CC), $(HOSTCC))
ifeq ($(strip $(LOCAL_NO_DMALLOC_SUPPORT)),)
CFLAGS += $(if $(ATP_DMALLOC),-DATP_DMALLOC,)
EXTRA_LIB += $(if $(ATP_DMALLOC),-ldmallocth)
endif
endif

# secure compile -Wshadow -Wcast-qual
CFLAGS += -Werror=format-security   
CPPFLAGS += -Werror=format-security 
CFLAGS += -D_FORTIFY_SOURCE=2 -O2
SECURE_LDFLAGS += -Wl,-z,relro,-z,noexecstack,-z,now -Wl,--disable-new-dtags,--rpath,/lib:/app/lib:/system/lib:/usr/lib

ifneq ($(ANDROID_BUILD_TOP),)
CFLAGS += -fstack-protector
endif

ifeq ($(STATIC_LINK),)
LINK_LIBS=$(LIBS) $(EXTRA_LIB)
else
LINK_LIBS=$(patsubst %-l$(STATIC_LINK),%-l$(STATIC_LINK)_pic,$(LIBS) $(EXTRA_LIB))
endif

#sed -e '/# /d' -e '/#/!d' -e 's/#define //' -e 's/#undef //' -e '/SUPPORT_/!d' package/atp/configuration/cwmp/cms/src/tmp_dU.txt

################ maybe we use more variety source code, then add rule below	
$(O)%.o: %.c
	@echo "	Compiling " $<
	@mkdir -p $(dir $@)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_$@) $(DBG_FLAGS) -c -o $@ $<

#$(Q)$(CC) -E -dU $< | tac | sed '/.h"/q' | sed '/.h>/q' | tac | sed -e '/# /d' -e '/#/!d' > $@
$(O)%.macro: %.c
	@echo "	Generating macros " $<
	@mkdir -p $(dir $@)
	$(Q)$(CC) -E -dU $< | sed -e '/# /d' -e '/#/!d' -e '/SUPPORT_/!d' > $@
	$(Q)python $(TARGET_DIR)/../../package/atp/hosttool/citools/src/macro_detect.py $< $@

$(O)%.mlog: %.c
	@echo "	Generating mlog " $<
	@mkdir -p $(dir $@)
	$(Q)-$(CC) -E -dU $< | grep -w 'mlog_print\|ATP_TRACE_PrintInfo' | sed -e '/void mlog_print/d' -e '/ATP_TRACE_PrintInfo(__FILE__/d' -e '/VOS_BOOL ATP_TRACE_PrintInfo/d' > $@
	$(Q)python $(TARGET_DIR)/../../package/atp/hosttool/citools/src/mlog_analyser.py $@ $(PACKAGE_NAME) $<

$(O)%.call: %.c
	@echo "	Generating symbol call report " $<
	@mkdir -p $(dir $@)
ifeq ($(CONVERT),)
	$(Q)python $(TARGET_DIR)/../../package/atp/hosttool/citools/src/call_analyse.py $< analyse $@
else
	@echo "Need convert now ..."
	$(Q)python $(TARGET_DIR)/../../package/atp/hosttool/citools/src/call_analyse.py $< convert $(TARGET_DIR)/../../output/package/atp/configuration/datamodel/cmo_report.xml
endif

$(O)%.o: %.cpp
	@echo "	Compiling " $<
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CFLAGS_$@) $(DBG_FLAGS) -c -o $@ $<

$(O)%.o: %.s
	$(AS) $(AFLAGS) -o $@ $<

$(O)%.so : $(O)%.o 
	$(CC) $(CFLAGS) $(SECURE_LDFLAGS) -fPIC -fvisibility=default -shared $^ -o $@

all_targets: $(O_TARGET) $(L_TARGET)

ifdef O_TARGET
ifeq ($(O_TARGET), $(REAL_OBJS))
$(O_TARGET):
else
$(O_TARGET): $(REAL_OBJS)
	rm -f $@
	$(ORIGIN_LD) $(EXTRA_LDFLAGS) $(LDFLAGS) -r -o $(O)$@ $(filter $(REAL_OBJS), $^)
endif
endif

ifdef L_TARGET
$(L_TARGET): $(REAL_OBJS)
	$(RM) lib$@.a
	$(AR) $(EXTRA_ARFLAGS) rcs $(O)lib$@.a $@.o	
endif

subdir-list = $(sort $(patsubst %,_subdir_%,$(SUB_DIRS)))
sub_dirs: $(subdir-list)
$(REAL_OBJS):sub_dirs

ifdef SUB_DIRS
$(subdir-list):
	@echo "mkdir -p $(O)$@"
	@mkdir -p $(O)$(patsubst _subdir_%,%,$@)
	$(MAKE) -C $(patsubst _subdir_%,%,$@)
endif

dynamic: $(O)$(PROGRAM_NAME)

static: $(O)lib$(PROGRAM_NAME).a

CFLAGS_LINT =$(subst $(EXTRA_FLAG), ,$(CFLAGS))
WINE_LINT_FLAG=$(subst -I,-i,$(CFLAGS_LINT))

PCLINT_FLAGS =  -i$(TARGET_DIR)/../../package/atp/hosttool/PCLINT/lintinclude \
		-i$(TARGET_DIR)/../../package/atp/hosttool/PCLINT/lintinclude/asm \
		-i$(TARGET_DIR)/../../package/atp/hosttool/PCLINT/lintinclude/bits \
		-i$(TARGET_DIR)/../../package/atp/hosttool/PCLINT/lintinclude/gnu \
		-i$(TARGET_DIR)/../../package/atp/hosttool/PCLINT/lintinclude/linux \
		-i$(TARGET_DIR)/../../package/atp/hosttool/PCLINT/lintinclude/sys \
		-i$(STAGING_DIR)/usr/include

PCLINT_FLAGS +=	-DVTOP_OS_TYPE=VTOP_OS_LINUX \
                -D_GNU_SOURCE \
                -D__FUNCTION__=\"\"\
                -DATP_RELEASE \
                -DVOS_ERROR \
                -DNULL=0 \
                -D_POSIX

CFILES = $(patsubst %.o,%.c,$(OBJS))
CFILES_PATH=`pwd`
CFLIES_FULL_PATH = $(addprefix $(CFILES_PATH)/,$(CFILES))

pclint:
	@echo "std_new.lnt env-si.lnt" > $(O)$(PROGRAM_NAME).lnt
	@echo "-os($(O)$(PROGRAM_NAME)_lint_report.txt)" >>$(O)$(PROGRAM_NAME).lnt
	@echo $(WINE_LINT_FLAG) >>$(O)$(PROGRAM_NAME).lnt
	@echo $(PCLINT_FLAGS) >>$(O)$(PROGRAM_NAME).lnt
	@echo $(CFLIES_FULL_PATH) >>$(O)$(PROGRAM_NAME).lnt
	@if which wine; then \
		cd $(TARGET_DIR)/../../package/atp/hosttool/PCLINT; wine lint-nt.exe $(O)$(PROGRAM_NAME).lnt; \
	else \
		if [ -f $(TARGET_DIR)/../build/wine/wine/wine ]; then\
			cd $(TARGET_DIR)/../../package/atp/hosttool/PCLINT; $(TARGET_DIR)/../build/wine/wine/wine lint-nt.exe $(O)$(PROGRAM_NAME).lnt; \
		else \
			echo "You should execute [make VENDOR=$(VENDOR) CUSTOMER=$(CUSTOMER) wine] to generate wine."; \
			exit; \
		fi; \
	fi
	@echo "PCLint for $(PROGRAM_NAME) -----------------------"
	@cat $(O)$(PROGRAM_NAME)_lint_report.txt | sed "/--- Global Wrap-up/q"
	@echo ""
	@echo ""
	@echo ""
	@echo "PCLint report path: $(O)$(PROGRAM_NAME)_lint_report.txt"
	@echo ""

pclint_clean:

mlog_analysis: $(O)$(PROGRAM_NAME)_mlog.txt
    ifneq ($(REAL_MLOG),)
	$(Q)python $(TARGET_DIR)/../../package/atp/hosttool/citools/src/mlog_module.py $(O)$(PROGRAM_NAME)_mlog.txt $(PACKAGE_NAME) $(TARGET_DIR)/../../tmp_mlog_report.xml
    endif
mlog_clean:
	@rm -fr $(O)$(PROGRAM_NAME)_mlog.txt $(REAL_MLOG) $(O)$(PROGRAM_NAME)_mlog.xml

$(O)$(PROGRAM_NAME)_mlog.txt: $(REAL_MLOG)
    ifneq ($(REAL_MLOG),)
	$(Q)cat $(REAL_MLOG) > $(O)$(PROGRAM_NAME)_mlog.txt
    endif
macro_analysis: $(O)$(PROGRAM_NAME).mtxt
	$(Q)python $(TARGET_DIR)/../../package/atp/hosttool/citools/src/macro_analyser.py $(O)$(PROGRAM_NAME).mtxt $(PACKAGE_NAME) $(TARGET_DIR)/../../tmp_macro_report.xml

macro_clean:
	@rm -fr $(O)$(PROGRAM_NAME).mtxt $(REAL_MACROS)

$(O)$(PROGRAM_NAME).mtxt: $(REAL_MACROS)
	$(Q)cat $(REAL_MACROS) > $(O)$(PROGRAM_NAME).mtxt

$(O)$(PROGRAM_NAME)_scall.xml: $(REAL_SYMBOL_CALLS)

call_analysis: $(O)$(PROGRAM_NAME)_scall.xml
ifeq ($(CONVERT),)
	$(Q)echo "<items>" > $(O)$(PROGRAM_NAME)_scall.xml
	$(Q)cat $(REAL_SYMBOL_CALLS) >> $(O)$(PROGRAM_NAME)_scall.xml
	$(Q)echo "</items>" >> $(O)$(PROGRAM_NAME)_scall.xml
	$(Q)cat $(REAL_SYMBOL_CALLS) >> $(TARGET_DIR)/../../tmp_scall_report.xml
endif

call_clean:
	@rm -fr $(O)$(PROGRAM_NAME)_scall.xml $(REAL_SYMBOL_CALLS)

$(O)$(PROGRAM_NAME): $(REAL_OBJS)
ifeq ($(strip $(BR2_ARCH)),"i386")
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(SECURE_LDFLAGS) $(DBG_FLAGS) -Wl,--whole-archive $(patsubst %,-l%,$(SUBMODULES)) -Wl,--no-whole-archive -o $(O)$(PROGRAM_NAME) $(REAL_OBJS) $(LINK_LIBS) -lgcov
else
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(SECURE_LDFLAGS) $(DBG_FLAGS) -Wl,--whole-archive $(patsubst %,-l%,$(SUBMODULES)) -Wl,--no-whole-archive -o $(O)$(PROGRAM_NAME) $(REAL_OBJS) $(LINK_LIBS)
endif

ifneq ($(strip $(SUB_LIBA)),)
$(O)lib$(PROGRAM_NAME).a: $(O)lib$(PROGRAM_NAME)_pic.a $(REAL_OBJS)
	@echo "Static library build finished."
ifneq ($(CC), $(HOSTCC))
	if [ -f $(STAGING_DIR)/lib/lib$(PROGRAM_NAME)_pic.a ]; then \
		mv -f $(STAGING_DIR)/lib/lib$(PROGRAM_NAME)_pic.a $(O)lib$(PROGRAM_NAME).a; \
	fi
endif
else
$(O)lib$(PROGRAM_NAME).a: $(REAL_OBJS)
	$(AR) rcs $@ $^
endif

ifneq ($(CC), $(HOSTCC))
ifneq ($(strip $(SUB_LIBA)),)
$(O)lib$(PROGRAM_NAME)_pic.a: $(REAL_OBJS) $(EXTRA_OBJS)
	@echo ===================
	@echo $(SUB_LIBA) $(STAGING_DIR) $(SUB_LIBA)
	@echo ===================
	rm -fr $(STAGING_DIR)/lib/$(PROGRAM_NAME)
	mkdir -p $(STAGING_DIR)/lib/$(PROGRAM_NAME)
	$(foreach b,$(SUB_LIBA), cp $(STAGING_DIR)/lib/$(b) $(STAGING_DIR)/lib/$(PROGRAM_NAME);)
	cd $(STAGING_DIR)/lib/$(PROGRAM_NAME); \
	$(foreach b,$(SUB_LIBA), ar x $(STAGING_DIR)/lib/$(PROGRAM_NAME)/$(b);)
	$(ORIGIN_LD) $(LDFLAGS) -r -o $(STAGING_DIR)/lib/$(PROGRAM_NAME)_pic.o $(STAGING_DIR)/lib/$(PROGRAM_NAME)/*.o
	#rm -fr $(STAGING_DIR)/lib/$(PROGRAM_NAME)
	ar rc $(STAGING_DIR)/lib/lib$(PROGRAM_NAME)_pic.a $(STAGING_DIR)/lib/$(PROGRAM_NAME)_pic.o $(REAL_OBJS) $(EXTRA_OBJS)
	ranlib $(STAGING_DIR)/lib/lib$(PROGRAM_NAME)_pic.a
	rm -f $(STAGING_DIR)/lib/$(PROGRAM_NAME)_pic.o
else
$(O)lib$(PROGRAM_NAME)_pic.a: $(REAL_OBJS) $(EXTRA_OBJS)
	$(AR) rcs $@ $^
endif
else
ifneq ($(strip $(SUB_LIBA)),)
$(O)lib$(PROGRAM_NAME)_pic.a: $(REAL_OBJS) $(EXTRA_OBJS)
	echo $(SO_WHOLE_ARCHIVE_FLAG)
	@echo $(SUB_LIBA) $(ORIGIN_LD) $(SUB_LIBA)
	rm -fr $(HOST_LIB_DIR)/$(PROGRAM_NAME)
	mkdir -p $(HOST_LIB_DIR)/$(PROGRAM_NAME)
	$(foreach b,$(SUB_LIBA), cp $(HOST_LIB_DIR)/$(b) $(HOST_LIB_DIR)/$(PROGRAM_NAME);)
	cd $(HOST_LIB_DIR)/$(PROGRAM_NAME); \
	$(foreach b,$(SUB_LIBA), ar x $(HOST_LIB_DIR)/$(PROGRAM_NAME)/$(b);)
	
	#/usr/bin/ld -r -o $(HOST_LIB_DIR)/$(PROGRAM_NAME)_pic.o $(HOST_LIB_DIR)/$(PROGRAM_NAME)/*.o
	#rm -fr $(STAGING_DIR)/lib/$(PROGRAM_NAME)
	ar rc $(HOST_LIB_DIR)/lib$(PROGRAM_NAME)_pic.a $(HOST_LIB_DIR)/$(PROGRAM_NAME)/*.o $(REAL_OBJS) $(EXTRA_OBJS)
	ranlib $(HOST_LIB_DIR)/lib$(PROGRAM_NAME)_pic.a
	mv $(HOST_LIB_DIR)/lib$(PROGRAM_NAME)_pic.a $(HOST_LIB_DIR)/lib$(PROGRAM_NAME).a
	rm -f $(HOST_LIB_DIR)/$(PROGRAM_NAME)_pic.o
else
$(O)lib$(PROGRAM_NAME)_pic.a: $(REAL_OBJS) $(EXTRA_OBJS)
	$(AR) rcs $@ $^
endif
endif

shared: $(O)lib$(PROGRAM_NAME)_pic.a $(REAL_OBJS)
	echo $(SO_WHOLE_ARCHIVE_FLAG)
	$(CC) $(CFLAGS) $(SECURE_LDFLAGS) -fPIC -fvisibility=default -shared $(REAL_OBJS) $(EXTRA_OBJS) $(LINK_LIBS) -Wl,--whole-archive $(SO_WHOLE_ARCHIVE_FLAG) -Wl,--no-whole-archive -o $(O)lib$(PROGRAM_NAME).so -Wl,--soname,lib$(PROGRAM_NAME).so

clean:
	@rm -f $(O)*.o $(O)*.a $(O)*.so $(O)*.gcda $(O)*.gcno
	@find $(O) -name "*.o" 2>/dev/null | xargs rm -f
	@find $(O) -name "*.so" 2>/dev/null | xargs rm -f 2>&1 >/dev/null
	@find $(O) -name "*.gcda" 2>/dev/null | xargs rm -f 2>&1 >/dev/null
	@find $(O) -name "*.gcno" 2>/dev/null | xargs rm -f 2>&1 >/dev/null
	@find $(O) -name "*.macro" 2>/dev/null | xargs rm -f 2>&1 >/dev/null
	@find $(O) -name "*.mlog" 2>/dev/null | xargs rm -f 2>&1 >/dev/null
	@$(foreach dir,$(SUB_DIRS), if [ -d $(dir) ];then cd $(dir);make clean; cd $(CURR_DIR);fi;)

cfile:
	@echo "<files>$(patsubst %.o,%.c,$(OBJS))</files>" >> $(TOPDIR)/cfiles.xml
