#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(char **gv)
{
    for (int i = 1; gv[i] != NULL; ++i)
    {
        std::istringstream iss(gv[i]);
        long int num;
        if (!(iss >> num))
            throw std::invalid_argument("Error: Invalid number format");
        if (num < 0)
            throw std::invalid_argument("Error: Negative numbers are not allowed");
        if (num > std::numeric_limits<int>::max())
            throw std::out_of_range("Error: Number is too large");
    }
    notpair = -1;
}

void PmergeMe::printArguments(char **gv)
{
    std::cout << "Before: ";
    for (int i = 1; gv[i] != NULL; ++i)
        std::cout << gv[i] << " ";
    std::cout << std::endl;
}

PmergeMe::~PmergeMe(){}

void PmergeMe::listCreatePairs(char **gv)
{
    starttime = clock();
    int i = 1;
	while (gv[i])
	{
		if (gv[i] && gv[i + 1])
		{
			std::pair<int, int> pair(std::atoi(gv[i]), std::atoi(gv[i + 1]));
			listpairs.push_back(pair);
			i += 2;
		}
		else
			notpair = std::atoi(gv[i++]);
	}
}

void PmergeMe::listSortPairs()
{
    for (std::list<std::pair<int, int> >::iterator it = listpairs.begin(); it != listpairs.end(); ++it)
	{
		if (it->first > it->second)
		{
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void PmergeMe::mergeSort(std::list<std::pair<int, int> >::iterator start, std::list<std::pair<int, int> >::iterator end, size_t size)
{
    if (size == 0 && start != end)
		size = std::distance(start, end);
    if (size <= 1)
        return; 
    size_t left = size / 2;
	size_t right = size - left;
	std::list<std::pair<int, int> >::iterator center = start;
	std::advance(center, left);
	mergeSort(start, center, left);
	mergeSort(center, end, right);
	std::inplace_merge(start, center, end);
}

void PmergeMe::listInit()
{
    for (std::list<std::pair<int, int> >::iterator it = listpairs.begin(); it != listpairs.end(); ++it)
		_list.push_back(it->second);
	if (!listpairs.empty())
		_list.push_front(listpairs.begin()->first);
}

void PmergeMe::insertBinSearch(std::list<int>::iterator end, int number)
{
    std::list<int>::iterator it = std::lower_bound(_list.begin(), end, number);
    _list.insert(it, number);
}

void PmergeMe::insertIntoList()
{
    size_t JacobsThal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int id = 1;

	std::list<int>::iterator slicedelimit;
	std::list<std::pair<int, int> >::iterator pairit;
	std::list<std::pair<int, int> >::iterator lastjacobit = listpairs.begin();

	while (JacobsThal[id] <= listpairs.size())
	{
		pairit = listpairs.begin();
		std::advance(pairit, JacobsThal[id] - 1);
		lastjacobit = pairit;
		int numberofinsertions = 0;
		while (JacobsThal[id] - numberofinsertions > JacobsThal[id - 1])
		{
			slicedelimit = std::find(_list.begin(), _list.end(), pairit->second);
			insertBinSearch(slicedelimit, pairit->first);
			pairit--;
			numberofinsertions++;
		}
		id++;
	}
	if (JacobsThal[id] != listpairs.size())
	{
		pairit = listpairs.end();
		if (pairit != listpairs.begin())
			pairit--;
		while (pairit != lastjacobit)
		{
			slicedelimit = std::find(_list.begin(), _list.end(), pairit->second);
			insertBinSearch(slicedelimit, pairit->first);
			pairit--;
		}
	}
	if (notpair != -1)
		insertBinSearch(_list.end(), notpair);
    endtime = clock();
}

void PmergeMe::printList()
{   
    std::cout << "After: ";
    for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

std::list<std::pair<int, int> >::iterator PmergeMe::getListBegin() 
{
    return this->listpairs.begin();
}
std::list<std::pair<int, int> >::iterator PmergeMe::getListEnd()
{
    return this->listpairs.end();
}

void PmergeMe::printTime()
{
    double time = static_cast<double>(endtime - starttime) / CLOCKS_PER_SEC * 1000;
    std::cout << "Time to process a range of " << _list.size() << " elements : " << time << " ms" << std::endl;
}