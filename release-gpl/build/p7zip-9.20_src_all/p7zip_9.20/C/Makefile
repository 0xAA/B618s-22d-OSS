LIB_OBJECT = liblzma.a

RM = rm -fr

CFLAGS = -c -O2 -Wall



APTH_NOW = $(ANDROID_BUILD_TOP)/vendor/output/build/p7zip-9.20_src_all/p7zip_9.20
SRC_OBJECT = LzmaDec.c Alloc.c
OBJECT    := $(patsubst %.c,%.o,$(SRC_OBJECT))
H_OBJECT  := -I./  \
			-I$(APTH_NOW) \
          		 
all:$(LIB_OBJECT)
$(LIB_OBJECT):$(OBJECT)
	$(ARR) rcv $(LIB_OBJECT) $(OBJECT)

$(OBJECT):$(SRC_OBJECT)
	$(GCC)  $(CFLAGS) $(SRC_OBJECT) $(H_OBJECT)

	
	
#clean:
#	$(RM) $(LIB_DIR)/$(LIB_OBJECT) $(OBJECT)

	
