# One solution for reading a value of a TLS variable from a core file generated on a target machine

-Building the tool (Multiarch version):
	
	mkdir build
	cd build
	~/$GDB_SRC/configure --enable-thread-access --enable-build-with-cxx=no --with-python --enable-targets=all
	make

-Installing the tool:

	mkdir INSTALL
	make install DESTDIR= ~/$path_to_build/INSTALL

-Using the tool:
(NOTE: The version of the glibc on the host machine should match the glibc version
of the target process being debugged. In the following example we built glibc 2.22,
because the program being debugged from target machine (with MIPS arch) was
built with glibc 2.22.. We are trying to print, by using Multiarch GNU GDB,
the value of the TLS variable (declared as __thread int foo = 0xdeadbeef;) from
a core file generated on a target machine.)


./gdb
...
(gdb) add-auto-load-safe-path ~/path_to_the_glibc22_build/INSTALL/lib
(gdb) set libthread-db-search-path ~/path_to_the_glibc22_build/INSTALL/lib
(gdb) set solib-search-path ~/path_to_libs_from_target_machine/
(gdb) file exampleFromMipsPlatform
Reading symbols from exampleFromMipsPlatform...done.
(gdb) core-file core.mips
...
[Thread debugging using libthread_db enabled]
Using host libthread_db library "~/path_to_the_glibc22_build/INSTALL/liblibthread_db.so.1".
Core was generated by `./exampleFromMipsPlatform'.
Program terminated with signal SIGABRT, Aborted.
#0  0x00000000 in ?? ()
[Current thread is 1 (Thread 0x771bf000 (LWP 21808))]


-before patching:
(gdb) p/x foo
Cannot find user-level thread for LWP 21808: generic error


-after pathing:
(gdb) p/x foo
$1 = 0xdeadbeef
