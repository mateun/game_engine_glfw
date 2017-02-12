#pragma once

#define REFLECTION_CODE(className) \
public:\
	std::string getTypeName() {\
	return "className";\
}\

;
