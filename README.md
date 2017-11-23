## Asurino-Library

This is a C++ library for Arduino for controlling the [ASURO](http://www.arexx.nl/arexx.php?cmd=goto&cparam=p_asuro) robot.
Tested with Arduino IDE v1.6.13 and 1.8 on macOS and Windows.

## Setup

1. Download the ZIP file and extract everything.
2. Rename the folder `Asurino-Library-master` or `Asurino-Library-0.6.1` (depending on 
the way you downloaded it from GitHub) to `asuro`.
3. Move the `asuro` folder to `C:\Users\<username>\Documents\Arduino\libraries` (Windows) 
  or your `˜/Documents/Arduino/libraries` folder (macOS).
4. Move the contents of `move to hardware` to `C:\Users\<username>\Documents\Arduino\hardware` 
  (Windows) or your `˜/Documents/Arduino/hardware` folder (macOS). If the "hardware"
  folder does not exist, create it.
5. Delete the empty `move to hardware` folder.

When installed, the library should look like this (macOS example):

```
˜/Documents/Arduino/libraries/asuro                  (this library's folder)
˜/Documents/Arduino/libraries/asuro/src/Asuro.cpp    (the library implementation file)
˜/Documents/Arduino/libraries/asuro/src/Asuro.h      (the library description file)
˜/Documents/Arduino/libraries/asuro/keywords.txt     (the syntax coloring file)
˜/Documents/Arduino/libraries/asuro/examples         (the examples in the "open" menu)
˜/Documents/Arduino/libraries/asuro/readme.txt       (this file)
˜/Documents/Arduino/hardware/asuro/avr/boards.txt    (ASURO board definition)
˜/Documents/Arduino/hardware/asuro/avr/platform.txt  (ASURO platform compile options)
```

Done.

Instead of adding the two hardware definition files to your installation, you can also 
edit the original boards.txt file (not recommended, as it will get overwritten when
installing new versions of the Arduino IDE):

- Close the Arduino IDE
- Windows: Open `C:\Program Files\Arduino\hardware\arduino\avr\boards.txt` with
  WordPad, for example
- macOS: Right-click on the Arduino programm in your Programs folder, select
  `Show Content`, then open `.../Contents/Java/hardware/arduino/avr/boards.txt`
- Add the following lines to the end of `boards.txt`:

```
 asuro8.name=Asuro w/ ATmega8
 
 asuro8.upload.protocol=stk500
 asuro8.upload.maximum_size=7168
 asuro8.upload.speed=2400
 asuro8.upload.tool=arduino:avrdude
 
 asuro8.bootloader.low_fuses=0xdf
 asuro8.bootloader.high_fuses=0xca
 asuro8.bootloader.path=atmega8asuro
 asuro8.bootloader.unlock_bits=0x3F
 asuro8.bootloader.lock_bits=0x0F
 # asuro8.bootloader.file=ATmegaBOOT_8_asuro.hex
 
 asuro8.build.mcu=atmega8
 asuro8.build.f_cpu=8000000L
 asuro8.build.board=AVR_ASURO8
 asuro8.build.core=arduino:arduino
 asuro8.build.variant=arduino:standard
``` 
 
## Building an ASURO sketch

After the library is installed, you just have to start the Arduino application.

- Select `Tools` - `Boards` - `Asuro w/ ATmega8` from the Arduino menu

To use this library in a sketch, go to the Sketch | Import Library menu and
select Asuro.  This will add a corresponding line to the top of your sketch:

`#include <Asuro.h>`

To stop using this library, delete that line from your sketch.

Uploading the compiled sketch to ASURO directly from the Arduino iDE is not
supported. You have to select `Export compiled binary file` and `Show sketch folder` 
from the `Sketch` menu. Upload this file with [ASURO Flash Tool](http://www.arexx.com/downloads/asuro/ASURO_flash_v155.zip) (Windows)
or [ASURO McFlash](https://itunes.apple.com/app/asuro-mcflash/id982784471?mt=12) (macOS). 
You'll find ASURO McFlash in the Mac App store.

Geeky information:
After a successful build of this library, a new file named `Asuro.o` will appear
in `Arduino-xxxx/hardware/libraries/Asuro`. This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. `Asuro.cpp` or `Asuro.h`),
then you must first 'unbuild' this library by deleting the `Asuro.o` file. The
new `Asuro.o` with your code will appear after the next press of `verify`.
 
## Credits
 
This library is based on a sketch for the ASURO by Jakob Remin.
Version 0.3 of this library was developed by m_a_r_v_i_n and sternthaler.
 

