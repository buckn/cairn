#!/bin/sh 

# Remove Shaders
rm -f ./shaders.glsl.h

# Remove build dir
rm -rf build

# --Make build dirs--
mkdir build
# Dir for native builds
mkdir build/native
# Dir for web builds
mkdir build/web
# Dir for debugging, logging, output, etc.
mkdir build/debug
# Dir for server builds
mkdir build/server

# Args
str="'$*'"

# Make sure that sokol-tools-bin has been initiated, if not initiate it
a=`ls ./sokol-tools-bin`
if [ -z $a ]
then
	git submodule update --init
fi

# Update Modules
git submodule foreach --recursive git reset --hard

if [ $str == "'--server'" ]
then
	echo server
	#server build and run
	cd build/server
	gcc ../../server.c -o ./server && ./server
else
	if [ $str == "'--web'" ]
	then
		echo web
		# web client build and run
		source ~/bin/emsdk/emsdk_env.sh
		cd build/web
		cmake ../..
		emcmake cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ../..
		cmake --build .
	else
		if [ $str == "'--build'" ]
		then
			echo desk
			# native client build and run
			cd build/native
			cmake ../..
			cmake --build .
		else
			echo desk
			# native client build and run
			cd build/native
			cmake ../..
			cmake --build . && ./game
		fi
	fi
fi
