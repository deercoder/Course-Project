#include "stdafx.h"
#include <stdio.h>
#include "GaborFilter.h"
#include "math.h"

template <class T>
T**	New2DPointer(int n1D, int n2D)
{
	T**		pp;
	typedef		T*	T_P;
	int		i, j;
	if(n1D <= 0 || n2D <= 0)
		return FALSE;

	pp = new T_P[n1D];
	if(!pp)
		return NULL;
	for(i=0; i<n1D; i++)
	{
		pp[i] = new T[n2D];
		if(!pp[i])
		{
			for(j=0; j<i; j++)
			{
				delete	pp[j];
			}
			delete	pp;
			return NULL;
		}
	}
	return pp;
}

template <class T>
void	Delete2DPointer(T **pp, int n1D)
{
	int		i;
	if(pp == NULL)
		return;

	for(i=0; i<n1D; i++)
	{
		if(pp[i])
			delete pp[i];
	}

	delete	pp;
}

#define pi 3.1415926535897932384626433832795


CGaborFilter::CGaborFilter()//????????5????8????(???)
{
	m_pOriImageData = NULL;
    m_pReal = NULL;     
	m_pImaginary = NULL;
	m_pMagnitude = NULL;
	m_pCurGaborKernel = NULL;

    m_ppGaborKernelReal = NULL;
    m_ppGaborKernelConj = NULL;
	m_pKernal = NULL;
    m_bFileLoad = FALSE;

	m_nGaborWinWidth = 64;
	m_nGaborWinHeight = 64;
	m_bParamentsSet = false;
	m_bTransform = FALSE;
	m_strStorePath  = "";
	m_nScale = 5;
	m_nOrientation = 8;
	
	FILE *pfile = fopen("Gabor_Kernel_64x64.Gabor","r");
	
	if(!pfile) 
	{
         
		 KernelCreate();
		 KernelLoad();

	}
	else
	{
		fclose(pfile);
		KernelLoad();
		m_bFileLoad = TRUE;
	}

	//SetGaborKernelParas(64,64,5,8,2*pi,2*pi, pi*1.1,sqrt(2));


}

CGaborFilter::CGaborFilter(int Orientation,int Scale)//??????????(??????)
{
	m_pOriImageData = NULL;
    m_pReal = NULL;     
	m_pImaginary = NULL;
	m_pMagnitude = NULL;
	m_pCurGaborKernel = NULL;
	
    m_ppGaborKernelReal = NULL;
    m_ppGaborKernelConj = NULL;
	m_pKernal = NULL;
    m_bFileLoad = FALSE;
	
	m_nGaborWinWidth = 64;
	m_nGaborWinHeight = 64;
	m_bParamentsSet = false;
	m_bTransform = FALSE;
	m_strStorePath  = "";

	m_nScale = Scale;
	m_nOrientation = Orientation;

	FILE *pfile = fopen("Gabor_Kernel_64x64.Gabor","r");
	
	if(!pfile) 
	{
		
		KernelCreate();
		KernelLoad();
		
	}
	else
	{
		fclose(pfile);
		KernelLoad();
		m_bFileLoad = TRUE;
	}
	
	//SetGaborKernelParas(64,64,5,8,2*pi,2*pi, pi*1.1,sqrt(2));
	
	
}




CGaborFilter::~CGaborFilter()
{
    MemoryFree();
}

BOOL CGaborFilter::SetImageData(BYTE *pdata, int ImgWidth,int ImgHeight)
{
	int size;
	int i;
	if(m_pOriImageData != NULL )
	{
		delete []m_pOriImageData;
		m_pOriImageData = NULL;
	}

	m_nImgWidth = ImgWidth; 
    m_nImgHeight = ImgHeight;

	size = ImgWidth * ImgHeight;

	m_pOriImageData = new float[size];
	for(i =0 ;i < size ; i++)
	{
		m_pOriImageData[i] = (float)pdata[i];
	}
   
	m_bTransform = GaborTransform(size);
	
    
	return TRUE;
}


