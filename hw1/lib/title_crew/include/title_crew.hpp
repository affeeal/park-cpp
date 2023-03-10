#pragma once

#include <string>
#include <vector>

class TitleCrew {
 public:
   static const size_t kColumnsCount;
   
   enum class Column {
     kTconst = 0,
     kDirectors,
     kWriters
   };
   
   TitleCrew(const std::vector<std::string>& columns);

   const std::vector<std::string>& get_columns() const;
 private:
   std::vector<std::string> columns_;
};
