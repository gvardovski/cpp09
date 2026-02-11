#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe() : notpair(-1) {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_list = other._list;
	listpairs = other.listpairs;
	_deque = other._deque;
	dequepairs = other.dequepairs;
	starttime = other.starttime;
	endtime = other.endtime;
	notpair = other.notpair;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_list = other._list;
		listpairs = other.listpairs;
		_deque = other._deque;
		dequepairs = other.dequepairs;
		starttime = other.starttime;
		endtime = other.endtime;
		notpair = other.notpair;
	}
	return *this;
}	

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

void PmergeMe::listMergeSort(std::list<std::pair<int, int> >::iterator start, std::list<std::pair<int, int> >::iterator end, size_t size)
{
    if (size == 0 && start != end)
		size = std::distance(start, end);
    if (size <= 1)
        return; 
    size_t left = size / 2;
	size_t right = size - left;
	std::list<std::pair<int, int> >::iterator center = start;
	std::advance(center, left);
	listMergeSort(start, center, left);
	listMergeSort(center, end, right);
	std::inplace_merge(start, center, end);
}

void PmergeMe::listInit()
{
    for (std::list<std::pair<int, int> >::iterator it = listpairs.begin(); it != listpairs.end(); ++it)
		_list.push_back(it->second);
	if (!listpairs.empty())
		_list.push_front(listpairs.begin()->first);
}

void PmergeMe::insertBinSearchList(std::list<int>::iterator end, int number)
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
			insertBinSearchList(slicedelimit, pairit->first);
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
			insertBinSearchList(slicedelimit, pairit->first);
			pairit--;
		}
	}
	if (notpair != -1)
		insertBinSearchList(_list.end(), notpair);
    endtime = clock();
}

void PmergeMe::printList()
{   
    std::cout << "After: ";
    for (std::list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

std::list<std::pair<int, int> >::iterator PmergeMe::Begin() 
{
    return this->listpairs.begin();
}
std::list<std::pair<int, int> >::iterator PmergeMe::End()
{
    return this->listpairs.end();
}

void PmergeMe::printTime(size_t n)
{
    double time = static_cast<double>(endtime - starttime) / CLOCKS_PER_SEC * 1000;
	if (n == 0)
		std::cout << "Time to process a range of " << _list.size() << " elements with std::list: ";
	else
		std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque: ";
	std::cout<< time << " ms" << std::endl;
}

void PmergeMe::dequeCreatePairs(char **gv)
{
	starttime = clock();
	int i = 1;
	while (gv[i])
	{
		if (gv[i] && gv[i + 1])
		{
			std::pair<int, int> pair_temp(std::atoi(gv[i]), std::atoi(gv[i + 1]));
			dequepairs.push_back(pair_temp);
			i += 2;
		}
		else
			notpair = std::atoi(gv[i++]);
	}
}

void PmergeMe::dequeSortPairs()
{
	for (std::deque<std::pair<int, int> >::iterator it = dequepairs.begin(); it != dequepairs.end(); ++it)
	{
		if (it->first > it->second)
		{
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void PmergeMe::dequeMergeSort(std::deque<std::pair<int, int> >::iterator start, std::deque<std::pair<int, int> >::iterator end, size_t size)
{
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return; 
	size_t left = size / 2;
	size_t right = size - left;
	std::deque<std::pair<int, int> >::iterator center = start;
	std::advance(center, left);
	dequeMergeSort(start, center, left);
	dequeMergeSort(center, end, right);
	std::inplace_merge(start, center, end);
}

std::deque<std::pair<int, int> >::iterator PmergeMe::dequeBegin() 
{
	return this->dequepairs.begin();
}

std::deque<std::pair<int, int> >::iterator PmergeMe::dequeEnd()
{
	return this->dequepairs.end();
}

void PmergeMe::dequeInit()
{
	for (std::deque<std::pair<int, int> >::iterator it = dequepairs.begin(); it != dequepairs.end(); ++it)
		_deque.push_back(it->second);
	if (!dequepairs.empty())
		_deque.push_front(dequepairs.begin()->first);
}

void PmergeMe::insertBinSearchDeque(std::deque<int>::iterator end, int number)
{
	std::deque<int>::iterator it = std::lower_bound(_deque.begin(), end, number);
	_deque.insert(it, number);
}

void PmergeMe::insertIntoDeque()
{
	size_t JacobsThal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int id = 1;

	std::deque<int>::iterator slicedelimit;
	std::deque<std::pair<int, int> >::iterator pairit;
	std::deque<std::pair<int, int> >::iterator lastjacobit = dequepairs.begin();

	while (JacobsThal[id] <= dequepairs.size())
	{
		pairit = dequepairs.begin();
		std::advance(pairit, JacobsThal[id] - 1);
		lastjacobit = pairit;
		int numberofinsertions = 0;
		while (JacobsThal[id] - numberofinsertions > JacobsThal[id - 1])
		{
			slicedelimit = std::find(_deque.begin(), _deque.end(), pairit->second);
			insertBinSearchDeque(slicedelimit, pairit->first);
			pairit--;
			numberofinsertions++;
		}
		id++;
	}
	if (JacobsThal[id] != dequepairs.size())
	{
		pairit = dequepairs.end();
		if (pairit != dequepairs.begin())
			pairit--;
		while (pairit != lastjacobit)
		{
			slicedelimit = std::find(_deque.begin(), _deque.end(), pairit->second);
			insertBinSearchDeque(slicedelimit, pairit->first);
			pairit--;
		}
	}
	if (notpair != -1)
		insertBinSearchDeque(_deque.end(), notpair);
	endtime = clock();
}

void PmergeMe::printDeque()
{
	std::cout << "After: ";
	for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}