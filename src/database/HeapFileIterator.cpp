#include "database.h"
#include "table.h"
#include "field.h"
#include "integer_field.h"
#include "string_field.h"
#include "double_field.h"
#include "date_field.h"
#include "row_store.h"
#include "tuple.h"
#include "utility.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "summary_list.h"
#include "column_store.h"

namespace emerald {
    HeapFileIterator::HeapFileIterator(TransactionId tid, HeapFile f){
        this->interator  = NULL;
        this->pageIndex = 0;
        this->tid = tid;
        this->file = file;
    }

    void HeapFileIterator::open(){
        pageIndex = 0;
        PageId pageId = new HeapPageId(file.getId(), pageIndex);
        Page page = database.getBufferPool().getPage(tid,pageId,Permissions.READ_ONLY);
        HeapPage heapPage = (HeapPage)page;
        iterator = heapPage.iterator();
    }

    bool HeapFileIterator::hasNext(){
        if (iterator==NULL) return false;
        if (iterator.hasNext()) return true;
        else{
            if(pageIndex>=file.numPages()-1){
                return false;
            }
            else{
                PageId pageId = new HeapPageId(file.getId(), pageIndex+1);
                Page page = Database.getBufferPool().getPage(tid,pageId,Permissions.READ_ONLY);
                HeapPage heapPage = (HeapPage)page;
                return heapPage.iterator().hasNext();
            }
        }

    }

    tuple HeapFileIterator::next(){
        if(iterator==null)  throw new NoSuchElementException();
        
        if (iterator.hasNext())  return iterator.next();
        else{
            PageId pageId = new HeapPageId(file.getId(), pageIndex+1);
            Page page = database.getBufferPool().getPage(tid,pageId,Permissions.READ_ONLY);
            HeapPage heapPage = (HeapPage)page;
            
            if (page!=null)
                if (heapPage.iterator().hasNext()){
                    pageIndex++;
                    iterator = heapPage.iterator();
                    return iterator.next();
                }
            throw new NoSuchElementException();
        }

    }

    void HeapFileIterator::restart(){
        close();
        open();
    }

    void HeapFileIterator::close(){
        iterator = null;
        pageIndex = 0;
    }
} // emerald
