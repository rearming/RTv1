#!/bin/zsh

PROJECT_DIR=$(pwd)

SDL_DIR="$PROJECT_DIR"/SDL2_libs

SDL2="$SDL_DIR"/SDL2

if [[ ! -d "$SDL_DIR" ]]; then
	mkdir "$SDL_DIR"
fi

#
# install SDL2 basic library
#

install_SDL2()
{
	echo "installing SDL2 core libs"
	git clone https://github.com/spurious/SDL-mirror.git "$SDL2" || return
	cd "$SDL2"
	if [[ ! -f "Makefile" ]]; then
		./configure --prefix="$SDL2"
		make && make install
	fi
}

if [[ ! -d "$SDL2" ]]; then
	install_SDL2
else
	echo "SDL2 is already installed!"
fi
