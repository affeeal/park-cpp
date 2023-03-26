#pragma once

#include "dataset.hpp"

class TitleBasics : public Dataset {
 public:
  using Dataset::Dataset;
  
  enum class Column {
    kTconst = 0,
    kTitleType,
    kPrimaryTitle,
    kOriginalTitle,
    kIsAdult,
    kStartYear,
    kEndYear,
    kRuntimeMinutes,
    kGenres,
  };
};
