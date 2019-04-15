#include <gtest/gtest.h>
#include "heap_page_id.h"

#include <vector>

namespace emerald {
class HeapPageReadTest {
public:
  HeapPageReadTest() {
    int EXAMPLE_VALUES[20][2] = {
      { 31933, 862 },
      { 29402, 56883 },
      { 1468, 5825 },
      { 17876, 52278 },
      { 6350, 36090 },
      { 34784, 43771 },
      { 28617, 56874 },
      { 19209, 23253 },
      { 56462, 24979 },
      { 51440, 56685 },
      { 3596, 62307 },
      { 45569, 2719 },
      { 22064, 43575 },
      { 42812, 44947 },
      { 22189, 19724 },
      { 33549, 36554 },
      { 9086, 53184 },
      { 42878, 33394 },
      { 62778, 21122 },
      { 17197, 16388 }
    }

    std::vector<std::vector<int>> table = new std::vector<std::vector<int>>();
    for (auto &tuple: EXAMPLE_VALUES) {
      std::vector<int> listTuple = new std::vector<int>();
      for (auto &value: tuple) {
        listTuple.push_back(value);
      }
      table.push_back(listTuple);
    }

    // Convert it to a HeapFile and read in the bytes
    // try {
    //     File temp = File.createTempFile("table", ".dat");
    //     temp.deleteOnExit();
    //     HeapFileEncoder.convert(table, temp, BufferPool.getPageSize(), 2);
    //     EXAMPLE_DATA = TestUtil.readFileBytes(temp.getAbsolutePath());
    // } catch (IOException e) {
    //     throw new RuntimeException(e);
    // }

    
  }

  ~HeapPageReadTest() {

  }

private:
  HeapPageId* pid;
}
}