build:
	clang++ -std=c++11 -O3 -I$(BOOST_ROOT)/include/ -I../lib/cpp/json/src -o 230e 230e.cc

run: inputs build
	./230e < inputs/challenge2.txt
