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

  To create tables and load data into them, use the following command
    ```./test/emerald -f "../schema/catalog.txt" -d "../data"```
    
  New tables can be added by updating catalog file with the table schema. A corresponding csv file (with the same name as the table) needs to be present in the data directory. 

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
