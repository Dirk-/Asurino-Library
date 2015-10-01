This is a C++ library for Arduino for controlling the ASURO robot.
Tested with Arduino IDE v1.6.5.

--------------------------------------------------------------------------------
INSTALLATION
--------------------------------------------------------------------------------

To install this library

- Download the ZIP file and extract everything
- Rename the folder "Asurino-Library-master" to "asuro"
- Move the "asuro" folder to "C:\Program Files\Arduino\libraries" (Windows) or
  your "˜/Documents/Arduino/libraries" folder (OS X) 

When installed, the library should look like this (OS X example):

˜/Documents/Arduino/libraries/asuro              (this library's folder)
˜/Documents/Arduino/libraries/asuro/Asuro.cpp    (the library implementation file)
˜/Documents/Arduino/libraries/asuro/Asuro.h      (the library description file)
˜/Documents/Arduino/libraries/asuro/keywords.txt (the syntax coloring file)
˜/Documents/Arduino/libraries/asuro/examples     (the examples in the "open" menu)
˜/Documents/Arduino/libraries/asuro/readme.txt   (this file)

Now you have to tell the Arduino IDE about the ASURO robot board specifications:

- Close the Arduino IDE
- Windows: Open "C:\Program Files\Arduino\hardware\arduino\avr\boards.txt" with
  WordPad, for example
- Mac OS X: Right-click on the Arduino programm in your Programs folder, select
  "Show Content", then open ".../Contents/Java/hardware/arduino/avr/boards.txt"
- Add the following lines to the end of "boards.txt":

##############################################################
 asuro8.name=Asuro w/ ATmega8
 asuro8.upload.protocol=stk500
 asuro8.upload.maximum_size=7168
 asuro8.upload.speed=2400
 asuro8.bootloader.low_fuses=0xdf
 asuro8.bootloader.high_fuses=0xca
 asuro8.bootloader.path=atmega8asuro
 asuro8.bootloader.file=ATmegaBOOT_8_asuro.hex
 asuro8.bootloader.unlock_bits=0x3F
 asuro8.bootloader.lock_bits=0x0F
 asuro8.build.mcu=atmega8
 asuro8.build.f_cpu=8000000L
 asuro8.build.core=arduino
 asuro8.build.variant=standard
   
##############################################################
 asuro168.name=Asuro w/ ATmega168
 asuro168.upload.protocol=stk500
 asuro168.upload.maximum_size=14336
 asuro168.upload.speed=9600
 asuro168.bootloader.low_fuses=0xff
 asuro168.bootloader.high_fuses=0xdd
 asuro168.bootloader.extended_fuses=0x00
 asuro168.bootloader.path=atmega168asuro
 asuro168.bootloader.file=ATmegaBOOT_168_asuro.hex
 asuro168.bootloader.unlock_bits=0x3F
 asuro168.bootloader.lock_bits=0x0F
 asuro168.build.mcu=atmega168
 asuro168.build.f_cpu=8000000L
 asuro168.build.core=arduino
  
The first board entry represents the original ASURO, the second entry the
modified one.


--------------------------------------------------------------------------------
BUILDING
--------------------------------------------------------------------------------

After the library is installed, you just have to start the Arduino application.

- Select "Tools" - "Boards" - "Asuro w/ ATmega8" from the Arduino menu

To use this library in a sketch, go to the Sketch | Import Library menu and
select Asuro.  This will add a corresponding line to the top of your sketch:

#include <Asuro.h>

To stop using this library, delete that line from your sketch.

Geeky information:
After a successful build of this library, a new file named "Asuro.o" will appear
in "Arduino-xxxx/hardware/libraries/Asuro". This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. "Asuro.cpp" or "Asuro.h"),
then you must first 'unbuild' this library by deleting the "Asuro.o" file. The
new "Asuro.o" with your code will appear after the next press of "verify"

--------------------------------------------------------------------------------
Credits
--------------------------------------------------------------------------------
This library is based on a sketch for the ASURO by Jakob Remin.
Version 0.3 of this library was developed by m_a_r_v_i_n and sternthaler

--------------------------------------------------------------------------------
License: GNU General Public License version 2.0 (GPLv2)
--------------------------------------------------------------------------------


