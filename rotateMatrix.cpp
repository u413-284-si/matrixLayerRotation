#include "rotateMatrix.hpp"

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
	// Number of cycles determined by the smaller matrix dimension which is
	// required to be even. One cycle takes up two rows/columns.
	int	cycleNum = std::min(nRows, nCols) / 2;
	// Array with as many rows as number of cycles with each row having the size
	// of the largest cycle
	int	cycleArr[cycleNum][2 * (nRows + nCols) - 4];
	int	cycleLen, i, x, y;

	std::fill(&cycleArr[0][0], &cycleArr[0][0] + cycleNum * (2 * (nRows + nCols) - 4), 0);
	// Spiraling starts at matrix[0][0] going counter-clockwise. Moves inwards
	// along the diagonal.
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
		for (; x < nCols - cycleIdx - 1; x++)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
		for (; y > cycleIdx; y--)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
		for (; x > cycleIdx; x--)
			matrix[y][x] = cycleArr[cycleIdx][i++ % cycleLen];
	}
	printMatrix(matrix, nRows, nCols);
	return;
}
