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

    HeapPage::HeapPage(HeapPageId id, byte[] data)(){
        this->pid = id;
        this->td = database.getCatalog().getTupleDesc(id.getTableId());
        this->numSlots = getNumTuples();
        //DataInputStream dis = new DataInputStream(new ByteArrayInputStream(data));
        this->readIndex = 0;

        header = new byte[getHeaderSize()];
        for (int i=0; i<sizeof(header)/sizeof(header[0]); i++){
            header[i] = data[readIndex];
            readIndex++;
        }
        
        tuples = new tuple[numSlots];
        try{
            // allocate and read the actual records of this page
            for (int i=0; i<sizeof(tuples)/sizeof(tuples[0]); i++){
                tuples[i] = readNextTuple(data,i);
            }

        }
        catch(NoSuchElementException e){
            std::cout << "Exception occurred"; 
        }

        setBeforeImage();
    }

    int HeapPage::getNumTuples(){
        double pagesize = (double)database.getBufferPool().getPageSize()*8;
        double tuplesize = (double)(td.getSize()* 8 + 1);
        double res = pagesize / tuplesize;
        return (int)floor(res);  
    }

    int HeapPage::getHeaderSize(){
        double res = (double)numSlots/(double)8;    
        return (int)ceil(res); 
    }

    HeapPage HeapPage::getBeforeImage(){
         try {
            byte[] oldDataRef = null;
            oldDataRef = oldData;
            return new HeapPage(pid,oldDataRef);
        } 

        catch (IOException e) {
            System.exit(1);
        }
        return null;
    }

    void HeapPage::setBeforeImage(){

    }

    HeapPageId HeapPage::getId(){
        return pid;
    }

    tuple HeapPage::readNextTuple(byte[] data, int slotId)(){
         if (!isSlotUsed(slotId)) {
            for (int i=0; i<td.getSize(); i++) {
                try {
                    readIndex++;
                } 
                catch (IOException e) {
                    throw new NoSuchElementException("error reading empty tuple");
                }
            }
            return null;
        }

        // read fields in the tuple
        tuple t = new tuple(td);
        RecordId rid = new RecordId(pid, slotId);
        t.setRecordId(rid);
        try {
            for (int j=0; j<td.numFields(); j++) {
                field f = td.getFieldType(j).parse(dis);
                t.setField(j, f);
            }
        } 
        catch (Exception e) {
            throw new NoSuchElementException("parsing error!");
        }

        return t;
    }


    byte[] HeapPage::getPageData() {}

    
    static byte[] HeapPage::createEmptyPageData() {
        int len = BufferPool.getPageSize();
        return new byte[len]; 
    }

   
    void HeapPage::deleteTuple(tuple t) throws DbException {    
    }

    void HeapPage::insertTuple(tuple t) throws DbException {
    }

    void HeapPage::markDirty(bool dirty, transactionId tid) {
    }

    transactionId HeapPage::isDirty() {
        // some code goes here
        return null;      
    }

    
    int HeapPage::getNumEmptySlots() {
        int count = 0;
        for(int i=0;i<sizeof(tuples)/sizeof(tuples[0]);++i){
            if(!isSlotUsed(i))
                count++;
        }
        return count;
    }

    
    bool HeapPage::isSlotUsed(int i) {
        int x = i / 8;
        int y = i % 8;
            
        return ((header[x] >> y) & 1)==1;
    }

  
    void HeapPage::markSlotUsed(int i, bool value) {
    }

    Iterator<tuple> HeapPage::iterator() {
        std::vector<tuple> arr = new std::vector<tuple>();
        for(tuple t: tuples){
            if (t!=null) arr.push_back(t);
        }
        return arr.iterator();
    }

           
} // emerald
