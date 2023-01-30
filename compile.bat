cl -c topcat-launcher.c
rc topcat-launcher.rc
link topcat-launcher.obj topcat-launcher.res User32.lib Gdi32.lib -out:topcat-launcher.exe