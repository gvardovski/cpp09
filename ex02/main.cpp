#include "inc/PmergeMe.hpp"

int main(int gc, char** gv)
{
    if (gc < 2)
        return (std::cerr << "Error: Not enough arguments" << std::endl, 1);
    try
    {
        PmergeMe pmergeMe(gv);
        pmergeMe.printArguments();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}