#include "RPN.hpp"

int main(int argc, char** argv)
{
	//checks if there is an
    if (argc != 2)
	{
		std::cerr << "Error: The program must have an argument" << std::endl;
		return (2);
	}
    try
    {
        RPN rpn;
        rpn.executeRPN(argv[1]);
    }
    catch (const std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
	}
}