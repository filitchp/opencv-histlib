//=================================================================================================
// Copyright (c) 2011, Paul Filitchkin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this list of
//      conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright notice, this list of
//      conditions and the following disclaimer in the documentation and/or other materials
//      provided with the distribution.
//
//    * Neither the name of the <ORGANIZATION> nor the names of its contributors may be used
//      to endorse or promote products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#include "histLib.h"
#include <highgui.h>
using namespace cv;
using namespace std;

//=================================================================================================
// Description:
//   Draws bars corresponding to the bin count in Hist onto HistImage in some desired color
//=================================================================================================
void DrawHistogram(CvHistogram* Hist, unsigned HistSize, IplImage* HistImage, CvScalar Color,
                   unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  IplImage* HistLayer = cvCreateImage(cvGetSize(HistImage), IPL_DEPTH_8U, 3);

  if (HistLayer)
  {
    // Make sure image starts out with zero entries
    cvSetZero(HistLayer);

    // Draw the bins
    for( unsigned i= 0; i < HistSize; i++ )
    {
      unsigned binValue = cvRound(cvQueryHistValue_1D(Hist,i));
      if (binValue)
      {
        cvLine(HistLayer,
          cvPoint(i*3+histEdge, histEdge + histHeight),
          cvPoint(i*3+histEdge, histEdge + histHeight - binValue),
          Color);
      }
    }
    cvAdd(HistImage, HistLayer, HistImage);
    cvReleaseImage(&HistLayer);
  }
}

//=================================================================================================
// Description:
//   Overloaded DrawHistogram function that takes a CvMat object instead of a CvHistogram.
//   This function only supports column vectors.
//=================================================================================================
void DrawHistogram(CvMat* Hist, IplImage* HistImage, CvScalar Color,
                   unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  // Make sure the input is a column vector with at least two elements
  if ((Hist->rows < 2) || (Hist->cols != 1))
  {
    return;
  }

  IplImage* HistLayer = cvCreateImage(cvGetSize(HistImage), IPL_DEPTH_8U, 3);

  if (HistLayer)
  {
    // Make sure image starts out with zero entries
    cvSetZero( HistLayer );

    // Draw the bins
    unsigned binValue = 0;

    switch(Hist->type)
    {
      // When Hist contains floats
      case (CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG | CV_32F):
        for (int i= 0; i < Hist->rows; i++)
        {
          binValue = (unsigned)cvRound(Hist->data.fl[i]);

          if (binValue)
          {
            cvLine(HistLayer,
              cvPoint(i*3 + histEdge, histEdge + histHeight),
              cvPoint(i*3 + histEdge, histEdge + histHeight - binValue),
              Color);
          }
        }
      break;

      // When Hist contains doubles
      case (CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG | CV_64F):
        for (int i= 0; i < Hist->rows; i++)
        {
          binValue = (unsigned)cvRound(Hist->data.db[i]);

          if (binValue)
          {
            cvLine(HistLayer,
              cvPoint(i*3 + histEdge, histEdge + histHeight),
              cvPoint(i*3 + histEdge, histEdge + histHeight - binValue),
              Color);
          }
        }
      break;

      // When Hist contains ints
      case (CV_MAT_MAGIC_VAL | CV_MAT_CONT_FLAG | CV_32S):
        for (int i= 0; i < Hist->rows; i++)
        {
          binValue = (unsigned)cvRound(Hist->data.i[i]);

          if (binValue)
          {
            cvLine(HistLayer,
              cvPoint(i*3 + histEdge, histEdge + histHeight),
              cvPoint(i*3 + histEdge, histEdge + histHeight - binValue),
              Color);
          }
        }
      break;

      default:
        return;
    }

    cvAdd(HistImage, HistLayer, HistImage);
    cvReleaseImage(&HistLayer);
  }
}

