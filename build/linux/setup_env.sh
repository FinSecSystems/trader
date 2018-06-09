#!/bin/bash
if [ -n "$CC_VER" ]
then
	echo Setiing up for gcc-$CC_VER
	export CC=gcc-$CC_VER
	export CXX=g++-$CC_VER
fi

