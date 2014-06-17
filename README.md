simple-ls
=========

A simple C program listing all files (including symbolic links) contained within a directory.
Similar functionality to the linux ls program (except written in >200 lines).

Instructions
------------
Run make. Simple and easy.

Usage
----
./simple-ls <option> <directory>

Options can contain -u (last access time), -c (creation time), or -l (last modified time).

Example:

```
colin@colin-laptop-linux:~/Documents/github/simple-ls$ ./simple-ls -u .
rw-rw-r-- colin   colin  234 Jun   17:14:44	 README.md 
rwxr-xr-x colin   colin  4096 Jun   17:14:46	 . 
rw-rw-r-- colin   colin  234 Jun   17:14:45	 Makefile 
rwxrwxr-x colin   colin  4096 Jun   17:14:40	 .. 
rw-rw-r-- colin   colin  0 Jun   17:14:41	 simple-ls.c~ 
rwxrwxr-x colin   colin  4096 Jun   17:14:40	 .git 
rwxrwxr-x colin   colin  17181 Jun   17:14:46	 simple-ls 
rw-rw-r-- colin   colin  2725 Jun   17:14:46	 simple-ls.c ```