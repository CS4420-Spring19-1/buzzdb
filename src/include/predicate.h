#pragma once

#include <string>

namespace emerald {

/**
 * Class for enabling comparisons for fields
 */
    class Predicate {
        public:
            
            /**
             * Indicates the type of comparison
             */
            enum opType {
                EQ, // equals
                NE, // not equals
                GT, // greater than
                LT, // less than
                GE, // greater than or equal
                LE  // less than or equal
            };

            Predicate();
            
            Predicate(std::string column_name, std::string op, std::string value);

            std::string getColumn();
            
            std::string getValue();
            
            opType getOp();

        private:
            std::string column; // not sure what this is for, probably column store?
            
            opType op;
            
            std::string value; // not sure what this is for
        
    };
} // emerald
