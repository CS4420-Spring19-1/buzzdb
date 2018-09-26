Emerald
-------


a) Build instructions:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

b) Run Emerald

```
./test/emerald
```

c) Debugging (Optional)

```
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
gdb ./test/emerald
```

References
----------

a) GDB

https://www.cs.cmu.edu/~gilpin/tutorial/

b) Valgrind

http://cs.ecs.baylor.edu/~donahoo/tools/valgrind/

c) Perf

https://baptiste-wicht.com/posts/2011/07/profile-applications-linux-perf-tools.html