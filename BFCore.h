#ifndef BF_COMPLIER_CORE
#define BF_COMPLIER_CORE
#include <string>
#include <unordered_map>
#include <vector>

struct OperatorList
{
	std::string code;
	std::unordered_map<int, int> brackets;
	size_t ptrPos;

	std::vector<char> array;
	std::vector<char>::iterator iterator;
};

OperatorList preProcess(std::string);
bool parser(OperatorList&);
void run(std::string);

#endif // !BF_COMPLIER_CORE
