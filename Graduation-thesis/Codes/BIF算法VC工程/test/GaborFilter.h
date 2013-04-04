#ifndef	_GABORFILTER_H_
#define	_GABORFILTER_H_

#include <afx.h>

class _declspec(dllexport) CGaborFilter
{
public:
	BOOL GetGaborKernelData(float *pdata,int GaborWinWidth,int GaborWinHeight,int scale, int orientation,int Type);
	BOOL VisualizeGaborKernel(BYTE* pTransImg, int GaborWinWidth,int GaborWinHeight,int scale, int orientation,int nType);
	BOOL SetImageData(float *pdata,int ImgWidth,int ImgHeight,int scale, int orientation);
	BOOL SetImageData(BYTE *pdata,int ImgWidth,int ImgHeight,int scale, int orientation);
	BOOL SetGaborKernelParas(int KernelWidth,int KernelHeight,int scale, int nOrientation, float xSigma, float ySigma,float Kmax,float Frequency,CString StorePath);
	CGaborFilter();
	CGaborFilter(BOOL Create);  // this function decide whether create kernel data 
	CGaborFilter(int Orientation,int Scale);//确定尺度和方向参数的函数
	~CGaborFilter();
	
	
	BOOL SetImageData(BYTE *pdata, int ImgWidth,int ImgHeight);
	BOOL SetGaborKernelParas(int scale, int nOrientation, float xSigma, float ySigma);
	//BOOL GaborTransform();
	
	BOOL GetDataLength(int &nLen);
	BOOL GetGaborSize(int &nWidth,int &nHeight);	
	BOOL GetTransFormData(float *pTransData, int size,int nType); // type will decide the transform result,
	//    0 means Magnitude, 1 means real,2 means imaginary
	
	BOOL VisualizeGaborImage(BYTE* pTransImg,int size, int nType);
	BOOL VisualizeGaborKernel(BYTE* pTransImg,int GaborWinWidth,int GaborWinHeight,int scale, int orientation, int xSigma, int ySigma, int nType);
	void  GrayStrtch(int imagesize, float *pGabordata, BYTE *pdata);
private:
	
	float *m_pCurGaborKernel;
	
	float **m_ppGaborKernelReal;   // this pointer will be allocated space in KernelLoad()
	// the other functions  all are private type
	float **m_ppGaborKernelConj;
	float *m_pOriImageData;
	
	float* m_pReal;
	float* m_pImaginary;
	float* m_pMagnitude;
	
	int     m_nImgWidth;
	int     m_nImgHeight;
	int     m_nGaborWinWidth;
	int     m_nGaborWinHeight;
	BOOL    m_bKernelFileCreated;
	BOOL    m_bTransform;
	BOOL    m_bFaceGabor;
	BOOL    m_bFileLoad;
	float  m_dSigmaY;
	float  m_dSigmaX;
	float  m_dfrequency;
	float  m_dKmax;
	
	float * m_pKernal;
	int m_nScale;
	int m_nOrientation;
	
	float m_dlmd;
	float m_dSigma;
	int m_ns,m_nt,m_nsdown,m_ntdown;
	float m_dreal;
	float m_dconj;
	
private:
	CString m_strStorePath;
	BOOL MemoryFree();
	BOOL GaborTransform(int size, int scale ,int orientation);
	BOOL m_bParamentsSet;
	int m_nKernelHeight;
	int m_nKernelWidth;
	
	BOOL KernelLoad();  // during this function , 16 scales data set will be loaded
	BOOL KernelCreate(); //during this function, 16 scales data set will be loaded
	BOOL GaborTransform(int size);
	int  GetMatchScale();
	int  Get2MofSerialSize(int N);
	BOOL MatrixExtend(int OldWidth,int OldHeight,int NewWidth,int NewHeight, float **pOlddata, float **pNewdata);
	BOOL FFT2(short dir, long X_m,long Y_m, float **X,float **Y);
	BOOL FFT(short int dir,long m,float *x,float *y);
	void SetWinodwsSize(int imagewidth,int imageheight, int *widthup,
		int *widthdown,int *heightdown, int *heightup);
	void  ComplexMatirxProduction(int width, int height, float **inputA_X, float **inputA_Y, float **inputB_X, 
		float **inputB_Y, float **output_X, float **output_Y);
	void  MatrixPointerProduct(int width, int height, float **inputA, float **inputB, float **output);
	//  void  GrayStrtch(int imagesize, float *pGabordata, BYTE *pdata);
};
//包含工具函数的声明部分。

double stard_deviation(double *a,int Num);//求标准差

#endif




