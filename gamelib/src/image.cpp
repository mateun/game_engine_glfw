#include <image.h>
#include <FreeImage.h>



FreeImageBitmap::~FreeImageBitmap() {
	FreeImage_Unload(_image);
}

unsigned char* FreeImageBitmap::getPixels() {
	return FreeImage_GetBits(_image);
}

int FreeImageBitmap::getWidth() {
	return FreeImage_GetWidth(_image);
}

int FreeImageBitmap::getHeight() {
	return FreeImage_GetHeight(_image);
}