#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "ioperation.hpp"
#include "cat.hpp"
#include "echo.hpp"
#include "head.hpp"
#include "utils.hpp"

constexpr std::string_view kUsage {
  "Usage: ./hw2 '<operations>'\n"
  "<operations> ::= <operation> { \" | \" <operation> }\n"
  "<operation>  ::= \"cat \" filename | \"echo \" string | \"head \" number" };

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << kUsage << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<std::string> tokens;
  if (!Parse(std::string_view { argv[1] }, tokens)) {
    std::cout << "failed to parse" << std::endl;
    return EXIT_FAILURE;
  }

  auto first_operation = CreateOperation(0, tokens);
  IOperation* previous_operation = first_operation.get();
  for (auto i = 2; i < tokens.size(); i += 2) {
    previous_operation->SetNextOperation(CreateOperation(i, tokens));
    previous_operation = previous_operation->GetNextOperation();
  }
  
  first_operation->HandleEndOfInput();

  return EXIT_SUCCESS;
}
