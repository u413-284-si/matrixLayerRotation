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

/* Take matrix to be rotated and the number of rotations.
Read matrix elements into a buffer array "cycleArr". The matrix is read in
cycles spiraling inwards where each cycle is traversed in counter-clockwise
direction. One cycle is saved into one row of "cycleArr". Then the matrix is
traversed in the same manner where each element is being assigned the
corresponding element from "cycleArr" in order to represent a counter-clockwise
rotation. Finally the new matrix is printed to standard output.  
 */
void matrixRotation(std::vector<std::vector<int>> matrix, int r){
	int	nRows = matrix.size();
	int	nCols = matrix[0].size();
	int	cycleNum = std::min(nRows, nCols) / 2;
	int	cycleArr[cycleNum][2 * (nRows + nCols) - 4];
	int	cycleLen, i, x, y;

	std::fill(&cycleArr[0][0], &cycleArr[0][0] + cycleNum * (2 * (nRows + nCols) - 4), 0);
	for (int cycleIdx = 0; cycleIdx < cycleNum; cycleIdx++){
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

	for (int cycleIdx = 0; cycleIdx < cycleNum; cycleIdx++){
		cycleLen = 2 * ((nRows - 2 * cycleIdx) + (nCols - 2 * cycleIdx)) - 4;
		// If number of rotations is equal to number of elements in the cycle
		// (or a multiple of it), the elements would only rotate to their original position
		if (r % cycleLen == 0)
			continue;
		// Substract the number of rotations from the number of elements in the
		// cycle to get the index for the element to replace matrix[0][0]. 
		// Use modulo to stay in range of [0, cyclelen]
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

/* Verify validity of input regarding matrix dimensions and number of
rotations according to the subject limitations.
 */
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

/* Verify number of row elements corresponds to the amount specified
beforehand as number of columns.
 */
void	checkRowSize(const std::vector<std::string>& matrixRow, const int& nCols){
	if (static_cast<int>(matrixRow.size()) != nCols)
		throw std::invalid_argument(INV_ROW_SZ);
	return;
}

/* Verifiy that each matrix element stays within the subject limitations.
 */
void	checkMatrixElements(const int& element){
	if (element < 1 || element > 1e8)
		throw std::invalid_argument(INV_ELEM_DIM);
	return;
}

/* Parse line from standard input and check its contents validity.
 */
void	parseMatrixConditions(int& nRows, int& nCols, int& nRotations){
    std::string	firstMultipleInputTemp;

	std::getline(std::cin, firstMultipleInputTemp);
    std::vector<std::string> firstMultipleInput = split(ltrim(rtrim(firstMultipleInputTemp)));
	checkMatrixConditions(firstMultipleInput, nRows, nCols, nRotations);
	return;
}

/* Parse as many lines from standard input as specified by "nRows" and check its
contents validity. Save valid elements into matrix. If one element is different
from the first, set the boolean "constMatrix" to false, indicating that the
matrix is not constant.
*/
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
