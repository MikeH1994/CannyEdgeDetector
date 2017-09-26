#include "CannyEdgeDetector.h"

float CannyEdgeDetector::getConvolutionAtPoint(int x, int y, char * image)
{
	return 0.0f;
}

CannyEdgeDetector::CannyEdgeDetector(int k, float currentSigma):_k(k),_sigma(currentSigma)
{
	_kernel = createKernel(k / 2, currentSigma);
}

float CannyEdgeDetector::getKernelElement(int i, int j, int k, float sigma)
{
	float exponent = -((i - k)*(i - k) + (j - k)*(j - k)) / (2 * sigma*sigma);
	return (float)(std::exp(exponent) / (2 * _PI_*sigma*sigma));
}

float ** CannyEdgeDetector::createKernel(int k, float sigma)
{
	int size = 2 * k + 1;
	float sum = 0;
	//create 2D array with length 2k+1
	float** kernel = new float*[size];
	for (int i = 0; i < size; i++) {
		//create innner arrays
		kernel[i] = new float[size];
		for (int j = 0; j < size; j++) {
			//set each element to it's un-normalised gaussian value
			kernel[i][j] = getKernelElement(i, j, k, sigma);
			sum += kernel[i][j];
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//normalise each value to sum
			kernel[i][j] /= sum;
		}
	}
	return kernel;
}

void CannyEdgeDetector::setKernel(int k, float sigma)
{
	if (_kernel != (float**)0) {
		delete _kernel;
	}
	_kernel = createKernel(k, sigma);
	_sigma = sigma;
	_k = k;
}

void CannyEdgeDetector::gaussianFilter(<T> * image, char * convolutedImage, int height, int width)
{
	int index;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			index = x + width*y;
			convolutedImage[index] = getConvolutionAtPoint(image, x, y);
		}
	}
}
template <class T>
T* CannyEdgeDetector::getConvolutionAtPoint(T* image, int x, int y, int width, int height) {
	int index = x + width*y;
	for (int i = -_k; i < _k + 1; i++) {
		for (int j = -_k; j < _k + 1; j++) {

		}
	}
}

template <class T>
T* CannyEdgeDetector::gaussianFilter(char * image, int width, int height)
{
	char* convolutedImage = new char[width*height];
	gaussianFilter(image,convolutedImage,width,height);
	return convolutedImage;
}

int main() {
	float** kernel = CannyEdgeDetector::createKernel(2, 1.4f);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << round(159 * kernel[i][j]) << "\t";
		}
		std::cout << std::endl;
	}
}