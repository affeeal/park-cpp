#include "title_akas.hpp"

#include <cassert>

const int TitleAkas::kColumnsCount = 8;

TitleAkas::TitleAkas(const std::vector<std::string>& columns) {
  assert(columns.size() == kColumnsCount);
  columns_ = columns;
}

const std::vector<std::string>& TitleAkas::get_columns() const {
  return columns_;
}
