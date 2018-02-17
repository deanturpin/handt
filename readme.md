The code is designed to run periodically on a web server. Therefore, between
runs, state must be saved. Positions are stored in a temporary text file
```buys.txt```. Reads and writes are facilitated by operator<< and operator>>
overloads.

The first incarnation of this project was centered around the graphical
elements. But once it started generating trades automatically I found myself
refreshing the plain text buy and sell files. You often don't know whether a
feature is useful until you use it.

Splitting the design into trading and graphics much easier to reason about and
aligns with the MCV design pattern.

# C++
The C++ can be built with any C++11 compliant compiler (gcc, clang). The code
confirms to LLVM's coding standard by virtue of periodic passes of
```clang-format``` over the source.

# Web server
```cron``` is used to schedule builds on a Linux web server. The project is
periodically pulled from GitHub, compiled from clean and if successful copied
into the web root. The main site is generated from the master branch, there's
also a beta site which is generated from the current dev branch.
