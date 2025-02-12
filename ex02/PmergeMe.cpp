#include "PmergeMe.hpp"

// CONSTRUCTORS & DESTRUCTORS

PmergeMe::PmergeMe()
{
	//std::cout << "PmergeMe default constructor called\n";
}

PmergeMe::PmergeMe(char** sequence, size_t size)
{
	if (size < 2)
		throw InvalidNumberOfArguments();

	long number ;
	_v.reserve(size - 1);
	for (size_t i = 0; i < size; i++)
	{
		// Checks the validity of an argument
		if (!hasOnlyDigits(sequence[i]) || sequence[i][0] == '\0')
			throw InvalidCharacters(sequence[i]);
		number = strtol(sequence[i], NULL, 10);
		if (number < 0)
			throw NegativeNumber();
		if (number > std::numeric_limits<unsigned int>::max())
			throw LargeNumber();

		// Inserts the arguments if they are valid
		_v.insert(_v.end(), number);
		_l.insert(_l.end(), number);
	}
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	//std::cout << "PmergeMe copy constructor called\n";
	*this = copy;
}

PmergeMe::~PmergeMe()
{
	//std::cout << "PmergeMe default destructor called\n";
}

// OPERATORS

PmergeMe&	PmergeMe::operator=(const PmergeMe &copy)
{
	//std::cout << "PmergeMe copy assignment operator called\n";
	(void)copy;
	return (*this);
}

// GETTERS

long	PmergeMe::getLTime()
{
	return (_lTime);
}

long	PmergeMe::getVTime()
{
	return (_vTime);
}

size_t	PmergeMe::getContainerSize()
{
	return (_l.size());
}

// MEMBER FUNCTIONS

