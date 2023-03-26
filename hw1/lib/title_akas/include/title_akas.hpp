#pragma once

#include "dataset.hpp"

class TitleAkas : public Dataset {
 public:
  using Dataset::Dataset;

  enum class Column {
    kTitleId = 0,
    kOrdering,
    kTitle,
    kRegion,
    kLanguage,
    kTypes,
    kAttributes,
    kIsOriginalTitle
  };
};
