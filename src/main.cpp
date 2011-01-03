#include "histLib.h"
#include <highgui.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
  // ============================Manually draw histogram (C++ style)===============================
  Mat HistImage = Mat(2*HIST_EDGE + HIST_HEIGHT, 2*HIST_EDGE + 3*HIST_BINS, CV_8UC3, Scalar(0));

  // Draw background and labels
  DrawHistBar(HistImage);

  // Create a row vector for histogram values
  Mat Hist = Mat(256, 1, CV_32S);

  // The ith bin gets i
  for (int i = 0; i < Hist.rows; i++)
  {
    Hist.at<int>(i,0) = i;
  }

  //Draw it!
  DrawHistogram(Hist, HistImage);

  if (imwrite("images/testRampA.hist.png", HistImage))
  {
    cout << "Manually draw histogram (C++ style)... saved testRampA.hist.png\n";
  }

  // =============================Manually draw histogram (C style)================================
  CvSize HistSize = cvSize(2*HIST_EDGE + 3*HIST_BINS, 2*HIST_EDGE + HIST_HEIGHT);
  IplImage *HistMImg = cvCreateImage(HistSize , IPL_DEPTH_8U, 3);

  // Draw the histogram background and labels
  DrawHistBar(HistMImg);

  // Create a row vector for histogram values
  CvMat* Histo = cvCreateMat(256, 1, CV_32S);

  // The ith bin gets 255 - i
  for (int i = 0; i < Histo->rows; i++)
  {
    Histo->data.i[i] = 255 - i;
  }

  //Draw it!
  DrawHistogram(Histo, HistMImg);

  if (cvSaveImage("images/testRampB.hist.png", HistMImg))
  {
    cout << "Manually draw histogram (C style)... saved testRampB.hist.png\n";
  }

  // Clean up
  cvReleaseImage(&HistMImg);
  cvReleaseMat(&Histo);

  //===========================Value (grayscale) histogram (C++ style)=============================
  // Open the image
  Mat ImageV = imread("images/fiveShades.png");

  // Generate color histogram for the current image
  Mat HistImageV = Mat(2*HIST_EDGE + HIST_HEIGHT, 2*HIST_EDGE + 3*HIST_BINS, CV_8UC3, Scalar(0));

  // Draw the histogram background and labels
  DrawHistBar(HistImageV);

  // Draw the histogram levels
  DrawHistogramGray(ImageV, HistImageV);

  // Save the histogram image
  if (imwrite("images/fiveShadesA.hist.png", HistImageV))
  {
    cout << "Value histogram (C++ style)... saved fiveShadesA.hist.png\n";
  }

  //============================Value (grayscale) histogram (C style)==============================
  // Open the image
  IplImage *ImgV = cvLoadImage("images/fiveShades.png");

  // If we opened a valid image
  if (ImgV)
  {
    // Generate color histogram for the current image
    CvSize HistSize = cvSize(2*HIST_EDGE + 3*HIST_BINS, 2*HIST_EDGE + HIST_HEIGHT);
    IplImage *HistImgV = cvCreateImage(HistSize , IPL_DEPTH_8U, 3);

    // Draw the histogram background and labels
    DrawHistBar(HistImgV);

    // Draw the histogram levels
    DrawHistogramGray(ImgV, HistImgV);

    // Save the histogram image
    if (cvSaveImage("images/fiveShadesB.hist.png", HistImgV))
    {
      cout << "Value histogram (C style)... saved fiveShadesB.hist.png\n";
    }

    // Clean up
    cvReleaseImage(&HistImgV);
    cvReleaseImage(&ImgV);
  }

  //================================BGR histogram (C++ style)======================================
  // Open the image
  Mat ImageBGR = imread("images/rgb.png");

  // Generate color histogram for the current image
  Mat HistImageBGR = Mat(2*HIST_EDGE + HIST_HEIGHT, 2*HIST_EDGE + 3*HIST_BINS, CV_8UC3, Scalar(0));

  // Draw the histogram background and labels
  DrawHistBar(HistImageBGR);

  // Draw the histogram levels
  DrawHistogramBGR(ImageBGR, HistImageBGR);

  // Save the histogram image
  if (imwrite("images/rgbA.hist.png", HistImageBGR))
  {
    cout << "BGR histogram (C++ style)... saved rgbA.hist.png\n";
  }

  //=================================BGR histogram (C style)=======================================
  // Open the image
  IplImage *ImgBGR = cvLoadImage("images/rgb.png");

  // If we opened a valid image
  if (ImgBGR)
  {
    // Generate color histogram for the current image
    CvSize HistSize = cvSize(2*HIST_EDGE + 3*HIST_BINS, 2*HIST_EDGE + HIST_HEIGHT);
    IplImage *HistImgBGR = cvCreateImage(HistSize, IPL_DEPTH_8U, 3);

    // Draw the histogram background and labels
    DrawHistBar(HistImgBGR);

    // Draw the histogram levels
    DrawHistogramBGR(ImgBGR, HistImgBGR);

    // Save the histogram image
    if (cvSaveImage("images/rgbB.hist.png", HistImgBGR))
    {
      cout << "BGR histogram (C style)... saved rgbB.hist.png\n";
    }

    // Clean up
    cvReleaseImage(&HistImgBGR);
    cvReleaseImage(&ImgBGR);
  }

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

  //=================================Auto levels (C style)=======================================
  // Open the image
  IplImage *ImgLowContrastBGR = cvLoadImage("images/fiveShadesLowContrast.png");

  // If we opened a valid image
  if (ImgLowContrastBGR)
  {
    IplImage *ImgLowContrastBGRNorm = cvCreateImage(cvGetSize(ImgLowContrastBGR), IPL_DEPTH_8U, 3);
    NormalizeClipImageBGR(ImgLowContrastBGR, ImgLowContrastBGRNorm);

    // Generate color histogram for the current image
    CvSize HistSize = cvSize(2*HIST_EDGE + 3*HIST_BINS, 2*HIST_EDGE + HIST_HEIGHT);
    IplImage *HistImgBGR     = cvCreateImage(HistSize, IPL_DEPTH_8U, 3);
    IplImage *HistImgBGRNorm = cvCreateImage(HistSize, IPL_DEPTH_8U, 3);

    // Draw the histogram background and labels
    DrawHistBar(HistImgBGR);
    DrawHistBar(HistImgBGRNorm);

    // Draw the histogram levels
    DrawHistogramBGR(ImgLowContrastBGR, HistImgBGR);
    DrawHistogramBGR(ImgLowContrastBGRNorm, HistImgBGRNorm);

    // Save the histogram image
    if (cvSaveImage("images/fiveShadesLowContrastB.hist.png", HistImgBGR))
    {
      cout << "Auto levels (C style)... saved fiveShadesLowContrastB.hist.png\n";
    }
    if (cvSaveImage("images/fiveShadesLowContrastNormB.hist.png", HistImgBGRNorm))
    {
      cout << "Auto levels (C style)... saved fiveShadesLowContrastNormB.hist.png\n";
    }
    if (cvSaveImage("images/fiveShadesLowContrastNormB.png", ImgLowContrastBGRNorm))
    {
      cout << "Auto levels (C style)... saved fiveShadesLowContrastNormB.png\n";
    }

    // Clean up
    cvReleaseImage(&HistImgBGR);
    cvReleaseImage(&HistImgBGRNorm);
    cvReleaseImage(&ImgLowContrastBGR);
    cvReleaseImage(&ImgLowContrastBGRNorm);
  }


  // Leave the prompt up so user can view messages (for Windows)
  cout << "Enter some text to exit\n";
  int someInput;
  cin >> someInput;
  return 0;
}
