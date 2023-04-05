#include "utils.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

#include "ioperation.hpp"
#include "cat.hpp"
#include "echo.hpp"
#include "head.hpp"

bool IsKnownName(const std::string& token) {
  for (const auto& name : kNames) {
    if (token == name)
      return true;
  }
  return false;
}

bool IsNonNegativeNumber(const std::string& token) {
  auto number { 0 };
  // Придерживаясь Google codestyle'а нельзя использовать исключения,
  // но здесь необходимо отловить std::invalid_argument, выбрасываемый
  // std::stoi, если на вход подано не число.
  try {
    number = std::stoi(token);
  } catch (std::invalid_argument) {
    return false;
  }
  if (number < 0)
    return false;
  return true;
}

bool Parse(std::string_view line, std::vector<std::string>& tokens) {
  auto begin { 0 };
  auto end { 0 };
  while (true) {
    end = line.find(' ', begin);
    if (end == std::string::npos)
      return false;

    std::string name { line.substr(begin, end - begin) };
    if (!IsKnownName(name))
        return false;
    tokens.push_back(name);

    begin = end + 1;
    end = line.find(' ', begin);
    std::string argument { line.substr(begin, end - begin) };

    if (name == kNames[NameIndex::kHead] && !IsNonNegativeNumber(argument))
      return false;
    tokens.push_back(argument);

    if (end == std::string::npos)
      break;

    begin = end + 1;
    if (line.substr(begin, 2) != "| ")
      return false;

    begin += 2;
  }

  return true;
}

std::unique_ptr<IOperation> CreateOperation(
    int i, const std::vector<std::string>& tokens) {
  if (tokens[i] == kNames[NameIndex::kCat])
    return std::make_unique<Cat>(Cat(tokens[i + 1]));
  else if (tokens[i] == kNames[NameIndex::kEcho])
    return std::make_unique<Echo>(Echo(tokens[i + 1]));
  else if (tokens[i] == kNames[NameIndex::kHead])
    return std::make_unique<Head>(Head(tokens[i + 1]));
  else
   return nullptr;
}
