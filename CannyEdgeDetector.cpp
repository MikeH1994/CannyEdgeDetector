#include "CannyEdgeDetector.h"


CannyEdgeDetector::CannyEdgeDetector(int k, float currentSigma, int nChannels = 3):_k(k),_sigma(currentSigma),_nChannels(nChannels)
{
	_kernel = createKernel(k / 2, currentSigma);
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

float CannyEdgeDetector::getKernelElement(int i, int j, int k, float sigma)
{
	float exponent = -((i - k)*(i - k) + (j - k)*(j - k)) / (2 * sigma*sigma);
	return (float)(std::exp(exponent) / (2 * _PI_*sigma*sigma));
}

void CannyEdgeDetector::setNChannels(int n) {
	_nChannels = n;
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

template <class T>
void CannyEdgeDetector::gaussianFilter(T * image, T * convolutedImage, int width, int height)
{
	int index;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			index = x + width*y;
			convolutedImage[index] = getConvolutionAtPoint(image, x, y,width,height);
		}
	}
}

template <class T>
T CannyEdgeDetector::getConvolutionAtPoint(T* image, int x, int y, int width, int height) {
	int ii, jj,index;
	float convolutedValue = 0;
	float normalisationValue = 0;
	for (int i = -_k; i < _k + 1; i++) {
		ii = x + i;
		if (ii > 0 && ii < width) {
			for (int j = -_k; j < _k + 1; j++) {
				jj = y + j;
				if (jj > 0 && jj < height) {
					index = jj*width + ii;
					convolutedValue += (float) (image[index]*_kernel[i][j]);
					normalisationValue += _kernel[i][j];
				}
			}
		}
	}
	convolutedValue /= normalisationValue;
	return (T) convolutedValue;
}

template <class T>
T* CannyEdgeDetector::gaussianFilter(T * image, int width, int height)
{
	T* convolutedImage = new T[width*height];
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