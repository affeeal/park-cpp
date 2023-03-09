#include "name_basics.hpp"

#include <cstddef>
#include <string>

NameBasics::NameBasics(std::string line) {
  size_t nconst_end = line.find('\t');
  nconst_ = line.substr(0, nconst_end);
  size_t primary_name_end = line.find('\t', nconst_end + 1);
  primary_name_ = line.substr(nconst_end + 1,
                              primary_name_end - nconst_end - 1);
}
