all:
	g++ decode.cc -o decode
	./decode
	g++ encode.cc -o encode -std=c++14
	./encode
