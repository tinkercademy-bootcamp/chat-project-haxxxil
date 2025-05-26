# Exercise 2

**Update this README with your answers to the questions below.**

## Sources of Information for Questions from Before

### Socket 
- https://man7.org/linux/man-pages/man2/socket.2.html - System call reference
  for creating communication endpoints
- Or type `man socket` in terminal
- https://man7.org/linux/man-pages/man7/socket.7.html - Socket interface 
  overview and protocol families
- Or type `man 7 socket` in terminal
- When would you want to use a `SOCK_RAW` stream?
  - I would use `SOCK_RAW` if I have my own protocol I want to use to communicate.

### TCP and IP Protocols
- [IPv4](https://www.rfc-editor.org/info/rfc791) - Internet Protocol 
  specification defining packet structure and routing
- [IPv6](https://www.rfc-editor.org/info/rfc8200) - Next-generation Internet 
  Protocol with expanded address space
- [TCP](https://datatracker.ietf.org/doc/html/rfc9293) - Transmission Control 
  Protocol providing reliable, ordered data delivery
    
### C++
- [C++23 ISO standard draft](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) - 
  Working draft of the C++ language specification
- Is the above the official C++23 spec? 
  - No. This is just a draft of the spec. This is written on the cover page : "Note: this is an early draft. It’s known to be incomplet and incorrekt, and it has lots of bad
formatting.".
- Where is the official C++23 spec?
  - The official C++23 spec is on the [ISO website](https://www.iso.org/standard/83626.html).
- Why was this link chosen instead?
  - Because the official spec needs to be bought and the draft is probably also alright.
- Is this a helpful reference for learning C++?
  - Not for a beginner. It would be better to learn from some tutorials and look up documentation or the specifications when needed.
- Can the various implementations of C++ compilers be different from the
  C++ standard?
  - A proper compiler must aim to conform to the C++ standard. How each compiler is implemented and the extensions available (e.g. `<bits/stdc++.h>` in `g++`) may vary from compiler to compiler.
- What are the most widely used and most significant C++ compilers?
  - The most widely used and significant C++ compilers are:
    - GCC C++ Compiler
    - Clang
    - Microsoft Visual C++
    - Intel C++ Compiler 
- Where is the equivalent spec for C++26?
  - The correct working draft for the C++26 spec is at [https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/n5008.pdf](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/n5008.pdf).
- Where do you find the spec for the HTTP protocol?
  - Specs for different HTTP versions can be accessed from the [HTTP Documentation Website](https://httpwg.org/specs/).
- What about HTTPS? Is there a spec for that protocol?
  - HTTPS is the HTTP protocol over TLS, so there isn't a spec for it. The HTTP communication protocol is the same though the TLS spec may vary.

## Introduction to C++ and Sockets Programming

- Read the code in `src/`
- Are there any bugs in this code?
  - One small bug (or maybe it was intended) that I could find is that both client and server just get stuck when client sends empty string, i.e. on `./client ""`.
- What can you do to identify if there are bugs in the code?
  - We can try to test this program manually on normal and edge cases, write tests to test it, run the code through a debugger and see if anything is off, or maybe have multiple people read through the code to catch any bugs.

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
  - This code is much more modular than exercise-1.
- Is this code better or worse than exercise-1?
  - This code is better than exercise-1 since modularity helps in readability, debugging, organization and testing.
- What are the tradeoffs compared to exercise-1?
  - This code might have more overhead compared to exercise-1 but is much easier to write and debug.
- Are you able to spot any mistakes or inconsistencies in the changes?
  - One slight difference is that in exercise-1 server code, there was only one buffer that kept being reused, but in this exercise each new connection gets its own buffer, which is better.
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
- What do we mean when we say performance?
- How do we measure performance in a program?

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the 
  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more
  readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
- How can you use `git tag` and `git branch` to make programming easier and
  more fun?

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?