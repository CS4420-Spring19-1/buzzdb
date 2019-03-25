#include "column.h"

namespace emerald {
    Column::Column() {
    }

    size_t Column::size() const {
        return fields_.size();
    }

    void Column::insert(Field* field) {
        fields_.push_back(field);
    }

    Field* Column::get_field(int index) const {
        return fields_[index];
    }

    std::vector<Field*> Column::get_fields() const {
        return fields_;
    }
} // emerald
