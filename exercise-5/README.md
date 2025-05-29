# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise
  to another?
  - `diff` is a convenient tool for identifying changes between exercises. Other code comparision tools also exist but the GNU `diff` is installed by default so I use it.
    
## Using Classes

- Here is one way to separate out the code into multiple files
- Is this the best way to do it? 
  - This seems like a nice way to do it but some inconsistencies annoyed me.
    - Why does server code have its own namespace but not client?
    - In fact even the code in `net/` has its own namespace.
    - Code in client uses the `using namespace` declaration however in the server the functions use `namespace ttc = tt::chat`.
  - Making a `chat` namespace doesn't seem useful when the chat is the whole program, but would be useful if it's part of a larger project.
  - For larger projects namespaces would be useful for grouping related code but in this case classes might be more useful, especially since in the case of larger programs we now have the option to have multiple instances of clients and sockets.
- What are the advantages and disadvantages?
  - Namespaces are useful in large projects to organize code and prevent naming conflicts. If someone is reading through the code, namespaces can be helpful in communicating what each object or function is for.
  - Namespaces can be bad because they increase code size, and in many places classes might be more useful. Also, using namespaces too frequently or nesting many namespaces will only make it harder to read and debug code.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
- Which way is better? What are the advantages and disadvantages?
  - While `using namespace tt::chat` is convenient when writing code, it kind of goes over the point of namespaces. Multiple `using` statements might lead to naming conflicts, and it makes it unclear which names come from that namespace.
  - `namespace ttc = tt::chat` leads to a bit more typing but anyone reading the code can easily look up any `ttc` to find out what it means, and this is a better way to shorten code than the `using` declaration.

## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files?
  - We should divide code into different files based on what that code does, and group related files in a directory. Using header files is always nice. Classes can have their own files and directories usually. For example, we have the `Client` and `Server` classes in their own files, and a `utils.cc` separately. This gives a really clean look to the main `tcp_echo_client.cpp` and `tcp_echo_server.cpp`.
- What namespace and directory structure should you use? Why?
  - A namespace and directory structure that can represent the heirarchies and uses of different components in the software would be nice. For example, bundling the client and server into a `net` directory or namespace would be helpful for anyone going through the project, and in this case we would also separate networking related functionality and other functionality (such as `check_error`). If the chat was just a part of a bigger project, then a `chat` namespace or directory would be helpful.

## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure? 
  - I think a particular choice of namespace and directory is good if it makes the code easier to read and navigate through, and gives me a good idea of what each name means when I am reading the code, but there shouldn't be too much nesting since that will make it very tedious to read and code.
- How do you judge what makes a good naming convention or programming style?
  - It would be good if the name makes it clear and unambiguous what it refers to and why its there without being too long. For programming style, readability and consistency are important (only one style throughout the project).

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
  - Yes. Code may smell because of bad coding practices, such as high degree of nesting, huge functions and classes, dead code etc. which might indicate presence of unfound bugs.
- What does it mean to have a sense of taste in programming? How can code
  taste?
  - Sense of taste in programming means having specific preferences about how code should be written and maintained (formatting, naming, code structure etc.) developed through experience. Code can taste because it requires some creativity to write good (or bad) code. Different people have different styles and some can be more generally preferable than others, and this is essentially code taste. 
- Is there an analogue for every sense?
- What other code senses can you think of?
- How many senses do humans have?
- When would you want to see something before you touch it?
- When would you want to touch something before you see it?