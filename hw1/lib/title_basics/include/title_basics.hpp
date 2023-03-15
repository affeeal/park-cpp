#pragma once

#include <string>
#include <vector>

class TitleBasics {
 public:
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

   TitleBasics(const std::vector<std::string>& columns);

   const std::vector<std::string>& get_columns() const;
 private:
   std::vector<std::string> columns_;
};
