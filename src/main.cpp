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
#include <highgui.h>
#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
using namespace cv;

//-----------------------------------------------------------------------------
// Description:
//  Draws an ascending ramp such that each histogram bar is separated by
//  one pixel.  The bars are colored red, the background is a light shade
//  of grey and the axis is black.  The height is chosen to fit the height
//  of the bars (if the height is too small the bars will simply get cropped).
//-----------------------------------------------------------------------------
void DrawManuallyHistogram()
{
  CHistLib Histogram;
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
    cout << "Manually drawing histogram... saved " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//-----------------------------------------------------------------------------
void DrawSimpleValueHistogram()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/bars.png");
  assert(!ImageBGR.empty());

  // Generate color histogram for the current image
  Mat HistImageGray;
  Histogram.DrawHistogramValue(ImageBGR, HistImageGray);

  // Save the histogram image
  string ImageName("bars.value.hist.png");

  if (imwrite(ImageName, HistImageGray))
  {
    cout << "Drawing value histogram... created " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//
// Note:
//  At first the large spike at zero might seem unintuitive, but it's there
//  because each channel has many pixels with the absence of color (0 values).
//  For example, if you had just an image that was just blue, the red and green
//  channels would have lots of zeros and you would see a similar spike in at
//  zero is this type of histogram plot.
//-----------------------------------------------------------------------------
void DrawSimpleBgrHistogram()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/bars.png");
  assert(!ImageBGR.empty());

  // Generate histogram for the current image
  Mat HistImageBGR;
  Histogram.DrawHistogramBGR(ImageBGR, HistImageBGR);

  // Save the histogram image
  string ImageName("bars.rgb.hist.png");

  if (imwrite(ImageName, HistImageBGR))
  {
    cout << "Drawing BGR histogram... create " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
// Description:
//-----------------------------------------------------------------------------
void DrawPhotoValueHistogram()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/sunset.jpg");
  assert(!ImageBGR.empty());

  // Generate color histogram for the current image
  Mat HistImageGray;
  Histogram.DrawHistogramValue(ImageBGR, HistImageGray);

  // Save the histogram image
  string ImageName("sunset.gray.hist.png");

  if (imwrite(ImageName, HistImageGray))
  {
    cout << "Drawing value histogram... created " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DrawPhotoBgrHistogram()
{
  CHistLib Histogram;
  // Open the image
  Mat ImageBGR = imread("images/sunset.jpg");
  assert(!ImageBGR.empty());

  Mat HistImageBGR;
  Histogram.DrawHistogramBGR(ImageBGR, HistImageBGR);

  // Save the histogram image
  string ImageName("sunset.bgr.hist.png");

  if (imwrite(ImageName, HistImageBGR))
  {
    cout << "Drawing BGR histogram... created " << ImageName << endl;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LevelShift()
{
  CHistLib Histogram;

  // Open the image
  Mat ImageBGR = imread("images/bars.png");
  assert(!ImageBGR.empty());

  // Generate color histogram for the current image
  Mat HistImageGray;
  Histogram.DrawHistogramValue(ImageBGR, HistImageGray);

  // Save the histogram image
  string ImageName("bars.value.hist.png");

  if (imwrite(ImageName, HistImageGray))
  {
    cout << "Drawing value histogram... created " << ImageName << endl;
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

  LevelShift();

#if 0

  //=================================Auto levels (C++ style)=======================================
  // Open the image
  Mat ImgLowContBGR     = imread("images/fiveShadesLowContrast.png");
  Mat ImgLowContBGRNorm = Mat(ImgLowContBGR.size(), CV_32F);

  NormalizeImageBGR(ImgLowContBGR, ImgLowContBGRNorm);

  // Generate color histogram for the current image
  Mat HistLowContBGR     = Mat(HIST_ROWS, HIST_COLS, CV_8UC3, Scalar(0,0,0));
  Mat HistLowContBGRNorm = Mat(HIST_ROWS, HIST_COLS, CV_8UC3, Scalar(0,0,0));

  // Draw the histogram background and labels
  DrawHistBar(HistLowContBGR);
  DrawHistBar(HistLowContBGRNorm);

  // Draw the histogram levels
  DrawHistogramBGR(ImgLowContBGR, HistLowContBGR);
  DrawHistogramBGR(ImgLowContBGRNorm, HistLowContBGRNorm);

  if (imwrite("images/fiveShadesLowContrastA.hist.png", HistLowContBGR))
  {
    cout << "Auto levels (C++ style)... saved fiveShadesLowContrastA.hist.png\n";
  }
  if (imwrite("images/fiveShadesLowContrastNormA.hist.png", HistLowContBGRNorm))
  {
    cout << "Auto levels (C++ style)... saved fiveShadesLowContrastNormA.hist.png\n";
  }
  if (imwrite("images/fiveShadesLowContrastNormA.png", ImgLowContBGRNorm))
  {
    cout << "Auto levels (C++ style)... saved fiveShadesLowContrastNormA.png\n";
  }

  //================================= Photo BGR histogram =======================================
  // Open the image
  Mat PhotoBGR = imread("images/sunset.jpg");

  // Generate color histogram for the current image
  Mat HistPhotoBGR = Mat(2*HIST_EDGE + HIST_HEIGHT, 2*HIST_EDGE + 3*HIST_BINS, CV_8UC3, Scalar(0));

  // Draw the histogram background and labels
  DrawHistBar(HistPhotoBGR);

  // Draw the histogram levels
  DrawHistogramBGR(PhotoBGR, HistPhotoBGR);

  // Save the histogram image
  if (imwrite("images/sunset.hist.png", HistPhotoBGR))
  {
    cout << "Photo BGR histogram... saved sunset.hist.png\n";
  }

#endif
  return 0;
}
