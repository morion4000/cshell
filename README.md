# CShell

C implementation of an UNIX shell.

The following commands are implemented:

* `?` - Display the help.
* `dummy` - Dummy function.
* `printenv` - Print enviroment variables.
* `exit` - Exit the shell.
* `pwd` - Print working directory.
* `ls` - List information about the FILE.
* `cp` - Copies SOURCE to DESTINATION.
* `dir` - List information about the FILE.
* `yes` - Repeatedly output a line with all specified STRING, or 'y'.
* `cd` - Change the current directory.
* `mkdir` - Create a DIRECTORY, if it does not already exist.
* `rmdir` - Remove the DIRECTORY, if it is empty.
* `rm` - Remove (unlink) the FILE.
* `chmod` - Change the mode of each FILE to MODE.
* `exec` - Execute external commands.

## Compile guide

#### Get the source

`git clone git@github.com:morion4000/cshell.git`

#### Install readline library (Debian / Ubuntu)

`sudo apt-get install libreadline5-dev`

#### Run make

`cd src`

and then

`make`

#### Add permissions 

`chmod +x shell`

#### Run the shell

`./shell`

## Copyright

Copyright (c) 2010 morion4000. See LICENSE for details.
