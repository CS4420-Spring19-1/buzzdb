#pragma once
#include <vector>
#include <string>

#include "integer_field.h"
#include "record_id.h"
#include "tuple.h"
#include "tuple_desc.h"
#include "heap_page_id.h"

namespace emerald {
class Utility {
public:
  /*
   * @return: Type array of length len populated with Type::INTEGER
   */
  static std::vector<Type*> GetTypes(int len);
  /**
   * @return a String array of length len populated with the (possibly null) strings in val,
   * and an appended increasing integer at the end (val1, val2, etc.).
   */
  static std::vector<std::string> GetStrings(int len, std::string val);
  
  /**
   * @return a TupleDesc with n fields of type Type.INT_TYPE, each named
   * name + n (name1, name2, etc.).
   */
  static TupleDesc* GetTupleDesc(int n, std::string name);
  
  /**
   * @return a TupleDesc with n fields of type Type.INT_TYPE
   */
  static TupleDesc* GetTupleDesc(int n);

  /**
   * @return a Tuple with a single IntField with value n and with
   *   RecordId(HeapPageId(1,2), 3)
   */
  static Tuple* GetHeapTuple(int n);

  /**
   * @return a Tuple with an IntField for every element of tupdata
   *   and RecordId(HeapPageId(1, 2), 3)
   */
  static Tuple* GetHeapTuple(std::vector<int> tupdata);

  /**
   * @return a Tuple with a 'width' IntFields with the value tupledata[i]
   *         in each field.
   *         do not set it's RecordId, hence do not distinguish which
   *         sort of file it belongs to.
   */
  static Tuple* GetTuple(std::vector<int> tupledata, int width);

  /**
   * A utility method to create a new HeapFile with a single empty page,
   * assuming the path does not already exist. If the path exists, the file
   * will be overwritten. The new table will be added to the Catalog with
   * the specified number of columns as IntFields.
   */
  static HeapFile* createEmptyHeapFile(std::string path, int cols);

  /** Opens a HeapFile and adds it to the catalog.
   *
   * @param cols number of columns in the table.
   * @param f location of the file storing the table.
   * @return the opened table.
   */
  static HeapFile* OpenHeapFile(int cols, )
private:

}
}
