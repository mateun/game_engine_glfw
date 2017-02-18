#pragma once
#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileHelper {
public:
	static std::string readFileIntoString(const std::string& fileName);
};

