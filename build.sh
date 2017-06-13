#!/bin/bash
g++ -c -fPIC push.cpp -o push.o -I /usr/include/python2.7/
g++ -shared -Wl,-soname,push.so -o push.so push.o -lpython2.7 -lboost_python
