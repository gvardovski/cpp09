#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <sstream>
#include <limits>

class PmergeMe
{   
    private:
        std::list<int> _list;
        std::list< std::pair<int, int> > listpairs;
        std::deque<int> _deque;
        std::deque< std::pair<int, int> > dequepairs;
        clock_t starttime;
        clock_t endtime;
        int notpair;

    public:
        PmergeMe();
        PmergeMe(char **gv);
        // PmergeMe(const PmergeMe& other);
        // PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
        
        void printArguments(char **gv);
        void listCreatePairs(char **gv);
        void listSortPairs();
        void mergeSort(std::list<std::pair<int, int> >::iterator start, std::list<std::pair<int, int> >::iterator end, size_t size);
        void listInit();
        void insertIntoList();
        void insertBinSearch(std::list<int>::iterator end, int number);
        void printList();
        void printTime();
        std::list<std::pair<int, int> >::iterator getListBegin();
        std::list<std::pair<int, int> >::iterator getListEnd();
};

#endif