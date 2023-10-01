#ifndef AiAS_Utils_IO
#define AiAS_Utils_IO
#include <vector>
#include <string>
#include <utility>
#include "Utils.h"

// Input file format:
// first line - integer 'size', size of array of Points
// next 'size' lines - doubles 'x' and 'y' - coordinates of Points

std::vector<Point> readFile(std::string filename);

// Output file format:
// first line - integer 'size', size of array of Points
// next 'size' lines - doubles 'x' and 'y' - coordinates of Points
// next line - integer 'time' in milliseconds

void saveFile(std::string filename, std::vector<Point> result, int time_ms);

// Tests result file format:
// each line - two integers: n t(n), where t(n) - time in milliseconds

void saveTestsResults(std::string filename, std::vector<std::pair<int, int>> results);

#endif // !AiAS_Utils_IO
