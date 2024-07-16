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


#include "binarizeByLocalVariances.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdexcept>
#include <string>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main    prl_binarizeByLocalVariances_sample_main
#endif

int main(int argc, const char**argv)
{
    if (argc < 4)
    {
        throw std::invalid_argument("Usage: progs image_in image_out1 image_out2." );
    }
    const std::string inputImageFilename = argv[1];
    const std::string outputImageFilenameFirst = argv[2];
    const std::string outputImageFilenameSecond = argv[3];

    if (inputImageFilename.empty())
    {
        throw std::invalid_argument("Input image filename is empty.");
    }

    if (outputImageFilenameFirst.empty())
    {
        throw std::invalid_argument("First output image file name is empty.");
    }

    if (outputImageFilenameSecond.empty())
    {
        throw std::invalid_argument("Second output image file name is empty.");
    }

    cv::Mat inputImage = cv::imread(inputImageFilename);
    cv::Mat outputImageFirst, outputImageSecond;

    prl::binarizeByLocalVariances(inputImage, outputImageFirst);
    prl::binarizeByLocalVariancesWithoutFilters(inputImage, outputImageSecond);

    cv::imwrite(outputImageFilenameFirst, outputImageFirst);
    cv::imwrite(outputImageFilenameSecond, outputImageSecond);
		return 0;
}

