#include "tuple_desc.h"

namespace emerald {
TupleDesc::TupleDesc TupleDesc::combine(TupleDesc td1, TupleDesc td2) {
}

TupleDesc::TupleDesc() {
}

TupleDesc::TupleDesc(Type type_array[]) {
}

TupleDesc::TupleDesc(Type type_array[], std::string field_array[]) {
}

TupleDesc::TupleDesc(const TupleDesc & other) {
}

int TupleDesc::get_number_fields() const {
}

std::string TupleDesc::get_field_name(int index) const {
}

int TupleDesc::get_index(std::string name) const {
}

Type TupleDesc::get_type(int index) const {
}

int TupleDesc::get_size() const {
}

bool TupleDesc::operator==(TupleDesc other) {
}
}
