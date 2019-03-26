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
    HeapPageId::HeapPageId(int table_id, int pageNo){
        this->table_id = table_id;
        this->pageNo = pageNo;
    }

          
    int HeapPageId::getTableId(){
        return table_id;
    }

    int HeapPageId::getPageNo(){
        return pageNo;
    }

    int HeapPageId::getHashCode(){
        return table_id*pageNo;
    }

    bool HeapPageId::equals(HeapPageId heapPageid){
        if (table_id==heapPageid.table_id && pageNo==heapPageid.pageNo){
            return true;
        }
        else return false;
    }

    std::vector<int> HeapPageId::serialize(){
        int data[] = new int[2];
        data[0] = getTableId();
        data[1] = getPageNo();

        return data;
    }  
} 