//=================================================================================================
// Description:
//   Overloaded function using C++ libraries/conventions. Here Hist can be either a row or column
//   vector.
//=================================================================================================
void DrawHistogram(Mat& Hist, Mat& HistImage, Scalar Color,
                   unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  bool rowVector;

  // Make sure we have a row or column vector
  if ( Hist.rows > Hist.cols )
  {
    if ((Hist.rows < 2) || (Hist.cols != 1))
    {
      return;
    }
    rowVector = false;
  }
  else
  {
    if ((Hist.rows != 1) || (Hist.cols < 2))
    {
      return;
    }
    rowVector = true;
  }

  Mat HistLayer = Mat(HistImage.size(), CV_8UC3, Scalar(0));

  // Draw the bins
  unsigned binValue = 0;

  switch(Hist.type())
  {
    // When Hist contains floats
    case CV_32F:
      if (rowVector)
      {
        for (int i= 0; i < Hist.cols; i++)
        {
          DrawHistBin(HistLayer, Hist.at<float>(0,i),
            i*3, Color, histBins, histEdge, histHeight);
        }
      }
      else
      {
        for (int i= 0; i < Hist.rows; i++)
        {
          DrawHistBin(HistLayer, Hist.at<float>(i,0),
            i*3, Color, histBins, histEdge, histHeight);
        }
      }
    break;

    // When Hist contains doubles
    case CV_64F:
      if (rowVector)
      {
        for (int i= 0; i < Hist.cols; i++)
        {
          DrawHistBin(HistLayer, Hist.at<double>(0,i),
            i*3, Color, histBins, histEdge, histHeight);
        }
      }
      else
      {
        for (int i= 0; i < Hist.rows; i++)
        {
          DrawHistBin(HistLayer, Hist.at<double>(i,0),
            i*3, Color, histBins, histEdge, histHeight);
        }
      }
    break;

    // When Hist contains ints
    case CV_32S:
      if (rowVector)
      {
        for (int i= 0; i < Hist.cols; i++)
        {
          DrawHistBin(HistLayer, Hist.at<double>(0,i),
            i*3, Color, histBins, histEdge, histHeight);
        }
      }
      else
      {
        for (int i= 0; i < Hist.rows; i++)
        {
          DrawHistBin(HistLayer, Hist.at<int>(i,0),
            i*3, Color, histBins, histEdge, histHeight);
        }
      }
    break;

    default:
      return;
  }

  add(HistLayer, HistImage, HistImage);
}

//=================================================================================================
// Desrcription:
//   Helper function that draws a bin on the histogram image
//=================================================================================================
void DrawHistBin(Mat& HistLayer, int value,
                 unsigned x, const Scalar& Color,
                 unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  unsigned pixelHeight = (unsigned)value;
  if (pixelHeight)
  {
    line(HistLayer,
         Point(x + histEdge, histEdge + histHeight),
         Point(x + histEdge, histEdge + histHeight - pixelHeight), Color);
  }
}

//=================================================================================================
// Desrcription:
//   Overloaded function that accepts a float for the bin height
//=================================================================================================
void DrawHistBin(Mat& HistLayer, float value,
                 unsigned x, const Scalar& Color,
                 unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  unsigned pixelHeight = (unsigned)cvRound(value);
  if (pixelHeight)
  {
    line(HistLayer,
         Point(x + histEdge, histEdge + histHeight),
         Point(x + histEdge, histEdge + histHeight - pixelHeight), Color);
  }
}

//=================================================================================================
// Desrcription:
//   Overloaded function that accepts a double for the bin height
//=================================================================================================
void DrawHistBin(Mat& HistLayer, double value,
                 unsigned x, const Scalar& Color,
                 unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  unsigned pixelHeight = (unsigned)cvRound(value);
  if (pixelHeight)
  {
    line(HistLayer,
         Point(x + histEdge, histEdge + histHeight),
         Point(x + histEdge, histEdge + histHeight - pixelHeight), Color);
  }
}

