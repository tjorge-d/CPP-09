#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: The program must have exactly one argument" << std::endl;
		return (2);
	}
	try
	{
		BitcoinExchange btc;
		btc.fetchDataBase();
		btc.exchangeConvertion(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}

	return (0);
}
