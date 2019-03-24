#pragma once

#include <cstddef>

namespace emerald {
    class Summary {
        public:
            enum SummaryType {
                SUMMARY_INDEX,
                SUMMARY_LIST
            };

            Summary(SummaryType type);

            SummaryType get_type() const;

            virtual size_t size() const = 0;

        private:
            SummaryType summary_type_;
    };
} // emerald
