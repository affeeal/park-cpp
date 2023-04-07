#pragma once

#include <memory>

#include "ioperation.hpp"

class Cat : public IOperation {
 public:
  Cat(const std::string& filename);

  void ProcessLine(const std::string& line) override;
  void HandleEndOfInput() override;
  void SetNextOperation(std::unique_ptr<IOperation> next_operation) override;
  IOperation* GetNextOperation() const override;
 private:
  std::string filename_;
  std::unique_ptr<IOperation> next_operation_;
};
