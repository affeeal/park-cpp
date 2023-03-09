#include "name_basics.hpp"

#include <cstddef>
#include <string>

NameBasics::NameBasics(const std::string& line) {
  size_t nconst_end = line.find('\t');
  nconst_ = line.substr(0, nconst_end);
  
  size_t primary_name_end = line.find('\t', nconst_end + 1);
  primary_name_ = line.substr(nconst_end + 1,
                              primary_name_end - nconst_end - 1);
}

const std::string& NameBasics::get_nconst() const {
  return nconst_;
}

const std::string& NameBasics::get_primary_name() const {
  return primary_name_;
}

void NameBasics::FindAndWrite(std::ifstream& in,
    const std::string& primary_name, NameBasics& name_basics) {
  std::string line;
  while (std::getline(in, line)) {
    NameBasics nb(line);
    if (nb.get_primary_name() == primary_name) {
      name_basics = nb;
      break;
    }
  }
}
