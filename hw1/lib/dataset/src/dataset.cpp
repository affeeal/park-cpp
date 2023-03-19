#include "dataset.hpp"

Dataset::Dataset(const std::vector<std::string>& columns)
  : columns_ (columns) {}

const std::vector<std::string>& Dataset::get_columns() const {
  return columns_;
}
