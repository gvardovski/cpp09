#include "inc/PmergeMe.hpp"

int main(int gc, char** gv)
{
    if (gc < 2)
        return (std::cerr << "Error: Not enough arguments" << std::endl, 1);
    try
    {
        PmergeMe pmergeMeList(gv);
        pmergeMeList.printArguments(gv);
        pmergeMeList.listCreatePairs(gv);
        pmergeMeList.listSortPairs();
        pmergeMeList.listMergeSort(pmergeMeList.Begin(), pmergeMeList.End(), 0);
        pmergeMeList.listInit();
        pmergeMeList.insertIntoList();
        pmergeMeList.printList();
        pmergeMeList.printTime(0);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    try
    {
        PmergeMe pmergeMeDeque;
        pmergeMeDeque.dequeCreatePairs(gv);
        pmergeMeDeque.dequeSortPairs();
        pmergeMeDeque.dequeMergeSort(pmergeMeDeque.dequeBegin(), pmergeMeDeque.dequeEnd(), 0);
        pmergeMeDeque.dequeInit();
        pmergeMeDeque.insertIntoDeque();
        pmergeMeDeque.printDeque();
        pmergeMeDeque.printTime(1);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}