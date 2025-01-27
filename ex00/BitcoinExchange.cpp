#include "BitcoinExchange.hpp"

// CONSTRUCTORS & DESTRUCTORS

BitcoinExchange::BitcoinExchange()
{
	std::cout << "BitcoinExchange default constructor called\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	std::cout << "BitcoinExchange copy constructor called\n";
	*this = copy;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "BitcoinExchange default destructor called\n";
}

// GETTERS

// SETTERS

// OPERATORS

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	std::cout << "BitcoinExchange copy assignment operator called\n";
	(void)copy;
	//_example = copy._example;
	return (*this);
}

// MEMBER FUNCTIONS

void BitcoinExchange::getDataBase()
{
	std::fstream dbFile;
	std::string date;
	std::string value;

	dbFile.open("data.csv");
	while (dbFile.is_open())
	{
		getline(dbFile, date, ',');
		if (date.empty())
		{
			dbFile.close();
			break;
		}
		getline(dbFile, value);
		if (date != "date")
			_dataBase[date] = strtof(value.c_str(), NULL);
	}
}

void BitcoinExchange::printDataBase()
{
	for (std::map<std::string, float>::iterator i = _dataBase.begin(); i != _dataBase.end(); ++i)
		std::cout << i->first << " = " << i->second << '\n';
}

void BitcoinExchange::exchangeConvertion(std::string input)
{
	std::fstream inputFile;
	std::string year;
	std::string month;
	std::string day;
	std::string separator;
	std::string	value;

	std::cout << std::endl << "=========================================" << std::endl << std::endl;
	inputFile.open(input.c_str());
	while (inputFile.is_open())
	{
		try
		{
			getline(inputFile, year, '-');
			if (year.empty())
			{
				inputFile.close();
				break;
			}
			checkYear(year);
			std::cout << year << std::endl;

			getline(inputFile, month, '-');
			checkMonth(month);
			std::cout << month << std::endl;

			getline(inputFile, day, ' ');
			checkDay(day, atoi(month.c_str()), atoi(year.c_str()));
			std::cout << day << std::endl;

			getline(inputFile, separator, ' ');
			if (separator != "|")
				throw InvalidFormat();
			std::cout << separator << std::endl;

			getline(inputFile, value);
			checkValue(value);
			std::cout << value << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	inputFile.close();
}

void	BitcoinExchange::checkYear(std::string year)
{
	int	y = atoi(year.c_str());

	if (year.size() != 4 || y < 2009 || y > 2025)
		throw InvalidDate();
}

void	BitcoinExchange::checkMonth(std::string month)
{
	int	m = atoi(month.c_str());
	if (month.size() != 2 || m < 1 || m > 12)
		throw InvalidDate();
}

void	BitcoinExchange::checkDay(std::string day, int month, int year)
{
	int	d = atoi(day.c_str());
	if (d < 1 || d > 30 + month % 2 || (month == 2 && (year % 4) && d > 28))
		throw InvalidDate();
}

void	BitcoinExchange::checkValue(std::string value)
{
	float	v = strtof(value.c_str(), NULL);
	if (v < 0 || v > 1000)
		throw InvalidValue();
}

const char *BitcoinExchange::InputFileOpenFailure::what() const throw()
{
	return ("The vector has already reached the max capacity");
}

const char *BitcoinExchange::InvalidDate::what() const throw()
{
	return ("Invalid Date");
}

const char *BitcoinExchange::InvalidFormat::what() const throw()
{
	return ("Invalid Format");
}

const char *BitcoinExchange::InvalidValue::what() const throw()
{
	return ("Invalid Value");
}