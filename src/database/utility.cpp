#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "utility.h"
#include "field.h"

namespace buzzdb {
void Utility::GetTypes(int len, std::vector<Field::Type> &types) {
  int idx = 0;
  while (idx < len) {
    types.push_back(Field::Type::INTEGER);
    idx++;
  }
}

void Utility::GetStrings(int len, std::string val, std::vector<std::string> &strings) {
  int idx = 0;
  while (idx < len) {
    strings.push_back(val + std::to_string(idx));
    idx++;
  }
}

TupleDesc* Utility::GetTupleDesc(int n, std::string name) {
  std::vector<Field::Type> types;
  std::vector<std::string> strings;
  GetTypes(n, types);
  GetStrings(n, name, strings);
  return new TupleDesc(types, strings);
}


TupleDesc* Utility::GetTupleDesc(int n) {
  std::vector<Field::Type> types;
  GetTypes(n, types);
  return new TupleDesc(types);
}

Tuple* Utility::GetHeapTuple(int n) {
  Tuple* tup = new Tuple(*GetTupleDesc(1));
  tup->set_record_id(new RecordId(new HeapPageId(1, 2), 3));
  tup->set_field(0, new IntegerField(n));
  return tup;
}

Tuple* Utility::GetHeapTuple(std::vector<int> tupdata) {
  Tuple* tup = new Tuple(*GetTupleDesc(tupdata.size()));
  HeapPageId* heap_page_id = new HeapPageId(1, 2);
  tup->set_record_id(new RecordId(*heap_page_id, 3));
  for (int i = 0; i < tupdata.size(); i++) {
    tup->set_field(i, new IntegerField(tupdata[i]));
  }
  return tup;
}

Tuple* Utility::GetTuple(std::vector<int> tupledata, int width) {
  if (tupledata.size() != width) {
    std::cout << "Get Hash Tuple has the wrong length!" << std::endl;
    return nullptr;
  }

  Tuple* tup = new Tuple(*GetTupleDesc(width));
  for (int i = 0; i < width; i++) {
    tup->set_field(i, new IntegerField(tupledata[i]));
  }
  return tup;
}

HeapFile* Utility::OpenHeapFile(int cols, std::ifstream file) {
  // create the HeapFile and add it to the catalog
  TupleDesc* td = GetTupleDesc(cols);
  HeapFile* hf = new HeapFile(file, *td);
  // Database.getCatalog().addTable(hf, UUID.randomUUID().toString());
  return hf;
}

HeapFile* Utility::OpenHeapFile(int cols, std::string colPrefix, std::ifstream file) {
  // create the HeapFile and add it to the catalog
  TupleDesc* td = GetTupleDesc(cols, colPrefix);
  HeapFile* hf = new HeapFile(file, *td);
  // Database.getCatalog().addTable(hf, UUID.randomUUID().toString());
  return hf;
}


HeapFile* Utility::createEmptyHeapFile(std::string path, int cols) {
  std::ifstream file(path, std::ifstream::in);
  // touch the file
  std::ofstream fos(file);
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

std::string Utility::ListToString (std::vector<int> list) {
  std::string out = "";
  for (int i: list) {
    if (out.size() > 0) out += "\t";
    out += i;
  }
  return out;
}
}