# Makefile for Independent JPEG Group's software

# This makefile is suitable for Watcom C/C++ 10.0 on MS-DOS (using
# dos4g extender), OS/2, and Windows NT console mode.
# Thanks to Janos Haide, jhaide@btrvtech.com.

# Read installation instructions before saying "wmake" !!

# Uncomment line for desired system
SYSTEM=DOS
#SYSTEM=OS2
#SYSTEM=NT

# The name of your C compiler:
CC= wcl386

# You may need to adjust these cc options:
CFLAGS= -4r -ort -wx -zq -bt=$(SYSTEM)
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

# Put here the object file name for the correct system-dependent memory
# manager file.  jmemnobs should work fine for dos4g or OS/2 environment.
SYSDEPMEM= jmemnobs.obj

# End of configurable options.


# source files: JPEG library proper
LIBSOURCES= jcapimin.c jcapistd.c jccoefct.c jccolor.c jcdctmgr.c jchuff.c &
		jcinit.c jcmainct.c jcmarker.c jcmaster.c jcomapi.c jcparam.c &
		jcphuff.c jcprepct.c jcsample.c jctrans.c jdapimin.c jdapistd.c &
		jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c jddctmgr.c jdhuff.c &
		jdinput.c jdmainct.c jdmarker.c jdmaster.c jdmerge.c jdphuff.c &
		jdpostct.c jdsample.c jdtrans.c jerror.c jfdctflt.c jfdctfst.c &
		jfdctint.c jidctflt.c jidctfst.c jidctint.c jidctred.c jquant1.c &
		jquant2.c jutils.c jmemmgr.c
# memmgr back ends: compile only one of these into a working library
SYSDEPSOURCES= jmemansi.c jmemname.c jmemnobs.c jmemdos.c jmemmac.c
# source files: cjpeg/djpeg/jpegtran applications, also rdjpgcom/wrjpgcom
APPSOURCES= cjpeg.c djpeg.c jpegtran.c rdjpgcom.c wrjpgcom.c cdjpeg.c &
		rdcolmap.c rdswitch.c transupp.c rdppm.c wrppm.c rdgif.c wrgif.c &
		rdtarga.c wrtarga.c rdbmp.c wrbmp.c rdrle.c wrrle.c
SOURCES= $(LIBSOURCES) $(SYSDEPSOURCES) $(APPSOURCES)
# files included by source files
INCLUDES= jchuff.h jdhuff.h jerror.h jinclude.h jmorecfg.h &
		jpegint.h jpeglib.h jversion.h cdjpeg.h cderror.h transupp.h
# documentation, test, and support files
DOCS= README install.doc usage.doc cjpeg.1 djpeg.1 jpegtran.1 rdjpgcom.1 &
		wrjpgcom.1 wizard.doc example.c libjpeg.doc structure.doc &
		coderules.doc filelist.doc change.log
MKFILES= configure makefile.cfg makefile.ansi makefile.unix makefile.bcc &
		makefile.mc6 makefile.dj makefile.wat makefile.vc makelib.ds &
		makeapps.ds makeproj.mac makcjpeg.st makdjpeg.st makljpeg.st &
		maktjpeg.st makefile.manx makefile.sas makefile.mms makefile.vms &
		makvms.opt
CONFIGFILES= jconfig.cfg jconfig.bcc jconfig.mc6 jconfig.dj jconfig.wat &
		jconfig.vc jconfig.mac jconfig.st jconfig.manx jconfig.sas &
		jconfig.vms
CONFIGUREFILES= config.guess config.sub install-sh ltconfig ltmain.sh
OTHERFILES= jconfig.doc ckconfig.c ansi2knr.c ansi2knr.1 jmemdosa.asm
TESTFILES= testorig.jpg testimg.ppm testimg.bmp testimg.jpg testprog.jpg &
		testimgp.jpg
