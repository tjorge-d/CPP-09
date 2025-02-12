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
		std::vector<unsigned int>	_v;
		std::list<unsigned int>		_l;
		
		PmergeMe();
		PmergeMe(const PmergeMe &a);

		bool	hasOnlyDigits(char* str);
		void	sortList();

		void	mergeInsertVector(size_t step);
		void	swapVectorPairs(size_t step, size_t pos);
		size_t	binarySearchVector(std::vector<unsigned int> &K, unsigned int x, size_t step);

		void	mergeInsertList(size_t step);
		void	swapListPairs(size_t step, size_t pos);
		size_t	binarySearchList(std::List<unsigned int> &K, unsigned int x, size_t step);


	public:
		PmergeMe(char** sequence, size_t size);
		~PmergeMe() ;

		PmergeMe&	operator=(const PmergeMe &copy);

		void	printContainers();
		void	printVector();
		void	sortContainers();

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
	class	InvalidCharacters : public std::runtime_error
	{
		public :
			InvalidCharacters(std::string info);
	};
};

#endif