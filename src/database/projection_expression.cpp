#include "projection_expression.h"

namespace emerald
{
    ProjectionExpression::ProjectionExpression(){
        
    }

    ProjectionExpression::ProjectionExpression(std::string operation, std::string column){
        column_ = column;

        if (operation.compare("SUM")) {
            op_type_ = SUM;
        } else if(operation.compare("AVG")){
            op_type_ = AVG;
        } else if(operation.compare("MAX")){
            op_type_ = MAX;
        } else if(operation.compare("MIN")){
            op_type_ = MIN;
        } else if(operation.compare("COUNT")){
            op_type_ = COUNT;
        } else {
            op_type_ = NONE;
        }
        
    }

    std::string ProjectionExpression::get_column() const {
        return column_;
    }
} // emerald
