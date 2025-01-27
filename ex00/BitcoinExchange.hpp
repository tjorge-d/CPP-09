#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <stdio.h>
# include <stdlib.h> 
# include <iostream>
# include <string.h>
# include <fstream>
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, float>	_dataBase;
		std::map<std::string, float>	_input;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &a);
		~BitcoinExchange() ;

		BitcoinExchange&	operator=(const BitcoinExchange &copy);

		void	getDataBase();
		void	printDataBase();
		void	exchangeConvertion(std::string input);
		void	checkYear(std::string year);
		void	checkMonth(std::string month);
		void	checkDay(std::string day, int month, int year);
		void	checkValue(std::string value);

	class	InputFileOpenFailure: public std::exception
	{
		virtual const char* what() const throw();
	};

	class	InvalidDate: public std::exception
	{
		virtual const char* what() const throw();
	};

	class	InvalidFormat: public std::exception
	{
		virtual const char* what() const throw();
	};

	class	InvalidValue: public std::exception
	{
		virtual const char* what() const throw();
	};
};

#endif