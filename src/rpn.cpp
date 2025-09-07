#include "rpn.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

RPN::RPN() {}

bool RPN::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::validateExpression(const std::string& expression) const {
    if (expression.empty()) {
        throw RPNException("Error: Empty expression");
    }
    
    int operandCount = 0;
    int operatorCount = 0;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        if (token.length() != 1) {
            throw RPNException("Error: Invalid token '" + token + "'");
        }
        
        char c = token[0];
        if (std::isdigit(c)) {
            operandCount++;
        } else if (isOperator(c)) {
            operatorCount++;
        } else {
            throw RPNException("Error: Invalid character '" + std::string(1, c) + "'");
        }
    }
    
    if (operandCount != operatorCount + 1) {
        throw RPNException("Error: Invalid RPN expression - operands and operators mismatch");
    }
}

void RPN::performOperation(char op) {
    if (operands_.size() < 2) {
        throw RPNException("Error: Not enough operands for operation '" + std::string(1, op) + "'");
    }
    
    int b = operands_.top();
    operands_.pop();
    int a = operands_.top();
    operands_.pop();
    
    switch (op) {
        case '+':
            operands_.push(a + b);
            break;
        case '-':
            operands_.push(a - b);
            break;
        case '*':
            operands_.push(a * b);
            break;
        case '/':
            if (b == 0) {
                throw RPNException("Error: Division by zero");
            }
            operands_.push(a / b);
            break;
        default:
            throw RPNException("Error: Unknown operator '" + std::string(1, op) + "'");
    }
}

int RPN::calculate(const std::string& expression) {
    // Clear previous state
    while (!operands_.empty()) {
        operands_.pop();
    }
    
    validateExpression(expression);
    
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        char c = token[0];
        
        if (std::isdigit(c)) {
            operands_.push(c - '0');
        } else if (isOperator(c)) {
            try {
                performOperation(c);
            } catch (const RPNException& e) {
                // Add context to the error message
                throw RPNException(std::string(e.what()) + " in expression: '" + expression + "'");
            }
        }
    }
    
    if (operands_.size() != 1) {
        throw RPNException("Error: Invalid RPN expression - too many operands left");
    }
    
    return operands_.top();
}
