################### program name 

################### depend objects
#OBJS = gplutil.o gplmsg.o loginctl.o bget.o gplshmem.o procutil.o
OBJS = gplutil.o gplmsg.o bget.o gplshmem.o procutil.o loginctl.o proclockutil.o base64.o
OBJS += atpmiclisten.o listutil.o strutil.o traceapi.o

#ifneq ($(strip $(BUILD_IPV6)),)
OBJS += ifaddrs.o 
#endif

REAL_OBJS:=$(patsubst %,$(O)%,$(OBJS))
#REAL_LIBS = libtraceapi_gpl.a

#SUB_LIBA=libtraceapi_gpl.a

PROGRAM_NAME = gplutil
######################### compile options
CFLAGS = -fPIC -I../inc/ -I../../../host/usr/arm-unknown-linux-gnueabi/sysroot/usr/include
#LDFLAGS = ./libtraceapi_gpl.a
#CFLAGS += -fno-strict-aliasing -lsecurec
CFLAGS += -fno-strict-aliasing
LOCAL_NO_DMALLOC_SUPPORT:=y
include rule.mak
