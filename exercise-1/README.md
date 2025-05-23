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
- How do you find out which part of the below code comes from which header?
- How do you change the code so that you are sending messages to servers
  other than localhost?
- How do you change the code to send to a IPv6 address instead of IPv4?
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- What is the difference between a pointer and a reference?
- When is it better to use a pointer?
- When is it better to use a reference?
- What is the difference between `std::string` and a C-style string?
- What type is a C-style string?
- What happens when you iterate a pointer?
- What are the most important safety tips to know when using pointers?

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- What is the difference between LLM and AI?
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?