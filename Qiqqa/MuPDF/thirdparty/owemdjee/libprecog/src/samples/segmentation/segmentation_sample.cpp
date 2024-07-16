/*
    MIT License

    Copyright (c) 2017 Alexander Zaitsev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "segmentation/segmentation_ccc.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdexcept>
#include <string>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main    prl_segmentation_sample_main
#endif

int main(int argc, const char**argv)
{
    const std::string inputImageFilename = (argc >= 2 && argv[1]) ? argv[1] : "input.tif";
    const std::string outputImageFilename = (argc >= 3 && argv[2]) ? argv[2] : "binary_sample";

    /*if (inputImageFilename.empty())
    {
        throw std::invalid_argument("Input image filename is empty.");
    }

    if (outputImageFilename.empty())
    {
        throw std::invalid_argument("Output image file name is empty.");
    }*/

    cv::Mat inputImage = cv::imread(inputImageFilename);
		std::vector<cv::Mat> outputImages;

    prl::segmentation_ccc(inputImage, outputImages);

    cv::imwrite(outputImageFilename + ".text-layer.tif", outputImages[0]);
		cv::imwrite(outputImageFilename + ".foreground-layer.tif", outputImages[1]);
		cv::imwrite(outputImageFilename + ".background-layer.tif", outputImages[2]);
		return 0;
}