//=================================================================================================
// Description:
//   Takes the three channel BGR image (ImageBGR) and plots the corresponding histogram from each
//   channel onto ImageHist.  The colors for each channel histogram are combined additively.
//=================================================================================================
void DrawHistogramBGR(const IplImage *ImageBGR, IplImage* ImageHist)
{
  // Create a 1 channel image for each color
  IplImage *ImageRed   = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageBlue  = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageGreen = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);

  // Split the input image into blue/green/red channels
  cvCvtPixToPlane( ImageBGR, ImageBlue, ImageGreen, ImageRed, 0 );

  // Initialize histogram settings
  int HistSize = HIST_BINS;
  float Range[] = {0, 256}; //{0, 256} = 0 to 255
  float *Ranges[] = {Range};

  // Allocate memory for histograms
  CvHistogram* HistRed = cvCreateHist(1, &HistSize, CV_HIST_ARRAY, Ranges, 1);
  CvHistogram* HistBlue = cvCreateHist(1, &HistSize, CV_HIST_ARRAY, Ranges, 1);
  CvHistogram* HistGreen = cvCreateHist(1, &HistSize, CV_HIST_ARRAY, Ranges, 1);

  // Calculate the histograms
  cvCalcHist(&ImageRed, HistRed, 0, NULL);
  cvCalcHist(&ImageBlue, HistBlue, 0, NULL);
  cvCalcHist(&ImageGreen, HistGreen, 0, NULL);

  float MaxValueRed;
  float MaxValueGreen;
  float MaxValueBlue;

  // Get the maximum bin value in the histogram
  cvGetMinMaxHistValue(HistRed, 0, &MaxValueRed);
  cvGetMinMaxHistValue(HistBlue, 0, &MaxValueBlue);
  cvGetMinMaxHistValue(HistGreen, 0, &MaxValueGreen);

  // The largest value in all the HistImage is found.
   float MaxValue = max( max( MaxValueRed, MaxValueGreen), MaxValueBlue );

  // Scale the bin values so they can be drawn
  cvScale(HistRed->bins, HistRed->bins, (float)HIST_HEIGHT/MaxValue);
  cvScale(HistBlue->bins, HistBlue->bins, (float)HIST_HEIGHT/MaxValue);
  cvScale(HistGreen->bins, HistGreen->bins, (float)HIST_HEIGHT/MaxValue);

  // Draw each channel in the corresponding color
  DrawHistogram(HistRed, HistSize, ImageHist, RED);
  DrawHistogram(HistBlue, HistSize, ImageHist, BLUE);
  DrawHistogram(HistGreen, HistSize, ImageHist, GREEN);

  // Clean up
  cvReleaseImage(&ImageRed);
  cvReleaseImage(&ImageBlue);
  cvReleaseImage(&ImageGreen);
  cvReleaseHist(&HistRed);
  cvReleaseHist(&HistBlue);
  cvReleaseHist(&HistGreen);
}

//=================================================================================================
// Description:
//   Additional info:
//   http://opencv.willowgarage.com/documentation/cpp/imgproc_histograms.html
//=================================================================================================
void DrawHistogramBGR(const Mat& ImageBGR, Mat& ImageHist)
{
  // Initialize histogram settings
  int histSize[] = {HIST_BINS};
  float Range[] = {0, 256}; //{0, 256} = 0 to 255
  const float *Ranges[] = {Range};
  int chanB[] = {0};
  int chanG[] = {1};
  int chanR[] = {2};

  MatND HistB;
  MatND HistG;
  MatND HistR;

  calcHist(&ImageBGR, 1, chanB, Mat(), // do not use mask
           HistB, 1, histSize, Ranges,
           true, // the histogram is uniform
           false);

  calcHist(&ImageBGR, 1, chanG, Mat(), // do not use mask
           HistG, 1, histSize, Ranges,
           true, // the histogram is uniform
           false);

  calcHist(&ImageBGR, 1, chanR, Mat(), // do not use mask
           HistR, 1, histSize, Ranges,
           true, // the histogram is uniform
           false);

  double maxB = 0;
  double maxG = 0;
  double maxR = 0;

  minMaxLoc(HistB, 0, &maxB, 0, 0);
  minMaxLoc(HistG, 0, &maxG, 0, 0);
  minMaxLoc(HistR, 0, &maxR, 0, 0);

  double maxBGR = max(maxB, max(maxG, maxR));

  for (int i = 0; i < HistB.rows; i++)
  {
    HistB.at<float>(i,0) = (float)HIST_HEIGHT*HistB.at<float>(i,0)/(float)maxBGR;
    HistG.at<float>(i,0) = (float)HIST_HEIGHT*HistG.at<float>(i,0)/(float)maxBGR;
    HistR.at<float>(i,0) = (float)HIST_HEIGHT*HistR.at<float>(i,0)/(float)maxBGR;
  }

  DrawHistogram(HistB, ImageHist, BLUE_N);
  DrawHistogram(HistG, ImageHist, GREEN_N);
  DrawHistogram(HistR, ImageHist, RED_N);
}

