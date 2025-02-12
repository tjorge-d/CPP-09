#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	try
	{
		PmergeMe	FordJohnson(argv + 1, argc - 1);

		std::cout << "Before:	";
		FordJohnson.printVector();

		FordJohnson.sortContainers();
		FordJohnson.checkSort();

		std::cout << "After:	";
		FordJohnson.printList();

		std::cout << "Time to process a range of " << FordJohnson.getContainerSize() \
		<< " elements with std::list : " << FordJohnson.getLTime() << " μs" << std::endl;
		std::cout << "Time to process a range of " << FordJohnson.getContainerSize() \
		<< " elements with std::vector : " << FordJohnson.getVTime() << " μs" << std::endl;
	}
	catch(const std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}
}