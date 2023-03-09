#include "title_crew.hpp"

#include <string>
#include <vector>

TitleCrew::TitleCrew(const std::string& line) {
  size_t tconst_end = line.find('\t');
  tconst_ = line.substr(0, tconst_end);

  size_t directors_end = line.find('\t', tconst_end + 1);
  std::string directors_str = line.substr(tconst_end + 1,
                                          directors_end - tconst_end - 1);
  
  size_t pos = 0;
  size_t end;
  while (true) {
    end = directors_str.find(',', pos);
    directors_.push_back(directors_str.substr(pos, end - pos));
    if (end == std::string::npos)
      break;
    pos = end + 1;
  }
}

const std::string& TitleCrew::get_tconst() const {
  return tconst_;
}

const std::vector<std::string>& TitleCrew::get_directors() const {
  return directors_;
}

bool TitleCrew::HasDirector(const std::string &nconst) const {
  for (auto const& director : directors_)
    if (director == nconst)
      return true;
  return false;
}

void TitleCrew::FindAndWrite(std::ifstream &in,
    const std::string& nconst, std::vector<TitleCrew> &title_crew_entries) {
  std::string line;
  while(std::getline(in, line)) {
    TitleCrew title_crew(line);
    if (title_crew.HasDirector(nconst)) {
      title_crew_entries.push_back(title_crew);
    }
  }
}
