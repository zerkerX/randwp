Randwp is a simple tool for selecting a random JPEG wallpaper 
from a folder and writing it in BMP format to a destination path. 
It is an extended DOS executable, and can be used in DOS or 
anything compatible. Usage is quite simple:

    Usage: randwp searchpath outname
    
Where:

searchpath
:   The path to search for JPEG images

outname
:   The output path and filename to write the .BMP image

To integrate in a DOS or Win 9x system, the easiest option is to simply
add this tool to the **autoexec.bat** file. As such, it will pick a new
wallpaper each time the machine is started. For example, the line in 
my Retro PC's autoexec.bat is:

    C:\APPS\RANDWP.EXE D:\FILES\PICTURES C:\WINDOWS\RANDOM.BMP

As implied above, this tool is rather limited and only works with JPEG
source files and BMP output files. Internally, it is based on
[version 6b of libjpeg](https://ijg.org/files/jpegsr6b.zip) by 
the [Independent JPEG Group](https://ijg.org/). 
The application is built with [OpenWatcom](http://openwatcom.org/).
