#pragma once

#include <string>
#include <memory>

class IOperation {
 public:
  virtual void ProcessLine(const std::string& line) = 0;
  virtual void HandleEndOfInput() = 0;
  virtual void SetNextOperation(std::unique_ptr<IOperation> next_operation) = 0;
  // для удобства к геттеру добавил сеттер.
  virtual IOperation* GetNextOperation() const = 0;
};