DISTFILES= $(DOCS) $(MKFILES) $(CONFIGFILES) $(SOURCES) $(INCLUDES) &
		$(CONFIGUREFILES) $(OTHERFILES) $(TESTFILES)
# library object files common to compression and decompression
COMOBJECTS= jcomapi.obj jutils.obj jerror.obj jmemmgr.obj $(SYSDEPMEM)
# compression library object files
CLIBOBJECTS= jcapimin.obj jcapistd.obj jctrans.obj jcparam.obj jdatadst.obj &
		jcinit.obj jcmaster.obj jcmarker.obj jcmainct.obj jcprepct.obj &
		jccoefct.obj jccolor.obj jcsample.obj jchuff.obj jcphuff.obj &
		jcdctmgr.obj jfdctfst.obj jfdctflt.obj jfdctint.obj
# decompression library object files
DLIBOBJECTS= jdapimin.obj jdapistd.obj jdtrans.obj jdatasrc.obj &
		jdmaster.obj jdinput.obj jdmarker.obj jdhuff.obj jdphuff.obj &
		jdmainct.obj jdcoefct.obj jdpostct.obj jddctmgr.obj jidctfst.obj &
		jidctflt.obj jidctint.obj jidctred.obj jdsample.obj jdcolor.obj &
		jquant1.obj jquant2.obj jdmerge.obj
# These objectfiles are included in libjpeg.lib
LIBOBJECTS= $(CLIBOBJECTS) $(DLIBOBJECTS) $(COMOBJECTS)
# object files for sample applications (excluding library files)
COBJECTS= cjpeg.obj rdppm.obj rdgif.obj rdtarga.obj rdrle.obj rdbmp.obj &
		rdswitch.obj cdjpeg.obj 
DOBJECTS= djpeg.obj wrppm.obj wrgif.obj wrtarga.obj wrrle.obj wrbmp.obj &
		rdcolmap.obj cdjpeg.obj
TROBJECTS= jpegtran.obj rdswitch.obj cdjpeg.obj transupp.obj


all:  libjpeg.lib


libjpeg.lib: $(LIBOBJECTS)
	- del libjpeg.lib
	* wlib -n libjpeg.lib $(LIBOBJECTS)

cjpeg.exe: $(COBJECTS) libjpeg.lib
	$(CC) $(LDFLAGS) $(COBJECTS) libjpeg.lib 

djpeg.exe: $(DOBJECTS) libjpeg.lib
	$(CC) $(LDFLAGS) $(DOBJECTS) libjpeg.lib

jpegtran.exe: $(TROBJECTS) libjpeg.lib
	$(CC) $(LDFLAGS) $(TROBJECTS) libjpeg.lib

rdjpgcom.exe: rdjpgcom.c
	$(CC) $(CFLAGS) $(LDFLAGS) rdjpgcom.c

wrjpgcom.exe: wrjpgcom.c
	$(CC) $(CFLAGS) $(LDFLAGS) wrjpgcom.c

.c.obj:
	$(CC) $(CFLAGS) -c $<

jconfig.h: jconfig.doc
	echo You must prepare a system-dependent jconfig.h file.
	echo Please read the installation directions in install.doc.
	exit 1

clean: .SYMBOLIC
	- del *.obj
	- del libjpeg.lib
	- del cjpeg.exe
	- del djpeg.exe
	- del jpegtran.exe
	- del rdjpgcom.exe
	- del wrjpgcom.exe
	- del testout*.*

test: cjpeg.exe djpeg.exe jpegtran.exe  .SYMBOLIC
	- del testout*.*
	djpeg -dct int -ppm -outfile testout.ppm  testorig.jpg
	djpeg -dct int -bmp -colors 256 -outfile testout.bmp  testorig.jpg
	cjpeg -dct int -outfile testout.jpg  testimg.ppm
	djpeg -dct int -ppm -outfile testoutp.ppm testprog.jpg
	cjpeg -dct int -progressive -opt -outfile testoutp.jpg testimg.ppm
	jpegtran -outfile testoutt.jpg testprog.jpg
