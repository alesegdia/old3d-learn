#!/usr/bin/env bash

function compile {
	EXENAME=$1
	echo $EXENAME
	g++ -o bin/${EXENAME} src/test/${EXENAME}.cpp -lallegro -lallegro_primitives -std=c++11
}

compile test_single_line
compile test_line_list

g++ -o bin/apptest_line_list src/app/allegroapp.cpp  src/test/allapp_test_line_list_app.cpp -lallegro -lallegro_primitives -std=c++11
g++ -o bin/apptest_sector_render src/app/allegroapp.cpp  src/test/allapp_test_sector_render_app.cpp -lallegro -lallegro_primitives -std=c++11
