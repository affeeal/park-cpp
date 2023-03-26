#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <string_view>

#include "name_basics.hpp"
#include "title_akas.hpp"
#include "title_basics.hpp"
#include "title_crew.hpp"
#include "utils.hpp"

constexpr std::string_view kNameBasicsFlag  { "--name-basics-path" };
constexpr std::string_view kTitleAkasFlag   { "--title-akas-path" };
constexpr std::string_view kTitleBasicsFlag { "--title-basics-path" };
constexpr std::string_view kTitleCrewFlag   { "--title-crew-path" };
constexpr std::string_view kPrimaryNameFlag { "--primary-name" };

constexpr std::string_view kNameBasicsColumns { 
  "nconst\tprimaryName\tbirthYear\t"
  "deathYear\tprimaryProfession\tknownForTitles" };

constexpr std::string_view kTitleAkasColumns { 
  "titleId\tordering\ttitle\tregion\t"
  "language\ttypes\tattributes\tisOriginalTitle" };

constexpr std::string_view kTitleBasicsColumns { 
  "tconst\ttitleType\tprimaryTitle\toriginalTitle\t"
  "isAdult\tstartYear\tendYear\truntimeMinutes\tgenres" };

constexpr std::string_view kTitleCrewColumns { 
  "tconst\tdirectors\twriters" };

constexpr std::string_view kIsAdult   { "0" };
constexpr std::string_view kRegion    { "RU" };
constexpr std::string_view kTitleType { "movie" };

int main(int argc, char* argv[]) {
  if (argc != 11) {
    std::cerr
      << "Usage: ./hw1 <flags>" << std::endl
      << "Flags:" << std::endl
      << '\t' << kNameBasicsFlag  << "  <path-to-name-basics>"  << std::endl
      << '\t' << kTitleAkasFlag   << "   <path-to-title-akas>"  << std::endl
      << '\t' << kTitleBasicsFlag << " <path-to-title-basics>"  << std::endl
      << '\t' << kTitleCrewFlag   << "   <path-to-title-crew>"  << std::endl
      << '\t' << kPrimaryNameFlag << "      \"<primary-name>\"" << std::endl;
    return EXIT_FAILURE;
  }

  int name_basics_index = 0;
  int title_akas_index = 0;
  int title_basics_index = 0;
  int title_crew_index = 0;
  int primary_name_index = 0;
  
  for (auto i = 1; i < argc; i += 2) {
    std::string_view arg { argv[i] };
    if (arg == kNameBasicsFlag && name_basics_index == 0) {
      name_basics_index = i + 1;
    } else if (arg == kTitleAkasFlag && title_akas_index == 0) {
      title_akas_index = i + 1;
    } else if (arg == kTitleBasicsFlag && title_basics_index == 0) {
      title_basics_index = i + 1;
    } else if (arg == kTitleCrewFlag && title_crew_index == 0) {
      title_crew_index = i + 1;
    } else if (arg == kPrimaryNameFlag && primary_name_index == 0) {
      primary_name_index = i + 1;
    } else {
      std::cerr
        << "unrecognised or repeated command-line option " << arg
        << std::endl;
      return EXIT_FAILURE;
    }
  }

  std::ifstream name_basics_file(argv[name_basics_index]);
  if (!CheckFileAndCompareRows(
        name_basics_file, "name.basics.tsv", kNameBasicsColumns)) {
    name_basics_file.close();
    return EXIT_FAILURE;
  }
    
  auto name_basics = SelectNameBasicsByPrimaryName(
      name_basics_file,
      argv[primary_name_index]);

  name_basics_file.close();
  
  if (name_basics == nullptr) {
    std::cerr << "failed to find appropriate name.basics.tsv row" << std::endl;
    return EXIT_FAILURE;
  }
  
  std::ifstream title_crew_file(argv[title_crew_index]);
  if (!CheckFileAndCompareRows(
        title_crew_file, "title.crew.tsv", kTitleCrewColumns)) {
    title_crew_file.close();
    return EXIT_FAILURE;
  }
  
  std::ifstream title_basics_file(argv[title_basics_index]);
  if (!CheckFileAndCompareRows(
        title_basics_file, "title.basics.tsv", kTitleBasicsColumns)) {
    title_crew_file.close();
    title_basics_file.close();
    return EXIT_FAILURE;
  }

  std::vector<std::shared_ptr<TitleCrew>> title_crew_rows;
  std::vector<std::shared_ptr<TitleBasics>> title_basics_rows;
  SelectAppropriateTitleCrewAndTitleBasicsRows(
      title_crew_file,
      title_basics_file,
      title_crew_rows,
      title_basics_rows,
      name_basics,
      kIsAdult,
      kTitleType);
  
  title_crew_file.close();
  title_basics_file.close();

  std::ifstream title_akas_file(argv[title_akas_index]);
  if (!CheckFileAndCompareRows(
        title_akas_file, "title.akas.tsv", kTitleAkasColumns)) {
    title_akas_file.close();
    return EXIT_FAILURE;
  }

  std::vector<std::shared_ptr<TitleAkas>> title_akas_rows(
      title_crew_rows.size());
  SelectAppropriateTitleAkasRows(
      title_akas_file,
      title_akas_rows,
      title_crew_rows,
      kRegion);

  title_akas_file.close();

  PrintMovies(title_akas_rows, title_basics_rows);

	return EXIT_SUCCESS;
}
