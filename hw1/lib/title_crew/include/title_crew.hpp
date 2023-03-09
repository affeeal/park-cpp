#pragma once

#include <fstream>
#include <string>
#include <vector>

class TitleCrew {
 public:
   TitleCrew() : tconst_("") {}
   TitleCrew(const std::string& line);

   const std::string& get_tconst() const;
   const std::vector<std::string>& get_directors() const;

   bool HasDirector(const std::string& nconst) const;

   static void FindAndWrite(std::ifstream& in,
       const std::string& nconst, std::vector<TitleCrew>& title_crew_entries);
 private:
   std::string tconst_;
   std::vector<std::string> directors_;
};