//=================================================================================================
// Description:
//   Takes the three channel BGR image (ImageBGR) and plots the corresponding histogram of the
//   grayscale values in the image
//=================================================================================================
void DrawHistogramGray(const IplImage *ImageBGR, IplImage *ImageHist)
{
  // Create 1 channel image for grayscale representation
  IplImage *ImageGray = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);

  // Perform the color conversion to grayscale
  cvCvtColor(ImageBGR, ImageGray, CV_BGR2GRAY);

  // Initialize histogram settings
  int HistSize = HIST_BINS;
  float Range[] = {0, 256}; //{0, 256} = 0 to 255
  float *Ranges[] = {Range};

  // Allocate memory for the histogram
  CvHistogram* HistGray = cvCreateHist(1, &HistSize, CV_HIST_ARRAY, Ranges, 1);

  // Calculate the histogram
  cvCalcHist(&ImageGray, HistGray, 0, NULL);

  float MaxValue = 0;

  // Get the maximum bin value in the histogram
  cvGetMinMaxHistValue(HistGray, 0, &MaxValue);

  // Scale the bin values so they can be drawn
  cvScale(HistGray->bins, HistGray->bins, (float)HIST_HEIGHT/MaxValue);

  // Draw the histogram
  DrawHistogram(HistGray, HistSize, ImageHist, WHITE);

  // Clean up
  cvReleaseImage(&ImageGray);
  cvReleaseHist(&HistGray);
}

//=================================================================================================
// Description:
//   Overloaded function using the C++ formats/functions
//=================================================================================================
void DrawHistogramGray(const Mat& ImageBGR, Mat& ImageHist)
{
  // Create 1 channel image for grayscale representation
  Mat ImageGray = Mat(ImageBGR.rows, ImageBGR.cols, CV_8UC1);
  cvtColor(ImageBGR, ImageGray, CV_BGR2GRAY);

  // Initialize histogram settings
  int histSize[] = {HIST_BINS};
  float Range[] = {0, 256}; //{0, 256} = 0 to 255
  const float *Ranges[] = {Range};
  int channels[] = {0};

  MatND Hist;

  calcHist(&ImageGray, 1, channels, Mat(), // do not use mask
           Hist, 1, histSize, Ranges,
           true, // the histogram is uniform
           false);

  double maxVal=0;
  minMaxLoc(Hist, 0, &maxVal, 0, 0);

  for (int i = 0; i < Hist.rows; i++)
  {
    Hist.at<float>(i,0) = (float)HIST_HEIGHT*Hist.at<float>(i,0)/(float)maxVal;
  }

  DrawHistogram(Hist, ImageHist);
}

//=================================================================================================
// Description:
//   Draws the background and labels of the histogram
//=================================================================================================
void DrawHistBar(IplImage *HistImage, unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  // Clear image contents
  cvSetZero(HistImage);

  // Draw the horizontal axis
  cvLine(HistImage,
    cvPoint(histEdge, histEdge + histHeight),
    cvPoint(histEdge + 3*histBins, histEdge + histHeight),
    WHITE, 0);

  CvFont font;
  cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.3f, 0.3f, 0, 1);

  cvPutText(
    HistImage,
    "0",
    cvPoint(histEdge - 3, histEdge + histHeight + 10),
    &font,
    WHITE );

  // Create text to display number of histogram bins
  stringstream histBinsSS;
  histBinsSS << (histBins-1);

  cvPutText(
    HistImage,
    histBinsSS.str().c_str(),
    cvPoint(histEdge + 3*histBins - 10, histEdge + histHeight + 10),
    &font, WHITE);
}

