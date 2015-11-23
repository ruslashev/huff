all:
	g++ decode.cc -o decode -std=c++14
	./decode
	# g++ encode.cc -o encode -std=c++14
	# ./encode

decoder:
	g++ decode.cc -o decode -std=c++14
	./decode

encoder:
	g++ encode.cc -o encode -std=c++14
	./encode

