#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "utility.h"
#include "field.h"
#include "heap_page.h"

namespace buzzdb {
Utility::Utility() {}

std::vector<Field::Type> Utility::GetTypes(int len) {
  std::vector<Field::Type> types;
  int idx = 0;
  while (idx < len) {
    types.push_back(Field::Type::INTEGER);
    idx++;
  }
  return types;
}

std::vector<std::string> Utility::GetStrings(int len, std::string val) {
  std::vector<std::string> strings;
  int idx = 0;
  while (idx < len) {
    strings.push_back(val + std::to_string(idx++));
  }
  return strings;
}

TupleDesc Utility::GetTupleDesc(int n, std::string name) { 
  return TupleDesc(GetTypes(n), GetStrings(n, name));
}


TupleDesc Utility::GetTupleDesc(int n) {
  return TupleDesc(GetTypes(n));
}

Tuple Utility::GetHeapTuple(int n) {
  Tuple tup = Tuple(GetTupleDesc(1));
  HeapPageId heap_page_id(1, 2);
  RecordId* rid = new RecordId(heap_page_id, 3);
  tup.set_record_id(rid);

  Field* field = new IntegerField(n);
  tup.set_field(0, field);

  return tup;
}

Tuple Utility::GetHeapTuple(std::vector<int> tupdata) {
  Tuple tup = Tuple(GetTupleDesc(tupdata.size()));
  HeapPageId heap_page_id(1, 2);
  RecordId* rid = new RecordId(heap_page_id, 3);
  tup.set_record_id(rid);
  Field* field = nullptr;
  
  for (int i = 0; i < tupdata.size(); i++) {
    field = new IntegerField(tupdata[i]);
    tup.set_field(i, field);
  }

  return tup;
}

Tuple Utility::GetTuple(std::vector<int> tupledata, int width) {
  if (tupledata.size() != width) {
    throw std::invalid_argument("Get Hash Tuple has the wrong length!");
  }

  Tuple tup = Tuple(GetTupleDesc(width));
  
  Field* field = nullptr;
  for (int i = 0; i < width; i++) {
    field = new IntegerField(tupledata[i]);
    tup.set_field(i, field);
  }

  return tup;
}

HeapFile* Utility::OpenHeapFile(int cols, std::ifstream file) {
  // create the HeapFile and add it to the catalog
  // HeapFile* hf = new HeapFile(file, *GetTupleDesc(cols));
  // Database.getCatalog().addTable(hf, UUID.randomUUID().toString());
  // return hf;
}

HeapFile* Utility::OpenHeapFile(int cols, std::string colPrefix, std::ifstream file) {
  // create the HeapFile and add it to the catalog
  // HeapFile* hf = new HeapFile(file, *GetTupleDesc(cols));
  // Database.getCatalog().addTable(hf, UUID.randomUUID().toString());
  // return hf;
}


HeapFile* Utility::createEmptyHeapFile(std::string path, int cols) {
  // touch the file
  // std::ofstream fos(path, std::ofstream::out);
  // fos << "";
  // fos.close();
  // HeapFile* hf = OpenHeapFile(cols, fos);
  // HeapPageId* pid = new HeapPageId(hf->get_id(), 0);

  // HeapPage* page = nullptr;
  // // try {s
  // //   // page = new HeapPage(pid, HeapPage.createEmptyPageData());
  // // } catch {
  // //   // this should never happen for an empty page; bail;
  // //   // throw new RuntimeException("failed to create empty page in HeapFile");
  // // }

  // hf->WritePage(page);
  // return hf;
  return nullptr;
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
