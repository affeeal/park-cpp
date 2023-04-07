#include "echo.hpp"

#include <iostream>

#include "ioperation.hpp"

Echo::Echo(const std::string& argument)
  : argument_(argument), next_operation_(nullptr) {}

void Echo::ProcessLine(const std::string& line) {}

void Echo::HandleEndOfInput() {
  if (next_operation_) {
    next_operation_->ProcessLine(argument_);
    next_operation_->HandleEndOfInput();
  } else {
   std::cout << argument_ << std::endl;
  }
}

void Echo::SetNextOperation(std::unique_ptr<IOperation> next_operation) {
  next_operation_ = std::move(next_operation);
}

IOperation* Echo::GetNextOperation() const {
  return next_operation_.get();
}
