#include "test.hpp"

/* Run series of tests provided as pairs: First element is the test input,
second is the expected result. To be able to interact with the program
the input and output are redirected to string streams.
 */
void	runTests(const std::string& name, size_t total,\
			const std::pair<std::string, std::string> tests[]){
	std::cout << "\n* " << name << " *\n";
	for (size_t i = 0; i < total; i++){
		std::cout << "\nTest [" << i << "]:\n" << tests[i].first << std::endl;
		// Initialise with test input
		std::istringstream	iss(tests[i].first);
		std::ostringstream	oss;
		// Save original stream buffer
		std::streambuf*		oldCin = std::cin.rdbuf();
		std::streambuf*		oldCout = std::cout.rdbuf();
		// Redirect stream buffer to stringstreams
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
			// Retrieve output of computing
			std::string	ossContent = oss.str();
			// Restore cout to its original stream buffer
			std::cout.rdbuf(oldCout);
			if (ossContent == tests[i].second){
				std::cout << GREEN << "\nSUCCESS -- result:\n" << ossContent << RESET << std::endl;
			}
			else{
				std::cerr << RED << "\nFAILURE\nexpected:\n" << tests[i].second;
				std::cerr << "\ncalculated:\n" << ossContent << RESET << std::endl;
			}
		}
		catch(std::exception& e){
			std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		}
		// Restore cin to its original stream buffer
		std::cin.rdbuf(oldCin);
	}
	return;
}

/* Tests provided by the subject
 */
void	testSubject(void){
	std::pair<std::string, std::string>	tests[] = {
		std::make_pair("4 4 1\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "2 3 4 8\n1 7 11 12\n5 6 10 16\n9 13 14 15"),
		std::make_pair("4 4 2\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "3 4 8 12\n2 11 10 16\n1 7 6 15\n5 9 13 14"),
		std::make_pair("5 4 7\n1 2 3 4\n7 8 9 10\n13 14 15 16\n19 20 21 22\n25 26 27 28", "28 27 26 25\n22 9 15 19\n16 8 21 13\n10 14 20 7\n4 3 2 1"),
		std::make_pair("2 2 3\n1 1\n1 1", "1 1\n1 1"),
	};
	runTests("SUBJECT TEST CASES", sizeof(tests) / sizeof(tests[0]), tests);
	return;
}

/* Main for running tests
 */
int	main(void){
	testSubject();
	return 0;
}
