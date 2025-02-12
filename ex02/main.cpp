#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	try
	{
		PmergeMe	A(argv + 1, argc - 1);
		std::cout << "Before:	";
		A.printVector();
		A.sortContainers();
		A.checkSort();
		std::cout << "After:\n";
		A.printList();
		A.printVector();
	}
	catch(const std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}
}