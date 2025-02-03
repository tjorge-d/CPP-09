#include "BitcoinExchange.hpp"

// CONSTRUCTORS & DESTRUCTORS

BitcoinExchange::BitcoinExchange()
{
	//std::cout << "BitcoinExchange default constructor called\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	//std::cout << "BitcoinExchange copy constructor called\n";
	*this = copy;
}

BitcoinExchange::~BitcoinExchange()
{
	//std::cout << "BitcoinExchange default destructor called\n";
}

// GETTERS

int	BitcoinExchange::getYear(std::map<std::string, float>::iterator i)
{
	return (atoi(i->first.substr(0, 4).c_str()));
}

int	BitcoinExchange::getMonth(std::map<std::string, float>::iterator i)
{
	return (atoi(i->first.substr(5, 2).c_str()));
}

int	BitcoinExchange::getDay(std::map<std::string, float>::iterator i)
{
	return (atoi(i->first.substr(8, 2).c_str()));
}

// OPERATORS

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	std::cout << "BitcoinExchange copy assignment operator called\n";
	(void)copy;
	_dataBase = copy._dataBase;
	return (*this);
}

// MEMBER FUNCTIONS

void BitcoinExchange::fetchDataBase()
{
	std::fstream dbFile;
	std::string line;
	std::string dbName = "data.csv";

	dbFile.open(dbName.c_str());
	if (!dbFile.is_open())
		throw InvalidDataBase(dbName);
	getline(dbFile, line);
	while (getline(dbFile, line))
	{
		if (!line.empty())
			_dataBase[line.substr(0, 10)] = strtof(line.substr(11).c_str(), NULL);
	}
	dbFile.close();
}

void BitcoinExchange::printDataBase()
{
	for (std::map<std::string, float>::iterator i = _dataBase.begin(); i != _dataBase.end(); ++i)
		std::cout << i->first << " = " << i->second << '\n';
}

void BitcoinExchange::exchangeConvertion(std::string input)
{
	std::fstream inputFile;
	std::string line;

	inputFile.open(input.c_str());
	if (!inputFile.is_open())
		throw InputFileOpenFailure(input);
	getline(inputFile, line);
	if (line != "date | value")
	{
		inputFile.close(); 
		throw InputFileInvalidFormat(input);
	}
	while (getline(inputFile, line))
	{
		try
		{
			checkFormat(line);
			checkYear(line.substr(0,4));
			checkMonth(line.substr(5,2), atoi(line.substr(0,4).c_str()));
			checkDay(line.substr(8,2), atoi(line.substr(5,2).c_str()), atoi(line.substr(0,4).c_str()));
			checkValue(line.substr(13));
			convertLine(line.substr(0,10), line.substr(13));
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	inputFile.close();
}

void	BitcoinExchange::convertLine(std::string date, std::string value)
{
	std::map<std::string, float>::iterator	i;
	i = _dataBase.find(date);
	if (i == _dataBase.end())
	{
		i = _dataBase.upper_bound(date);
		if (i != _dataBase.begin())
			i--;
	}
	std::cout << date << " => " << value << " = " \
		<< (strtof(value.c_str(), NULL) * i->second) << std::endl;
}

void	BitcoinExchange::checkFormat(std::string line)
{
	if (line.length() < 14 || line.substr(10,3) != " | " \
	|| line[4] != '-' || line[7] != '-')
		throw InvalidFormat(line);
}

void	BitcoinExchange::checkYear(std::string year)
{
	int	y = atoi(year.c_str());

	if (year.size() != 4 || y < 1 || y < getYear(_dataBase.begin()))
		throw InvalidDate(std::string("year = ").append(year));
}

void	BitcoinExchange::checkMonth(std::string month, int year)
{
	int	m = atoi(month.c_str());

	if (month.size() != 2 || m < 1 || m > 12)
		throw InvalidDate(std::string("month = ").append(month));
	if (year == getYear(_dataBase.begin()) && m < getMonth(_dataBase.begin()))
		throw InvalidDate(std::string("month = ").append(month));
}

void	BitcoinExchange::checkDay(std::string day, int month, int year)
{
	int	d = atoi(day.c_str());

	if (d < 1 || (month < 8 && d > 30 + month % 2) || \
		(month >= 8 && d > 30 + (month + 1) % 2) || (month == 2 && (year % 4) && d > 28))
		throw InvalidDate(std::string("day = ").append(day));
	if (year == getYear(_dataBase.begin()) && month == getMonth(_dataBase.begin()) && \
		d < getDay(_dataBase.begin()))
		throw InvalidDate(std::string("day = ").append(day));
}

void	BitcoinExchange::checkValue(std::string value)
{
	float	v = strtof(value.c_str(), NULL);
	unsigned long i = 0;

	if (value[0] == '-' || value[0] == '+')
	{
		if(value.size() == 1)
			throw InvalidValue(value);
		i++;
	}
	if (value[i] == '.')
		throw InvalidValue(value);
	while(i < value.size())
	{ 
		if (!isdigit(value[i]) && value[i] != '.')
			throw InvalidValue(value);
		i++;
	}
	if (value[i - 1] == '.')
		throw InvalidValue(value);
	if (std::count(value.begin(), value.end(), '.') > 1)
		throw InvalidValue(value);

	if (v < 0)
		throw NegativeValue(value);
	if (v > 1000)
		throw LargeValue(value);
}

// EXCEPTIONS

BitcoinExchange::InputFileOpenFailure::InputFileOpenFailure(std::string& info) 
: std::runtime_error("The input file (" + info + ") failed to open"){}

BitcoinExchange::InputFileInvalidFormat::InputFileInvalidFormat(std::string& info)
: std::runtime_error("The input file (" + info + ") has an invalid format"){}

BitcoinExchange::InvalidDataBase::InvalidDataBase(std::string& info)
: std::runtime_error("There must be a data base named (" + info + ")"){}

BitcoinExchange::InvalidDate::InvalidDate(std::string& info)
: std::runtime_error("Invalid date (" + info + ")"){}

BitcoinExchange::InvalidFormat::InvalidFormat(std::string& info)
: std::runtime_error("Invalid data format (\"" + info + "\" > \"yyyy-mm-dd | value\")"){}

BitcoinExchange::InvalidValue::InvalidValue(std::string& info)
: std::runtime_error("The value is invalid (" + info + ")"){}

BitcoinExchange::NegativeValue::NegativeValue(std::string& info)
: std::runtime_error("The value should be positive (" + info + ")"){}

BitcoinExchange::LargeValue::LargeValue(std::string& info)
: std::runtime_error("The value should be less or equal to 1000 (" + info + ")"){}