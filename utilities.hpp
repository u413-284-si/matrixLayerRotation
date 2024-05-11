#pragma once

/* ====== LIBRARIES ====== */
#include <vector>
#include <algorithm>
#include <iostream>

/* ====== DECLARATIONS ====== */
std::string 				ltrim(const std::string&);
std::string 				rtrim(const std::string&);
std::vector<std::string>	split(const std::string&);
void						printMatrix(const std::vector<std::vector<int>>& matrix, const int& nRows, const int& nCols);
