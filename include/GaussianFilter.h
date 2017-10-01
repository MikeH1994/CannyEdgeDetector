#ifndef _H_GAUSSIANFILTER_H_
#define _H_GAUSSIANFILTER_H_
#define _PI_ 3.1415926535
#include <cmath>
#include <iostream>

class GaussianFilter {
private:
	float** _kernel = (float**) 0;
	int _k;
	float _sigma;
	int _nChannels = 3;

public:

	GaussianFilter(int kernelSize = 5, float currentSigma = 1.4f,int nChannels = 3);
	int getIndex(int x, int y, int channel);
	void setKernel(int k, float sigma);
	float** createKernel(int k, float sigma);
	float getKernelElement(int i, int j, int k, float sigma);
	void setNChannels(int nChannels);

	template <class T>
	void gaussianFilter(T* image, T* convultedImage, int width, int height);
	template <class T>
	T* gaussianFilter(T* image, int width, int height);
	template <class T>
	T getConvolutionAtPoint(T* image, int x, int y, int width, int height);


};

template void GaussianFilter::gaussianFilter<float>(float* image, float* convultedImage, int height, int width);
template void GaussianFilter::gaussianFilter<char>(char* image, char* convultedImage, int height, int width);
template void GaussianFilter::gaussianFilter<int>(int* image, int* convultedImage, int height, int width);

template float* GaussianFilter::gaussianFilter<float>(float* image, int height, int width);
template char* GaussianFilter::gaussianFilter<char>(char* image, int height, int width);
template int* GaussianFilter::gaussianFilter<int>(int* image, int height, int width);

template char GaussianFilter::getConvolutionAtPoint(char* image, int x, int y, int width, int height);
template float GaussianFilter::getConvolutionAtPoint(float* image, int x, int y, int width, int height);
template int GaussianFilter::getConvolutionAtPoint(int* image, int x, int y, int width, int height);


#endif