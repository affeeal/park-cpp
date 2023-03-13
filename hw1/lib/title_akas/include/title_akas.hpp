#pragma once

#include <string>
#include <vector>

class TitleAkas {
 public:
   static const int kColumnsCount;
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

   TitleAkas(const std::vector<std::string>& columns);

   const std::vector<std::string>& get_columns() const;
 private:
   std::vector<std::string> columns_;
};
