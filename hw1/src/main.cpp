#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

#include "name_basics.hpp"
#include "title_akas.hpp"
#include "title_basics.hpp"
#include "title_crew.hpp"

// TODO: разобраться с заголовками

void SplitColumns(
    const std::string& row,
    std::vector<std::string>& columns) {
  size_t begin = 0;
  size_t end = 0;
  while (end != std::string::npos) {
    end = row.find('\t', begin);
    columns.push_back(row.substr(begin, end - begin));
    begin = end + 1;
  }
}

std::unique_ptr<NameBasics> FindNameBasicsByPrimaryName(
    std::ifstream& name_basics_file,
    const std::string& primary_name) {
  std::string row;
  while (std::getline(name_basics_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns);
    assert(columns.size() == NameBasics::kColumnsCount);
    if (columns[int(NameBasics::Column::kPrimaryName)] == primary_name)
      return std::make_unique<NameBasics>(NameBasics(columns));
  }
  return nullptr;
}

void FindTitleCrewRowsByNconst(
    std::ifstream& title_crew_file,
    std::ifstream& title_basics_file,
    const std::string& nconst,
    std::vector<TitleCrew>& title_crew_rows) {
  std::string row;
  while (std::getline(title_crew_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns);
    assert(columns.size() == TitleCrew::kColumnsCount);
    if (columns[int(TitleCrew::Column::kDirectors)].find(nconst)
        == std::string::npos) continue;
    // ...
  }
}

int main(int argc, char* argv[]) {
  // input is supposed to be correct

  // processing name.basics.tsv
  std::ifstream name_basics_file(argv[2]);
  if (!name_basics_file.is_open()) {
    std::cerr << "failed to open name.basics.tsv" << std::endl;
    return 1;
  }
  
  auto name_basics = FindNameBasicsByPrimaryName(name_basics_file, argv[1]);
  if (name_basics == nullptr) {
    std::cerr << "failed to find appropriate name.basics.tsv row" << std::endl;
    return 1;
  }
  
  name_basics_file.close();
  
  // processing title.crew.tsv
  std::ifstream title_crew_file(argv[5]);
  std::ifstream title_basics_file(argv[4]);
  if (!title_crew_file.is_open()) {
    std::cerr << "failed to open title.crew.tsv" << std::endl;
    return 1;
  }
  if (!title_basics_file.is_open()) {
    std::cerr << "failed to open title.basics.tsv" << std::endl;
    return 1;
  }

  std::vector<TitleCrew> title_crew_rows;
  FindTitleCrewRowsByNconst(
      title_crew_file, title_basics_file,
      name_basics->get_columns()[int(NameBasics::Column::kNconst)],
      title_crew_rows);

  // ...

  title_crew_file.close();
  title_basics_file.close();
  
	return 0;
}
