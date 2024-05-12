#include "checkInput.hpp"

/**
 * @brief Verify validity of input regarding matrix dimensions and number of
rotations according to the subject limitations.
 * 
 * @param input 		Input string containing conditions
 * @param nRows 		Number of matrix rows
 * @param nCols 		Number of matrix columns
 * @param nRotations 	Number of rotations
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

/**
 * @brief Verify number of row elements corresponds to the amount specified
beforehand as number of columns.
 * 
 * @param matrixRow 	Input string containing row elements
 * @param nCols 		Number of matrix columns
 */
void	checkRowSize(const std::vector<std::string>& matrixRow, const int& nCols){
	if (static_cast<int>(matrixRow.size()) != nCols)
		throw std::invalid_argument(INV_ROW_SZ);
	return;
}

/**
 * @brief Verifiy that each matrix element stays within the subject limitations.
 * 
 * @param element		Matrix element 
 */
void	checkMatrixElements(const int& element){
	if (element < 1 || element > 1e8)
		throw std::invalid_argument(INV_ELEM_DIM);
	return;
}

/**
 * @brief Parse line from standard input and check its contents validity.
 * 
 * @param nRows 		Number of matrix rows
 * @param nCols 		Number of matrix columns
 * @param nRotations 	Number of rotations
 */
void	parseMatrixConditions(int& nRows, int& nCols, int& nRotations){
    std::string	firstMultipleInputTemp;

	std::getline(std::cin, firstMultipleInputTemp);
    std::vector<std::string> firstMultipleInput = split(ltrim(rtrim(firstMultipleInputTemp)));
	checkMatrixConditions(firstMultipleInput, nRows, nCols, nRotations);
	return;
}

/**
 * @brief Parse as many lines from standard input as specified by "nRows" and check its
contents validity. Save valid elements into matrix. If one element is different
from the first, set the boolean "constMatrix" to false, indicating that the
matrix is not constant.
 * 
 * @param matrix 		Matrix where elements are stored
 * @param nRows 		Number of matrix rows
 * @param nCols 		Number of matrix columns
 * @param constMatrix 	Boolean indicating if the matrix is constant
 */
void	parseMatrixElements(std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols, bool& constMatrix){
	int			firstElement = {};
	std::string	testStr;

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
	std::getline(std::cin, testStr);
	if (!testStr.empty())
		throw std::invalid_argument(INV_ROW_SZ);
	return;
}
