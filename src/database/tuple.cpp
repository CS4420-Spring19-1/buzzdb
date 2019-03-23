#include "tuple.h"
#include <iostream>

namespace emerald {
    Tuple::Tuple() {
    }
    
    Tuple::Tuple(std::vector<Field*> fields) {
        fields_ = fields;
        // does the tuple description need to be handled here?
    }; // redundant semicolon?

    // Copy constructor for Tuple class
    Tuple::Tuple(const Tuple& tuple) {
        fields_ = tuple.get_fields();
    }; // redundant semicolon?

    void Tuple::print() const {
        for (auto &field : fields_) {
            field->print();
        }
        std::cout << std::endl;
    }; // redundant semicolon?

    Field* Tuple::getField(int index) const {
        return fields_[index];
    }; // redundant semicolon?

    std::vector<Field*> Tuple::get_fields() const {
        return fields_;
    }; // redundant semicolon?

    void Tuple::append_fields(std::vector<Field*> fields) {
        fields_.insert(fields_.end(), fields.begin(), fields.end());
    }; // redundant semicolon?

    void Tuple::add_field(Field* field) {
        fields_.push_back(field);
    }
} // emerald
