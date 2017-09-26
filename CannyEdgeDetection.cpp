#include "CannyEdgeDetection.h"

CannyEdgeDetection::CannyEdgeDetection(int kernelSize, float currentSigma):_currentKernelSize(kernelSize),_currentSigma(currentSigma)
{
	_currentKernel = createKernel(kernelSize / 2, currentSigma);
}

float CannyEdgeDetection::getKernelElement(int i, int j, int k, float sigma)
{
	float exponent = -((i - k)*(i - k) + (j - k)*(j - k)) / (2 * sigma*sigma);
	return (float)(std::exp(exponent) / (2 * _PI_*sigma*sigma));
}

float ** CannyEdgeDetection::createKernel(int k, float sigma)
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

void CannyEdgeDetection::setKernel(int k, float sigma)
{
}

void CannyEdgeDetection::gaussianFilter(char * image, char * convultedImage, int height, int width)
{
}

void CannyEdgeDetection::gaussianFilter(char * image, int width, int height)
{
}

int main() {
	float** kernel = CannyEdgeDetection::createKernel(2, 1.4f);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << round(159 * kernel[i][j]) << "\t";
		}
		std::cout << std::endl;
	}
}
