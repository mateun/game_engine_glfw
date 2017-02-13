#include <imageimport.h>
#include <FreeImage.h>
#include <memory>

std::unique_ptr<unsigned char> MultiFormatImageImporter::importImage(const std::string& imageFileName) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFileName.c_str(), 0);
	FIBITMAP* image = FreeImage_Load(format, imageFileName.c_str());

	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);

	image = FreeImage_ConvertTo32Bits(image);

	unsigned char* c = new unsigned char(10);

	std::unique_ptr<BYTE> p(FreeImage_GetBits(image));
	return std::move(p);
	
}