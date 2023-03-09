#pragma once

#include <fstream>
#include <string>

class NameBasics {
 public:
   NameBasics() : nconst_(""), primary_name_("") {}
   NameBasics(const std::string& line);
   
   const std::string& get_nconst() const;
   const std::string& get_primary_name() const;
   
   static void FindAndWrite(std::ifstream& in,
       const std::string& primary_name, NameBasics& name_basics);
 private:
	std::string nconst_;
	std::string primary_name_;
};
