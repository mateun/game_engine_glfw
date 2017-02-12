#pragma once
#include <renderlib_api.h>
#include <string>
#include <png.h>

#ifdef _WIN32
class RENDERLIB_API ImageImporter
#else
class ImageImporter
#endif
{

public:
	virtual void importImage(const std::string& imageFileName) = 0;

};

#ifdef _WIN32
class RENDERLIB_API PngImporter : public ImageImporter
#else
class PngImporter : public ImageImporter
#endif
{

public:
	virtual void importImage(const std::string& imageFileName) override;
};