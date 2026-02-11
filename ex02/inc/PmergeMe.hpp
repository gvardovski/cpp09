#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <sstream>

class PmergeMe
{   
    private:
        std::list<int> _list;
        std::deque<int> _deque;

    public:
        PmergeMe();
        PmergeMe(char **gv);
        // PmergeMe(const PmergeMe& other);
        // PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
        
        void printArguments();
};

#endif