IPOBJ=ip.o ipaddress.o ipaddrlabel.o iproute.o iprule.o \
    rtm_map.o iptunnel.o ip6tunnel.o tunnel.o ipneigh.o ipntable.o iplink.o \
    ipmaddr.o ipmonitor.o ipmroute.o ipprefix.o \
    ipxfrm.o xfrm_state.o xfrm_policy.o xfrm_monitor.o \
    iplink_vlan.o link_veth.o ipl2tp.o link_gre.o

#RTMON = 1

ifdef RTMON
RTMONOBJ=rtmon.o
endif

ALLOBJ=$(IPOBJ) 

ifdef RTMON
ALLOBJ+=$(RTMONOBJ)
endif

SCRIPTS=ifcfg rtpr routel routef
TARGETS=ip

ifdef RTMON
TARGETS+=rtmon
endif

all: $(TARGETS) $(SCRIPTS) $(LIBS)

ip: $(IPOBJ) $(LIBNETLINK) $(LIBUTIL)

rtmon: $(RTMONOBJ) $(LIBNETLINK)

install: all
	install -m 0755 $(TARGETS) $(DESTDIR)$(SBINDIR)
	install -m 0755 $(SCRIPTS) $(DESTDIR)$(SBINDIR)

clean:
	rm -f $(ALLOBJ) $(TARGETS)

LDLIBS += -ldl

LDFLAGS += -Wl,-export-dynamic
