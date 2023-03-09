#pragma once

#include <string>

class NameBasics {
 public:
   NameBasics() : nconst_(""), primary_name_("") {}
   NameBasics(std::string line);
   
   void set_ncost(std::string nconst) {
     nconst_ = nconst;
   }
   std::string get_ncost() const {
     return nconst_;
   }

   void set_primary_name(std::string primary_name) {
     primary_name_ = primary_name;
   }
   std::string get_primary_name() const {
     return primary_name_;
   }
 private:
	std::string nconst_;
	std::string primary_name_;
};
