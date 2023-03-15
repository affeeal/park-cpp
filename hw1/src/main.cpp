#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <set>
#include <string>
#include <string_view>

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

std::shared_ptr<NameBasics> SelectNameBasicsByPrimaryName(
    std::ifstream& name_basics_file,
    const std::string& primary_name) {
  std::string row;
  
  while (std::getline(name_basics_file, row)) {
    std::vector<std::string> columns;
    SplitColumns(row, columns);
    assert(columns.size() == NameBasics::kColumnsCount);
    
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
    SplitColumns(row, columns);
    assert(columns.size() == TitleCrew::kColumnsCount);
    
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
    SplitColumns(row, columns);
    assert(columns.size() == TitleBasics::kColumnsCount);
    
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
    SplitColumns(row, columns);
    assert(columns.size() == TitleAkas::kColumnsCount);

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

constexpr std::string_view name_basics_flag  { "--name-basics-path" };
constexpr std::string_view title_akas_flag   { "--title-akas-path" };
constexpr std::string_view title_basics_flag { "--title-basics-path" };
constexpr std::string_view title_crew_flag   { "--title-crew-path" };
constexpr std::string_view primary_name_flag { "--primary-name" };

constexpr std::string_view name_basics_headers { 
  "nconst\tprimaryName\tbirthYear\t"
  "deathYear\tprimaryProfession\tknownForTitles" };

constexpr std::string_view title_akas_headers { 
  "titleId\tordering\ttitle\tregion\t"
  "language\ttypes\tattributes\tisOriginalTitle" };

constexpr std::string_view title_basics_headers { 
  "tconst\ttitleType\tprimaryTitle\toriginalTitle\t"
  "isAdult\tstartYear\tendYear\truntimeMinutes\tgenres" };

constexpr std::string_view title_crew_headers { 
  "tconst\tdirectors\twriters" };


int main(int argc, char* argv[]) {
  // checking command-line options count
  if (argc != 11) {
    std::cerr
      << "Usage: ./hw1 <flags>" << std::endl
      << "Flags:" << std::endl
      << '\t' << name_basics_flag << "  <path-to-name-basics>" << std::endl
      << '\t' << title_akas_flag << "   <path-to-title-akas>" << std::endl
      << '\t' << title_basics_flag << " <path-to-title-basics>" << std::endl
      << '\t' << title_crew_flag << "   <path-to-title-crew>" << std::endl
      << '\t' << primary_name_flag << "      \"<primary-name>\"" << std::endl;
    return EXIT_FAILURE;
  }

  int name_basics_index = 0;
  int title_akas_index = 0;
  int title_basics_index = 0;
  int title_crew_index = 0;
  int primary_name_index = 0;
  
  // identifying command-line options
  for (auto i = 1; i < argc; i += 2) {
    std::string_view arg { argv[i] };
    if (arg == name_basics_flag && name_basics_index == 0) {
      name_basics_index = i + 1;
    } else if (arg == title_akas_flag && title_akas_index == 0) {
      title_akas_index = i + 1;
    } else if (arg == title_basics_flag && title_basics_index == 0) {
      title_basics_index = i + 1;
    } else if (arg == title_crew_flag && title_crew_index == 0) {
      title_crew_index = i + 1;
    } else if (arg == primary_name_flag && primary_name_index == 0) {
      primary_name_index = i + 1;
    } else {
      std::cerr
        << "unrecognised or repeated command-line option " << arg
        << std::endl;
      return EXIT_FAILURE;
    }
  }

  // opening name.basics.tsv
  std::ifstream name_basics_file(argv[name_basics_index]);
  if (!name_basics_file.is_open()) {
    std::cerr << "failed to open name.basics.tsv" << std::endl;
    return EXIT_FAILURE;
  }

  // comparing name.basics.tsv headers
  std::string row;
  std::getline(name_basics_file, row);
  if (row != name_basics_headers) {
    std::cerr << "unexpected headers in name.basics.tsv" << std::endl;
    return EXIT_FAILURE;
  }
  
  // selecting appropriate name.basics.tsv row
  auto name_basics = SelectNameBasicsByPrimaryName(
      name_basics_file,
      argv[primary_name_index]);
  
  if (name_basics == nullptr) {
    std::cerr << "failed to find appropriate name.basics.tsv row" << std::endl;
    return EXIT_FAILURE;
  }
  
  name_basics_file.close();
  
  // opening title.crew.tsv
  std::ifstream title_crew_file(argv[title_crew_index]);
  if (!title_crew_file.is_open()) {
    std::cerr << "failed to open title.crew.tsv" << std::endl;
    return EXIT_FAILURE;
  }

  // comparing title.crew.tsv headers
  std::getline(title_crew_file, row);
  if (row != title_crew_headers) {
    std::cerr << "unexpected headers in title.crew.tsv" << std::endl;
    return EXIT_FAILURE;
  }
  
  // opening title.basics.tsv
  std::ifstream title_basics_file(argv[title_basics_index]);
  if (!title_basics_file.is_open()) {
    std::cerr << "failed to open title.basics.tsv" << std::endl;
    return EXIT_FAILURE;
  }

  // comparing title.basics.tsv headers
  std::getline(title_basics_file, row);
  if (row != title_basics_headers) {
    std::cerr << "unexpected headers in title.basics.tsv" << std::endl;
    return EXIT_FAILURE;
  }

  // selecting appropriate title.crew.tsv and title.basics.tsv rows
  std::vector<std::shared_ptr<TitleCrew>> title_crew_rows;
  std::vector<std::shared_ptr<TitleBasics>> title_basics_rows;
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
        == "0") {
      title_crew_rows.push_back(title_crew);
      title_basics_rows.push_back(title_basics);
    }
  }
  
  title_crew_file.close();
  title_basics_file.close();

  // opening title.akas.tsv
  std::ifstream title_akas_file(argv[title_akas_index]);
  if (!title_akas_file.is_open()) {
    std::cerr << "failed to open title.akas.tsv" << std::endl;
    return EXIT_FAILURE;
  }

  // comparing title.akas.tsv headers
  std::getline(title_akas_file, row);
  if (row != title_akas_headers) {
    std::cerr << "unexpected title.akas.tsv headers" << std::endl;
    return EXIT_FAILURE;
  }

  // set of numeric tconst to find title.akas.tsv rows by
  std::set<int> numeric_tconst_set;
  for (const auto& title_crew : title_crew_rows) {
    numeric_tconst_set.insert(std::stoi(title_crew->get_columns()
          [int(TitleCrew::Column::kTconst)].substr(2)));
  }
  
  // selecting appropriate title.akas.tsv rows
  std::vector<std::shared_ptr<TitleAkas>> title_akas_rows(
      title_crew_rows.size());
  while (true) {
    auto title_akas_rows_interim = SelectTitleAkasRowsByNumericTconstSet(
        title_akas_file,
        numeric_tconst_set);
    
    if (title_akas_rows_interim == nullptr)
      break;

    std::shared_ptr<TitleAkas> title_akas_region_ru = nullptr;
    for (const auto& title_akas : *title_akas_rows_interim) {
      if (title_akas.get_columns()[int(TitleAkas::Column::kRegion)] == "RU") {
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
  
  title_akas_file.close();

  // printing the result
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

	return 0;
}
