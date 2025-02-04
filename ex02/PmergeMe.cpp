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
		number = strtol(sequence[i], NULL, 10);
		if (number < 0)
			throw NegativeNumber();
		if (number > std::numeric_limits<unsigned int>::max())
			throw LargeNumber();
		_v.insert(_v.end(), number);
		_l.insert(_l.end(), number);
	}
}

void	PmergeMe::printContainer()
{
	size_t						i = 0;
	std::list<int>::iterator	it = _l.begin();

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

// EXCEPTIONS

PmergeMe::InvalidNumberOfArguments::InvalidNumberOfArguments() :
runtime_error("The program must have at least 2 arguments to sort"){}

PmergeMe::NegativeNumber::NegativeNumber() :
runtime_error("An element is negative"){}

PmergeMe::LargeNumber::LargeNumber() :
runtime_error("An element is greater than the maximum unsigned integer"){}