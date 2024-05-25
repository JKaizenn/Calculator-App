#include "calculator.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

// Constructor
Calculator::Calculator() {}

// Main loop to run the calculator
void Calculator::run() {
  int choice;
  do {
    displayMenu();
    while (!(std::cin >> choice)) {
      std::cout << "Invalid input. Please enter a number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      displayMenu();
    }
    handleChoice(choice);
  } while (choice != 6);
}

// Run the calculator using a file input
void Calculator::runFromFile(const std::string &inputFile,
const std::string &outputFile) {
  std::ifstream infile(inputFile);
  std::ofstream outfile(outputFile);

  if (!infile.is_open() || !outfile.is_open()) {
    std::cout << "Error opening files.\n";
    return;
  }

  std::string operation;
  double a, b, result;

  while (infile >> operation >> a >> b) {
    if (operation == "add") {
      result = a + b;
    } else if (operation == "subtract") {
      result = a - b;
    } else if (operation == "multiply") {
      result = a * b;
    } else if (operation == "divide") {
      if (b != 0) {
        result = a / b;
      } else {
        outfile << "Cannot divide by zero\n";
        continue;
      }
    } else {
      outfile << "Invalid operation: " << operation << "\n";
      continue;
    }
    outfile << operation << " " << a << " " << b << " = " << result << "\n";
    saveResult(operation, result);
  }

  infile.close();
  outfile.close();
}

// Display the menu options
void Calculator::displayMenu() {
  std::cout << "Simple Calculator\n";
  std::cout << "1. Add\n";
  std::cout << "2. Subtract\n";
  std::cout << "3. Multiply\n";
  std::cout << "4. Divide\n";
  std::cout << "5. Show History\n";
  std::cout << "6. Exit\n";
  std::cout << "Choose an option: ";
}

// Handle the user's menu choice
void Calculator::handleChoice(int choice) {
  switch (choice) {
  case 1:
    add();
    break;
  case 2:
    subtract();
    break;
  case 3:
    multiply();
    break;
  case 4:
    divide();
    break;
  case 5:
    showHistory();
    break;
  case 6:
    std::cout << "Exiting...\n";
    break;
  default:
    std::cout << "Invalid choice. Try again.\n";
  }
}

// Get a number from the user with a prompt
double Calculator::getNumber(const std::string &prompt) {
  double number;
  std::cout << prompt;
  while (!(std::cin >> number)) {
    std::cout << "Invalid input. Please enter a number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << prompt;
  }
  return number;
}

// Perform addition
void Calculator::add() {
  double a = getNumber("Enter the first number: ");
  double b = getNumber("Enter the second number: ");
  double result = a + b;
  std::cout << "Result: " << result << "\n";
  saveResult("Add", result);
}

// Perform subtraction
void Calculator::subtract() {
  double a = getNumber("Enter the first number: ");
  double b = getNumber("Enter the second number: ");
  double result = a - b;
  std::cout << "Result: " << result << "\n";
  saveResult("Subtract", result);
}

// Perform multiplication
void Calculator::multiply() {
  double a = getNumber("Enter the first number: ");
  double b = getNumber("Enter the second number: ");
  double result = a * b;
  std::cout << "Result: " << result << "\n";
  saveResult("Multiply", result);
}

// Perform division with error handling for division by zero
void Calculator::divide() {
  double a = getNumber("Enter the first number: ");
  double b;
  do {
    b = getNumber("Enter the second number (non-zero): ");
    if (b == 0) {
      std::cout << "Cannot divide by zero. Try again.\n";
    }
  } while (b == 0);
  double result = a / b;
  std::cout << "Result: " << result << "\n";
  saveResult("Divide", result);
}

// Save the result of the operation to a file and in memory
void Calculator::saveResult(const std::string &operation, double result) {
  std::ofstream file("history.txt", std::ios::app);
  if (file.is_open()) {
    file << operation << ": " << result << "\n";
    file.close();
  } else {
    std::cout << "Unable to open file\n";
  }
  history.push_back(operation + ": " + std::to_string(result));
}

// Show the calculation history from the file
void Calculator::showHistory() {
  std::ifstream file("history.txt");
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << line << "\n";
    }
    file.close();
  } else {
    std::cout << "No history available\n";
  }
}
