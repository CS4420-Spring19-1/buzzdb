#pragma once

#include <string>

namespace emerald{
    class ProjectionExpression
    {
        public:
            enum OP_TYPE {
                SUM,
                AVG,
                MAX,
                MIN,
                COUNT,
                NONE
            };
            ProjectionExpression();
            std::string get_column() const;
            ProjectionExpression(std::string operation, std::string column);
        private:
            OP_TYPE op_type_;
            std::string column_;
    };
    
}