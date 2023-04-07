#include "cat.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "ioperation.hpp"

Cat::Cat(const std::string& filename)
  : filename_(filename), next_operation_(nullptr) {}

void Cat::ProcessLine(const std::string& line) {
  if (next_operation_)
    next_operation_->ProcessLine(line);
  else
    std::cout << line << std::endl;
}

void Cat::HandleEndOfInput() {
  std::ifstream file(filename_);
  std::string line;
  while (std::getline(file, line)) {
    if (next_operation_)
      next_operation_->ProcessLine(line);
    else
      std::cout << line << std::endl;
  }

  if (next_operation_)
    next_operation_->HandleEndOfInput();
  file.close();
}

void Cat::SetNextOperation(std::unique_ptr<IOperation> next_operation) {
  next_operation_ = std::move(next_operation);
}

IOperation* Cat::GetNextOperation() const {
  return next_operation_.get();
}
