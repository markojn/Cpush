# Cpush
C++ based (python-wrapped) particle tracking code

# Compiler commands for CC7 VM

g++ -c -fPIC track.cpp -o track.o -I /usr/include/python2.7/

g++ -shared -Wl,-soname,tracklib.so -o tracklib.so track.o -lpython2.7 -lboost_python
