//=============================================================================
// Copyright (c) 2012, Paul Filitchkin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in
//      the documentation and/or other materials provided with the
//      distribution.
//
//    * Neither the name of the organization nor the names of its contributors
//      may be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=============================================================================

#include "histLib.h"
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
using namespace cv;

//-----------------------------------------------------------------------------
// Description:
//  This examples draws an ascending ramp such that each histogram bar is
//  separated by one pixel.  The bars are colored red, the background is a
//  light shade of grey and the axis is black.  The height is chosen to fit the
//  height of the bars (if the height is too small the bars will simply get
//  cropped).
//-----------------------------------------------------------------------------
void DrawManuallyHistogram()
{
  // Declare histlib instance
  CHistLib Histogram;

  // Customize the display properties
  Histogram.SetPlotColor(Scalar(0x00, 0x00, 0xff));
  Histogram.SetAxisColor(Scalar(0x00, 0x00, 0x00));
  Histogram.SetBackgroundColor(Scalar(0xee, 0xee, 0xee));
  Histogram.SetHistImageHeight(133);
  Histogram.SetDrawSpreadOut(true);

  // Create a row vector for histogram values
  Mat Hist = Mat(128, 1, CV_32S);

  // The ith bin gets i
  for (int i = 0; i < Hist.rows; i++)
  {
    Hist.at<int>(i,0) = i;
  }

  Mat HistImage;
  Histogram.DrawHistogram(Hist, HistImage);

  string ImageName("ramp.hist.png");

  if (imwrite(ImageName, HistImage))
  {
    cout << "Created single channel histogram: " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example draws a value histogram from a test image.
//-----------------------------------------------------------------------------
void DrawSimpleValueHistogram()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/bars.png");
  assert(!ImageBGR.empty());

  // Generate color histogram for the current image
  Mat HistImageGray;
  Histogram.ComputeAndDrawHistogramValue(ImageBGR, HistImageGray);

  // Save the histogram image
  string ImageName("bars.value.hist.png");

  if (imwrite(ImageName, HistImageGray))
  {
    cout << "Created value histogram: " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example draws a color histogram from a test image.
// Note:
//  At first the large spike at zero might seem unintuitive, but it's there
//  because each channel has many pixels with the absence of color (0 values).
//  For example, if you had an image that was just blue, the red and green
//  channels would have lots of zeros and you would see a similar spike in at
//  zero in this type of histogram plot.
//-----------------------------------------------------------------------------
void DrawSimpleBgrHistogram()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/bars.png");
  assert(!ImageBGR.empty());

  // Generate histogram for the current image
  Mat HistImageBGR;
  Histogram.ComputeAndDrawHistogramBGR(ImageBGR, HistImageBGR);

  // Save the histogram image
  string ImageName("bars.rgb.hist.png");

  if (imwrite(ImageName, HistImageBGR))
  {
    cout << "Created BGR histogram: " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example draws a value histogram from a photo.  It is broken up into
//   two steps to show how get access to the histogram vector
//-----------------------------------------------------------------------------
void DrawPhotoValueHistogram()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/sunset.jpg");
  assert(!ImageBGR.empty());

  // Generate value channel histogram for the current image
  Mat HistImageGray;

  MatND Hist;
  Histogram.ComputeHistogramValue(ImageBGR, Hist);
  Histogram.DrawHistogramValue(Hist, HistImageGray);

  // Save the histogram image
  string ImageName("sunset.gray.hist.png");

  if (imwrite(ImageName, HistImageGray))
  {
    cout << "Created value histogram: " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example draws a color histogram from a photo. It is broken up into
//   two steps to show how get access to the histogram vectors
//-----------------------------------------------------------------------------
void DrawPhotoBgrHistogram()
{
  CHistLib Histogram;
  // Open the image
  Mat ImageBGR = imread("images/sunset.jpg");
  assert(!ImageBGR.empty());

  // Generate a color channel (BGR) histogram
  Mat HistImageBGR;

  MatND HistB;
  MatND HistG;
  MatND HistR;
  Histogram.ComputeHistogramBGR(ImageBGR, HistB, HistG, HistR);
  Histogram.DrawHistogramBGR(HistB, HistG, HistR, HistImageBGR);

  // Save the histogram image
  string ImageName("sunset.bgr.hist.png");

  if (imwrite(ImageName, HistImageBGR))
  {
    cout << "Created BGR histogram: " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example shows how to scale the value channel of an image.  This is
//   a potential way to implement an auto-contrast/auto-levels operation
//-----------------------------------------------------------------------------
void LevelScalingLowContrast()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageLowContrast = imread("images/fiveShadesLowContrast.png");

  assert(!ImageLowContrast.empty());

  Mat ImageOriginalNorm;
  Mat ImageLowContrastNorm;

  // Generate color histogram for the current image
  Mat HistImageGray;

  Histogram.NormalizeImageBGR(ImageLowContrast, ImageLowContrastNorm);

  Mat HistImageLowContrast;
  Mat HistImageLowContrastNorm;

  Histogram.ComputeAndDrawHistogramValue(ImageLowContrast, HistImageLowContrast);
  Histogram.ComputeAndDrawHistogramValue(ImageLowContrastNorm, HistImageLowContrastNorm);

  // Save the histogram images
  string HistImageLowContrastName("fiveShadesLowContrast.value.hist.png");
  string HistImageLowContrastNormName("fiveShadesLowContrastNorm.value.hist.png");
  string ImageLowContrastNormName("fiveShadesLowContrastNorm.png");

  if (imwrite(HistImageLowContrastName, HistImageLowContrast))
  {
    cout << "Created value histogram: " << HistImageLowContrastName << endl;
  }

  if (imwrite(HistImageLowContrastNormName, HistImageLowContrastNorm))
  {
    cout << "Created value histogram: " << HistImageLowContrastNormName << endl;
  }

  if (imwrite(ImageLowContrastNormName, ImageLowContrastNorm))
  {
    cout << "Created normalized image: " << ImageLowContrastNormName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example shows how to scale the value channel of an image.  This is
//   a potential way to implement an auto-contrast/auto-levels operation
//-----------------------------------------------------------------------------
void LevelScalingWithClipping()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageLowContrast = imread("images/fiveShadesLowContrast.png");

  assert(!ImageLowContrast.empty());

  Mat ImageLowContrastClipped;

  // Perform the normalized clipping procedure
  double clipPercent = 50;
  Histogram.NormalizeClipImageBGR(ImageLowContrast, ImageLowContrastClipped, clipPercent);

  Mat HistImageLowContrastClipped;
  Histogram.ComputeAndDrawHistogramValue(ImageLowContrastClipped, HistImageLowContrastClipped);

  // Save the modified image
  string ImageLowContrastClippedName("fiveShadesLowContrastClipped.value.png");

  if (imwrite(ImageLowContrastClippedName, ImageLowContrastClipped))
  {
    cout << "Created clipped image: " << ImageLowContrastClippedName << endl;
  }

  // Save the histogram image
  string HistImageLowContrastClippedName("fiveShadesLowContrastClipped.value.hist.png");

  if (imwrite(HistImageLowContrastClippedName, HistImageLowContrastClipped))
  {
    cout << "Created value histogram: " << HistImageLowContrastClippedName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//   This example shows how to scale the value channel of an image.  This is
//   a potential way to implement an auto-contrast/auto-levels operation
//-----------------------------------------------------------------------------
void LevelScalingNoEffect()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageOriginal = imread("images/fiveShades.png");

  assert(!ImageOriginal.empty());

  Mat ImageOriginalNorm;

  // Generate color histogram for the current image
  Mat HistImageGray;

  // Used to verify that this operation does not modify the original image
  Histogram.NormalizeImageBGR(ImageOriginal, ImageOriginalNorm);

  Mat HistImageOriginal;
  Mat HistImageOriginalNorm;

  Histogram.ComputeAndDrawHistogramValue(ImageOriginal, HistImageOriginal);
  Histogram.ComputeAndDrawHistogramValue(ImageOriginalNorm, HistImageOriginalNorm);

  // Save the histogram images
  string HistImageOriginalName("fiveShades.value.hist.png");
  string HistImageOriginalNormName("fiveShadesNorm.value.hist.png");

  if (imwrite(HistImageOriginalName, HistImageOriginal))
  {
    cout << "Created value histogram: " << HistImageOriginalName << endl;
  }

  if (imwrite(HistImageOriginalNormName, HistImageOriginalNorm))
  {
    cout << "Created value histogram: " << HistImageOriginalNormName << endl;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
  // Sample histogram plot using a user-defined histogram
  DrawManuallyHistogram();

  // Sample histogram plots using the image bars.png
  DrawSimpleValueHistogram();
  DrawSimpleBgrHistogram();

  // Sample histogram plots using the image sunset.jpg
  DrawPhotoValueHistogram();
  DrawPhotoBgrHistogram();

  // The examples below demonstrate the level scaling
  // (auto-contrast/auto-levels) functionality

  // Demonstrates level scaling on a low contrast image
  LevelScalingLowContrast();

  // Demonstrates level scaling functionality where the value channel is
  // scaled to the point of clipping
  LevelScalingWithClipping();

  // Verify that level scaling does not change an image that is already
  // at full contrast
  LevelScalingNoEffect();

  return 0;
}
