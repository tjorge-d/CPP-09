#ifndef RPN_HPP
# define RPN_HPP
# include <stdio.h>
# include <iostream>
# include <string.h>
# include <fstream>
# include <stack> 

class RPN
{
	private:
		std::stack<float> _rpn;

		RPN(const RPN &a);
		RPN&	operator=(const RPN &copy);

	public:
		RPN();
		~RPN() ;

		void 	executeRPN(std::string input);
		void	executeOperation(char operation);

		class	InvalidChar : public std::runtime_error
		{
			public :
				InvalidChar(char info);
		};
		class	InvalidOperation : public std::runtime_error
		{
			public :
				InvalidOperation(char info);
		};
		class	InvalidSeparation : public std::runtime_error
		{
			public :
				InvalidSeparation();
		};
		class	InvalidResult : public std::runtime_error
		{
			public :
				InvalidResult();
		};
};

#endif