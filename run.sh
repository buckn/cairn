#!/bin/sh 

# Remove Shaders
rm -f ./shaders.glsl.h

# Remove build directories
rm -rf build
rm -rf web

# Make build directories
mkdir build -p
mkdir web -p

# Args
str="'$*'"

# Make sure the csound header is there, if not download it
if [ ! -f ./csound.h ]; then
	wget --no-parent -r https://github.com/csound/csound/tree/develop/include/ -nH
	mv ./csound/csound/tree/develop/include/
fi

# Make sure that sokol-tools-bin has been initiated, if not initiate it
a=`ls ./sokol-tools-bin`
if [[ -z $a ]]
then
	git submodule update --init
fi

# Update Modules
git submodule update

if [ str == "'--server'" ]
then
	echo server
	#server build and run
	cd build
	gcc ./server.c && ./a
else
	if [ $str == "'--web'" ]
	then
		echo web
		# web client build and run
		source ~/bin/emsdk/emsdk_env.sh
		cd web
		cmake ..
		emcmake cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..
		cmake --build .
	else
		echo desk
		# native client build and run
		cd build
		cmake ..
		cmake --build . && ./game
	fi
fi