//=================================================================================================
// Description:
//   Overloaded function, uses newer formats/functions
//=================================================================================================
void DrawHistBar(Mat& HistImage, unsigned histBins, unsigned histEdge, unsigned histHeight)
{
  // Draw the horizontal axis
  line(HistImage,
       Point(histEdge, histEdge + histHeight),
       Point(histEdge + 3*histBins, histEdge + histHeight),
       WHITE_N, 0);

  // Label initial bin
  putText(HistImage,
          "0", Point(histEdge - 3, histEdge + histHeight + 10),
          FONT_HERSHEY_SIMPLEX, 0.3f, WHITE_N);

  // Create text to display number of histogram bins
  stringstream histBinsSS;
  histBinsSS << (histBins-1);

  // Label last bin
  putText(
    HistImage,
    histBinsSS.str().c_str(),
    Point(histEdge + 3*histBins - 10, histEdge + histHeight + 10),
    FONT_HERSHEY_SIMPLEX, 0.3f, WHITE_N);
}

//=================================================================================================
// Description:
//   Takes the three channel BGR image ImageBGR and normalizes the image brightness where a
//   percentage of the pixels are discarded.  The minimum and maxium values int the image get
//   rescaled to 0 and 255 respectively.
//=================================================================================================
void NormalizeClipImageBGR(const IplImage *ImageBGR, IplImage *ImageBGRNorm, double clipPercent)
{
  IplImage *ImageHSV     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 3);
  IplImage *ImageHSVNorm = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 3);
  IplImage *ImageHue     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageSat     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageVal     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);

  // Convert from blue, green, red -> hue, value, saturation
  cvCvtColor(ImageBGR, ImageHSV, CV_BGR2HSV);

  // Split the input image into hue/saturation/value channels
  cvSplit(ImageHSV, ImageHue, ImageSat, ImageVal, 0);

  // Normalize the value channel (remove clipPercent% of the pixel values)
  NormalizeClipImageGray(ImageVal, clipPercent);

  // Reconstruct the image with the new value channel
  cvMerge(ImageHue, ImageSat, ImageVal, 0, ImageHSVNorm);

  // Convert back to blue, green, red
  cvCvtColor(ImageHSVNorm, ImageBGRNorm, CV_HSV2BGR);

  // Clean up
  cvReleaseImage(&ImageHSV);
  cvReleaseImage(&ImageHSVNorm);
  cvReleaseImage(&ImageHue);
  cvReleaseImage(&ImageSat);
  cvReleaseImage(&ImageVal);
}

//=================================================================================================
//=================================================================================================
void NormalizeImageBGR(const IplImage *ImageBGR, IplImage *ImageBGRNorm)
{
  IplImage *ImageHSV     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 3);
  IplImage *ImageHSVNorm = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 3);
  IplImage *ImageHue     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageSat     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageVal     = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);
  IplImage *ImageValNorm = cvCreateImage(cvGetSize(ImageBGR), IPL_DEPTH_8U, 1);

  // Convert from blue, green, red -> hue, value, saturation
  cvCvtColor(ImageBGR, ImageHSV, CV_BGR2HSV);

  // Split the input image into hue/saturation/value channels
  cvSplit(ImageHSV, ImageHue, ImageSat, ImageVal, 0);

  // Normalize the values of the value channel (stretch the histogram)
  cvNormalize(ImageVal, ImageValNorm, 0, 255, CV_MINMAX);

  // Reconstruct the image with the new value channel
  cvMerge(ImageHue, ImageSat, ImageValNorm, 0, ImageHSVNorm);

  // Convert back to blue, green, red
  cvCvtColor(ImageHSVNorm, ImageBGRNorm, CV_HSV2BGR);

  // Clean up
  cvReleaseImage(&ImageHSV);
  cvReleaseImage(&ImageHSVNorm);
  cvReleaseImage(&ImageHue);
  cvReleaseImage(&ImageSat);
  cvReleaseImage(&ImageVal);
  cvReleaseImage(&ImageValNorm);
}

