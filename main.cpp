#include "calculator.h"
#include <iostream>

int main() {
  Calculator calculator;
  int interfaceChoice;

  std::cout << "Select Interface:\n";
  std::cout << "1. Command Line Interface\n";
  std::cout << "2. File-Based Interface\n";
  std::cout << "Choose an option: ";

  while (!(std::cin >> interfaceChoice)) {
    std::cout << "Invalid input. Please enter a number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Choose an option: ";
  }

  if (interfaceChoice == 1) {
    calculator.run();
  } else if (interfaceChoice == 2) {
    std::string inputFile, outputFile;
    std::cout << "Enter input file name: ";
    std::cin >> inputFile;
    std::cout << "Enter output file name: ";
    std::cin >> outputFile;
    calculator.runFromFile(inputFile, outputFile);
  } else {
    std::cout << "Invalid choice. Exiting...\n";
  }

  return 0;
}
