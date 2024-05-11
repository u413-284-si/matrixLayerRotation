#include "test.hpp"

void	runTests(const std::string& name, size_t total,\
			const std::pair<std::string, std::string> tests[]){
	int					passed = 0;

	std::cout << "\n* " << name << " *\n";
	for (size_t i = 0; i < total; i++){
		std::cout << "Test [" << i << "]:\n" << tests[i].first << std::endl;
		std::istringstream	iss(tests[i].first);
		std::ostringstream	oss;
		std::streambuf*		oldCin = std::cin.rdbuf();
		std::streambuf*		oldCout = std::cout.rdbuf();
		
		std::cin.rdbuf(iss.rdbuf());
		std::cout.rdbuf(oss.rdbuf());
		try{
			int		nRows, nCols, nRotations;
			bool	constMatrix = true;

			parseMatrixConditions(nRows, nCols, nRotations);
			std::vector<std::vector<int>>	matrix(nRows);
			parseMatrixElements(matrix, nRows, nCols, constMatrix);
			if (constMatrix)
				printMatrix(matrix, nRows, nCols);
			else
				matrixRotation(matrix, nRotations);

			std::string	ossContent = oss.str();
			std::cout.rdbuf(oldCout);
			if (ossContent == tests[i].second){
				std::cout << GREEN << "\nSUCCESS -- result:\n" << ossContent << RESET << std::endl;
				passed++;
			}
			else{
				std::cerr << RED << "\nFAILURE\nexpected:\n" << tests[i].second;
				std::cerr << "\ncalculated:\n" << ossContent << RESET << std::endl;
			}
		}
		catch(std::exception& e){
			std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		}
		std::cin.rdbuf(oldCin);
	}
	return;
}

void	testSubject(void){
	std::pair<std::string, std::string>	tests[] = {
		std::make_pair("4 4 2\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "3 4 8 12\n2 11 10 16\n1 7 6 15\n5 9 13 14"),
	};
	runTests("SUBJECT TEST CASES", sizeof(tests) / sizeof(tests[0]), tests);
	return;
}

int	main(void){
	testSubject();
	return 0;
}
