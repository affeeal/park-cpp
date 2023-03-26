#pragma once

#include "dataset.hpp"

class NameBasics : public Dataset {
 public:
  using Dataset::Dataset;
   
  enum class Column {
    kNconst = 0,
    kPrimaryName,
    kBirthYear,
    kDeathYear,
    kPrimaryProfession,
    kKnownFowTitles,
  };
};
