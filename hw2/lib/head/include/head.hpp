#pragma once

#include <string>

#include "ioperation.hpp"

class Head : public IOperation {
 public:
  Head(const std::string& argument);

  void ProcessLine(const std::string& line) override;
  void HandleEndOfInput() override;
  void SetNextOperation(std::unique_ptr<IOperation> next_operation) override;
  IOperation* GetNextOperation() const override;
 private:
  int argument_;
  int count_;
  std::unique_ptr<IOperation> next_operation_;
};
