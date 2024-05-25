#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

// Calculator class definition
class Calculator {
public:
  Calculator();
  void run();
  void runFromFile(const std::string &inputFile, const std::string &outputFile);

private:
  void displayMenu();
  void handleChoice(int choice);
  double getNumber(const std::string &prompt);
  void add();
  void subtract();
  void multiply();
  void divide();
  void saveResult(const std::string &operation, double result);
  void showHistory();
  std::vector<std::string> history;
};

#endif
