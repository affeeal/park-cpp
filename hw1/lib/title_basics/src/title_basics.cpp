#include "title_basics.hpp"

#include <cassert>

const int TitleBasics::kColumnsCount = 9;

TitleBasics::TitleBasics(const std::vector<std::string>& columns) {
  assert(columns.size() == kColumnsCount);
  columns_ = columns;
}

const std::vector<std::string>& TitleBasics::get_columns() const {
  return columns_;
}
