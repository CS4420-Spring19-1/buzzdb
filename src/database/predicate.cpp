#include "predicate.h"

namespace emerald {
    /** 
     * 1. Why use compare for strings?
     * 2. Should this function's signature be declared in predicate.h?
     * 3. Is it opstring being a valid op a prerequisite?
     */
    Predicate::opType toOpType(std::string op) {
        if (op.compare("=") == 0) {
            return Predicate::opType::EQ;
        } else if (op.compare("!=") == 0) {
            return Predicate::opType::NE;
        } else if (op.compare(">") == 0) {
            return Predicate::opType::GT;
        } else if (op.compare("<") == 0) {
            return Predicate::opType::LT;
        } else if (op.compare(">=") == 0) {
            return Predicate::opType::GE;
        } else {
            return Predicate::opType::LE;
        }
    };
    
    Predicate::Predicate(std::string column_name, std::string op, std::string value) {
        this->column = column_name; // interface could be wrong here: no pointers in interface
        this->op = toOpType(op);
        this->value = value;
    };

    std::string Predicate::getColumn() {
        return this->column;
    };

    std::string Predicate::getValue() {
        return this->value;
    };

    Predicate::opType Predicate::getOp() {
        return this->op;
    };

} // emerald
