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
