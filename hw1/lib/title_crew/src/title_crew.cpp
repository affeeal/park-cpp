#include "title_crew.hpp"

TitleCrew::TitleCrew(const std::vector<std::string>& columns)
  : columns_(columns) {}

const std::vector<std::string>& TitleCrew::get_columns() const {
  return columns_;
}
