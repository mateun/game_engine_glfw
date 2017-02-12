#include <imageimport.h>

void PngImporter::importImage(const std::string& imageFileName) { 
	png_const_bytep header[8];


	FILE* f = fopen(imageFileName.c_str(), "rb");
	if (!f)
		throw std::runtime_error("could not read file" + imageFileName);

	if (fread(header, 1, 8, f) != 8)
		throw std::runtime_error("header could not be read");

	if (png_sig_cmp((png_const_bytep)header, 0, 8)) {
		throw std::runtime_error("given file " + imageFileName + " is no valid png file");
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!png_ptr)
		throw std::runtime_error("png_create_read_struct failed");
	
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		throw std::runtime_error("png info struct failed");

	
	if (setjmp(png_jmpbuf(png_ptr))) {
		throw std::runtime_error("erorr during init_io");
	}

	png_init_io(png_ptr, f);
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);
	int width = png_get_image_width(png_ptr, info_ptr);
	int height = png_get_image_height(png_ptr, info_ptr);
	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	int number_of_passes = png_set_interlace_handling(png_ptr);

	if (bit_depth == 16)
		png_set_strip_16(png_ptr);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if (color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	png_read_update_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr)))
		throw std::runtime_error("error during readimage");

	
	png_bytep* row_pointers = nullptr;
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for (int y = 0; y < height; y++) {
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
	}
	
	try {
		png_read_image(png_ptr, row_pointers);
	}
	catch (...) {
		printf("error");
	}

	//fclose(f);


}