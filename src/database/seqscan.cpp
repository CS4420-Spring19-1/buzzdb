#include "seqscan.h"

SeqScan::SeqScan(TransactionId* tid, int table_id, std::string table_alias){
  this->tid = tid;
  this->table_id = table_id;
  this->table_alias = table_alias;
}

std::string SeqScan::get_table_name{
  // return Database.getCatalog().getTableName(tableid);
}

std::string SeqScan::get_alias{
  return table_alias;
}

void SeqScan::reset(int table_id, ){

}