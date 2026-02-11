#include "inc/PmergeMe.hpp"

int main(int gc, char** gv)
{
    if (gc < 2)
        return (std::cerr << "Error: Not enough arguments" << std::endl, 1);
    try
    {
        PmergeMe pmergeMe(gv);
        pmergeMe.printArguments(gv);
        pmergeMe.listCreatePairs(gv);
        pmergeMe.listSortPairs();
        pmergeMe.mergeSort(pmergeMe.getListBegin(), pmergeMe.getListEnd(), 0);
        pmergeMe.listInit();
        pmergeMe.insertIntoList();
        pmergeMe.printList();
        pmergeMe.printTime();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}