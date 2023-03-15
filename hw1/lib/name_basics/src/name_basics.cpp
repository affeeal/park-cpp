#include "name_basics.hpp"

NameBasics::NameBasics(const std::vector<std::string>& columns)
  : columns_ (columns) {}

const std::vector<std::string>& NameBasics::get_columns() const {
  return columns_;
}
