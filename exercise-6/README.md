# Exercise 6

**Update this README with your answers to the questions below.**

## Adding Third Party Libraries or Source Code to Your Project

- There is a new file `src/spdlog-hello-world-main.cc`
- It uses the spdlog and fmt libraries. 
  [More info here](https://github.com/gabime/spdlog) - Fast C++ logging 
  library with various sink types and formatting options
- How do you compile this file using the `g++` CLI?
  - I can install `include/spdlog` from the GitHub repo and use the `-I` flag to include the directory in which `spdlog` is located.
- What do you need to change in your makefile to use this library?
  - With makefile, we can add variables like `INC_DIR` and use flags like `-I` or `-l`
- How many different ways can this library be added into your project?
  - There are multiple different ways:
    - I can clone the library repo and directly include the relevant header.
    - I can clone the repo, compile the library and then include the precompiled library into my executable.
    - I can use a package manager (`e.g. apt`) to install the library onto my system and it will be included then.
- What are the tradeoffs in the different ways?
  - Header-only includes will be easy and portable but will also increase compile times are wouldn't be practical for very large projects.
  - Building the library on my own would give faster compile times, but handling installation and builds of many different libraries and linking them would also be tedious.
  - With package managers, managing libraries becomes easier but many libraries may not support this, and library developers would have to put in the extra effort to make their libraries available on as many package managers as possible.
- Why are there so many different ways to do it?
  - C++ doesn't specify any standards related to adding external libraries, and many projects have different needs and developers have different preferences. As a result, there are many different build systems and package managers, and they may all work differently and be incompatible.
  
## Static Linking vs Dynamic Linking

- What are the differences between static linking and dynamic linking?
  - In static linking, the library binary is embedded in your executable at compile time and references to the library in the code refer to this embedded part. In dynamic linking, the library is loaded at runtime and isn't part of the executable.
- What are the tradeoffs?
  - Static libraries ensures that releases always have the correct versions of libraries and users don't have to download it themselves. However, static libraries result in longer compile times and larger executables, and if many different executables use the same library then a lot of memory/disk space would be wasted.
  - Many executables can share a single copy of a dynamic library. Additionally, they can be updated without affecting the executables that rely on it. However, users may have to install some dependencies themselves and also dynamic linking may be slower than static linking.
- How do you enable static linking or dynamic linking in your makefile?
  - We can include library name in the compilation command whenever we need it for static libraries (or use `-l`).
  For dynamic libraries we need `-fPIC` flag, along with `-l`, `-L` or `-rpath` to tell where the library is located to compile (we can create necessary variables, flags and dependencies for each library) and also update `LD_LIBRARY_PATH` to run.

## Git Clone and Building from Source

- Where is `g++` looking for the include files and library files?
  - `g++` looks for header files in some of the `include` directories in `/usr`, in my case I find this:
  ```
  #include <...> search starts here:
  /usr/include/c++/14
  /usr/include/aarch64-linux-gnu/c++/14
  /usr/include/c++/14/backward
  /usr/lib/gcc/aarch64-linux-gnu/14/include
  /usr/local/include
  /usr/include/aarch64-linux-gnu
  /usr/include
  End of search list.
  ``` 
  - It also looks for them in the directory of the source file and we can also tell `g++` the include directory with `-I`.
  - For libraries, the linker searches in some of the `/usr/lib` directories, in my case:
  ```
  SEARCH_DIR("=/usr/local/lib/aarch64-linux-gnu"); SEARCH_DIR("=/lib/aarch64-linux-gnu"); SEARCH_DIR("=/usr/lib/aarch64-linux-gnu"); SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib"); SEARCH_DIR("=/usr/aarch64-linux-gnu/lib");
  ```
  - We can also use the `-L` to specify a directory to search in for libraries.
- How do you find out?

## C++ Package Managers

- Why are there so many C++ package managers?
- Which one is the best one?
- Which are the most notable ways to manage the compilation of C++ projects?