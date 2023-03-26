#pragma once

#include <fstream>
#include <memory>
#include <set>
#include <string_view>

#include "name_basics.hpp"
#include "title_akas.hpp"
#include "title_basics.hpp"
#include "title_crew.hpp"

bool CheckFileAndCompareRows(
    std::ifstream& file,
    const std::string_view name,
    const std::string_view expected_row);

void SplitColumns(const std::string& row,
    std::vector<std::string>& columns, int columns_count);

std::shared_ptr<NameBasics> SelectNameBasicsByPrimaryName(
    std::ifstream& name_basics_file, const std::string& primary_name);

std::shared_ptr<TitleCrew> SelectTitleCrewByNconst(
    std::ifstream& title_crew_file, const std::string& nconst);

std::shared_ptr<TitleBasics> SelectTitleBasicsByTconst(
    std::ifstream& title_basics_file, const std::string& tconst);

std::shared_ptr<std::vector<TitleAkas>> SelectTitleAkasRowsByNumericTconstSet (
    std::ifstream& title_akas_file, const std::set<int>& numeric_tconst_set);

void SelectAppropriateTitleCrewAndTitleBasicsRows(
    std::ifstream& title_crew_file,
    std::ifstream& title_basics_file,
    std::vector<std::shared_ptr<TitleCrew>>& title_crew_rows,
    std::vector<std::shared_ptr<TitleBasics>>& title_basics_rows,
    const std::shared_ptr<NameBasics> name_basics,
    const std::string_view kIsAdult,
    const std::string_view kTitleType);

void SelectAppropriateTitleAkasRows(
    std::ifstream& title_akas_file,
    std::vector<std::shared_ptr<TitleAkas>>& title_akas_rows,
    const std::vector<std::shared_ptr<TitleCrew>>& title_crew_rows,
    const std::string_view kRegion);

void PrintMovies(
    const std::vector<std::shared_ptr<TitleAkas>>& title_akas_rows,
    const std::vector<std::shared_ptr<TitleBasics>>& title_basics_rows);
