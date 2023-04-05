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

  std::unique_ptr<IOperation> first_operation(nullptr);
  if (tokens[0] == kNames[NameIndex::kCat])
    first_operation = std::make_unique<Cat>(Cat(tokens[1]));
  else if (tokens[0] == kNames[NameIndex::kEcho])
    first_operation = std::make_unique<Echo>(Echo(tokens[1]));
  // ...

  IOperation* previous_operation = first_operation.get();
  for (auto i = 2; i < tokens.size(); i += 2) {
    if (tokens[i] == kNames[NameIndex::kCat]) {
      previous_operation->SetNextOperation(
          std::make_unique<Cat>(Cat(tokens[i + 1])));
    } else if (tokens[i] == kNames[NameIndex::kEcho]) {
      previous_operation->SetNextOperation(
          std::make_unique<Echo>(Echo(tokens[i + 1])));
    }
    // ...

    previous_operation = previous_operation->GetNextOperation();
  }
  
  first_operation->HandleEndOfInput();

  return EXIT_SUCCESS;
}
