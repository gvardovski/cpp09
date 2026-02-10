#include "../inc/RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN& other)
{
    _stack = other._stack;
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::RPN(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error: Invalid RPN expression");
            int b = _stack.top(); 
            _stack.pop();
            int a = _stack.top(); 
            _stack.pop();
            if (token == "+") 
                _stack.push(a + b);
            else if (token == "-") 
                _stack.push(a - b);
            else if (token == "*")
                _stack.push(a * b);
            else
                _stack.push(a / b);
        }
        else
        {
            std::istringstream ss(token);
            unsigned int num;
            ss >> num;
            if (ss.fail())
                throw std::runtime_error("Error: Invalid token in RPN expression");
            if (num > 9)
                throw std::runtime_error("Error: Arguments must be single-digit numbers"); 
            _stack.push(num);
        }
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error: Invalid RPN expression");
    std::cout << "Result: " << _stack.top() << std::endl;
}

RPN::~RPN(){}