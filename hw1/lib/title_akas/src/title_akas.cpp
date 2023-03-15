#include "title_akas.hpp"

TitleAkas::TitleAkas(const std::vector<std::string>& columns)
  : columns_(columns) {}

const std::vector<std::string>& TitleAkas::get_columns() const {
  return columns_;
}
