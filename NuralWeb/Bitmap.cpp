#include "stdafx.h"
#include "Bitmap.h"

void Bitmap::roll90(double**img, int height, int width) {
	for (int i = 0; i<height / 2; i++)
		for (int j = 0; j < (width + 1) / 2; j++) {
			double temp = img[i][j];
			img[i][j] = img[height - 1 - j][i];
			img[height - 1 - j][i] = img[height - 1 - i][width - 1 - j];
			img[height - 1 - i][width - 1 - j] = img[j][width - 1 - i];
			img[j][width - 1 - i] = temp;
		}

}

Bitmap::Bitmap(const char* path) {
	width = 0;
	height = 0;
	file.open(path, std::ios::in | std::ios::binary);
	file.seekg(18, std::ios::beg);
	file.read((char*)&width, sizeof(int));
	file.read((char*)&height, sizeof(int));
};

double** Bitmap::getArray() {
	int pixels_adress = 0;
	file.seekg(10, std::ios::beg);
	file.read((char*)&pixels_adress, sizeof(int));
	file.seekg(pixels_adress, std::ios::beg);

	double **img = new double*[height];
	for (int i = 0; i < height; i++)
		img[i] = new double[width];

	unsigned int bgr = 0;

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = width - 1; x >= 0; x--)
		{
			file.read((char*)&bgr, 3);

			if (bgr == 0xFFFFFF)
				img[x][y] = 0;
			else
				img[x][y] = 1;

			bgr = 0;
		}
	}

	roll90(img, height, width);
	return img;
}

std::ostream& operator<< (std::ostream& stream, Bitmap& bm) {
	double** img = bm.getArray();
	for (int i = 0; i < bm.height; i++) {
		for (int j = 0; j < bm.width; j++) {
			stream << img[i][j];
			if ((i * bm.height + j) % bm.width == 0)
				stream << std::endl;
		}
	}
	return stream;
}