BOOL CGaborFilter::KernelCreate()
{
	int i,j;
	if(m_bParamentsSet == false)
	{
		m_dSigma  = 2*pi;
		m_dfrequency = sqrt((double)2);
		m_dKmax  = pi/2;
	}
	else
	{
		m_dSigma = m_dSigmaX;
	}
	int x,y;
	int widthdown,widthup,heightdown,heightup;
	int k;
	
	CString Gaborfile;

	float *pImagereal = NULL;
	float * pImageconj = NULL;

    float preConstant_Kuv;
	float postConstant;
 // m_nGaborWinWidth = 64;
//	m_nGaborWinHeight = 64;
	FILE  *pfile; 
	postConstant    = exp(-m_dSigma*m_dSigma/2);
	
	SetWinodwsSize(m_nGaborWinWidth,m_nGaborWinHeight,&widthup,&widthdown,&heightdown,&heightup);
    int size =m_nGaborWinWidth * m_nGaborWinHeight;
	
	pImagereal = new float[size];
	pImageconj = new float[size];
   

	float exppart;
	float Phi ;
    float Kv  ;

	//???Gabor_Kernel?64*64?,??????????????
	if(m_bParamentsSet == false )
	{
	   Gaborfile = 	m_strStorePath + CString("Gabor_Kernel_64x64.Gabor") ; 
//	   m_nScale = 5;
	   m_nScale = 16;
	   m_nOrientation = 8;
	}
	else
	{
        Gaborfile =	m_strStorePath + CString("Gabor_Kernel.Gabor");
		
	}
    pfile = fopen(Gaborfile,"wb");

//	float angle;
    for(j=0;j<m_nOrientation;j++)
	{
		Phi = j * pi / (float)m_nOrientation;
		
		for(i=0;i<m_nScale;i++)
		{   
			
			preConstant_Kuv = pow((double)(m_dKmax / pow(m_dfrequency,(int)i)),(double)2.0);
			Kv  = m_dKmax / pow(m_dfrequency,i);
		//	Kv= i*m_dfrequency/16 ; 
			
			
			k = 0;			
			for( x = heightdown ; x <= heightup; x++ )
			{
				for( y= widthdown; y<= widthup; y++)
				{
				//	angle = 2* pi * Kv * sqrt(x*x + y * y);
                //    exppart =exp(-(x*x + y * y)/(2*m_dSigma*m_dSigma))/(2*pi *m_dSigma*m_dSigma);
				
					//	exppart = exp(-1 * preConstant_Kuv * (x*x/(m_dSigmaX*m_dSigmaX) + y*y/(m_dSigmaY*m_dSigmaY))) * preConstant_Kuv / (m_dSigmaX*m_dSigmaY) ;
				//	preConstant_Kuv = pow((m_dKmax / pow(m_dfrequency,3)),2.0);

					exppart = exp(-1 * preConstant_Kuv * (x*x/(m_dSigmaX*m_dSigmaX) + y*y/(m_dSigmaY*m_dSigmaY))) * preConstant_Kuv / (m_dSigmaX*m_dSigmaY) ;
					pImagereal[k] =  exppart * ( cos(  Kv*(  cos(Phi)*x + sin(Phi)*y ) ) - postConstant );
					pImageconj[k] =  exppart * ( sin(  Kv*(  cos(Phi)*x + sin(Phi)*y ) ) );
				//	pImagereal[k] = exppart*cos(angle);
				//	pImageconj[k] = exppart*sin(angle);
					k++;
				}
			}
			
			//		fwrite(&m_nGaborWinWidth,sizeof(int),1,pfile);
			//		fwrite(&m_nGaborWinHeight,sizeof(int),1,pfile);
			fwrite(pImagereal,sizeof(float),size,pfile);
			fwrite(pImageconj,sizeof(float),size,pfile);
			
		}
	}

	fclose(pfile);
	delete []pImagereal;
	delete []pImageconj;
    return TRUE;

}

BOOL CGaborFilter::KernelLoad()
{
    int i;
	CString GaborFile;
	int size;
	
    FILE * pfile;
    
  /*  if( m_ppGaborKernelReal != NULL) Delete2DPointer 
    m_ppGaborKernelConj
	*/	
	size = m_nGaborWinWidth * m_nGaborWinHeight;
	if( m_bParamentsSet == false)
	{
		m_ppGaborKernelReal = New2DPointer<float>(m_nScale*m_nOrientation,size);
        m_ppGaborKernelConj = New2DPointer<float>(m_nScale*m_nOrientation,size);
	    GaborFile =	m_strStorePath + CString("Gabor_Kernel_64x64.Gabor") ; 
		pfile = fopen(GaborFile,"rb");
		if(!pfile ) return FALSE;
		int k;
		for(i=0;i<m_nScale*m_nOrientation;i++)
		{
			k = fread(m_ppGaborKernelReal[i],sizeof(float),size,pfile);
			k = fread(m_ppGaborKernelConj[i],sizeof(float),size,pfile);
			
		}
		
	}
	else
	{ 
		if(m_ppGaborKernelReal != NULL ) 
			 Delete2DPointer<float>(m_ppGaborKernelReal,m_nScale*m_nOrientation);
			
		 if(m_ppGaborKernelConj != NULL )   
			 Delete2DPointer<float>(m_ppGaborKernelConj,m_nScale*m_nOrientation);
		 
		 GaborFile = 	m_strStorePath + CString("Gabor_Kernel.Gabor") ; 	
		 
		 m_ppGaborKernelReal = New2DPointer<float>(m_nScale*m_nOrientation,size);
		 m_ppGaborKernelConj = New2DPointer<float>(m_nScale*m_nOrientation,size);
		 
		 
		 pfile = fopen(GaborFile,"rb");
		 if(!pfile ) return FALSE;
		 int k;
		 for(i=0;i<m_nScale*m_nOrientation;i++)
		 {
			 k = fread(m_ppGaborKernelReal[i],sizeof(float),size,pfile);
			 k = fread(m_ppGaborKernelConj[i],sizeof(float),size,pfile);
			 
		 }
		
	}
	fclose(pfile);
	return TRUE;
}

BOOL CGaborFilter::SetGaborKernelParas(int scale, int nOrientation, float xSigma, float ySigma)
{
	 m_nScale = scale;
     m_nOrientation = nOrientation;
	 m_dSigmaY = xSigma ;
	 m_dSigmaX = ySigma ;
     return TRUE;
}




