#include <imageimport.h>
#include <FreeImage.h>
#include <memory>
#include <image.h>

std::unique_ptr<FBImage> MultiFormatImageImporter::importImage(const std::string& imageFileName) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imageFileName.c_str(), 0);
	FIBITMAP* image = FreeImage_Load(format, imageFileName.c_str());

	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);

	FIBITMAP* temp = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);
	image = temp;

	std::unique_ptr<FBImage> i(new FreeImageBitmap(image));
	return std::move(i);
}