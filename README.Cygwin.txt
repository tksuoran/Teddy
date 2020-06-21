
---- Notice for Cygwin ----

So far I have not succeeded to build Teddy with Cygwin.
The problems arise from a contradiction in include paths.
SDL uses mingw setup and thus wants to use /usr/include/mingw
instead of /usr/include. If these include paths are mixed,
the result is failed compilation or execution.

I tried to copy library headers from /usr/include to 
/usr/include/mingw, but the resulting test executables
crashed the machine right after opening the window before
drawing anything to it.

Since MingW successfully build Teddy and test executables,
I did not investigate more cygwin. I suggest you use mingw
with msys for Teddy.
