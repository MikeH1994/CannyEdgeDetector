#ifndef _H_CANNYEDGEDETECTION_H_
#define _H_CANNYEDGEDETECTION_H_
#define _PI_ 3.1415926535
#include <cmath>
#include <iostream>

class CannyEdgeDetection {
private:
	float** _currentKernel = (float**) 0;
	int _currentKernelSize;
	float _currentSigma;

public:
	CannyEdgeDetection(int kernelSize = 5, float currentSigma = 1.4f);
	void setKernel(int k, float sigma);
	void gaussianFilter(char* image, char* convultedImage, int height, int width);
	void gaussianFilter(char* image, int width, int height);
	static float** createKernel(int k, float sigma);
	static float getKernelElement(int i, int j, int k, float sigma);
};

#endif