!ifeq SYSTEM DOS
	fc /b testimg.ppm testout.ppm
	fc /b testimg.bmp testout.bmp
	fc /b testimg.jpg testout.jpg
	fc /b testimg.ppm testoutp.ppm
	fc /b testimgp.jpg testoutp.jpg
	fc /b testorig.jpg testoutt.jpg
!else
	echo n > n.tmp
	comp testimg.ppm testout.ppm < n.tmp
	comp testimg.bmp testout.bmp < n.tmp
	comp testimg.jpg testout.jpg < n.tmp
	comp testimg.ppm testoutp.ppm < n.tmp
	comp testimgp.jpg testoutp.jpg < n.tmp
	comp testorig.jpg testoutt.jpg < n.tmp
	del n.tmp
!endif


jcapimin.obj: jcapimin.c 
jcapistd.obj: jcapistd.c 
jccoefct.obj: jccoefct.c 
jccolor.obj: jccolor.c 
jcdctmgr.obj: jcdctmgr.c 
jchuff.obj: jchuff.c  
jcinit.obj: jcinit.c 
jcmainct.obj: jcmainct.c 
jcmarker.obj: jcmarker.c 
jcmaster.obj: jcmaster.c 
jcomapi.obj: jcomapi.c 
jcparam.obj: jcparam.c 
jcphuff.obj: jcphuff.c
jcprepct.obj: jcprepct.c 
jcsample.obj: jcsample.c 
jctrans.obj: jctrans.c 
jdapimin.obj: jdapimin.c 
jdapistd.obj: jdapistd.c 
jdatadst.obj: jdatadst.c 
jdatasrc.obj: jdatasrc.c 
jdcoefct.obj: jdcoefct.c 
jdcolor.obj: jdcolor.c 
jddctmgr.obj: jddctmgr.c 
jdhuff.obj: jdhuff.c  
jdinput.obj: jdinput.c 
jdmainct.obj: jdmainct.c 
jdmarker.obj: jdmarker.c 
jdmaster.obj: jdmaster.c 
jdmerge.obj: jdmerge.c 
jdphuff.obj: jdphuff.c
jdpostct.obj: jdpostct.c 
jdsample.obj: jdsample.c 
jdtrans.obj: jdtrans.c 
jerror.obj: jerror.c 
jfdctflt.obj: jfdctflt.c 
jfdctfst.obj: jfdctfst.c 
jfdctint.obj: jfdctint.c 
jidctflt.obj: jidctflt.c 
jidctfst.obj: jidctfst.c 
jidctint.obj: jidctint.c 
jidctred.obj: jidctred.c 
jquant1.obj: jquant1.c 
jquant2.obj: jquant2.c 
jutils.obj: jutils.c 
jmemmgr.obj: jmemmgr.c 
jmemansi.obj: jmemansi.c 
jmemname.obj: jmemname.c 
jmemnobs.obj: jmemnobs.c 
jmemdos.obj: jmemdos.c 
jmemmac.obj: jmemmac.c 
cjpeg.obj: cjpeg.c 
djpeg.obj: djpeg.c 
jpegtran.obj: jpegtran.c 
rdjpgcom.obj: rdjpgcom.c 
wrjpgcom.obj: wrjpgcom.c 
cdjpeg.obj: cdjpeg.c
rdcolmap.obj: rdcolmap.c 
rdswitch.obj: rdswitch.c 
transupp.obj: transupp.c 
rdppm.obj: rdppm.c 
wrppm.obj: wrppm.c 
rdgif.obj: rdgif.c 
wrgif.obj: wrgif.c 
rdtarga.obj: rdtarga.c 
wrtarga.obj: wrtarga.c 
rdbmp.obj: rdbmp.c 
wrbmp.obj: wrbmp.c 
rdrle.obj: rdrle.c 
wrrle.obj: wrrle.c 
