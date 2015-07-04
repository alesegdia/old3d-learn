#!/usr/bin/env bash

function compile {
	EXENAME=$1
	echo $EXENAME
	g++ -o bin/${EXENAME} src/test/${EXENAME}.cpp -lallegro -lallegro_primitives -std=c++11
}

compile test_single_line
compile test_line_list
