#include <stdio.h>
#include <vector>
#include <fstream>
#include "utility.h"

namespace buzzdb {
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

static HeapFile* Utility::OpenHeapFile(int cols, std::ifstream file) {
  // create the HeapFile and add it to the catalog
  TupleDesc* td = GetTupleDesc(cols);
  HeapFile* hf = new HeapFile(file, td);
  // Database.getCatalog().addTable(hf, UUID.randomUUID().toString());
  return hf;
}

static HeapFile* Utility::OpenHeapFile(int cols, std::string colPrefix, std::ifstream file) {
  // create the HeapFile and add it to the catalog
  TupleDesc* td = GetTupleDesc(cols, colPrefix);
  HeapFile* hf = new HeapFile(file, td);
  // Database.getCatalog().addTable(hf, UUID.randomUUID().toString());
  return hf;
}


static HeapFile* Utility::createEmptyHeapFile(std::string path, int cols) {
  std::ifstream file(path, std::ifsteam::in);
  // touch the file
  std::ostream fos(file);
  fos << std::vector<unsigned char>(0);
  fos.close();

  HeapFile* hf = OpenHeapFile(cols, file);
  HeapPageId* pid = new HeapPageId(hf->get_id(), 0);

  HeapPage* page = nullptr;
  try {
    // page = new HeapPage(pid, HeapPage.createEmptyPageData());
  } catch {
    // this should never happen for an empty page; bail;
    // throw new RuntimeException("failed to create empty page in HeapFile");
  }

  hf->WritePage(page);
  return hf;
}

static std::string Utility::ListToString (std::vector<int> list) {
  std::string out = "";
  for (int i: list) {
    if (out.size() > 0) out += "\t";
    out += i;
  }
  return out;
}
}