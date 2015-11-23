all:
	g++ decode.cc -o decode -std=c++14
	./decode
	# g++ encode.cc -o encode -std=c++14
	# ./encode

decode:
	g++ decode.cc -o decode -std=c++14
	./decode

encode:
	g++ encode.cc -o encode -std=c++14
	./encode

