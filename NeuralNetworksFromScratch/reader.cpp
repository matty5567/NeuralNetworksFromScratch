#include "reader.h"
#include <array>

int reverseINT(int i)
{
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}



std::vector<value*> read_labels(const std::string& file_loc)
{
	std::ifstream file;

	file.open(file_loc);

	if (file.is_open())
	{
		int magic_number = 0;
		int num_labels = 0;

		file.read((char*)&magic_number, sizeof(int));
		magic_number = reverseINT(magic_number);

		file.read((char*)&num_labels, sizeof(int));
		num_labels = reverseINT(num_labels);


		std::vector<value*> labels;

		for (int i = 0; i < 3; i++)
		{
			uint8_t px = 0;
			file.read((char*)&px, sizeof(char));
			value* val = new value((int)px);
			labels.push_back(val);
		}

		return labels;
	}
	else {
		return std::vector<value*> {};
	}
}

mat read_images(const std::string& file_loc)
{

	std::ifstream file;

	file.open(file_loc);

	if (file.is_open())
	{
		int magic_number = 0;
		int num_images = 0;
		int n_rows = 0;
		int n_cols = 0;

		file.read((char*)&magic_number, sizeof(int));
		magic_number = reverseINT(magic_number);

		file.read((char*)&num_images, sizeof(int));
		num_images = reverseINT(num_images);

		file.read((char*)&n_rows, sizeof(int));
		n_rows = reverseINT(n_rows);

		file.read((char*)&n_cols, sizeof(int));
		n_cols = reverseINT(n_cols);


		mat images;

		for (int i = 0; i < 3; i++)
		{
			std::vector<value*> image;
			for (int j = 0; j < n_rows * n_cols; j++)
			{
				unsigned char px = 0;
				file.read((char*)&px, sizeof(px));
				value* val = new value((float)px);
				image.push_back(val);
			}

			for (int a = 0; a < 28; a++) {
				for (int b = 0; b < 28; b++) {
					std::cout << image[28 * a + b]->data <<  " ";
				}
				std::cout << '\n';
			}
			std::cout << '\n';


 			images.push_back(image);
		}

		return images;
	}
	else {
		return mat{};
	}
}
