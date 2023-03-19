#pragma once

#include <dataset.hpp>

class TitleCrew : public Dataset {
 public:
  using Dataset::Dataset;

  enum class Column {
    kTconst = 0,
    kDirectors,
    kWriters
  };
};
