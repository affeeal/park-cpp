#pragma once

#include <string>
#include <vector>

class NameBasics {
 public:
   static const int kColumnsCount;

   enum class Column {
     kNconst = 0,
     kPrimaryName,
     kBirthYear,
     kDeathYear,
     kPrimaryProfession,
     kKnownFowTitles,
   };
   
   NameBasics(const std::vector<std::string>& columns);
   
   const std::vector<std::string>& get_columns() const;
 private:
   std::vector<std::string> columns_;
};
