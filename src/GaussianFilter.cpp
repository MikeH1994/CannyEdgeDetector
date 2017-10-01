#include "../include/GaussianFilter.h"
#include "../include/CImg.h"


GaussianFilter::GaussianFilter(int size, float currentSigma, int nChannels):_k(size/2),_sigma(currentSigma),_nChannels(nChannels)
{
	_kernel = createKernel(size / 2, currentSigma);
}

void GaussianFilter::setKernel(int k, float sigma)
{
	if (_kernel != (float**)0) {
		delete _kernel;
	}
	_kernel = createKernel(k, sigma);
	_sigma = sigma;
	_k = k;
}

float GaussianFilter::getKernelElement(int i, int j, int k, float sigma)
{
	float exponent = -((i - k)*(i - k) + (j - k)*(j - k)) / (2 * sigma*sigma);
	return (float)(std::exp(exponent) / (2 * _PI_*sigma*sigma));
}

void GaussianFilter::setNChannels(int n) {
	_nChannels = n;
}

float ** GaussianFilter::createKernel(int k, float sigma)
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

int GaussianFilter::getIndex(int x, int y, int channel){
	return j*width*_nChannels + i*_nChannels + channel;
}

template <class T>
void GaussianFilter::gaussianFilter(T * image, T * convolutedImage, int width, int height)
{
	int index;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			for(int channel = 0; channel<_nChannels; channel++){
				index = getIndex(x,y,channel);
				convolutedImage[index] = getConvolutionAtPoint(image, x, y,width,height);
			}
		}
	}
}

template <class T>
T GaussianFilter::getConvolutionAtPoint(T* image, int xCoord, int yCoord,int channel, int width, int height) {
	int i, j,index;
	float convolutedValue = 0;
	float normalisationValue = 0;
	for (int xKernel = -_k; xKernel < _k + 1; xKernel++) {
		i = xCoord + xKernel;
		if (i > 0 && i < width) {
			for (int yKernel = -_k; yKernel < _k + 1; yKernel++) {
				j = y + yKernel;
				if (j > 0 && j < height) {
					index = getIndex(i,j,channel);
					convolutedValue += (float) (image[index]*_kernel[xKernel][yKernel]);
					normalisationValue += _kernel[xKernel][yKernel];
				}
			}
		}
	}
	convolutedValue /= normalisationValue;
	return (T) convolutedValue;
}

template <class T>
T* GaussianFilter::gaussianFilter(T * image, int width, int height)
{
	T* convolutedImage = new T[width*height];
	gaussianFilter(image,convolutedImage,width,height);
	return convolutedImage;
}

int main() {
	float** kernel = GaussianFilter().createKernel(2, 1.4f);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << round(159 * kernel[i][j]) << "\t";
		}
		std::cout << std::endl;
	}
}