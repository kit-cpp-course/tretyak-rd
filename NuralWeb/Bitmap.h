#pragma once
class Bitmap {
private:
	void roll90(double**img, int height, int width);
public:
	std::ifstream file;
	unsigned width;
	unsigned height;

	Bitmap(const char* path);

	arma::mat getArray();
};