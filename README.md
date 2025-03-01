# GitReal

Git Real is an Immediate mode Git client.


### Build
run `make`


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
