#include "utils.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

#include "name_basics.hpp"
#include "title_akas.hpp"
#include "title_basics.hpp"
#include "title_crew.hpp"

void SplitColumns(
    const std::string& row,
    std::vector<std::string>& columns,
    int columns_count) {
  int begin = 0;
  int end = 0;
  for (auto i = 0; i < columns_count; i++) {
    assert(end != std::string::npos);
    end = row.find('\t', begin);
    columns.push_back(row.substr(begin, end - begin));
    begin = end + 1;
  }
}

std::shared_ptr<NameBasics> SelectNameBasicsByPrimaryName(
    std::ifstream& name_basics_file,
    const std::string& primary_name) {
  std::string row;
  
  while (std::getline(name_basics_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns, int(NameBasics::Column::kPrimaryName) + 1);
    assert(columns.size() == int(NameBasics::Column::kPrimaryName) + 1);
    
    if (columns[int(NameBasics::Column::kPrimaryName)] == primary_name)
      return std::make_shared<NameBasics>(NameBasics(columns));
  }
  
  return nullptr;
}

std::shared_ptr<TitleCrew> SelectTitleCrewByNconst(
    std::ifstream& title_crew_file,
    const std::string& nconst) {
  std::string row;
  
  while (std::getline(title_crew_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns, int(TitleCrew::Column::kDirectors) + 1);
    assert(columns.size() == int(TitleCrew::Column::kDirectors) + 1);
    
    if (columns[int(TitleCrew::Column::kDirectors)].find(nconst)
        != std::string::npos)
      return std::make_shared<TitleCrew>(TitleCrew(columns));
  }
  
  return nullptr;
}

std::shared_ptr<TitleBasics> SelectTitleBasicsByTconst(
    std::ifstream& title_basics_file,
    const std::string& tconst) {
  std::string row;
  
  while (std::getline(title_basics_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns, int(TitleBasics::Column::kIsAdult) + 1);
    assert(columns.size() == int(TitleBasics::Column::kIsAdult) + 1);
    
    if (columns[int(TitleBasics::Column::kTconst)] == tconst)
      return std::make_shared<TitleBasics>(TitleBasics(columns));
  }
  
  return nullptr;
}

std::shared_ptr<std::vector<TitleAkas>> SelectTitleAkasRowsByNumericTconstSet (
    std::ifstream& title_akas_file,
    const std::set<int>& numeric_tconst_set) {
  std::string row;
  std::vector<TitleAkas> title_akas_rows;
  
  auto position = title_akas_file.tellg();
  bool is_begin_found = false;
  
  while (std::getline(title_akas_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns, int(TitleAkas::Column::kRegion) + 1);
    assert(columns.size() == int(TitleAkas::Column::kRegion) + 1);

    int numeric_tconst = std::stoi(
        columns[int(TitleAkas::Column::kTitleId)].substr(2));

    bool is_tconst_matched = false;
    for (const auto& numeric_tconst_from_set : numeric_tconst_set) {
      if (numeric_tconst < numeric_tconst_from_set) {
        break;
      } else if (numeric_tconst == numeric_tconst_from_set) {
        is_tconst_matched = true;
        break;
      }
    }

    if (is_tconst_matched == true) {
      if (is_begin_found == false)
        is_begin_found = true;
      title_akas_rows.push_back(TitleAkas(columns));
      position = title_akas_file.tellg();
    } else if (is_begin_found == true) {
      title_akas_file.seekg(position, title_akas_file.beg);
      return std::make_shared<std::vector<TitleAkas>>(title_akas_rows);
    }    
  }
  
  return nullptr;
}

void SelectAppropriateTitleCrewAndTitleBasicsRows(
    std::ifstream& title_crew_file,
    std::ifstream& title_basics_file,
    std::vector<std::shared_ptr<TitleCrew>>& title_crew_rows,
    std::vector<std::shared_ptr<TitleBasics>>& title_basics_rows,
    const std::shared_ptr<NameBasics> name_basics,
    const std::string_view kIsAdult,
    const std::string_view kTitleType) {
  while (true) {
    auto title_crew = SelectTitleCrewByNconst(
        title_crew_file,
        name_basics->get_columns()[int(NameBasics::Column::kNconst)]);
    
    if (title_crew == nullptr)
      break;
    
    auto title_basics = SelectTitleBasicsByTconst(
          title_basics_file,
          title_crew->get_columns()[int(TitleCrew::Column::kTconst)]);
    
    if (title_basics->get_columns()[int(TitleBasics::Column::kIsAdult)]
        == kIsAdult
        && title_basics->get_columns()[int(TitleBasics::Column::kTitleType)]
        == kTitleType) {
      title_crew_rows.push_back(title_crew);
      title_basics_rows.push_back(title_basics);
    }
  }
}

void SelectAppropriateTitleAkasRows(
    std::ifstream& title_akas_file,
    std::vector<std::shared_ptr<TitleAkas>>& title_akas_rows,
    const std::vector<std::shared_ptr<TitleCrew>>& title_crew_rows,
    const std::string_view kRegion) {
  std::set<int> numeric_tconst_set;
  for (const auto& title_crew : title_crew_rows) {
    numeric_tconst_set.insert(std::stoi(title_crew->get_columns()
          [int(TitleCrew::Column::kTconst)].substr(2)));
  }

  while (true) {
    auto title_akas_rows_interim = SelectTitleAkasRowsByNumericTconstSet(
        title_akas_file,
        numeric_tconst_set);
    
    if (title_akas_rows_interim == nullptr)
      break;

    std::shared_ptr<TitleAkas> title_akas_region_ru = nullptr;
    for (const auto& title_akas : *title_akas_rows_interim) {
      if (title_akas.get_columns()[int(TitleAkas::Column::kRegion)]
          == kRegion) {
        title_akas_region_ru = std::make_shared<TitleAkas>(title_akas);
        break;
      }
    }
    
    assert(title_akas_rows_interim->size() >= 1);
    const std::string& tconst = (*title_akas_rows_interim)[0].get_columns()
      [int(TitleAkas::Column::kTitleId)];
    
    for (auto i = 0; i < title_akas_rows.size(); i++) {
      if (title_crew_rows[i]->get_columns()[int(TitleCrew::Column::kTconst)]
          == tconst) {
        title_akas_rows[i] = title_akas_region_ru;
        break;
      }
    }

    const int numeric_tconst = std::stoi(tconst.substr(2));
    for (const auto numeric_tconst_from_set : numeric_tconst_set) {
      if (numeric_tconst == numeric_tconst_from_set) {
        numeric_tconst_set.erase(numeric_tconst);
        break;
      }
    }
  }
}

void PrintMovies(
    const std::vector<std::shared_ptr<TitleAkas>>& title_akas_rows,
    const std::vector<std::shared_ptr<TitleBasics>>& title_basics_rows) {
  for (auto i = 0; i < title_akas_rows.size(); i++) {
    if (title_akas_rows[i] != nullptr) {
      std::cout
        << title_akas_rows[i]->get_columns()[int(TitleAkas::Column::kTitle)]
        << std::endl;
    } else {
      std::cout
        << title_basics_rows[i]->get_columns()
        [int(TitleBasics::Column::kPrimaryTitle)] << std::endl;
    }
  }
}
