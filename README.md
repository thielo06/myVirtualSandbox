### About
This repository is about a project wich was thought of as a windows application that has an user interface and is able to execute several computational methods. The purpose of this project is less to create a high perfomance application than more to learn the programming language it is written in and to understand the computational methods that are used.

It´s written in C++.

I´ve been told that it´s a bad idea to try to learn such a complicated language not following a well-structered textbook but I´ll try it anyways. Thanks for the advice.

### Preconditions
Set up Visual Studio Configuration Properties
- C/C++ > General > Common Language RunTime Support > Common Language RunTime Support
- Linker > System > Subsystem > Windows
- Linker > Additional Dependencies > Edit... > Add "dwmapi.lib"

### Code Design
The includes must follow a specific order
- System, POSIX, Windows, ...
- STL
- External third-party libraries
- Custom 
