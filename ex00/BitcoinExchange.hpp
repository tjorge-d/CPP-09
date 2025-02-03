#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <stdio.h>
# include <stdlib.h> 
# include <iostream>
# include <string.h>
# include <fstream>
# include <cctype>
# include <algorithm> 
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, float>	_dataBase;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &a);
		~BitcoinExchange() ;

		int	getYear(std::map<std::string, float>::iterator i);
		int	getMonth(std::map<std::string, float>::iterator i);
		int	getDay(std::map<std::string, float>::iterator i);

		BitcoinExchange&	operator=(const BitcoinExchange &copy);

		void	fetchDataBase();
		void	printDataBase();
		void	exchangeConvertion(std::string input);
		void	checkFormat(std::string line);
		void	checkYear(std::string year);
		void	checkMonth(std::string month, int year);
		void	checkDay(std::string day, int month, int year);
		void	checkValue(std::string value);
		void	convertLine(std::string date, std::string value);

	class	InputFileOpenFailure: public std::runtime_error
	{
		public:
			InputFileOpenFailure(std::string& info);
	};

	class	InputFileInvalidFormat: public std::runtime_error
	{
		public:
			InputFileInvalidFormat(std::string& info);
	};

	class	InvalidDataBase: public std::runtime_error
	{
		public:
			InvalidDataBase(std::string& info);
	};

	class	InvalidDate: public std::runtime_error
	{
		public:
			InvalidDate(std::string& info);
	};

	class	InvalidFormat: public std::runtime_error
	{
		public:
			InvalidFormat(std::string& info);
	};

	class	InvalidValue: public std::runtime_error
	{
		public:
			InvalidValue(std::string& info);
	};

	class	NegativeValue: public std::runtime_error
	{
		public:
			NegativeValue(std::string& info);
	};

	class	LargeValue: public std::runtime_error
	{
		public:
			LargeValue(std::string& info);
	};
};

#endif