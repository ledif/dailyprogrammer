build:
	clang++ -std=c++1y -O3 -I../lib/cpp/Streams/source -o 232e 232e.cc

range:
	clang++ -std=c++1y -O3 -I../lib/cpp/range-v3/include -o 232e-range range.cc

gen:
	clang++ -std=c++1y -O0 -g -I../lib/cpp/Streams/source -o gen gen.cc


run: build
	./232e
