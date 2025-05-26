# Exercise 1

**Update this README with your answers to the questions below.**

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
  - Google, or AI probably. Man pages for documentation (or other similar documentation) regarding function calls.
- How can you tell if the source of your information is good?
  - Man pages are the best but long to read. AI probably isn't always reliable (maybe Perplexity and check sources). Stack overflow is mostly reliable. Probably anything that multiple sources agree upon is good.
- How would you define "good" in this situation?
  - Sources and information that I can rely on without worrying their validity (man pages are the best) would be "good". 

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
- What are the most important command line arguments to learn for `g++`?
  - The most important `g++` arguments are `-c`(don't link), `-o`(output file), `-g`(debug mode), `-O`(optimizations), `-Wall`(all warnings), `-I`(include directories), `-l`, and `--std=c++<version>`. 
- What is the difference between debug vs release versions?
  - Debug versions also compile code that is useful for debugging and may be slow and inefficient. Release version is the final optimized code that is used in the final product.
- What are the tradeoffs between debug and release versions?
  - It would be harder to debug on a release version since it doesn't give the amount of information a debug version would, but this also makes debug versions slower and maybe less usable.
- What arguments would you use in a debug build?
  - `-g` is useful for a debug build, along with maybe some macros (with `-D`) that might give extra debug information.
- What about for release?
  - `-O` would be useful for release versions since it applies compiler optimizations. For release versions as well we may define macros that might compile code specifically for release version.
- What other kinds of build types are useful?
  - Other useful build types are profiling (for performance) and test (checking correctness).

## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
  - Search on Google or YouTube, or read GNU make documentation.
- How can you tell if the resource you are using is correct?
  - I can test and confirm with `make --help` or `man make` or just verify if multiple sources have the same information if something doesn't work as expected.
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
    - It rebuilds the executables if they don't exist or if the pre-requisites (the source files) have been modified after the last time the executables were modified.
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
  - Some important command line arguments to learn for make are:
    - `-f` to specify a makefile other than `Makefile`
    - `-C <dir>` to run execute the makefile from the directory `<dir>`
    - `-n` to dry-run, i.e. to just show what commands would be run without actually running them.
    - `VAR=value` override variable value in the makefile.
- What are the most important directives to learn about in Makefile?
  - The most important directives to learn about in makefile are:
    - `target: prerequisites`
    - Variables in makefiles.
    - Pattern rules
    - Conditionals
- What are the most important commands to implement in your Makefile?
  - The most important commands are:
    - `all`
    - `clean`
    - `test`
    - `install` and `uninstall`
- Which ones are essential, which ones are nice to haves?
  - `all` and `clean` are essential, and depending on the type of program the others are nice to have.

## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
  - This is useful so that we can track the changes and undo or track mistakes easily.
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
  - A lot of very small commits so that if we something goes wrong we can quickly track what may be causing the issue.
- What are the most important commands to know in git?
  - `add`, `commit`, `push`, `branch`, `checkout`, `fetch`, `merge`, `pull`, `reset`, `revert`, `rebase`, etc.

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
  - `arpa/inet.h` is a useful utility for manipulation of IP addresses and conversions between different formats.
  - `netinet/in.h` is useful for defining structures that help store IP and port addresses
  - `sys/socket.h` is useful for creating sockets and related system calls such as `send`, `connect`, `read` and `listen`.
- How do you find out which part of the below code comes from which header?
  - I can look up information about the headers or also look up information about the functions or types to find out which header they are from.
- How do you change the code so that you are sending messages to servers
  other than localhost?
  - We can change the `kServerAddress` to the target server IP address to send it to servers other than localhost.
- How do you change the code to send to a IPv6 address instead of IPv4?
  - Most network related functions and structs in the code are for IPv4. These need to be changed to support IPv6. To send data from `tcp_echo_client.cc`:
    - `kServerAddress` needs to be changed.
    - `AF_INET` should be changed to `AF_INET6`.
    - `sockaddr_in` should be changed to `sockaddr_in6` and consequently `sin_family` would become `sin6_family` and `sin_port` would become `sin6_port`.
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
  - We can use the `getaddrinfo` function to get a list of addresses for a given hostname and try creating a connection to them, and this would be compatible with both IPv4 and IPv6.
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
  - The `inet_pton` function tries converting the IPv4 address in `kServerAddress` from human-readable form to binary form so that it can be used to connect. If it is successful, it returns 1 and stores the binary form in `&address.sin_addr`, otherwise a value <=0 is returned. 
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
  - The `connect` function tries to initiate a connection to the server given by `address` on our socket `my_sock`. A negative value is returned if the function fails to establish a connection.
- What is the difference between a pointer and a reference?
  - A pointer is a variable that stores an address to an object whereas a reference is just an alias for the object. Pointers can be `NULL` or they can be reassigned to point to another object but a reference always refers to a single object.
- When is it better to use a pointer?
  - It is better to use pointers in cases where it may be useful to change where the pointer points or have null pointers (e.g. linked lists).
- When is it better to use a reference?
  - It is better to use a reference when there is no need to change the object which we need to point to, for example when passing an object without copying as a function parameter.
- What is the difference between `std::string` and a C-style string?
  - `std::string` is a class that is kind of like a wrapper around C-style strings with additional functionality, such as automated memory management. The `c_str()` method can be used to get the underlying C-style string from a `std::string`.
- What type is a C-style string?
  - A C-style string is a null-terminated (`\0`) array of `char`.
- What happens when you iterate a pointer?
  - Depending on the type of the pointer, the new value is the old value plus the size of the type of object the pointer refers to.
- What are the most important safety tips to know when using pointers?
  - Always initialize pointers(either to `NULL` or to the address of some existing object).
  - Make sure the pointer type matches the object it references, and that the pointer isn't out of bounds.
  - Always check whether pointer is `NULL` before dereferencing it.
  - Always `free()` dynamic memory after use and set pointer to `NULL`.

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?
  - For single file programs, I just go to terminal and use the compiler. Otherwise I will use a Makefile. 

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
  - The POSIX standard defining `socket()` at [https://pubs.opengroup.org/onlinepubs/9799919799/](https://pubs.opengroup.org/onlinepubs/9799919799/) is the most authoritative source of information about it. 
- What is the most authoritative source of information about the TCP and IP
  protocols?
  - The most authoritative sources of information about the TCP and IP protocols are the standards documents maintained by the IETF.
    - [TCP](https://datatracker.ietf.org/doc/html/rfc9293)
    - [IPv4](https://datatracker.ietf.org/doc/html/rfc791)
    - [IPv6](https://datatracker.ietf.org/doc/html/rfc8200)
- What is the most authoritative source of information about the C++
  programming language?
  - The most authoritative source of information about the C++ programming language would be the latest ISO C++ standard. Along with this, the compiler documentation would be useful for compiler specific knowledge.
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
  - Markdown formatting is useful to organize information given to an LLM and it helps in making the LLM better understand the prompt.
- What is the difference between LLM and AI?
  - LLMs are models that focus on processing and generating human languages, whereas AI is a broad term encompassing machines that can have human-like intelligence. LLMs are essentially a subset of AI.
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?
  - It is correct to say "an LLM" since the we say "ell-ell-emm" which starts with a vowel sound.
  