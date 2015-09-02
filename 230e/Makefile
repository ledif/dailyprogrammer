build:
	clang++ -std=c++11 -O3 -I$(BOOST_ROOT)/include/ -I../lib/cpp/json/src -o 230e 230e.cc

challenge1.txt:
	wget https://gist.githubusercontent.com/anonymous/8f35cc4fbbccf6d3f59f/raw/1f9786fc2fec9a7afa20cdd70d2d8afb7d3aecb9/challenge1.txt

challenge2.txt:
	wget https://gist.githubusercontent.com/anonymous/b7733192c0d1004a084b/raw/b5f8df53469410c634034c12d99bbb8ccc46f102/challenge2.txt

inputs: challenge1.txt challenge2.txt

run: inputs build
	./dp230 < challenge2.txt
