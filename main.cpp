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
# define INV_ARG_NUM "invalid number of arguments provided\nexpected: nRows nCols nRotations"
# define INV_MTX_DIM "invalid matrix dimension provided\nexpected: 2 <= nRows, nCols <= 300"
# define INV_ROT_DIM "invalid rotation dimension provided\nexpected: 1 <= nRotations <= 10⁹"
# define INV_MTX_MIN "invalid matrix dimension provided\nexpected: min(nRows, nCols) to be even"
# define INV_ROW_SZ	"invalid number of elements in row"
# define INV_ELEM_DIM "invalid matrix element dimension provided\n expected: 1 <= element <= 10⁸"

// Function declarations
std::string 				ltrim(const std::string&);
std::string 				rtrim(const std::string&);
std::vector<std::string>	split(const std::string&);
void 						matrixRotation(std::vector<std::vector<int>> matrix, int r);
void						checkMatrixConditions(const std::vector<std::string>& input, int& nRows, int& nCols, int& nRotations);
void						checkRowSize(const std::vector<std::string>& matrixRow, const int& nCols);
void						checkMatrixElements(const int& element);
void						parseMatrixConditions(int& nRows, int& nCols, int& nRotations);
void						parseMatrixElements(std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols, bool& constMatrix);
void						printMatrix(const std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols);

int main(void)
{
	int		nRows, nCols, nRotations;
	bool	constMatrix = true;

	try{
		parseMatrixConditions(nRows, nCols, nRotations);
		std::vector<std::vector<int>>	matrix(nRows);
		parseMatrixElements(matrix, nRows, nCols, constMatrix);
		std::cout << "\nOutput:\n";
		if (constMatrix)
			printMatrix(matrix, nRows, nCols);
		else
	    	matrixRotation(matrix, nRotations);
	}
	catch(std::exception& e){
		std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
		return 1;
	}
    return 0;
}

void matrixRotation(std::vector<std::vector<int>> matrix, int r){
	int	nRows = matrix.size();
	int	nCols = matrix[0].size();
	int	cycleNum = std::min(nRows, nCols) / 2;
	int	cycleArr[cycleNum][2 * (nRows + nCols) - 4];
	int	cycleIdx, cycleLen, i, x, y;

	std::fill(&cycleArr[0][0], &cycleArr[0][0] + cycleNum * (2 * (nRows + nCols) - 4), 0);
	for (cycleIdx = 0; cycleIdx < cycleNum; cycleIdx++){
		i = 0;
		x = y = cycleIdx;
		for (; y < nRows - cycleIdx - 1; y++)
			cycleArr[cycleIdx][i++] = matrix[y][x];
		for (; x < nCols - cycleIdx - 1; x++)
			cycleArr[cycleIdx][i++] = matrix[y][x];
		for (; y > cycleIdx; y--)
			cycleArr[cycleIdx][i++] = matrix[y][x];
		for (; x > cycleIdx; x--)
			cycleArr[cycleIdx][i++] = matrix[y][x];
	}

	for (cycleIdx = 0; cycleIdx < cycleNum; cycleIdx++){
		cycleLen = 2 * ((nRows - 2 * cycleIdx) + (nCols - 2 * cycleIdx)) - 4;
		if (r == cycleLen)
			continue;
		i = cycleLen - (r % cycleLen);
		x = y = cycleIdx;
		for (; y < nRows - cycleIdx - 1; y++)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
		for (; x < nCols - cycleIdx -1; x++)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
		for (; y > cycleIdx; y--)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
		for (; x > cycleIdx; x--)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
	}
	printMatrix(matrix, nRows, nCols);
	return;
}

// Input checking
void	checkMatrixConditions(const std::vector<std::string>& input, int& nRows, int& nCols, int& nRotations){
	if (input.size() != 3)
		throw std::invalid_argument(INV_ARG_NUM);

	nRows = stoi(input[0]);
	if (nRows < 2 || nRows > 300)
		throw std::invalid_argument(INV_MTX_DIM);
	nCols = stoi(input[1]);
	if (nCols < 2 || nCols > 300)
		throw std::invalid_argument(INV_MTX_DIM);
	if (std::min(nRows, nCols) % 2 != 0)
		throw std::invalid_argument(INV_MTX_MIN);

	nRotations = stoi(input[2]);
	if (nRotations < 1 || nRotations > 1e9)
		throw std::invalid_argument(INV_ROT_DIM);
	return;
}

void	checkRowSize(const std::vector<std::string>& matrixRow, const int& nCols){
	if (static_cast<int>(matrixRow.size()) != nCols)
		throw std::invalid_argument(INV_ROW_SZ);
	return;
}

void	checkMatrixElements(const int& element){
	if (element < 1 || element > 1e8)
		throw std::invalid_argument(INV_ELEM_DIM);
	return;
}

void	parseMatrixConditions(int& nRows, int& nCols, int& nRotations){
    std::string	firstMultipleInputTemp;

	std::getline(std::cin, firstMultipleInputTemp);
    std::vector<std::string> firstMultipleInput = split(ltrim(rtrim(firstMultipleInputTemp)));
	checkMatrixConditions(firstMultipleInput, nRows, nCols, nRotations);
	return;
}

void	parseMatrixElements(std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols, bool& constMatrix){
	int	firstElement = {};

	for (int i = 0; i < nRows; i++) {
        matrix[i].resize(nCols);
        std::string matrixRowTempTemp;
        std::getline(std::cin, matrixRowTempTemp);
        std::vector<std::string> matrixRowTemp = split(ltrim(rtrim(matrixRowTempTemp)));
		checkRowSize(matrixRowTemp, nCols);

		for (int j = 0; j < nCols; j++) {
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

void	printMatrix(const std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols){
	for (int y = 0; y < nRows; y++){
		for (int x = 0; x < nCols; x++)
			std::cout << matrix[y][x] << " ";
		std::cout << std::endl;
	}
	return;
}
