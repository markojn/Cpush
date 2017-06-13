# Cpush
C++ based (python-wrapped) particle tracking code

# Compiler commands for CC7 VM

g++ -c -fPIC hello.cpp -o hello.o -I /usr/include/python2.7/
g++ -shared -Wl,-soname,hello_ext.so -o hello_ext.so hello.o -lpython2.7 -lboost_python
