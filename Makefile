# Makefile for the Random Wallpaper Tool
# Adapted from the Watcom example makefile included with libjpeg.
# Libjpeg will also need to be separately built; the makefiles
# are not presently chained.
# This also uses the WRBMP file from libjpeg which is not actually
# built into the library

SYSTEM=DOS
CC= wcl386
CFLAGS= -4r -ort -wx -zq -bt=$(SYSTEM) -i=LIBJPEG

# Caution: avoid -ol or -ox; these generate bad code with 10.0 or 10.0a.
# Generally, we recommend defining any configuration symbols in jconfig.h,
# NOT via -D switches here.

# Link-time cc options:
!ifeq SYSTEM DOS
LDFLAGS= -zq -l=dos4g
!else ifeq SYSTEM OS2
LDFLAGS= -zq -l=os2v2
!else ifeq SYSTEM NT
LDFLAGS= -zq -l=nt
!endif

# Object files for Random wallpaper tool
RANDOBJS= randwp.obj wrbmp.obj

all: randwp.exe

# Random Wallpaper tool
randwp.exe: randwp.obj $(RANDOBJS) libjpeg\libjpeg.lib
	$(CC) $(LDFLAGS) $(RANDOBJS) libjpeg\libjpeg.lib

.c.obj:
	$(CC) $(CFLAGS) -c $<

clean: .SYMBOLIC
	- del *.obj
	- del randwp.exe

randwp.obj: randwp.c
wrbmp.obj: wrbmp.c
