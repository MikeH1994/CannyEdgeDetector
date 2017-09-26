#ifndef _H_CANNYEDGEDETECTION_H_
#define _H_CANNYEDGEDETECTION_H_
#define _PI_ 3.1415926535
#include <cmath>
#include <iostream>

class CannyEdgeDetector {
private:
	float** _kernel = (float**) 0;
	int _k;
	float _sigma;


public:

	CannyEdgeDetector(int kernelSize = 5, float currentSigma = 1.4f);
	void setKernel(int k, float sigma);
	static float** createKernel(int k, float sigma);
	static float getKernelElement(int i, int j, int k, float sigma);

	template <class T>
	void gaussianFilter(T* image, T* convultedImage, int height, int width);
	template <class T>
	T* gaussianFilter(T* image, int width, int height);
	template <class T>
	float getConvolutionAtPoint(T* image, int x, int y, int width, int height);


};

template void CannyEdgeDetector::gaussianFilter<float>(float* image, float* convultedImage, int height, int width);
template void CannyEdgeDetector::gaussianFilter<char>(char* image, char* convultedImage, int height, int width);
template void CannyEdgeDetector::gaussianFilter<int>(int* image, int* convultedImage, int height, int width);

template float* CannyEdgeDetector::gaussianFilter<float>(float* image, int height, int width);
template char* CannyEdgeDetector::gaussianFilter<char>(char* image, int height, int width);
template int* CannyEdgeDetector::gaussianFilter<int>(int* image, int height, int width);

template float CannyEdgeDetector::getConvolutionAtPoint(char* image, int x, int y, int width, int height);
template float CannyEdgeDetector::getConvolutionAtPoint(float* image, int x, int y, int width, int height);
template float CannyEdgeDetector::getConvolutionAtPoint(int* image, int x, int y, int width, int height);


#endif