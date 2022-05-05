/*
 * 包含构造、
 * 析构基本工具
 */

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include "alloc.h"
#include "construct.h"
#include "uninitialized.h"

#endif // end of ALLOCATOR_H_


#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<vector>
using namespace std;
using namespace cv;
/*
class Image {
private:
	Mat image;
public:
	Image(const string &s) : image(imread(s)) {}
	Image() = default;
	~Image() = default;
	inline int getRows() const { return image.rows; }
	inline int getCols() const { return image.cols; }
	inline int getType() const { return image.type(); }
	inline int getChannel() const { return image.channels(); }
	void del_black();
};
*/

vector<pair<int,int>> vec;

void get(Mat& image) {
	Mat ima;
	cvtColor(image, ima, COLOR_BGR2HSV);
	//imshow("ima", ima);
	int leftx = ima.rows / 2, lefty = 0, rightx = ima.rows / 2, righty = ima.cols - 1, 
		topx = 0, topy = ima.cols / 2, bottomx = ima.rows - 1, bottomy = ima.cols / 2;
	for (; lefty < righty, topx < bottomx; lefty++, righty--, topx++, bottomx--) {
		auto left = ima.at<Vec3b>(leftx, lefty);
		auto right = ima.at<Vec3b>(rightx, righty);
		auto top = ima.at<Vec3b>(topx, topy);
		auto bottom = ima.at<Vec3b>(bottomx, bottomy);
		if ( (left[2] >= 0 && left[2] <= 46) || (right[2] >= 0 && right[2]) <= 46 || 
			(top[2] >= 0 && top[2] <= 46) || (bottom[2] >= 0 && bottom[2] <= 46)) {
			continue;
		}
		else {
			int x = topx, y = lefty;
			int high = righty - lefty;
			int weight = bottomx - topx;
			vec.push_back(make_pair(x, y));
			vec.push_back(make_pair(weight, high));
			Mat result = ima(Rect(x, y, weight, high));
			imshow("result", result);
			image = result;
			break;
		}
	}
}


void csh(Mat& imag) {
	Mat result;
	cvtColor(imag, result, 40);
	imshow("hs", result);
	for (int i = 0; i < result.rows - 1; i++) {
		for (int j = 0; j < result.cols - 1; j++) {
			auto c = result.at<Vec3b>(i, j);
			if (c[2] >= 0 && c[2] <= 46) {
				result.at<Vec3b>(i, j)[0] = 255;
				result.at<Vec3b>(i, j)[1] = 255;
				result.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	imshow("result", result);
}

int main() {
	Mat mat = imread("E:/dows/1.jfif");
	get(mat);
	imshow("cs", mat);
	//csh(mat);
	for (auto c : vec) {
		cout << c.first << "  " << c.second << endl;
	}
	waitKey(0);
}
