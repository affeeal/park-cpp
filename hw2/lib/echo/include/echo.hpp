#pragma once

#include "ioperation.hpp"

class Echo : public IOperation {
 public:
  Echo(const std::string& argument);

  void ProcessLine(const std::string& line) override;
  void HandleEndOfInput() override;
  void SetNextOperation(std::unique_ptr<IOperation> next_operation) override;
  IOperation* GetNextOperation() const override;
 private:
  std::string argument_;
  std::unique_ptr<IOperation> next_operation_;
};
