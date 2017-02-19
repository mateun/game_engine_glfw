#pragma once
#include <renderlib_api.h>
#include <string>
#include <png.h>
#include <memory>

class FBImage;



#ifdef _WIN32
class RENDERLIB_API ImageImporter
#else
class ImageImporter
#endif
{

public:
	virtual std::unique_ptr<FBImage> importImage(const std::string& imageFileName) = 0;

};

#ifdef _WIN32
class RENDERLIB_API MultiFormatImageImporter : public ImageImporter
#else
class MultiFormatImageImporter : public ImageImporter
#endif
{

public:
	virtual std::unique_ptr<FBImage> importImage(const std::string& imageFileName) override;
};