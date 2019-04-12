#include "predicate.h"

namespace emerald {
Predicate::Predicate(int field, OpType op_type, Field * operand) {
  this->field = field;
  this->op_type = op_type;
  this->operand = operand;
}

bool Predicate::Filter(Tuple & t) {
  return t.get_field(field)->Compare(op_type, operand);
}

/* Parsing methods: not implemented
Predicate::OpType Predicate::GetOp(std::string s) {
}

Predicate::OpType Predicate::GetOp(int i) {
}
*/
}
