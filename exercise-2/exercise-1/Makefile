all: build/server build/client build

build:
	mkdir build

build/server: src/tcp_echo_server.cc build
	g++ src/tcp_echo_server.cc -o build/server

build/client: src/tcp_echo_client.cc build
	g++ src/tcp_echo_client.cc -o build/client

clean:
	rm -rf build
