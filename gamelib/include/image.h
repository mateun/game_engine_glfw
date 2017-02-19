#pragma once

class FIBITMAP;


class FBImage {
public:

	virtual ~FBImage() {};
	virtual unsigned char* getPixels() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

private:
	FIBITMAP* _image;
};

class FreeImageBitmap : public FBImage {
public:
	FreeImageBitmap(FIBITMAP* i) : _image(i) {}
	virtual ~FreeImageBitmap();
	virtual unsigned char* getPixels();
	virtual int getWidth();
	virtual int getHeight();

private:
	FIBITMAP* _image;
};
