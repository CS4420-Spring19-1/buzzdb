#pragma once

#include <cstdio>
#include <unordered_map>
#include "page.h"
#include "transaction_id.h"

namespace emerald {
class LogFile {
 public:
  LogFile(FILE * f);

  void PreAppend();

  int get_total_records();

  void LogAbort(TransactionId & tid);

  void LogCommit(TransactionId & tid);

  void LogWrite(TransactionId & tid, Page & before, Page & after);

  void WritePageData(RandomAccessFile raf, Page & p);

  Page * ReadPageData(RandomAccessFile raf);

  void LogXActionBegin(TransactionId & tid);

  void LogCheckpoint();

  void LogTruncate();

  void Rollback(TransactionId & tid);

  void Shutdown();

  void Recover();

  void Print();

  void Force();

 private:
  FILE * log_file;
  RandomAccessFile * raf;
  bool is_recovery_undecided;

  static const int ABORT_RECORD = 1;
  static const int COMMIT_RECORD = 2;
  static const int UPDATE_RECORD = 3;
  static const int BEGIN_RECORD = 4;
  static const int CHECKPOINT_RECORD = 5;
  static const int NO_CHECKPOINT_ID = -1;
  
  // might not be const, check original Java implementation
  static const int INT_SIZE = 4;
  static const int LONG_SIZE = 8;

  long current_offset;
  int page_size;
  int total_records;

  std::unordered_map<long, long> * tid_to_first_log_record;
};
}
