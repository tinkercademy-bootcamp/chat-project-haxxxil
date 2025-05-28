all: build/server.s build/client.s build

build:
	mkdir build

build/server.s: src/tcp_echo_server.cc build
	g++ -S src/tcp_echo_server.cc -o build/server.s

build/client.s: src/tcp_echo_client.cc build
	g++ -S src/tcp_echo_client.cc -o build/client.s

clean:
	rm -rf build