bool	PmergeMe::hasOnlyDigits(char* str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

void	PmergeMe::printVector()
{
	for (size_t i = 0; i < _v.size(); i++)
	{
		std::cout << _v[i];
		if (i < _v.size() - 1)
			std::cout << " ";
	}
   std::cout << std::endl;
}

void	PmergeMe::printList()
{
	for (std::list<unsigned int>::iterator it = _l.begin(); it != _l.end(); it++)
	{
		std::cout << *it;
		if (it != _l.end())
			std::cout << " ";
	}
   std::cout << std::endl;
}

void	PmergeMe::checkSort()
{
	size_t								i = 1;
	std::list<unsigned int>::iterator	it = _l.begin();
	std::list<unsigned int>::iterator	Pit = _l.begin();
	it++;

	while (i < _v.size())
	{
		if (*it < *Pit)
			throw UnsortedContainer("list");
		if (_v[i] < _v[i - 1])
			throw UnsortedContainer("vector");
		i++;
		it++;
		Pit++;
	}
}

void	PmergeMe::sortContainers()
{
	struct timeval				start;
	struct timeval				end;

	// Sorts the list and measures the time elapsed
	gettimeofday(&start, NULL);
	mergeInsertList(1);
	gettimeofday(&end, NULL);
	_lTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

	// Sorts the vector and measures the time elapsed
	gettimeofday(&start, NULL);
	mergeInsertVector(1);
	gettimeofday(&end, NULL);
	_vTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

void	PmergeMe::swapVectorPairs(size_t step, size_t pos)
{
	// Swaps the pairs without breaking them 
	for( size_t i = 0; i < step; i++)
		std::swap(_v[pos - i], _v[pos - i - step]);
}

size_t PmergeMe::binarySearchVector(std::vector<unsigned int> &K, unsigned int x, size_t step)
{
	size_t left = 0;
	size_t right = K.size() / step;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		if (K[mid * step + step - 1] < x)
			left = mid + 1;
        else
			right = mid;
	}
	return (left);
}

void	PmergeMe::mergeInsertVector(size_t step)
{
	// Stop recursivety
	if (step * 2 > _v.size())
		return;
	
	// Sorts recursively the pairs ramping up their size 
	size_t	i = step * 2 - 1;
	while (i < _v.size())
	{
		if (_v[i] < _v[i - step])
			swapVectorPairs(step, i);
		i += step * 2;
	}
	mergeInsertVector(step * 2);

	// Creates a new vector to be sorted (main chain)
	std::vector<unsigned int> K;
	std::vector<unsigned int>::iterator begin = _v.begin();
	std::vector<unsigned int>::iterator end = begin + step;
	size_t	pairSize = step * 2;
	K.reserve(_v.size());

	// Adds the first and the greater halves of each pair to the main chain (no need to compare them)
	K.insert(K.end(), begin, end);
	for (i = pairSize; i < _v.size() ; i += pairSize)
	{
		begin = _v.begin() + i - step;
		end = begin + step;
		K.insert(K.end(), begin, end);
	}

	// Iterates through the Vector in the Jacobsthal Sequence order
	size_t	lastJacob = 1;
	size_t	currJacob = 3;
	size_t	vecSize =  _v.size() / pairSize;
	vecSize += (_v.size() / step != vecSize * 2) ;
	i = currJacob;
	if (i > vecSize)
			i = vecSize;	
	while (lastJacob <= vecSize)
	{
		// Inserts the lower halves into the main chain
		while (i > lastJacob)
		{
			begin =  _v.begin() + (i * pairSize - pairSize);
			end = begin + step;
			K.insert(K.begin() + binarySearchVector(K, _v[i * pairSize - step - 1], step) * step, begin, end);
			i--;
		}
		i = currJacob;
		currJacob = (lastJacob * 2) + currJacob;
		lastJacob = i;
		i = currJacob;
		if (lastJacob <= vecSize && i > vecSize)
			i = vecSize;
	}

	// Adds the non-paired leftovers to K
	K.insert(K.end(), _v.begin() + K.size(), _v.end());
	std::swap(_v, K);
}

void	PmergeMe::swapListPairs(size_t step, std::list<unsigned int>::iterator it, std::list<unsigned int>::iterator Pit)
{
	std::swap(*it, *Pit);
	for( size_t i = 0; i < step - 1; i++)
	{
		std::advance(it, -1);
		std::advance(Pit, -1);
		std::swap(*it, *Pit);
	}
}

size_t	PmergeMe::binarySearchList(std::list<unsigned int> &K, unsigned int x, size_t step)
{
	size_t left = 0;
	size_t right = K.size() / step;
	std::list<unsigned int>::iterator it;

	while (left < right)
	{
		size_t mid = left + (right - left) / 2;
		it = K.begin();
		advance(it, mid * step + step - 1);
		if (*it < x)
			left = mid + 1;
        else
			right = mid;
	}
	return (left);
}

void	PmergeMe::mergeInsertList(size_t step)
{
	// Stop recursivety
	if (step * 2 > _l.size())
		return;
	
	// Sorts recursively the pairs ramping up their size
	std::list<unsigned int>::iterator it;
	std::list<unsigned int>::iterator Pit;
	size_t	i = step * 2 - 1;
	while (i < _l.size())
	{
		it = _l.begin();
		advance(it, i);
		Pit = _l.begin();
		advance(Pit, i - step);
		if (*it < *Pit)
			swapListPairs(step, it, Pit);
		i += step * 2;
	}
	mergeInsertList(step * 2);

	// Creates a new list to be sorted (main chain)
	std::list<unsigned int> K;
	std::list<unsigned int>::iterator begin = _l.begin();
	std::list<unsigned int>::iterator end = begin;
	advance(end, step);
	size_t	pairSize = step * 2;

	// Adds the first and the greater halves of each pair to the main chain (no need to compare them)
	K.insert(K.end(), begin, end);
	for (i = pairSize; i < _l.size() ; i += pairSize)
	{
		begin = _l.begin();
		advance(begin, i - step);
		end = begin;
		advance(end, step);
		K.insert(K.end(), begin, end);
	}

	// Iterates through the List in the Jacobsthal Sequence order
	size_t	lastJacob = 1;
	size_t	currJacob = 3;
	size_t	listSize =  _l.size() / pairSize;
	listSize += (_l.size() / step != listSize * 2) ;
	i = currJacob;
	if (i > listSize)
			i = listSize;	
	while (lastJacob <= listSize)
	{
		// Inserts the lower halves into the main chain
		while (i > lastJacob)
		{
			begin = _l.begin();
			advance(begin, i * pairSize - pairSize);
			end = begin;
			advance(end, step);
			it = _l.begin();
			advance(it, i * pairSize - step - 1);
			Pit = K.begin();
			advance(Pit, binarySearchList(K, *it, step) * step);
			K.insert(Pit, begin, end);
			i--;
		}
		i = currJacob;
		currJacob = (lastJacob * 2) + currJacob;
		lastJacob = i;
		i = currJacob;
		if (lastJacob <= listSize && i > listSize)
			i = listSize;
	}

	// Adds the non-paired leftovers to K
	begin = _l.begin();
	advance(begin, K.size());
	K.insert(K.end(), begin, _l.end());
	std::swap(_l, K);
}

// EXCEPTIONS

PmergeMe::InvalidNumberOfArguments::InvalidNumberOfArguments() :
runtime_error("The program must have at least 2 arguments to sort"){}

PmergeMe::NegativeNumber::NegativeNumber() :
runtime_error("An element is negative"){}

PmergeMe::LargeNumber::LargeNumber() :
runtime_error("An element is greater than the maximum unsigned integer"){}

PmergeMe::InvalidCharacters::InvalidCharacters(std::string info) :
runtime_error("An element has an invalid charater (" + std::string(info) + ")"){}

PmergeMe::UnsortedContainer::UnsortedContainer(std::string info) :
runtime_error("The " + std::string(info) + " is unsorted"){}