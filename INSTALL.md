# Install

In order to install the library without hiccups you need to have at least vesion 8.0.0 and 2.30 of clang and binutils respectively. You can clone the repo by typing the command below in your terminal.

$ git clone https://github.com/r0bin-dood/crcx.git

Entering the directory you can type these commands to install the library:

$ make all
$ sudo make install

Without sudo the header file "crcx.h" will not be copied to "/usr/include", in which case you can use the library by importing the header file with double quotes instead of angle brackets. 

That's it!