BOOL CGaborFilter::GaborTransform(int size)
 // type will decide the transform result,
{
	if(size !=  	m_nImgWidth*m_nImgHeight)   return FALSE;
	int ScaleIdex;
	int GaborSize = m_nGaborWinWidth * m_nGaborWinHeight;
	int ImageSize = m_nImgWidth*m_nImgHeight;
	int i,j;


	float *pRealpart = NULL ;
	float *pConjpart = NULL ;
    
	float **pImageReal = NULL ;
	float **pImageConj = NULL ;
	float **pGaborReal = NULL ; 
	float **pGaborConj = NULL ;
    
	int  ExtendedWidth,ExtendedHeight;

    pGaborReal = New2DPointer<float>(m_nGaborWinHeight,m_nGaborWinWidth);
	pGaborConj = New2DPointer<float>(m_nGaborWinHeight,m_nGaborWinWidth);

	
	ScaleIdex =  GetMatchScale();
	//////////////////////////////
    //ScaleIdex = 4;
	//////////////////////////////
	int dsize = sizeof(float);
	int BufferSize = m_nGaborWinWidth * dsize;
	float *pReal = NULL, *pConj = NULL;
	
	pReal = m_ppGaborKernelReal[ScaleIdex];
	pConj = m_ppGaborKernelConj[ScaleIdex];
	
	for(i = 0; i < m_nGaborWinHeight; i++)
	{
		//memcpy(pGaborReal[0],m_ppGaborKernelReal[ScaleIdex],GaborSize*dsize);
		//memcpy(pGaborConj[0],m_ppGaborKernelConj[ScaleIdex],GaborSize*dsize);
       memcpy(pGaborReal[i],pReal, BufferSize);
	   memcpy(pGaborConj[i],pConj, BufferSize);
	   pReal += m_nGaborWinWidth;
	   pConj += m_nGaborWinWidth;
    }
	pReal = NULL;
	pConj = NULL;
	
	pImageReal =  New2DPointer<float>(m_nImgHeight,m_nImgWidth);
	pImageConj =  New2DPointer<float>(m_nImgHeight,m_nImgWidth);
    
	float *pImage = NULL;
	pImage =  m_pOriImageData;
	BufferSize = m_nImgWidth * dsize ;
    
	for(i= 0 ; i < m_nImgHeight; i++)
	{
		memcpy(pImageReal[i],pImage,BufferSize);
		memset(pImageConj[i],0,BufferSize);
		pImage += m_nImgWidth;
	}
    pImage = NULL;

	ExtendedWidth  =  m_nImgWidth + m_nGaborWinWidth  - 1 ;
	ExtendedHeight =  m_nImgHeight + m_nGaborWinHeight - 1 ;
    
	long Wid_M =  Get2MofSerialSize(ExtendedWidth);
	long Hei_M =  Get2MofSerialSize(ExtendedHeight);
	
	int FFTWidth  = (int)pow((double)2,(int)Wid_M);
	int FFTHeight = (int)pow((double)2,(int)Hei_M);
    
	float **pGaborRealExtended = New2DPointer<float>(FFTHeight,FFTWidth);
    float **pGaborConjExtended = New2DPointer<float>(FFTHeight,FFTWidth);
    
    MatrixExtend(m_nGaborWinWidth,m_nGaborWinHeight,FFTWidth,FFTHeight,pGaborReal,pGaborRealExtended);
    MatrixExtend(m_nGaborWinWidth,m_nGaborWinHeight,FFTWidth,FFTHeight,pGaborConj,pGaborConjExtended);
	
	Delete2DPointer<float>(pGaborReal,m_nGaborWinHeight);
	Delete2DPointer<float>(pGaborConj,m_nGaborWinHeight);
    
	float **pImageRealExtended = New2DPointer<float>(FFTHeight,FFTWidth);
    float **pImageConjExtended = New2DPointer<float>(FFTHeight,FFTWidth);

	MatrixExtend(m_nImgWidth,m_nImgHeight,FFTWidth,FFTHeight,pImageReal,pImageRealExtended);
    MatrixExtend(m_nImgWidth,m_nImgHeight,FFTWidth,FFTHeight,pImageConj,pImageConjExtended);
	
	Delete2DPointer<float>(pImageReal,m_nImgHeight);
	Delete2DPointer<float>(pImageConj,m_nImgHeight);

	float **pImageRealTrans = New2DPointer<float>(FFTHeight,FFTWidth);
    float **pImageConjTrans = New2DPointer<float>(FFTHeight,FFTWidth);

	FFT2(1,Wid_M,Hei_M,pGaborRealExtended,pGaborConjExtended);
	FFT2(1,Wid_M,Hei_M,pImageRealExtended,pImageConjExtended);   
	ComplexMatirxProduction(FFTWidth,FFTHeight,pImageRealExtended,pImageConjExtended,
                            pGaborRealExtended,pGaborConjExtended,pImageRealTrans,pImageConjTrans);
	FFT2(-1,Wid_M,Hei_M,pImageRealTrans,pImageConjTrans);

	Delete2DPointer<float>(pGaborRealExtended,FFTHeight); 
    Delete2DPointer<float>(pGaborConjExtended,FFTHeight);
	
	Delete2DPointer<float>(pImageRealExtended,FFTHeight); 
    Delete2DPointer<float>(pImageConjExtended,FFTHeight);

	int widthup,widthdown,heightdown,heightup;
    SetWinodwsSize(m_nGaborWinWidth,m_nGaborWinHeight,&widthup,&widthdown,&heightdown,&heightup);
    
   
	if(m_pReal  != NULL) 
	{
		delete m_pReal;
		m_pReal = NULL;
	}
	if(m_pImaginary != NULL)
	{
		delete m_pImaginary;
		m_pImaginary = NULL;
	}
	if(m_pMagnitude != NULL)
	{
		delete m_pMagnitude;
        m_pMagnitude = NULL;
	}

	m_pReal = new float[ImageSize];     
    m_pImaginary = new float[ImageSize];
    m_pMagnitude = new float[ImageSize];




	int k=0;
	for(i = abs(heightdown); i < m_nImgHeight+m_nGaborWinHeight-1-heightup ;i ++)
	{
		for(j = abs(widthdown) ; j < m_nImgWidth+m_nGaborWinWidth-1-widthup ;j++)
		{
           m_pMagnitude[k] = sqrt(pImageRealTrans[i][j]*pImageRealTrans[i][j] + 
			                           pImageConjTrans[i][j]*pImageConjTrans[i][j]);
	       m_pReal[k] = pImageRealTrans[i][j];
		   m_pImaginary[k] = pImageConjTrans[i][j];
		   k++;
		   
		}
	}



    Delete2DPointer<float>(pImageRealTrans,FFTHeight); 
    Delete2DPointer<float>(pImageConjTrans,FFTHeight);	
    
    return TRUE;

}    

