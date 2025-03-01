# git-list - A Custom Git Extension

The `git-list` is a custom Git extension, developed in C/C++, that provides additional information about the local branches.

Its main feature is to display branches showing the tracked remote in a simple effecient interface.
It also displays the current state of the branch including if there is a current WIP commit.


## Why C++ and not Shell scripts
I originally wrote this in a shell script but because of the multiple git calls, it ran slowly. So moving to libgit2, I was able to perform multiple actions much faster than using scripts.

I will hopefully be porting most of my productivity commands to cpp over time as part of my GitReal project.

Example output

```
 upstream
   develop 
   master

 origin
   feature/git-sync

 local
   bug/fix-optimizer 
```


Example output with the -w option
```
 upstream
   develop 
   master

 origin
   feature/git-sync [w]

 local
   bug/fix-optimizer 
```


Example when there are no remotes tracked
```
 local
   develop 
   master
   feature/git-sync [w]
   bug/fix-optimizer 
```



## Project status
Currently git-list and GitReal is in early development as its a side project for me to learn cpp.
Im restructuring the build param and realigning the code into the GitReal project so during 
the refactor the code is not currently building.


### Build System
Build using  `make`
I will eventually include CMake to make this more portable for VS.


### Libs / Deps
Require libgit2 + ImGui 


### Lib Src
Included in the src is a parser for reading ini files which was sourced from  `https://github.com/benhoyt/inih`



## Build Debian Package

## Build
Build command

```
 dpkg-deb --build ./git-list/
```
## Dev install

```sh
sudo dpkg -i git-list.deb
```

## To uninstall

```sh
sudo dpkg -r git-list
```
