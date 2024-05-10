// Libraries
#include <iostream>
#include <algorithm>
#include <functional>		//not1
#include <vector>
#include <stdexcept>
#include <cstring>

// ANSI color codes
# define RESET   "\033[0m"
# define RED     "\033[31m"    

// Error definitions
# define INV_ARG_NUM "invalid number of arguments provided\nexpected: m n r"
# define INV_MTX_DIM "invalid matrix dimension provided\nexpected: 2 <= m, n <= 300"
# define INV_ROT_DIM "invalid rotation dimension provided\nexpected: 1 <= r <= 10⁹"
# define INV_MTX_MIN "invalid matrix dimension provided\nexpected: min(m, n) to be even"
# define INV_ROW_SZ	"invalid number of elements in row"
# define INV_ELEM_DIM "invalid matrix element dimension provided\n expected: 1 <= element <= 10⁸"

// Function declarations
std::string 				ltrim(const std::string&);
std::string 				rtrim(const std::string&);
std::vector<std::string>	split(const std::string&);
void 						matrixRotation(std::vector<std::vector<int>> matrix, int r);
void						checkMatrixConditions(const std::vector<std::string>& input, int& m, int& n, int& r);
void						checkRowSize(const std::vector<std::string>& matrixRow, const int& n);
void						checkMatrixElements(const int& element);
void						parseMatrixConditions(int& m, int& n, int& r);
void						parseMatrixElements(std::vector<std::vector<int>>& matrix, const int& m, const int& n, bool& constMatrix);
void						printMatrix(const std::vector<std::vector<int>>& matrix, const int& m, const int& n);

int main(void)
{
	int		m, n, r;
	bool	constMatrix = true;

	try{
		parseMatrixConditions(m, n, r);
		std::vector<std::vector<int>>	matrix(m);
		parseMatrixElements(matrix, m, n, constMatrix);
		std::cout << "\nOutput:\n";
		if (constMatrix)
			printMatrix(matrix, m, n);
		else
	    	matrixRotation(matrix, r);
	}
	catch(std::exception& e){
		std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		return 1;
	}
    return 0;
}

void matrixRotation(std::vector<std::vector<int>> matrix, int r){
	int	m = matrix.size();
	int	n = matrix[0].size();
	int	cycleNum = std::min(m, n) / 2;
	int	cycleArr[cycleNum][2 * (m + n) - 4];
	int	cycle, cycleLen, i, x, y;

	std::memset(cycleArr, 0, sizeof(cycleArr));
	for (cycle = 0; cycle < cycleNum; cycle++){
		i = 0;
		x = y = cycle;
		for (; y < m - cycle - 1; y++)
			cycleArr[cycle][i++] = matrix[y][x];
		for (; x < n - cycle - 1; x++)
			cycleArr[cycle][i++] = matrix[y][x];
		for (; y > cycle; y--)
			cycleArr[cycle][i++] = matrix[y][x];
		for (; x > cycle; x--)
			cycleArr[cycle][i++] = matrix[y][x];
	}

	for (cycle = 0; cycle < cycleNum; cycle++){
		cycleLen = 2 * ((m - 2 * cycle) + (n - 2 * cycle)) - 4;
		if (r == cycleLen)
			continue;
		i = cycleLen - r % cycleLen;
		x = y = cycle;
		for (; y < m - cycle - 1; y++)
			matrix[y][x] = cycleArr[cycle][i++ % cycleLen];
		for (; x < n - cycle -1; x++)
			matrix[y][x] = cycleArr[cycle][i++ % cycleLen];
		for (; y > cycle; y--)
			matrix[y][x] = cycleArr[cycle][i++ % cycleLen];
		for (; x > cycle; x--)
			matrix[y][x] = cycleArr[cycle][i++ % cycleLen];
	}
	printMatrix(matrix, m, n);
	return;
}

// Input checking
void	checkMatrixConditions(const std::vector<std::string>& input, int& m, int& n, int& r){
	if (input.size() != 3)
		throw std::invalid_argument(INV_ARG_NUM);

	m = stoi(input[0]);
	if (m < 2 || m > 300)
		throw std::invalid_argument(INV_MTX_DIM);
	n = stoi(input[1]);
	if (n < 2 || n > 300)
		throw std::invalid_argument(INV_MTX_DIM);
	if (std::min(m, n) % 2 != 0)
		throw std::invalid_argument(INV_MTX_MIN);

	r = stoi(input[2]);
	if (r < 1 || r > 1e9)
		throw std::invalid_argument(INV_ROT_DIM);
	return;
}

void	checkRowSize(const std::vector<std::string>& matrixRow, const int& n){
	if (static_cast<int>(matrixRow.size()) != n)
		throw std::invalid_argument(INV_ROW_SZ);
	return;
}

void	checkMatrixElements(const int& element){
	if (element < 1 || element > 1e8)
		throw std::invalid_argument(INV_ELEM_DIM);
	return;
}

void	parseMatrixConditions(int& m, int& n, int& r){
    std::string	firstMultipleInputTemp;

	std::getline(std::cin, firstMultipleInputTemp);
    std::vector<std::string> firstMultipleInput = split(ltrim(rtrim(firstMultipleInputTemp)));
	checkMatrixConditions(firstMultipleInput, m, n, r);
	return;
}

void	parseMatrixElements(std::vector<std::vector<int>>& matrix, const int& m, const int& n, bool& constMatrix){
	int	firstElement;

	for (int i = 0; i < m; i++) {
        matrix[i].resize(n);
        std::string matrixRowTempTemp;
        std::getline(std::cin, matrixRowTempTemp);
        std::vector<std::string> matrixRowTemp = split(ltrim(rtrim(matrixRowTempTemp)));
		checkRowSize(matrixRowTemp, n);

		for (int j = 0; j < n; j++) {
			int matrixRowItem = stoi(matrixRowTemp[j]);
			checkMatrixElements(matrixRowItem);
			if (i == 0 && j == 0)
				firstElement = matrixRowItem;
			if (constMatrix && matrixRowItem != firstElement)
				constMatrix = false;
			matrix[i][j] = matrixRowItem;
		}
    }
	return;
}

// Utilities
std::string ltrim(const std::string& str) {
    std::string s(str);

    s.erase(
        s.begin(),
        std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace)))
    );

    return s;
}

std::string rtrim(const std::string &str) {
    std::string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

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

void	printMatrix(const std::vector<std::vector<int>>& matrix, const int& m, const int& n){
	for (int y = 0; y < m; y++){
		for (int x = 0; x < n; x++)
			std::cout << matrix[y][x] << " ";
		std::cout << std::endl;
	}
	return;
}
