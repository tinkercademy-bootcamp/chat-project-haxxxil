# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
- How would you compile from the command line?
  - For each output file (server, and client), I will call `g++` with the corresponding source file and `utils.cc` together.  
- How would you compile using make?
  - With Makefile, I can add a new variable `UTILS_SRC` for this and any other files that both client and server may share and add this variable in the compilation commands.
- How would you compile using VS Code?
  - In VS Code we can either use an extension or configure `tasks.json` to compile such programs.

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  - Compiling involves turning the code in a single file into object files, however functions and objects defined in other files or in libraries aren't defined in these object files. Once all required object files are available, the linker "links" function calls and references between different files and combines the code into a single executable file.
- What is the difference between creating an executable and creating a 
  library?
  - An executable is code that is meant to be executed by itself, whereas a library is just some (often precompiled) useful functionality that can be used by other programs and included in other executables so that we don't need to rewrite code. A library object file may not run by itself but linkers can use its machine code to compile executables.
- How do you compile a library, and then use that library to compile an
  executable?
  - We can create a library using the `-c` compiler option (or `-shared` for shared libraries) and then archive the object files to a static library. When we want an executable we can use linker flags like `-I`, `-L` and `-l` to specify the location of the precompiled libraries.

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
- Is there a difference in compilation time between the two?
- How can you assess performance other than compilation speed?