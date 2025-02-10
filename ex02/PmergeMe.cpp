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

void	PmergeMe::swapPairs(size_t step, size_t pos)
{
	for( size_t i = 0; i < step; i++)
		std::swap(_v[pos - i], _v[pos - i - step]);
}

size_t PmergeMe::binarySearchVector(std::vector<unsigned int> &K, size_t l, size_t r, unsigned int x, size_t step)
{
	std::cout << "SEARCHING " << x << "\n";
	std::cout << "left = " << l << "\n";
	std::cout << "right = " << r << "\n";
	std::cout << "mid = " << l + (r - l) / 2 << " (" << K[(l + (r - l) / 2) * step + step - 1] << ")\n\n";
	if (l < r)
	{
		size_t mid = l + (r - l) / 2;
        if (x > K[mid * step + step - 1])
			return (binarySearchVector(K, mid + 1, r, x, step));
		else
			return (binarySearchVector(K, l, mid, x, step));
	}
	std::cout << "RETURNED " << l * step + step - 1 << "\n";
	return (l * step + step - 1);
}

void PmergeMe::InsertVector(std::vector<unsigned int> &K, size_t i, size_t main_i,  size_t step)
{
	//std::cout << "IN STEP " << step << "\n";
	printVector();
	std::cout << "\n";
	for (size_t counter = 0; counter < step; counter++)
	{
		std::cout << "Inserted " << _v[main_i - counter] << " in " << i << "\n";
		K.insert(K.begin() + i, _v[main_i - counter]);
		std::cout << "K[i] = " << K[i] << "\n";
		printVector();
		std::cout << "\n";
	}
}

void	PmergeMe::mergeInsertVector(size_t step)
{
	if (step * 2 > _v.size())
		return;

	std::cout << "IN STEP " << step << "\n";
	// Sorts recursively the pairs ramping up their size 
	size_t	i = step * 2 - 1;
	while (i < _v.size())
	{
		if (_v[i] < _v[i - step])
			swapPairs(step, i);
		i += step * 2;
	}
	printVector();
	mergeInsertVector(step * 2);
	std::cout << "IN STEP " << step << "\n";

	// Creates a new vector to be sorted (main chain)
	std::vector<unsigned int> K;
	K.reserve(_v.size());

	// Adds the first and the greater halves of each pair to the main chain (no need to compare them)
	std::cout << "inserted from  " << *(_v.begin()) << " to " << *(_v.begin() + step - 1) << "\n";
	K.insert(K.end(),_v.begin(), _v.begin() + step - 1);
	for (size_t i = (step * 2) - 1; i < _v.size() ; i += step * 2)
	{
		std::vector<unsigned int>::iterator end = _v.begin() + i;
		std::vector<unsigned int>::iterator begin = end - step + 1;
		std::cout << "inserted from  " << *begin << " to " << *end << "\n";
		K.insert(K.end(), begin, end);
	}

	// Sets i to the next Jacobsthal Sequence number
	int lastJacob = 1;
	int currJacob = 3;
	i = (step * currJacob) - 1;
	while (i <= step * (_v.size() / step))
	{
		while (i > step * lastJacob)
		{
			//std::cout << "i = " << i << "\n";
			//InsertVector(K, \
			//binarySearchVector(K, 0, (K.size() / step) - 1, _v[i], step), i, step);
			i -= step;
		}
		i = currJacob;
		currJacob = (lastJacob * 2) + currJacob;
		lastJacob = i;
		i = (step * currJacob) - step / 2 - 1;
	}

	// Adds the non-paired leftovers to K
	K.insert(K.end(), step, *_v.begin() + step * (_v.size() / step));
	//std::swap(_v, K);
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