#pragma once

#include <string>

namespace emerald
{
    class Predicate {
        public:
            enum opType {
                EQ,
                NE,
                GT,
                LT,
                GE,
                LE
            };
            Predicate();
            Predicate(std::string column_name, std::string op, std::string value);
            std::string getColumn();
            std::string getValue();
            opType getOp();
        private:
            std::string column;
            opType op;
            std::string value;
        
    };
} // emerald
