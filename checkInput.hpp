#pragma once

/* ====== LIBRARIES ====== */
#include <vector>
#include <iostream>
#include <stdexcept>
#include "utilities.hpp"

/* ====== DEFINITIONS ====== */

// Error definitions
#define INV_ARG_NUM "invalid number of arguments provided\nexpected: nRows nCols nRotations"
#define INV_MTX_DIM "invalid matrix dimension provided\nexpected: 2 <= nRows, nCols <= 300"
#define INV_ROT_DIM "invalid rotation dimension provided\nexpected: 1 <= nRotations <= 10^9"
#define INV_MTX_MIN "invalid matrix dimension provided\nexpected: min(nRows, nCols) to be even"
#define INV_ROW_SZ	"invalid number of elements in row"
#define INV_ELEM_DIM "invalid matrix element dimension provided\nexpected: 1 <= element <= 10^8"

/* ====== DECLARATIONS ====== */
void	checkMatrixConditions(const std::vector<std::string>& input, int& nRows, int& nCols, int& nRotations);
void	checkRowSize(const std::vector<std::string>& matrixRow, const int& nCols);
void	checkMatrixElements(const int& element);
void	parseMatrixConditions(int& nRows, int& nCols, int& nRotations);
void	parseMatrixElements(std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols, bool& constMatrix);
