#include "name_basics.hpp"

#include <cassert>

const int NameBasics::kColumnsCount = 6;

NameBasics::NameBasics(const std::vector<std::string>& columns) {
  assert(columns.size() == kColumnsCount);
  columns_ = columns;
}

const std::vector<std::string>& NameBasics::get_columns() const {
  return columns_;
}
