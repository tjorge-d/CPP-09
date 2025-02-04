#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <string.h>
# include <fstream>
# include <vector>
# include <list>
# include <limits>

class PmergeMe
{
	private:
		std::vector<int>	_v;
		std::list<int>		_l;
		
		PmergeMe();
		PmergeMe(const PmergeMe &a);

	public:
		PmergeMe(char** sequence, size_t size);
		~PmergeMe() ;

		PmergeMe&	operator=(const PmergeMe &copy);

		void	printContainer();
		void	sort();

	class	InvalidNumberOfArguments : public std::runtime_error
	{
		public :
			InvalidNumberOfArguments();
	};
	class	NegativeNumber : public std::runtime_error
	{
		public :
			NegativeNumber();
	};
	class	LargeNumber : public std::runtime_error
	{
		public :
			LargeNumber();
	};
};

#endif