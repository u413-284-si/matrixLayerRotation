#include "utilities.hpp"

/* Remove spaces at the beginning of the string str.
 */
std::string ltrim(const std::string& str) {
    std::string s(str);

    s.erase(
        s.begin(),
        std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace)))
    );

    return s;
}

/* Remove spaces from the end of the string str.
 */
std::string rtrim(const std::string &str) {
    std::string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

/* Split main string str by spaces and save substrings into a string vector.
Skips intermediary spaces.
 */
std::vector<std::string> split(const std::string &str) {
    std::vector<std::string> tokens;

    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while ((end = str.find(" ", start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
		while (str.at(end + 1) == ' ')
			end += 1;
        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

/* Print matrix elements separated by a space to standard output line by line.
 */
void	printMatrix(const std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols){
	for (int y = 0; y < nRows; y++){
		for (int x = 0; x < nCols; x++)
			std::cout << matrix[y][x] << " ";
		std::cout << std::endl;
	}
	return;
}
