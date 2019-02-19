#include "summary.h"

namespace emerald
{
    Summary::Summary(SummaryType type){
        summary_type_ = type;
    }

    Summary::SummaryType Summary::get_type() const {
        return summary_type_;
    }
} // emerald