//=================================================================================================
//=================================================================================================
void NormalizeImageBGR(const Mat& ImageBGR, Mat& ImageBGRNorm)
{

  Mat ImageHSV     = Mat(ImageBGR.size(), CV_8UC3);
  Mat ImageHSVNorm = Mat(ImageBGR.size(), CV_8UC3);

  cvtColor(ImageBGR, ImageHSV, CV_BGR2HSV);

  unsigned char* data     = ImageHSV.data;
  unsigned char* dataNorm = ImageHSVNorm.data;

  // The normalization procedure here is performed with efficiency in mind
  // Find min/max from the value channel
  unsigned char min = 255;
  unsigned char max = 0;
  for ( int i = 0; i < ImageHSV.rows*ImageHSV.cols; i++)
  {
    if( data[3*i+2] > max) max = data[3*i+2];
    if( data[3*i+2] < min) min = data[3*i+2];
  }

  for ( int i = 0; i < ImageHSV.rows*ImageHSV.cols; i++)
  {
    dataNorm[3*i]   = data[3*i];// Hue
    dataNorm[3*i+1] = data[3*i+1];//Saturation
     // Value
    dataNorm[3*i+2] =
      (unsigned char)cvRound(((double)data[3*i+2]-(double)min)*(255.0f/(double)(max-min)));
  }
  cvtColor(ImageHSVNorm, ImageBGRNorm, CV_HSV2BGR);
}

//=================================================================================================
// Description:
//  This is very similar to cvNormalize except a certain (approximate) percentage of pixels
//  (specified by clipPercent) are clipped from the image.  This is done to get rid of any
//  outliers during the normalization.  Modifications are performed on IplImage *Image directly.
//=================================================================================================
void NormalizeClipImageGray(IplImage *Image, double clipPercent)
{
  // It does not make sense to clip everything or have negative clip percentages
  if ((clipPercent >= 100) || (clipPercent < 0)) return;

  // Note: some operations below can be accomplished with opencv functions,
  // but are written in loops to keep the code easy to understand and efficient
  unsigned nl = Image->height;      // number of lines
  unsigned nc = Image->width;       // total number of elements per line
  unsigned step = Image->widthStep; // effective width
  unsigned bins[HIST_BINS];
  memset(bins, 0, HIST_BINS*sizeof(unsigned));
  unsigned max = HIST_BINS-1;
  unsigned min = 0;
  unsigned pixelCount = 0;

  // get the pointer to the image buffer
  unsigned char *data= reinterpret_cast<unsigned char *>(Image->imageData);

  // Get histogram
  for (unsigned i = 0; i < nl; i++ )
  {
    for (unsigned j = 0; j < nc; j++ )
    {
      bins[data[j]]++;
      pixelCount++;
    }
    data += step; // next line
  }

  // Maximum number of pixels to remove from the histogram
  // This is calculated by taking a percentage of the total number of pixels
  const double clipFraction = clipPercent/100.0f;
  unsigned pixelsToClip = cvRound(clipFraction*(double)pixelCount);
  unsigned pixelsToClipHalf = cvRound((double)pixelsToClip/2);
  unsigned binSum = 0;

  // Find the lower pixel bound
  if (bins[0] < pixelsToClipHalf)
  {
    binSum = bins[0];
    for (unsigned i = 1; i < 255; i++)
    {
      binSum = binSum + bins[i];
      if (binSum > pixelsToClipHalf)
      {
        min = i;
        break;
      }
    }
  }

  // Find the upper pixel bound
  if (bins[255] < pixelsToClipHalf)
  {
    binSum = bins[255];
    for (unsigned i = 255; i > 1; i--)
    {
      binSum = binSum + bins[i];
      if (binSum > pixelsToClipHalf)
      {
        max = i;
        break;
      }
    }
  }

  // Perform the normalization
  data = reinterpret_cast<unsigned char *>(Image->imageData);
  for (unsigned i = 0; i < nl; i++ )
  {
    for (unsigned j = 0; j < nc; j++ )
    {
      double newPixelVal = (double)((double)data[j]-(double)min)*(255.0f/(double)(max-min));

      if (newPixelVal > 255) // Take care of positive clipping
      {
        data[j] = 255;
      }
      else if(newPixelVal < 0) // Take care of negative clipping
      {
        data[j] = 0;
      }
      else // If there is no clipping
      {
        data[j] = cvRound(newPixelVal);
      }
    }
    data += step; // next line
  }
}
