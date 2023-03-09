#include <fstream>
#include <iostream>
#include <string>

#include <name_basics.hpp>

const std::string kUsage = "./main \"primary name\" name.basics.tsv "
    "title.akas.tsv title.basics.tsv title.crew.tsv title.ratings.tsv";

int main(int argc, char* argv[]) {
	// input is supposed to be correct
	if (argc != 7) {
		std::cerr << "usage:" << std::endl;
		std::cerr << '\t' << kUsage << std::endl;
		return 1;
	}
	// processing name.basics.tsv
	std::ifstream name_basics_file(argv[2]);
  NameBasics name_basics;
	if (name_basics_file.is_open()) {
		std::string line;
		while (std::getline(name_basics_file, line)) {
			NameBasics nb(line);
      if (nb.get_primary_name() == argv[1]) {
          name_basics = nb;
          break;
      }
		}
		name_basics_file.close();
	} else {
    std::cerr << "unable to open name.basics.tsv" << std::endl;
    return 1;
  }
  if (name_basics.get_primary_name() == "") {
    std::cerr << "primary name not found" << std::endl;
    return 1;
  }
  // ...
	return 0;
}
