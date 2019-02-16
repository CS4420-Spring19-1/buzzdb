#include "scan.h"
#include "utility.h"
#include "row_store.h"

namespace emerald
{
    Table* seqScanRowStore(RowStore* table, int columnIndex, Predicate::opType op, Field* value){
        
        std::vector<Tuple*> tuples = table->getTuples();
        RowStore* result = new RowStore(table->get_table_id());
        //new table will have the same descriptor as the input table
        result->copyTableDesc(table->getTableDescriptor());
        for(size_t i = 0; i < tuples.size(); i++)
        {
            if(tuples[i]->getField(columnIndex)->filter(op, value)){
                result->insertTuple(tuples[i]);
            }
        }
        return result;
    };
    Table* seqScan(Table* table, Predicate* predicate){
        TableDescriptor* tableDesc = table->getTableDescriptor();
        int columnIndex = tableDesc->getColumnId(predicate->getColumn());
        field_type type = tableDesc->getColumnType(columnIndex);
        Field* value = constructField(predicate->getValue(), type); 
        if(table->getStorageType() == Table::ROW_STORE){
            return seqScanRowStore(static_cast<RowStore*>(table), columnIndex, predicate->getOp(), value);
        }
        return nullptr;
    };
} // emerald
