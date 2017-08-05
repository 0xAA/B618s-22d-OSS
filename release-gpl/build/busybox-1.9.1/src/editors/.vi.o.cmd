cmd_editors/vi.o := cc -Wp,-MD,editors/.vi.o.d   -std=gnu99 -Iinclude -Ilibbb  -I/usr1/w00208043/test/package/xiaotiannew1248/release-gpl/build/busybox-1.9.1/src/libbb -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D"BB_VER=\"v1.9.1\"" -DBB_BT=AUTOCONF_TIMESTAMP -D_FORTIFY_SOURCE=2   -w -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Os -fno-builtin-strlen -finline-limit=0 -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -Wdeclaration-after-statement -Wno-pointer-sign -I/usr/include -I/openssl -I../../../host/usr/arm-unknown-linux-gnueabi/sysroot/usr/include -fno-strict-aliasing    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(vi)"  -D"KBUILD_MODNAME=KBUILD_STR(vi)" -c -o editors/vi.o editors/vi.c

deps_editors/vi.o := \
  editors/vi.c \
    $(wildcard include/config/feature/vi/crashme.h) \
    $(wildcard include/config/locale/support.h) \
    $(wildcard include/config/feature/vi/8bit.h) \
    $(wildcard include/config/feature/vi/max/len.h) \
    $(wildcard include/config/feature/vi/readonly.h) \
    $(wildcard include/config/feature/vi/dot/cmd.h) \
    $(wildcard include/config/feature/vi/optimize/cursor.h) \
    $(wildcard include/config/feature/vi/use/signals.h) \
    $(wildcard include/config/nals.h) \
    $(wildcard include/config/feature/vi/yankmark.h) \
    $(wildcard include/config/feature/vi/search.h) \
    $(wildcard include/config/feature/vi/colon.h) \
    $(wildcard include/config/feature/vi/setopts.h) \
    $(wildcard include/config/buffer.h) \
    $(wildcard include/config/ture/vi/colon.h) \
    $(wildcard include/config/ture/vi/readonly.h) \
    $(wildcard include/config/feature/vi/win/resize.h) \
    $(wildcard include/config/ture/vi/yankmark.h) \
    $(wildcard include/config/ture/vi/search.h) \
    $(wildcard include/config/feature/vi/set.h) \
    $(wildcard include/config/feature/allow/exec.h) \
  include/libbb.h \
    $(wildcard include/config/selinux.h) \
    $(wildcard include/config/feature/shadowpasswds.h) \
    $(wildcard include/config/lfs.h) \
    $(wildcard include/config/feature/buffers/go/on/stack.h) \
    $(wildcard include/config/ubuffer.h) \
    $(wildcard include/config/feature/buffers/go/in/bss.h) \
    $(wildcard include/config/feature/ipv6.h) \
    $(wildcard include/config/ture/ipv6.h) \
    $(wildcard include/config/feature/prefer/applets.h) \
    $(wildcard include/config/busybox/exec/path.h) \
    $(wildcard include/config/getopt/long.h) \
    $(wildcard include/config/feature/pidfile.h) \
    $(wildcard include/config/feature/syslog.h) \
    $(wildcard include/config/feature/individual.h) \
    $(wildcard include/config/route.h) \
    $(wildcard include/config/gunzip.h) \
    $(wildcard include/config/bunzip2.h) \
    $(wildcard include/config/ktop.h) \
    $(wildcard include/config/ioctl/hex2str/error.h) \
    $(wildcard include/config/feature/editing.h) \
    $(wildcard include/config/feature/editing/history.h) \
    $(wildcard include/config/ture/editing/savehistory.h) \
    $(wildcard include/config/feature/editing/savehistory.h) \
    $(wildcard include/config/feature/tab/completion.h) \
    $(wildcard include/config/feature/username/completion.h) \
    $(wildcard include/config/feature/editing/vi.h) \
    $(wildcard include/config/inux.h) \
    $(wildcard include/config/feature/topmem.h) \
    $(wildcard include/config/pgrep.h) \
    $(wildcard include/config/pkill.h) \
    $(wildcard include/config/feature/devfs.h) \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config///.h) \
    $(wildcard include/config//nommu.h) \
    $(wildcard include/config//mmu.h) \
  /usr/include/byteswap.h \
  /usr/include/x86_64-linux-gnu/bits/byteswap.h \
  /usr/include/x86_64-linux-gnu/bits/wordsize.h \
  /usr/include/endian.h \
    $(wildcard include/config/.h) \
  /usr/include/features.h \
    $(wildcard include/config/c99.h) \
    $(wildcard include/config/c95.h) \
    $(wildcard include/config/ix.h) \
    $(wildcard include/config/ix2.h) \
    $(wildcard include/config/ix199309.h) \
    $(wildcard include/config/ix199506.h) \
    $(wildcard include/config/en.h) \
    $(wildcard include/config/en/extended.h) \
    $(wildcard include/config/x98.h) \
    $(wildcard include/config/en2k.h) \
    $(wildcard include/config/en2kxsi.h) \
    $(wildcard include/config/en2k8.h) \
    $(wildcard include/config/en2k8xsi.h) \
    $(wildcard include/config/gefile.h) \
    $(wildcard include/config/gefile64.h) \
    $(wildcard include/config/e/offset64.h) \
    $(wildcard include/config/d.h) \
    $(wildcard include/config/c.h) \
    $(wildcard include/config/ile.h) \
    $(wildcard include/config/ntrant.h) \
    $(wildcard include/config/tify/level.h) \
    $(wildcard include/config/i.h) \
    $(wildcard include/config/ix/implicitly.h) \
    $(wildcard include/config/ern/inlines.h) \
    $(wildcard include/config/ern/inlines/in/libc.h) \
  /usr/include/x86_64-linux-gnu/bits/predefs.h \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
    $(wildcard include/config/espaces.h) \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/include/x86_64-linux-gnu/bits/endian.h \
  /usr/include/arpa/inet.h \
  /usr/include/netinet/in.h \
  /usr/include/stdint.h \
  /usr/include/x86_64-linux-gnu/bits/wchar.h \
  /usr/include/x86_64-linux-gnu/sys/socket.h \
  /usr/include/x86_64-linux-gnu/sys/uio.h \
  /usr/include/x86_64-linux-gnu/sys/types.h \
  /usr/include/x86_64-linux-gnu/bits/types.h \
  /usr/include/x86_64-linux-gnu/bits/typesizes.h \
  /usr/include/time.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.4.7/include/stddef.h \
  /usr/include/x86_64-linux-gnu/sys/select.h \
  /usr/include/x86_64-linux-gnu/bits/select.h \
  /usr/include/x86_64-linux-gnu/bits/sigset.h \
  /usr/include/x86_64-linux-gnu/bits/time.h \
  /usr/include/x86_64-linux-gnu/bits/select2.h \
  /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
  /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/x86_64-linux-gnu/bits/uio.h \
  /usr/include/x86_64-linux-gnu/bits/socket.h \
  /usr/include/x86_64-linux-gnu/bits/sockaddr.h \
  /usr/include/x86_64-linux-gnu/asm/socket.h \
  /usr/include/asm-generic/socket.h \
  /usr/include/x86_64-linux-gnu/asm/sockios.h \
  /usr/include/asm-generic/sockios.h \
  /usr/include/x86_64-linux-gnu/bits/socket2.h \
  /usr/include/x86_64-linux-gnu/bits/in.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.4.7/include/stdbool.h \
  /usr/include/x86_64-linux-gnu/sys/mount.h \
  /usr/include/x86_64-linux-gnu/sys/ioctl.h \
  /usr/include/x86_64-linux-gnu/bits/ioctls.h \
  /usr/include/x86_64-linux-gnu/asm/ioctls.h \
  /usr/include/asm-generic/ioctls.h \
  /usr/include/linux/ioctl.h \
  /usr/include/x86_64-linux-gnu/asm/ioctl.h \
  /usr/include/asm-generic/ioctl.h \
  /usr/include/x86_64-linux-gnu/bits/ioctl-types.h \
  /usr/include/x86_64-linux-gnu/sys/ttydefaults.h \
  /usr/include/ctype.h \
  /usr/include/xlocale.h \
  /usr/include/dirent.h \
  /usr/include/x86_64-linux-gnu/bits/dirent.h \
  /usr/include/x86_64-linux-gnu/bits/posix1_lim.h \
  /usr/include/x86_64-linux-gnu/bits/local_lim.h \
  /usr/include/linux/limits.h \
  /usr/include/errno.h \
  /usr/include/x86_64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/x86_64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/fcntl.h \
  /usr/include/x86_64-linux-gnu/bits/fcntl.h \
  /usr/include/x86_64-linux-gnu/bits/stat.h \
  /usr/include/x86_64-linux-gnu/bits/fcntl2.h \
  /usr/include/inttypes.h \
  /usr/include/mntent.h \
  /usr/include/stdio.h \
  /usr/include/paths.h \
  /usr/include/netdb.h \
    $(wildcard include/config/3/ascii/rules.h) \
  /usr/include/rpc/netdb.h \
  /usr/include/x86_64-linux-gnu/bits/siginfo.h \
  /usr/include/x86_64-linux-gnu/bits/netdb.h \
  /usr/include/setjmp.h \
  /usr/include/x86_64-linux-gnu/bits/setjmp.h \
  /usr/include/x86_64-linux-gnu/bits/setjmp2.h \
  /usr/include/signal.h \
  /usr/include/x86_64-linux-gnu/bits/signum.h \
  /usr/include/x86_64-linux-gnu/bits/sigaction.h \
  /usr/include/x86_64-linux-gnu/bits/sigcontext.h \
  /usr/include/x86_64-linux-gnu/bits/sigstack.h \
  /usr/include/x86_64-linux-gnu/sys/ucontext.h \
  /usr/include/x86_64-linux-gnu/bits/sigthread.h \
  /usr/include/libio.h \
    $(wildcard include/config/a.h) \
    $(wildcard include/config/ar/t.h) \
    $(wildcard include/config//io/file.h) \
  /usr/include/_G_config.h \
  /usr/include/wchar.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.4.7/include/stdarg.h \
  /usr/include/x86_64-linux-gnu/bits/stdio_lim.h \
  /usr/include/x86_64-linux-gnu/bits/sys_errlist.h \
  /usr/include/x86_64-linux-gnu/bits/stdio2.h \
  /usr/include/stdlib.h \
  /usr/include/x86_64-linux-gnu/bits/waitflags.h \
  /usr/include/x86_64-linux-gnu/bits/waitstatus.h \
  /usr/include/alloca.h \
  /usr/include/x86_64-linux-gnu/bits/stdlib.h \
  /usr/include/string.h \
    $(wildcard include/config/ing/inlines.h) \
  /usr/include/x86_64-linux-gnu/bits/string3.h \
  /usr/include/x86_64-linux-gnu/sys/poll.h \
  /usr/include/x86_64-linux-gnu/bits/poll.h \
  /usr/include/x86_64-linux-gnu/sys/mman.h \
  /usr/include/x86_64-linux-gnu/bits/mman.h \
  /usr/include/x86_64-linux-gnu/sys/stat.h \
  /usr/include/x86_64-linux-gnu/sys/statfs.h \
  /usr/include/x86_64-linux-gnu/bits/statfs.h \
  /usr/include/x86_64-linux-gnu/sys/time.h \
  /usr/include/x86_64-linux-gnu/sys/wait.h \
  /usr/include/x86_64-linux-gnu/sys/resource.h \
  /usr/include/x86_64-linux-gnu/bits/resource.h \
  /usr/include/termios.h \
  /usr/include/x86_64-linux-gnu/bits/termios.h \
  /usr/include/x86_64-linux-gnu/bits/timex.h \
  /usr/include/unistd.h \
  /usr/include/x86_64-linux-gnu/bits/posix_opt.h \
  /usr/include/x86_64-linux-gnu/bits/environments.h \
  /usr/include/x86_64-linux-gnu/bits/confname.h \
  /usr/include/getopt.h \
  /usr/include/x86_64-linux-gnu/bits/unistd.h \
  /usr/include/utime.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.4.7/include-fixed/limits.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.4.7/include-fixed/syslimits.h \
  /usr/include/limits.h \
  /usr/include/x86_64-linux-gnu/bits/posix2_lim.h \
  /usr/include/x86_64-linux-gnu/bits/xopen_lim.h \
  /usr/include/x86_64-linux-gnu/sys/param.h \
  /usr/include/linux/param.h \
  /usr/include/x86_64-linux-gnu/asm/param.h \
  /usr/include/asm-generic/param.h \
  include/pwd_.h \
    $(wildcard include/config/use/bb/pwd/grp.h) \
  /usr/include/pwd.h \
  include/grp_.h \
  /usr/include/grp.h \
  include/xatonum.h \

editors/vi.o: $(deps_editors/vi.o)

$(deps_editors/vi.o):
