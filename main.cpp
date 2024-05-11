#include "main.hpp"

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
