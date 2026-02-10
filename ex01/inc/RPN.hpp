#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>

class RPN
{
    private:
        std::stack<int> _stack;

    public:
        RPN();
        RPN(const std::string &expression);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();
        
};

#endif