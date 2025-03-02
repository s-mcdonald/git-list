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



#### CLI Commands
    git-list <OPTIONS>


##### Build
cd into the git-list dir and run `make`

This will build both the binary and the debian package `src/git-list/package/git-list.deb` file.
You can then install as per usual.
