#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(char **gv)
{
    for (int i = 1; gv[i] != NULL; ++i)
    {
        std::istringstream iss(gv[i]);
        int num;
        while (iss >> num)
        {
            if (num < 0)
                throw std::invalid_argument("Error: Negative numbers are not allowed");
            _list.push_back(num);
            _deque.push_back(num);
        }
    }
}

void PmergeMe::printArguments()
{
    std::cout << "List before: ";
    for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Deque before: ";
    for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

PmergeMe::~PmergeMe(){}