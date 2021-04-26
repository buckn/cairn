#!/bin/sh 

# Remove Shaders
rm ./shaders.glsl.h

# Remove build directories
rm -rf build
rm -rf web

# Make build directories
mkdir build -p
mkdir web -p

# Args
str="'$*'"

if [ str == "'--server'" ]
then
	echo server
	#server build and run
	cd build
	cmake ..
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
