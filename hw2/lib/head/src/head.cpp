#include "head.hpp"

#include <iostream>
#include <string>

#include "ioperation.hpp"

Head::Head(const std::string& argument)
  : argument_(std::stoi(argument)), count_(0), next_operation_(nullptr) {}

void Head::ProcessLine(const std::string& line) {
  if (count_ == argument_)
    return;
  if (next_operation_) {
    next_operation_->ProcessLine(line);
  } else {
    std::cout << line << std::endl;
  }
  count_++;
}

void Head::HandleEndOfInput() {
  if (next_operation_)
    next_operation_->HandleEndOfInput();
}

void Head::SetNextOperation(std::unique_ptr<IOperation> next_operation) {
  next_operation_ = std::move(next_operation);
}

IOperation* Head::GetNextOperation() const {
  return next_operation_.get();
}
