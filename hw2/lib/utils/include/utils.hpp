#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ioperation.hpp"

const std::vector<std::string> kNames { "cat", "echo", "head" };
enum NameIndex {
  kCat = 0,
  kEcho,
  kHead,
};

bool Parse(std::string_view line, std::vector<std::string>& tokens);

std::unique_ptr<IOperation> CreateOperation(
    int i, const std::vector<std::string>& tokens);
