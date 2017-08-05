cmd_applets/built-in.o :=  ld  -L/lib/ -L./ -L../../gplutil/src/ -lgplutil  -r -o applets/built-in.o applets/applets.o
