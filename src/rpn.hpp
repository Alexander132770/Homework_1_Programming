#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>

class RPN {
public:
    RPN();
    int calculate(const std::string& expression);
    
private:
    std::stack<int> operands_;
    
    bool isOperator(char c) const;
    void performOperation(char op);
    void validateExpression(const std::string& expression) const;
};

class RPNException : public std::runtime_error {
public:
    explicit RPNException(const std::string& message) : std::runtime_error(message) {}
};

#endif // RPN_HPP