int CGaborFilter::GetMatchScale()
{
    int scale;
	float a = 0.0214;
	float b = -0.8;
	if(m_nImgHeight <= 64 )
	{
		scale = 0;
	}
	else
	{
	  float y = m_nImgHeight * a + b;
	  int temp = abs(int(ceil(y))); 
      scale =  temp ;// + 1  ;	
	} 
	
	if(m_nImgHeight > 128 && m_nImgHeight <200 ) return scale-1; 
	else
		if(m_nImgHeight > 200 ) return scale-2; 
		    else return scale;
    
}  

int CGaborFilter::Get2MofSerialSize(int N)
{
	if(N<=0) return -1;
    if(N==1) return 1; 
	
	int i;

	int m=0;
	i =1;
	while( i < N)
	{   
        i = i*2;
		m ++;
	}
	return m;
}

BOOL CGaborFilter::MatrixExtend(int OldWidth,int OldHeight,int NewWidth,int NewHeight, float **pOlddata, float **pNewdata)
{
   int x,y;
   
  
   for(y = 0; y < NewHeight; y++)
   {
	   for(x = 0; x < NewWidth; x++)
	   {
           if( y< OldHeight &&  x< OldWidth)
		   {
              pNewdata[y][x] = pOlddata[y][x];      
			 //   float temp = pOlddata[y][x];      
		   }
		   else
		   {
			   pNewdata[y][x] = 0.0 ;
		   }
	   }

   }


   return(TRUE);
}


BOOL CGaborFilter::FFT2(short dir, long X_m, long Y_m, float **X, float **Y)
{       
	/********************************************************
	*  dir = 1 means forward , -1 means backward
	*  X_m  means 2^X_m length of X direction
	*  Y_m  means 2^Y_m length of Y direction
	*  **X  real part, ** conj part
	**********************************************************/
	int i ,j ;
    int height;
	int width;

	height = (int)pow((double)2,Y_m);
	width  = (int)pow((double)2,X_m);
	float *tempX = NULL;
	float *tempY = NULL;
	int Max ;
	if(height >= width ) Max =height;
	   else  Max = width;
    tempX  =  new float[Max];
	tempY  =  new float[Max];
	for(i=0 ; i<height;i++)
	{
	   	FFT(dir,X_m,X[i],Y[i]);	
	}
	
	for(j=0 ; j<width;j++)
	{   
		for(i=0 ; i<height;i++)
		{
			tempX[i] = X[i][j];
			tempY[i] = Y[i][j];
		}
	   	FFT(dir,Y_m,tempX,tempY);	
		for(i=0 ; i<height;i++)
		{
			X[i][j] = tempX[i]  ;
		    Y[i][j] = tempY[i]  ;
		}
	}
   delete []tempX;
   delete []tempY;
   return TRUE;
}


BOOL CGaborFilter::FFT(short dir, long m, float *x, float *y)
{
   
/*
   This computes an in-place complex-to-complex FFT 
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform 
*/	
   long n,i,i1,j,k,i2,l,l1,l2;
   float c1,c2,tx,ty,t1,t2,u1,u2,z;

   /* Calculate the number of points */
   n = 1;
   for (i=0;i<m;i++) 
      n *= 2;

   /* Do the bit reversal */
   i2 = n >> 1;
   j = 0;
   for (i=0;i<n-1;i++) {
      if (i < j) {
         tx = x[i];
         ty = y[i];
         x[i] = x[j];
         y[i] = y[j];
         x[j] = tx;
         y[j] = ty;
      }
      k = i2;
      while (k <= j) {
         j -= k;
         k >>= 1;
      }
      j += k;
   }

   /* Compute the FFT */
   c1 = -1.0; 
   c2 = 0.0;
   l2 = 1;
   for (l=0;l<m;l++) {
      l1 = l2;
      l2 <<= 1;
      u1 = 1.0; 
      u2 = 0.0;
      for (j=0;j<l1;j++) {
         for (i=j;i<n;i+=l2) {
            i1 = i + l1;
            t1 = u1 * x[i1] - u2 * y[i1];
            t2 = u1 * y[i1] + u2 * x[i1];
            x[i1] = x[i] - t1; 
            y[i1] = y[i] - t2;
            x[i] += t1;
            y[i] += t2;
         }
         z =  u1 * c1 - u2 * c2;
         u2 = u1 * c2 + u2 * c1;
         u1 = z;
      }
      c2 = sqrt((1.0 - c1) / 2.0);
      if (dir == 1) 
         c2 = -c2;
      c1 = sqrt((1.0 + c1) / 2.0);
   }

   /* Scaling for forward transform */
   if (dir == -1) {
      for (i=0;i<n;i++) {
         x[i] /= n;
         y[i] /= n;
      }
   }
   
   return(TRUE);
}

