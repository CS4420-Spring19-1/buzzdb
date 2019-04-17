#include <stdio.h>
#include "utility.h"

namespace emerald {


static std::vector<Type*> Utility::GetTypes(int len) {
  std::vector<Type*> types = new std::vector<Type*>(len);
  for (int i = 0; i < len; i++) {
    types[i] = Type::FieldType::INTEGER;
  }
  return types;
}

static std::vector<std::string> Utility::GetStrings(int len, std:::string val) {
  std::vector<std::string> strings = new std::vector<std::string>(len);
  for (int i = 0; i < len; i++) {
    strings[i] = val + std::to_string(i);
  }
  return strings;
}

static TupleDesc* Utility::GetTupleDesc(int n, std::string name) {
  return new TupleDesc(GetTypes(n), GetString(n, name));
}


static TupleDesc* Utility::GetTupleDesc(int n) {
  return new TupleDesc(GetTypes(n));
}

static Tuple* Utility::GetHeapTuple(int n) {
  Tuple* tup = new Tuple(GetTupleDesc(1));
  tup->set_record_id(new RecordId(new HeapPageId(1, 2), 3));
  tup->set_field(0, new IntegerField(n));
  return tup;
}

static Tuple* Utility::GetHeapTuple(std::vector<int> tupdata) {
  Tuple* tup = new Tuple(GetTupleDesc(tupdata.size()));
  tup->set_record_id(new RecordId(new HeapPageId(1, 2), 3));
  for (int i = 0; i < tupdata.size(); i++) {
    tup->set_field(i, new IntegerField(tupdata[i]));
  }
  return tup;
}

static Tuple* Utility::GetTuple(std::vector<int> tupledata, int width) {
  if (tupledata.size() != width) {
    std::cout << "Get Hash Tuple has the wrong length!" << std::endl;
    return nullptr;
  }

  Tuple* tup = new Tuple(GetTupleDesc(width));
  for (int i = 0; i < width; i++) {
    tup->set_field(i, new IntegerField(tupledata[i]));
  }
  return tup;
}
}
