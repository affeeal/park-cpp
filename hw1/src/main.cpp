#include <fstream>
#include <iostream>
#include <string>

#include <name_basics.hpp>
#include <title_crew.hpp>

int main(int argc, char* argv[]) {
  // input is supposed to be correct

  // processing name.basics.tsv
  std::ifstream name_basics_file(argv[2]);
  NameBasics name_basics;
  if (name_basics_file.is_open()) {
    NameBasics::FindAndWrite(name_basics_file, argv[1], name_basics);
    name_basics_file.close();
  } else {
    std::cerr << "unable to open name.basics.tsv" << std::endl;
    return 1;
  }
  if (name_basics.get_primary_name() == "") {
    std::cerr << "primary name not found" << std::endl;
    return 1;
  }
  
  // processing title.crew.tsv
  std::ifstream title_crew_file(argv[5]);
  std::vector<TitleCrew> title_crew_entries;
  if (title_crew_file.is_open()) {
    TitleCrew::FindAndWrite(title_crew_file, name_basics.get_nconst(), 
                            title_crew_entries);
    title_crew_file.close();
  } else {
    std::cerr << "unable to open title.crew.tsv" << std::endl;
    return 1;
  }
  if (title_crew_entries.empty()) {
    std::cerr << "titles not found" << std::endl;
    return 1;
  }
  
  // processing title.akas.tsv
  // ...
	return 0;
}
