#pragma once

#include <string>
#include <vector>

class Dataset {
 public:
  explicit Dataset(const std::vector<std::string>& columns);
  const std::vector<std::string>& get_columns() const;

 protected:
   std::vector<std::string> columns_;
};