void CGaborFilter::SetWinodwsSize(int imagewidth,int imageheight, int *widthup,
		                int *widthdown,int *heightdown, int *heightup)
{
    /***********************************************************
     * ??????Gabor?????,???(0,0)
     * this function set the windows size of Gaobr, the original for 
	 * Gabor is (0,0)
	 ***********************************************************   */
	int remainder;
	
	remainder = imagewidth % 2;
	
	if(remainder == 0 )
	{
        *widthdown = -(imagewidth / 2 - 1);
		*widthup   = imagewidth / 2 ;

	}
	else
	{
        *widthdown = - (imagewidth-1)/ 2;
		*widthup   =  (imagewidth-1) / 2;
	}
    
	remainder = imageheight % 2;
	
	if(remainder == 0 )
	{
        *heightdown = -(imageheight / 2 - 1);
		*heightup   = imageheight / 2 ;

	}
	else
	{
        *heightdown = - (imageheight-1)/ 2;
		*heightup   =  (imageheight-1)/ 2;
	}

}

BOOL CGaborFilter::GetTransFormData(float *pTransData, int size,int nType)
{
    //if(m_bTransform ==FALSE) 
	//{
	//	 if(!m_bParamentsSet) GaborTransform(size);
		// else 
	//}
	if(m_bTransform ==FALSE)  return FALSE;
	if(size != m_nImgWidth*m_nImgHeight) return FALSE;
	int dsize = sizeof(float);
	switch( nType)
	{
	    case 0 :  memcpy(pTransData,m_pMagnitude,size * dsize);
	              break;  
	    case 1 :  memcpy(pTransData,m_pReal,size * dsize);
		          break;  
	    case 2 :  memcpy(pTransData,m_pImaginary,size * dsize);
		          break;
	}
	return TRUE;
}

BOOL  CGaborFilter::VisualizeGaborImage(BYTE* pTransImg,int size, int nType)
{
	  if(size != m_nImgWidth*m_nImgHeight) return FALSE;
	  switch( nType)
	  {
	  case 0 :  GrayStrtch(size,m_pMagnitude,pTransImg);
		  break;  
	  case 1 :  GrayStrtch(size,m_pReal,pTransImg);
		  break;  
	  case 2 :  GrayStrtch(size,m_pImaginary,pTransImg);
		  break;
	  }
	  return TRUE;
	  
}

void CGaborFilter::GrayStrtch(int imagesize, float *pGabordata, BYTE *pdata)
{
   int i;
   float a ,b ;
   float min =1000000000000000000;
   float max =-100000000000000000;
   
   for(i = 0 ; i < imagesize;i++)
   {
      if( pGabordata[i] < min) min =  pGabordata[i];
	  if( pGabordata[i] > max) max =  pGabordata[i];
   }
    
	a =  255/(max-min);
	b =  -255*min / (max - min);
    int graylevel;

   for(i = 0 ; i < imagesize;i++)
   {
      graylevel = INT(a*pGabordata[i]+b);
      if(graylevel > 255) graylevel = 255;
				pdata[i] = (BYTE)graylevel;
   }
}


BOOL CGaborFilter::GetDataLength(int &nLen)
{
	nLen = m_nImgWidth*m_nImgHeight;
	return TRUE;
}


BOOL CGaborFilter::GetGaborSize(int &nWidth,int &nHeight)	
{
     nWidth  = m_nGaborWinWidth  ;
	 nHeight = m_nGaborWinHeight ;
	 return TRUE;
}


BOOL CGaborFilter::VisualizeGaborKernel(BYTE* pTransImg, int GaborWinWidth,int GaborWinHeight,int scale, int orientation, int xSigma, int ySigma, int nType)
{
    char chScale[20],chOrientation[20],chWidth[20],chHeight[20],chTotalScales[20],chTotalOrientations[20];
	float *pReal = NULL;
	float *pConj = NULL;
	float *pMag  = NULL; 
	int i;
	
	CString Gaborfile;
	FILE *pfile;
	
	_itoa(m_nGaborWinWidth,chWidth,10);
	_itoa(m_nGaborWinHeight,chHeight,10);
    
	_itoa(10,chTotalScales,10);
    _itoa(8,chTotalOrientations,10);

	_itoa(scale,chScale,10);
    _itoa(orientation,chOrientation,10);

	Gaborfile = CString("Gabor") + "-" + chTotalScales + "-" + chTotalOrientations + "-" + chScale + "-" + chOrientation + "-.Gabor" ; 
    pfile = fopen(Gaborfile,"r");
       
	if(!pfile) return FALSE;
    int size = GaborWinWidth * GaborWinHeight;
	pReal = new float[size];
	pConj = new float[size];
	pMag  = new float[size];

    fread(pReal,sizeof(float),size,pfile);
	fread(pConj,sizeof(float),size,pfile);
	fclose(pfile);

	switch(nType)
	{
	 case 0 :
		 for(i = 0 ;i < size ; i++)
		 {
			 pMag[i] = sqrt( pReal[i] * pReal[i] + pConj[i] * pConj[i]);
		 }
		 GrayStrtch(size,pMag,pTransImg);
		break;
	 case 1:
		 GrayStrtch(size,pReal,pTransImg);
		break;
	 case 2 :
		 GrayStrtch(size,pConj,pTransImg);
		break;
	}

	delete []pReal;
	delete []pConj;
	delete []pMag;
	
	return TRUE;


}

