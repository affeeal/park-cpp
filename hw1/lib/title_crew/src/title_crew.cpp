#include "title_crew.hpp"

#include <cassert>

const size_t TitleCrew::kColumnsCount = 3;

TitleCrew::TitleCrew(const std::vector<std::string>& columns) {
  assert(columns.size() == kColumnsCount);
  columns_ = columns;
}

const std::vector<std::string>& TitleCrew::get_columns() const {
  return columns_;
}
