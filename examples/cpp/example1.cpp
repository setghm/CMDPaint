#define UNICODE

#include <iostream>
#include <Windows.h>
#include <bytecolor_loader.hpp>

int main(void) {
	std::string filename = "bird-pos1.bytecolor";

	try {
		// Load image from file.
		ByteColorImage* image = ByteColorImage::fromFile(filename);

		// Setup for windows console.
		HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

		// Save original console attributes.
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(out_handle, &csbi);
		WORD original_attributes = csbi.wAttributes;

		// Print image info.
		std::cout << filename << " " << image->width << "x" << image->height << std::endl << std::endl;

		// Draw image into the windows console.
		size_t index = 0;
		for (unsigned char& color : image->data) {
			SetConsoleTextAttribute(out_handle, color);

			std::cout << ' ';

			if (++index % image->width == 0) {
				std::cout << std::endl;
			}
		}

		// Restore original console attributes.
		SetConsoleTextAttribute(out_handle, original_attributes);

		delete image;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}
