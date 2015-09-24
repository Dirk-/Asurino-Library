This is a C++ library for Arduino for controlling the Asuro robot
Tested on Arduino 0010 Alpha.

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino-xxxx/hardware/libraries folder.

When installed, this library should look like:

Arduino-xxxx/hardware/libraries/Asuro              (this library's folder)
Arduino-xxxx/hardware/libraries/Asuro/Asuro.cpp    (the library implementation file)
Arduino-xxxx/hardware/libraries/Asuro/Asuro.h      (the library description file)
Arduino-xxxx/hardware/libraries/Asuro/keywords.txt (the syntax coloring file)
Arduino-xxxx/hardware/libraries/Asuro/examples     (the examples in the "open" menu)
Arduino-xxxx/hardware/libraries/Asuro/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you just have to start the Arduino application.

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

Credits
--------------------------------------------------------------------------------
This library is based on the sketch for the asuro from Jakob Remin.


