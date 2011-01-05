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

#ifndef _HIST_LIB
#define _HIST_LIB

#include <cv.h>

// Default input values
#define HIST_HEIGHT 300 // Height of histogram image
#define HIST_BINS 256 // Number of bins in histogram
#define HIST_EDGE 15 // Border
#define HIST_ROWS 2*HIST_EDGE + HIST_HEIGHT
#define HIST_COLS 2*HIST_EDGE + 3*HIST_BINS

// Colors
#define RED   cvScalar(0x00, 0x00, 0xff, 0)
#define GREEN cvScalar(0x00, 0xff, 0x00, 0)
#define BLUE  cvScalar(0xff, 0x00, 0x00, 0)
#define WHITE cvScalar(0xff, 0xff, 0xff, 0)
#define RED_N   cv::Scalar(0x00, 0x00, 0xff, 0)
#define GREEN_N cv::Scalar(0x00, 0xff, 0x00, 0)
#define BLUE_N  cv::Scalar(0xff, 0x00, 0x00, 0)
#define WHITE_N cv::Scalar(0xff, 0xff, 0xff, 0)

// Histogram functions

void DrawHistogramBGR(const IplImage* ImageBGR, IplImage* ImageHist);
void DrawHistogramBGR(const cv::Mat& ImageBGR,  cv::Mat& ImageHist);

void DrawHistogramGray(const IplImage* ImageBGR, IplImage* ImageHist);
void DrawHistogramGray(const cv::Mat& ImageBGR,  cv::Mat& ImageHist);


void DrawHistogram(CvHistogram* Hist,
                   unsigned HistSize,
                   IplImage* HistImage,
                   CvScalar Color      = WHITE,
                   unsigned histBins   = HIST_BINS,
                   unsigned histEdge   = HIST_EDGE,
                   unsigned histHeight = HIST_HEIGHT);

void DrawHistogram(CvMat* Hist,
                   IplImage* HistImage,
                   CvScalar Color      = WHITE,
                   unsigned histBins   = HIST_BINS,
                   unsigned histEdge   = HIST_EDGE,
                   unsigned histHeight = HIST_HEIGHT);

void DrawHistogram(cv::Mat& Hist,
                   cv::Mat& HistImage,
                   cv::Scalar Color    = WHITE_N,
                   unsigned histBins   = HIST_BINS,
                   unsigned histEdge   = HIST_EDGE,
                   unsigned histHeight = HIST_HEIGHT);

void DrawHistBar(IplImage* HistImage,
                 unsigned histBins   = HIST_BINS,
                 unsigned histEdge   = HIST_EDGE,
                 unsigned histHeight = HIST_HEIGHT);

void DrawHistBar(cv::Mat& HistImage,
                 unsigned histBins   = HIST_BINS,
                 unsigned histEdge   = HIST_EDGE,
                 unsigned histHeight = HIST_HEIGHT);

// Normalization functions
void NormalizeImageBGR(const IplImage *ImageBGR, IplImage *ImageBGRNorm);
void NormalizeImageBGR(const cv::Mat&  ImageBGR, cv::Mat&  ImageBGRNorm);

void NormalizeClipImageBGR(const IplImage *ImageBGR, IplImage *ImageBGRNorm, double clipPercent = 2.0f);
void NormalizeClipImageBGR(const cv::Mat&  ImageBGR, cv::Mat&  ImageBGRNorm, double clipPercent = 2.0f);

void NormalizeClipImageGray(IplImage *Image, double clipPercent = 2.0f);
void NormalizeClipImageGray(cv::Mat&  Image, double clipPercent = 2.0f);

// Helper functions
void DrawHistBin(cv::Mat& HistLayer, int value, unsigned x,
             const cv::Scalar& Color = WHITE_N,
             unsigned histBins       = HIST_BINS,
             unsigned histEdge       = HIST_EDGE,
             unsigned histHeight     = HIST_HEIGHT);

void DrawHistBin(cv::Mat& HistLayer, float value, unsigned x,
             const cv::Scalar& Color = WHITE_N,
             unsigned histBins       = HIST_BINS,
             unsigned histEdge       = HIST_EDGE,
             unsigned histHeight     = HIST_HEIGHT);

void DrawHistBin(cv::Mat& HistLayer, double value, unsigned x,
             const cv::Scalar& Color = WHITE_N,
             unsigned histBins       = HIST_BINS,
             unsigned histEdge       = HIST_EDGE,
             unsigned histHeight     = HIST_HEIGHT);

#endif //end #ifndef _HIST_LIB
