
---- Notice for VisualC ----

VisualC is one of the native environments for Teddy.
Things you should know:

* VisualC version 6 is supported.

* You need SDL and SDL_image libraries. 

* All code, for example libraries and executables
  that are used with Teddy must use the same runtime
  library settings. For debug this means DLL multithreaded
  debug, and for release this means DLL multithreaded.
  You should also make sure that the structure alignment
  is set to 4 bytes, as SDL requires this.

* To be able to use libraries you need to add their
  include and lib paths to VisualC from Tools, Options,
  Directories.

* To make things easy some versions of the source package
  include a directory called Win32libs that contains all
  required DLL, lib, exp and include files.

* Once you manage to build a program you will need the
  DLL files in your path to be able to run the programs.
  Simplest and safest way is to copy the contents of the
  Win32libs/dll -directory to VisualC/Debug/TestEvents/
  -directory, or whatever is the build directory for the
  executable.
