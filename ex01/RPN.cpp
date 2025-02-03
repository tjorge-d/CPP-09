#include "RPN.hpp"

// CONSTRUCTORS & DESTRUCTORS

RPN::RPN()
{
	//std::cout << "RPN default constructor called\n";
}

RPN::RPN(const RPN &copy)
{
	//std::cout << "RPN copy constructor called\n";
	*this = copy;
}

RPN::~RPN()
{
	//std::cout << "RPN default destructor called\n";
}

// OPERATORS

RPN&	RPN::operator=(const RPN &copy)
{
	//std::cout << "RPN copy assignment operator called\n";
	(void)copy;
	return (*this);
}

// MEMBER FUNCTIONS

void RPN::executeRPN(std::string input)
{
	std::string digits = "01*3456789";
	std::string	operations = "+-/*";
	unsigned long lenght = input.size();

	for (unsigned long i = 0; i < lenght; i++)
	{
		//iteration through whitespaces
		while (i < lenght && isspace(input[i]))
			i++;
		if (i == lenght)
			break;
		//checks for signed digits
		if ((input[i] == '-') && i + 1 < lenght && isdigit(input[i + 1]))
			_rpn.push(-(input[++i] - 48));
		else if ((input[i] == '+') && i + 1 < lenght && isdigit(input[i + 1]))
			_rpn.push(input[++i] - 48);
		//checks if its a digit
		else if (isdigit(input[i]))
			_rpn.push(input[i] - 48);
		//checks if it's an operation 
		else if (operations.find(input[i]) != std::string::npos)
			executeOperation(input[i]);
		else
			throw InvalidChar(input[i]);
		//checks if there is a valid separation between arguments
		if (++i < lenght && !isspace(input[i]))
			throw InvalidSeparation();
	}
	if (_rpn.size() != 1)
		throw InvalidResult();
	std::cout << _rpn.top() << std::endl;
}

void	RPN::executeOperation(char operation)
{
	if (_rpn.size() < 2)
		throw InvalidOperation(operation);
	switch (operation)
	{
		case '+':
			additionOperation();
			break;
		case '-':
			subtractionOperation();
			break;
		case '/':
			divisionOperation();
			break;
		case '*':
			multiplicationOperation();
			break;
	}

}

void	RPN::additionOperation()
{
	float	x = _rpn.top();
	_rpn.pop();
	float	y = _rpn.top();
	_rpn.pop();
	_rpn.push(x + y);
	//std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void	RPN::subtractionOperation()
{
	float	x = _rpn.top();
	_rpn.pop();
	float	y = _rpn.top();
	_rpn.pop();
	_rpn.push(y - x);
	//std::cout << x << " - " << y << " = " << x - y << std::endl;
}

void	RPN::divisionOperation()
{
	float	x = _rpn.top();
	_rpn.pop();
	float	y = _rpn.top();
	_rpn.pop();
	_rpn.push(y / x);
	//std::cout << x << " / " << y << " = " << x / y << std::endl;
}

void	RPN::multiplicationOperation()
{
	float	x = _rpn.top();
	_rpn.pop();
	float	y = _rpn.top();
	_rpn.pop();
	_rpn.push(x * y);
	//std::cout << x << " * " << y << " = " << x * y << std::endl;
}

// EXCEPTIONS

RPN::InvalidChar::InvalidChar(char info)
: runtime_error("Invalid char found (" + std::string(1, info) + ")"){}

RPN::InvalidOperation::InvalidOperation(char info)
: runtime_error("Not enough elements in the stack to perform an operation (" + std::string(1, info) + ")"){}

RPN::InvalidResult::InvalidResult()
: runtime_error("Not enough operations to get a final result"){}

RPN::InvalidSeparation::InvalidSeparation()
: runtime_error("Each element must be separated by whitespaces"){}