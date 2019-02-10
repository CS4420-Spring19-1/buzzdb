#pragma once

namespace emerald
{
    class Summary {
        public:
            enum SummaryType {
                SUMMARY_INDEX,
                SUMMARY_LIST
            };
        private:
            SummaryType summary_type_;
    };
} // emerald
