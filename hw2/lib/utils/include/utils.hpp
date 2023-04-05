#pragma once

#include <string_view>
#include <vector>

#include "cat.hpp"
#include "echo.hpp"
#include "head.hpp"

const std::vector<std::string> kNames { "cat", "echo", "head" };
enum NameIndex {
  kCat = 0,
  kEcho,
  kHead,
};

bool Parse(std::string_view line, std::vector<std::string>& tokens);
