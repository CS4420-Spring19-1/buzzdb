#include "log_file.h"

namespace buzzdb {
LogFile::LogFile(FILE * f) {
}

void LogFile::PreAppend() {
}

int LogFile::get_total_records() {
}

void LogFile::LogAbort(TransactionId & tid) {
}

void LogFile::LogCommit(TransactionId & tid) {
}

void LogFile::LogWrite(TransactionId & tid, Page & before, Page & after) {
}

void LogFile::WritePageData(RandomAccessFile raf, Page & p) {
}

Page * LogFile::ReadPageData(RandomAccessFile raf) {
}

void LogFile::LogXActionBegin(TransactionId & tid) {
}

void LogFile::LogCheckpoint() {
}

void LogFile::LogTruncate() {
}

void LogFile::Rollback(TransactionId & tid) {
}

void LogFile::Shutdown() {
}

void LogFile::Recover() {
}

void LogFile::Print() {
}

void LogFile::Force() {
}
}
