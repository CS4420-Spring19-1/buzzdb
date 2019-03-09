Emerald
-------

a) Installing dependencies

```
sudo apt install cmake
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
sudo apt install libgoogle-glog-dev
```

b) Build instructions:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

c) Run Emerald

```
./test/emerald
```

  To create tables and load data into them, use the following command
    ```./test/emerald -f "../data/schema/catalog.txt" -d "../data/database"```
    
  New tables can be added by updating catalog file with the table schema. A corresponding csv file (with the same name as the table) needs to be present in the data directory. 

d) Debugging (Optional)

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
