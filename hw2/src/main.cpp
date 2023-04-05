#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

constexpr std::string_view kUsage {
  "Usage: ./hw2 '<operations>'\n"
  "<operations> ::= <operation> { '|' <operation> }\n"
  "<operation>  ::= 'cat' filename | 'echo' string | 'head' number" };

int main(int argc, char* argv[]) {
  if (argc != 2)
    std::cout << kUsage << std::endl;

  std::vector<std::string> tokens;
  if (!Parse(std::string_view { argv[1] }, tokens)) {
    std::cout << "failed to parse" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
