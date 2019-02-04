#include "predicate.h"

namespace emerald
{
    Predicate::opType toOpType(std::string op){
        if(op.compare("=")==0){
            return Predicate::opType::EQ;
        } else if(op.compare("!=")==0){
            return Predicate::opType::NE;
        } else if(op.compare(">")==0){
            return Predicate::opType::GT;
        } else if(op.compare("<")==0){
            return Predicate::opType::LT;
        } else if(op.compare(">=")==0){
            return Predicate::opType::GE;
        } else {
            return Predicate::opType::LE;
        }
    }
    Predicate::Predicate(std::string column_name, std::string op, std::string value){
        this->column = column_name;
        this->op = toOpType(op);
        this->value = value;
    }
    std::string Predicate::getColumn(){
        return this->column;
    }
    std::string Predicate::getValue(){
        return this->value;
    }
    Predicate::opType Predicate::getOp(){
        return this->op;
    }
} // emerald
