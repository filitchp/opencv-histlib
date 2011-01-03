#ifndef HIST_LIB
#define HIST_LIB

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
#endif //end #ifndef HIST_LIB