void CGaborFilter::ComplexMatirxProduction(int width, int height, float **inputA_X, float **inputA_Y, float **inputB_X, 
											  float **inputB_Y, float **output_X, float **output_Y)
{
     /*******************************************************************
	 *   width, height : matrix size 
	 *   inputA_X : matrix A's real part ; inputA_Y : matrix A's conj part
	 *   inputB_X : matrix B's real part ; inputB_Y : matrix B's conj part
	 *   output_X : matrix C's real part ; inputC_X : matrix C's conj part
	 *   output is the result 
	 ********************************************************************/
	 float **tempX = NULL;
	 float **tempY = NULL;
	 int i,j;


	 tempX = New2DPointer<float>(height,width);
     tempY = New2DPointer<float>(height,width);
	 
     MatrixPointerProduct(width,height,inputA_X,inputB_X,tempX);
     MatrixPointerProduct(width,height,inputA_Y,inputB_Y,tempY);
	 //the above is caculate the realpart of product
	 for(i = 0; i < height; i++)
	 {
         for(j = 0 ;j < width; j++)
		 {
              output_X[i][j] = tempX[i][j] - tempY[i][j];
		 }
	 }

     MatrixPointerProduct(width,height,inputA_X,inputB_Y,tempX);
	 MatrixPointerProduct(width,height,inputA_Y,inputB_X,tempY);
     for(i = 0; i < height; i++)
	 {
         for(j = 0 ;j < width; j++)
		 {
              output_Y[i][j] = tempX[i][j] + tempY[i][j];
		 }
	 }



	 Delete2DPointer<float>(tempX,height);
     Delete2DPointer<float>(tempY,height);
	 
}

void CGaborFilter::MatrixPointerProduct(int width, int height, float **inputA, float **inputB, float **output)
{
     int i,j;
	 for(i = 0 ;i <height ;i++)
	 {
		 for(j =0 ;j <width; j++)
		 {
			 output[i][j] = inputA[i][j] * inputB[i][j];
		 }
	 }
}


BOOL CGaborFilter::SetGaborKernelParas(int KernelWidth,int KernelHeight,int scale, 
									   int nOrientation, float xSigma, float ySigma, 
									   float Kmax, float Frequency,CString StorePath)
{
	m_nScale = scale;
	m_nOrientation = nOrientation;
	m_dSigmaY = xSigma ;
	m_dSigmaX = ySigma ;
        m_dfrequency = Frequency;
	m_dKmax = Kmax;

	m_nGaborWinHeight = KernelHeight;
	m_nGaborWinWidth  = KernelWidth;
    
	m_bParamentsSet = true ;

	MemoryFree();
	m_strStorePath = StorePath;
	KernelCreate();
	KernelLoad();
	m_bFileLoad = TRUE;
	return TRUE;
}

BOOL CGaborFilter::SetImageData(float *pdata, int ImgWidth, int ImgHeight, int scale, int orientation)
{
    int size;
	int i;
	
	if(!m_bParamentsSet) return FALSE;
	
	if(m_pOriImageData != NULL )
	{
		delete []m_pOriImageData;
		m_pOriImageData = NULL;
	}
 	
 	m_nImgWidth = ImgWidth; 
        m_nImgHeight = ImgHeight;

	size = ImgWidth * ImgHeight;

	m_pOriImageData = new float[size];
	for(i =0 ;i < size ; i++)
	{
		m_pOriImageData[i] = (float)pdata[i];
	}
   
	m_bTransform = GaborTransform(size,scale,orientation);
	


    
	return TRUE;
}

BOOL CGaborFilter::SetImageData(BYTE *pdata, int ImgWidth, int ImgHeight, int scale, int orientation)
{
    int size;
	int i;
	
	if(!m_bParamentsSet) return FALSE;
	
	if(m_pOriImageData != NULL )
	{
		delete []m_pOriImageData;
		m_pOriImageData = NULL;
	}
 	
 	m_nImgWidth = ImgWidth; 
        m_nImgHeight = ImgHeight;

	size = ImgWidth * ImgHeight;

	m_pOriImageData = new float[size];
	for(i =0 ;i < size ; i++)
	{
		m_pOriImageData[i] = (float)pdata[i];
	}
   
	m_bTransform = GaborTransform(size,scale,orientation);
	


    
	return TRUE;
}

