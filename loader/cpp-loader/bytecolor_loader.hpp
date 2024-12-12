/*
	.bytecolor loader for C++
	setghm (c) 2024
*/
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

class ByteColorImage {
public:
	/*
		Width of the image in characters.
	*/
	unsigned long int width;

	/*
		Height of the image in characters.
	*/
	unsigned long int height;

	/*
		Colors of the image (one element per color).
	*/
	std::vector<unsigned char> data;

	static ByteColorImage* fromFile(std::string filename);
};
