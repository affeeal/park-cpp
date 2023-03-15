#include "title_basics.hpp"

TitleBasics::TitleBasics(const std::vector<std::string>& columns)
  : columns_(columns) {}

const std::vector<std::string>& TitleBasics::get_columns() const {
  return columns_;
}
