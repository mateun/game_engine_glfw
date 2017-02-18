#include <filehelper.h>

std::string FileHelper::readFileIntoString(const std::string& fileName) {
	std::ifstream inFile(fileName, std::ios::in);
	std::ostringstream code;
	while (inFile.good()) {
		int c = inFile.get();
		if (!inFile.eof()) code << (char)c;
	}
	inFile.close();
	return code.str();
}