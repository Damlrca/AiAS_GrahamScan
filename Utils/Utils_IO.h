#ifndef AiAS_Utils_IO
#define AiAS_Utils_IO
#include <vector>
#include <string>
#include "Utils.h"

// Input file format:
// first line - integer 'size', size of array of Points
// next 'size' lines - doubles 'x' and 'y' - coordinates of Points

std::vector<Point> readFile(std::string filename);

// Output file format:
// first line - integer 'size', size of array of Points
// next 'size' lines - doubles 'x' and 'y' - coordinates of Points
// next line - integer 'time' in milliseconds

void saveResult(std::string filename, std::vector<Point> result, int time_ms);

#endif // !AiAS_Utils_IO
