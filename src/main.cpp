#include "rpn.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void processFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);
    RPN calculator;
    
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Cannot open input file '" + inputFilename + "'");
    }
    
    if (!outputFile.is_open()) {
        throw std::runtime_error("Error: Cannot open output file '" + outputFilename + "'");
    }
    
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(inputFile, line)) {
        lineNumber++;
        
        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        
        try {
            int result = calculator.calculate(line);
            outputFile << line << " = " << result << std::endl;
            std::cout << "Line " << lineNumber << ": " << line << " = " << result << std::endl;
        } catch (const RPNException& e) {
            outputFile << line << " = " << "Error: " << e.what() << std::endl;
            std::cerr << "Error in line " << lineNumber << ": " << e.what() << std::endl;
        } catch (const std::exception& e) {
            outputFile << line << " = " << "Error: " << e.what() << std::endl;
            std::cerr << "Unexpected error in line " << lineNumber << ": " << e.what() << std::endl;
        }
    }
    
    inputFile.close();
    outputFile.close();
}

void printUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " <input_file> <output_file>" << std::endl;
    std::cout << "Example: " << programName << " input.txt output.txt" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    
    try {
        processFile(inputFilename, outputFilename);
        std::cout << "Processing completed successfully. Results saved to " << outputFilename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