BOOL CGaborFilter::GaborTransform(int size, int scale, int orientation)
{
     
    if(size !=  	m_nImgWidth*m_nImgHeight)   return FALSE;
	int ScaleIdex;
	int GaborSize = m_nGaborWinWidth * m_nGaborWinHeight;
	int ImageSize = m_nImgWidth*m_nImgHeight;
	int i,j;


	float *pRealpart = NULL ;
	float *pConjpart = NULL ;
    
	float **pImageReal = NULL ;
	float **pImageConj = NULL ;
	float **pGaborReal = NULL ; 
	float **pGaborConj = NULL ;
    
	int  ExtendedWidth,ExtendedHeight;

    pGaborReal = New2DPointer<float>(m_nGaborWinHeight,m_nGaborWinWidth);
	pGaborConj = New2DPointer<float>(m_nGaborWinHeight,m_nGaborWinWidth);

	
	ScaleIdex =  scale +  m_nScale * orientation;
	//if(scale > 0 )  ScaleIdex -= 1;
	//////////////////////////////
    //ScaleIdex = 4;
	//////////////////////////////
	int dsize = sizeof(float);
	int BufferSize = m_nGaborWinWidth * dsize;
	float *pReal = NULL, *pConj = NULL;
	
	pReal = m_ppGaborKernelReal[ScaleIdex];
	pConj = m_ppGaborKernelConj[ScaleIdex];
	
	for(i = 0; i < m_nGaborWinHeight; i++)
	{
		//memcpy(pGaborReal[0],m_ppGaborKernelReal[ScaleIdex],GaborSize*dsize);
		//memcpy(pGaborConj[0],m_ppGaborKernelConj[ScaleIdex],GaborSize*dsize);
        memcpy(pGaborReal[i],pReal, BufferSize);
	  // memset(pGaborReal[i],0,BufferSize);
		memcpy(pGaborConj[i],pConj, BufferSize);
	   //memset(pGaborConj[i],0,BufferSize);
	   pReal += m_nGaborWinWidth;
	   pConj += m_nGaborWinWidth;
    }
	pReal = NULL;
	pConj = NULL;
	
	pImageReal =  New2DPointer<float>(m_nImgHeight,m_nImgWidth);
	pImageConj =  New2DPointer<float>(m_nImgHeight,m_nImgWidth);
    
	float *pImage = NULL;
	pImage =  m_pOriImageData;
	BufferSize = m_nImgWidth * dsize ;
    
	for(i= 0 ; i < m_nImgHeight; i++)
	{
		memcpy(pImageReal[i],pImage,BufferSize);
		memset(pImageConj[i],0,BufferSize);
		pImage += m_nImgWidth;
	}
    pImage = NULL;

	ExtendedWidth  =  m_nImgWidth + m_nGaborWinWidth  - 1 ;
	ExtendedHeight =  m_nImgHeight + m_nGaborWinHeight - 1 ;
    
	long Wid_M =  Get2MofSerialSize(ExtendedWidth);
	long Hei_M =  Get2MofSerialSize(ExtendedHeight);
	
	int FFTWidth  = (int)pow((double)2,Wid_M);
	int FFTHeight = (int)pow((double)2,Hei_M);
    
	float **pGaborRealExtended = New2DPointer<float>(FFTHeight,FFTWidth);
    float **pGaborConjExtended = New2DPointer<float>(FFTHeight,FFTWidth);
    
    MatrixExtend(m_nGaborWinWidth,m_nGaborWinHeight,FFTWidth,FFTHeight,pGaborReal,pGaborRealExtended);
    MatrixExtend(m_nGaborWinWidth,m_nGaborWinHeight,FFTWidth,FFTHeight,pGaborConj,pGaborConjExtended);
	
	Delete2DPointer<float>(pGaborReal,m_nGaborWinHeight);
	Delete2DPointer<float>(pGaborConj,m_nGaborWinHeight);
    
	float **pImageRealExtended = New2DPointer<float>(FFTHeight,FFTWidth);
    float **pImageConjExtended = New2DPointer<float>(FFTHeight,FFTWidth);

	MatrixExtend(m_nImgWidth,m_nImgHeight,FFTWidth,FFTHeight,pImageReal,pImageRealExtended);
    MatrixExtend(m_nImgWidth,m_nImgHeight,FFTWidth,FFTHeight,pImageConj,pImageConjExtended);
	
	Delete2DPointer<float>(pImageReal,m_nImgHeight);
	Delete2DPointer<float>(pImageConj,m_nImgHeight);

	float **pImageRealTrans = New2DPointer<float>(FFTHeight,FFTWidth);
    float **pImageConjTrans = New2DPointer<float>(FFTHeight,FFTWidth);

	FFT2(1,Wid_M,Hei_M,pGaborRealExtended,pGaborConjExtended);
	FFT2(1,Wid_M,Hei_M,pImageRealExtended,pImageConjExtended);   
	ComplexMatirxProduction(FFTWidth,FFTHeight,pImageRealExtended,pImageConjExtended,
                            pGaborRealExtended,pGaborConjExtended,pImageRealTrans,pImageConjTrans);
	FFT2(-1,Wid_M,Hei_M,pImageRealTrans,pImageConjTrans);

	Delete2DPointer<float>(pGaborRealExtended,FFTHeight); 
    Delete2DPointer<float>(pGaborConjExtended,FFTHeight);
	
	Delete2DPointer<float>(pImageRealExtended,FFTHeight); 
    Delete2DPointer<float>(pImageConjExtended,FFTHeight);

	int widthup,widthdown,heightdown,heightup;
    SetWinodwsSize(m_nGaborWinWidth,m_nGaborWinHeight,&widthup,&widthdown,&heightdown,&heightup);
    
   
	if(m_pReal  != NULL) delete []m_pReal;
	if(m_pImaginary != NULL) delete []m_pImaginary;
	if(m_pMagnitude != NULL) delete []m_pMagnitude;

	m_pReal = new float[ImageSize];     
    m_pImaginary = new float[ImageSize];
    m_pMagnitude = new float[ImageSize];


	int k=0;
	for(i = abs(heightdown); i < m_nImgHeight+m_nGaborWinHeight-1-heightup ;i ++)
	{
		for(j = abs(widthdown) ; j < m_nImgWidth+m_nGaborWinWidth-1-widthup ;j++)
		{
           m_pMagnitude[k] = sqrt(pImageRealTrans[i][j]*pImageRealTrans[i][j] + 
			                           pImageConjTrans[i][j]*pImageConjTrans[i][j]);
	       m_pReal[k] = pImageRealTrans[i][j];
		   m_pImaginary[k] = pImageConjTrans[i][j];
		   k++;
		   
		}
	}



    Delete2DPointer<float>(pImageRealTrans,FFTHeight); 
    Delete2DPointer<float>(pImageConjTrans,FFTHeight);	

    return TRUE;

}

