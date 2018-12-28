// NuralWeb.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <ctime>
#include "Bitmap.h"
using namespace std;
using namespace arma;

mat fastMergeY(vector <double> &imgs, int f, int l) {
	if (l - f == 0) {
		string tamplate = "0 0 0 0 0 0 0 0 0 0";
		mat y = tamplate.replace(imgs[f] * 2, 2, "1 ");
		return y;
	}
	if (l - f == 1) {
		string tamplate = "0 0 0 0 0 0 0 0 0 0";
		mat y = tamplate.replace(imgs[f] * 2, 2, "1 ");
		tamplate = "0 0 0 0 0 0 0 0 0 0";
		mat y_ = tamplate.replace(imgs[l] * 2, 2, "1 ");
		return join_cols(y, y_);
	}
	int m = (l + f) / 2;
	mat y = fastMergeY(imgs, f, m);
	mat y_ = fastMergeY(imgs, m + 1, l);
	return  join_cols(y, y_);
}

mat fastMergeX(vector <mat> &imgs, int f, int l) {
	if (l - f == 0) {
		mat x = imgs[f];
		x.reshape(1, 784);
		return x;
	}
	if (l - f == 1) {
		mat x = imgs[f];
		x.reshape(1, 784);
		mat x_ = imgs[l];
		x_.reshape(1, 784);
		return join_cols(x, x_);
	}
	int m = (l + f) / 2;
	mat x = fastMergeX(imgs, f, m);
	mat x_ = fastMergeX(imgs, m + 1, l);
	return  join_cols(x, x_);
}



int main()
{
	vector <int> sizes = { 784, 1568, 1568, 10 };
	Percs nw(2, sizes);
	nw.load("Nums/Nums");
	Bitmap img("6.bmp");
	mat x(img.getArray());
	x.reshape(1, 784);
	nw.solve(x);
	system("pause");
	return 0;
}

/*
cout << "Reading..." << endl;
MNISTreader imgs("train-images.idx3-ubyte", "train-labels.idx1-ubyte", 60000);
cout << "Merging..." << endl;
mat x = fastMergeX(imgs.Data, 0, 59999);
mat y = fastMergeY(imgs.Labels, 0, 59999);
cout << "Writing!" << endl;
x.save("MergedX");
y.save("MergedY");
cout << "Done!" << endl;
*/


/*
vector <int> sizes = { 784, 1568, 1568, 10 };
Percs nw(2, sizes);
mat x;
x.load("MergedX1");
mat y;
y.load("MergedY1");
cout << "begin traning..." << endl;
unsigned int start_time = clock();
nw.train(5000, 1000, 1, x, y);
cout << clock() - start_time << endl;
nw.save("Nums/Nums");

nw.load("Nums/Nums");
Bitmap img("6.bmp");
mat x(img.getArray());
x.reshape(1, 784);
nw.solve(x);
*/

/*
mat X = randu<mat>(28, 28);
mat Y = "0 0 0 0 1 0 0 0 0 0";
vector <int> sizes = { 2, 2, 2, 2, 2};
Conv conv(5, sizes);
conv.train(1, 1, 1, X, Y);
*/