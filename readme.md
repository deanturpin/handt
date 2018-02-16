The code is designed to run periodically on a web server. Therefore, between
runs, state must be saved. Positions are stored in a text file buys.txt. Reads
and writes are facilitated by operator<< and operator>> overloads.

The first incarnation of this project was centered around the graphical
elements. But once it started generating trades automatically I found myself
refreshing the plain text buy and sell files. You often don't know whether a
feature is useful until you use it.
