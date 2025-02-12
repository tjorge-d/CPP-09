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
		if (!hasOnlyDigits(sequence[i]))
			throw InvalidCharacters(sequence[i]);
		number = strtol(sequence[i], NULL, 10);
		if (number < 0)
			throw NegativeNumber();
		if (number > std::numeric_limits<unsigned int>::max())
			throw LargeNumber();
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

// GETTERS


// SETTERS


// OPERATORS

PmergeMe&	PmergeMe::operator=(const PmergeMe &copy)
{
	//std::cout << "PmergeMe copy assignment operator called\n";
	(void)copy;
	return (*this);
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

void	PmergeMe::printContainers()
{
	size_t								i = 0;
	std::list<unsigned int>::iterator	it = _l.begin();

	while (it != _l.end() && _v[i] == *it)
	{
		std::cout << _v[i];
		++i;
		++it;
		if (it != _l.end() && _v[i] == *it)
			std::cout << " ";
	}
   std::cout << std::endl;
}

void	PmergeMe::sortContainers()
{
	//sortList(newVector);
	mergeInsertVector(1);
}

void	PmergeMe::swapVectorPairs(size_t step, size_t pos)
{
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
			swapPairs(step, i);
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
	for (size_t i = pairSize; i < _v.size() ; i += pairSize)
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
			i --;
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

void	PmergeMe::sortList()
{

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