BOOL CGaborFilter::VisualizeGaborKernel(BYTE* pTransImg, int GaborWinWidth,int GaborWinHeight,int scale, int orientation,int nType)
{
	float *pReal = NULL ;
	float *pConj = NULL ;
	float *pMag  = NULL ; 
	
	int ScaleIdex =  scale +  m_nScale * orientation;
	int i;
    if(m_nGaborWinWidth!= GaborWinWidth || m_nGaborWinHeight != GaborWinHeight)
       return false;
	int size = m_nGaborWinWidth*m_nGaborWinHeight;
	pReal = m_ppGaborKernelReal[ScaleIdex];
	pConj = m_ppGaborKernelConj[ScaleIdex];
	pMag = new float[size];
	   
		   switch(nType)
		   {
		   case 0 :
			   for(i = 0 ;i < size ; i++)
			   {
				   pMag[i] = sqrt( pReal[i] * pReal[i] + pConj[i] * pConj[i]);
			   }
			   GrayStrtch(size,pMag,pTransImg);
			   break;
		   case 1:
			   GrayStrtch(size,pReal,pTransImg);
			   break;
		   case 2 :
			   GrayStrtch(size,pConj,pTransImg);
			   break;
		   }
		   

     delete []pMag;		   
	 return true;
}

BOOL CGaborFilter::MemoryFree()
{
   	if(m_pOriImageData != NULL)
	{
		delete []m_pOriImageData;
		m_pOriImageData = NULL;

	}
   
	if(m_pReal != NULL)
	{
		delete []m_pReal;
		m_pReal = NULL;
	}
	
	if(m_pImaginary != NULL)
	{
	    delete []m_pImaginary ;
		m_pImaginary = NULL;
	}

	if(m_pMagnitude != NULL)
	{
	    delete []m_pMagnitude ;
		m_pMagnitude = NULL;
	}

	if(m_pCurGaborKernel != NULL)
	{
	    delete []m_pCurGaborKernel;
		m_pCurGaborKernel = NULL ;
	}
	
	if(m_pKernal != NULL)
	{
        delete []m_pKernal;
		m_pKernal = NULL;
	}

   
		if(m_ppGaborKernelReal != NULL)
		{
	        Delete2DPointer<float>(m_ppGaborKernelReal,m_nScale*m_nOrientation); //?????
			m_ppGaborKernelReal = NULL;
			
		}
		
		if(m_ppGaborKernelConj != NULL)
		{
			Delete2DPointer<float>(m_ppGaborKernelConj,m_nScale*m_nOrientation);
			m_ppGaborKernelConj = NULL;
		}


		if(m_ppGaborKernelReal != NULL)
		{
			Delete2DPointer<float>(m_ppGaborKernelReal,m_nScale*m_nOrientation);
			m_ppGaborKernelReal = NULL;
			
		}
		
		if(m_ppGaborKernelConj != NULL)
		{
			Delete2DPointer<float>(m_ppGaborKernelConj,m_nScale*m_nOrientation);
			m_ppGaborKernelConj = NULL;
		}
	
    return true;
}

BOOL CGaborFilter::GetGaborKernelData(float *pdata, int GaborWinWidth, int GaborWinHeight,int scale, int orientation, int Type)
{
    float *pReal = NULL ;
	float *pConj = NULL ;
	float *pMag  = NULL ; 
	
	int ScaleIdex =  scale +  m_nScale * orientation;
	int i;
    if(m_nGaborWinWidth!= GaborWinWidth || m_nGaborWinHeight != GaborWinHeight)
       return false;
	int size = m_nGaborWinWidth*m_nGaborWinHeight;
	pReal = m_ppGaborKernelReal[ScaleIdex];
	pConj = m_ppGaborKernelConj[ScaleIdex];
	pMag = new float[size];
	   
		   switch(Type)
		   {
		   case 0 :
			   for(i = 0 ;i < size ; i++)
			   {
				   pMag[i] = sqrt( pReal[i] * pReal[i] + pConj[i] * pConj[i]);
			   }
			   //GrayStrtch(size,pMag,pTransImg);
			   memcpy(pdata,pMag,size*sizeof(float));
			   break;
		   case 1:
			   //GrayStrtch(size,pReal,pTransImg);
			   memcpy(pdata,pReal,size*sizeof(float));
			   break;
		   case 2 :
			   //GrayStrtch(size,pConj,pTransImg);
			   memcpy(pdata,pConj,size*sizeof(float));
			   break;
		   }
		   

     delete []pMag;		   
	 return true;
    
}


double stard_deviation(double ab[],int Num)
{
    double sum = 0;
    for(int i=0; i < Num; i++)
        sum += ab[i];
    double average = sum / Num;
    double all_sum = 0;
    for(int j = 0; j < Num; j++)
    {
        all_sum += pow((ab[j]-average),2);
    }
    return sqrt(all_sum / (Num-1));
}



