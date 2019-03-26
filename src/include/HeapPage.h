#pragma once

#include "table_descriptor.h"
#include "tuple.h"
#include <unordered_map>

namespace emerald {
    class HeapPage {
        public:
           

            HeapPage();

            HeapPage(HeapPageId id, byte[] data)();

            virtual ~HeapPage();

            int getNumTuples(); 

            int getHeaderSize();

            HeapPage getBeforeImage();

            void setBeforeImage();

            HeapPageId getId();

            tuple readNextTuple(DataInputStream dis, int slotId)();

            byte[] getPageData();

            static byte[] createEmptyPageData();

            void deleteTuple(tuple t);    

    		void insertTuple(tuple t);

            void markDirty(bool dirty, transactionId tid);

            transactionId isDirty();

            int getNumEmptySlots();

            bool isSlotUsed(int i);

    		void markSlotUsed(int i, bool value);

    		Iterator<tuple> iterator();



        private:
        	HeapPageId pid;
    		tuple_descriptor td;
    		byte header[];
    		tuple tuples[];
    	    int numSlots;
            byte oldData[];
    	    byte oldDataLock=new byte(0);
    	    int readIndex;

        };
};