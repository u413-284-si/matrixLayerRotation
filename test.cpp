#include "test.hpp"

/**
 * @brief Run series of tests provided as pairs: First element is the test input,
second is the expected result. To be able to interact with the program
the input and output are redirected to string streams.
 * 
 * @param name		Name of the test series being run
 * @param total		Total number of tests
 * @param tests		Array of tests containig pairs
 */
void	runTests(const std::string& name, size_t total, const std::pair<std::string, std::string> tests[]){
	// Save original stream buffer
	std::streambuf*	oldCin = std::cin.rdbuf();
	std::streambuf*	oldCout = std::cout.rdbuf();

	std::cout << "\n* " << name << " *\n";
	for (size_t i = 0; i < total; i++){
		std::cout << "\nTest [" << i << "]:\n" << tests[i].first << std::endl;
		// Initialise input string stream with test input
		std::istringstream	iss(tests[i].first);
		std::ostringstream	oss;
		// Redirect stream buffer to string streams
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
		// Restore cout to its original stream buffer in case of exception
		std::cout.rdbuf(oldCout);
		// Restore cin to its original stream buffer
		std::cin.rdbuf(oldCin);
	}
	return;
}

/**
 * @brief Tests provided by the subject
 * 
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

/**
 * @brief Test integer overflow
 * 
 */
void	testOverflow(void){
	std::pair<std::string, std::string>	tests[] = {
		std::make_pair("2147483648 4 1\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "2 3 4 8\n1 7 11 12\n5 6 10 16\n9 13 14 15"),
		std::make_pair("4 2147483648 2\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "3 4 8 12\n2 11 10 16\n1 7 6 15\n5 9 13 14"),
		std::make_pair("5 4 2147483648\n1 2 3 4\n7 8 9 10\n13 14 15 16\n19 20 21 22\n25 26 27 28", "28 27 26 25\n22 9 15 19\n16 8 21 13\n10 14 20 7\n4 3 2 1"),
		std::make_pair("2 2 3\n2147483648 1\n1 1", "1 1\n1 1"),
		std::make_pair("-2147483649 2 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 -2147483649 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 -2147483649\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n-2147483649 1\n1 1", "1 1\n1 1"),
	};
	runTests("OVERFLOW TEST CASES", sizeof(tests) / sizeof(tests[0]), tests);
	return;
}

/**
 * @brief Test for non numeric characters
 * 
 */
void	testNonNumeric(void){
	std::pair<std::string, std::string>	tests[] = {
		std::make_pair("r 4 1\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "2 3 4 8\n1 7 11 12\n5 6 10 16\n9 13 14 15"),
		std::make_pair("4 # 2\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "3 4 8 12\n2 11 10 16\n1 7 6 15\n5 9 13 14"),
		std::make_pair("5 4 !?\n1 2 3 4\n7 8 9 10\n13 14 15 16\n19 20 21 22\n25 26 27 28", "28 27 26 25\n22 9 15 19\n16 8 21 13\n10 14 20 7\n4 3 2 1"),
		std::make_pair("2 2 3\njo 1\n1 1", "1 1\n1 1"),
	};
	runTests("NON NUMERIC TEST CASES", sizeof(tests) / sizeof(tests[0]), tests);
	return;
}

/**
 * @brief Test for empty strings
 * 
 */
void	testEmpty(void){
	std::pair<std::string, std::string>	tests[] = {
		std::make_pair(""" 4 1\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "2 3 4 8\n1 7 11 12\n5 6 10 16\n9 13 14 15"),
		std::make_pair("4 "" 2\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "3 4 8 12\n2 11 10 16\n1 7 6 15\n5 9 13 14"),
		std::make_pair("5 4 ""\n1 2 3 4\n7 8 9 10\n13 14 15 16\n19 20 21 22\n25 26 27 28", "28 27 26 25\n22 9 15 19\n16 8 21 13\n10 14 20 7\n4 3 2 1"),
		std::make_pair("2 2 3\n"" 1\n1 1", "1 1\n1 1"),
		std::make_pair("", "1 1\n1 1"),
	};
	runTests("EMPTY STRING TEST CASES", sizeof(tests) / sizeof(tests[0]), tests);
	return;
}

/**
 * @brief Test for invalid input
 * 
 */
void	testInvalid(void){
	std::pair<std::string, std::string>	tests[] = {
		std::make_pair("4 4\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "2 3 4 8\n1 7 11 12\n5 6 10 16\n9 13 14 15"),
		std::make_pair("1 4 2\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16", "3 4 8 12\n2 11 10 16\n1 7 6 15\n5 9 13 14"),
		std::make_pair("301 4 2\n1 2 3 4\n7 8 9 10\n13 14 15 16\n19 20 21 22\n25 26 27 28", "28 27 26 25\n22 9 15 19\n16 8 21 13\n10 14 20 7\n4 3 2 1"),
		std::make_pair("2 1 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 301 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("5 3 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 0\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 1000000001\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("-2 2 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 -2 3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 -3\n1 1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n1 \n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n1 0\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n1 -1\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n1 100000001\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n1 1", "1 1\n1 1"),
		std::make_pair("2 2 3\n", "1 1\n1 1"),
		std::make_pair("2 2 3\n1 1\n1 1\n1 1", "1 1\n1 1"),	
	};
	runTests("INVALID INPUT TEST CASES", sizeof(tests) / sizeof(tests[0]), tests);
	return;
}

/**
 * @brief Main for running tests
 * 
 * @return int	0 for successful execution
 */
int	main(void){
	testSubject();
	testOverflow();
	testNonNumeric();
	testEmpty();
	testInvalid();
	return 0;
}
