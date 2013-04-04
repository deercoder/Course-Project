// BIF.cpp: implementation of the BIF class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TOOL.h"
#include "GaborFilter.h"
#include "math.h"
#include "BIF.h"
#include "set.h"
#include <vector>
using namespace std;

#define pi 3.1415926



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BIF::BIF():SxSy(32)//默认构造函数是针对16个尺度和8个方向
{
	this->kernelsize[0] = 32;
	this->kernelsize[1]  = 32;
	this->m_nOrientation = 8;
	this->Scale = 16;
}

BIF::BIF(double *ImgSize, int m_nScale):SxSy(32)//这里自定义的构造函数可以定义尺度
{
	kernelsize[0] = 32;
	kernelsize[1] = 32;
	m_nOrientation = 8;
	Scale = m_nScale;
	Width = ImgSize[0];
	Height = ImgSize[1];
	HeiWid = Height * Width;
	numGabor = m_nScale * m_nOrientation;
	pos_all = new double [MAX_NUM];				//用于存放所有的取得的VC下标（放在这一个数组中）
	double *pos_temp = new double [MAX_NUM];	//用于存放所有的取得的MATLAB下标（放在这一个数组中）
	memset(pos_num,0,8 * sizeof(int));	//设定每一个pos_num为0,pos_num表示每一次取得的数组的大小，最后要全部放在一个数组中
	int *indexAll = new int [Height * Width];//index就是后面要扭转的下标，存放的值很重要！(转置)
	for (int cross_h = 1; cross_h <= Height; cross_h++)
	{
		for(int cross_w = 1 ; cross_w <= Width; cross_w++)
		{
			indexAll[(cross_w-1)*Height + cross_h - 1] = (cross_h-1)* Width +  cross_w;
		}
	}
	int flag = 0;	//标记pos_all已经占用的下标数量
	pos_buffer[0] = 0;
	double ImgSize1[] = {Width,Height};
	double *pos_all1 = new double [POS_ALL_INIT];	//用于存放每一次循环取得的下标
	int xFlag = 0;
	if(32 == ImgSize[0])
	{
		xFlag = 3;
	}
	else if(64 == ImgSize[0])
	{
		xFlag = 4;
	}
	for(int cross_scale = 0; cross_scale < Scale / 2; cross_scale++)
	{
		int gap = cross_scale + xFlag; //cross_scale+2
		int sub_width = gap * 2;
		int sub_height = sub_width;
		int sub_heiwid = sub_height * sub_width;
		double  blockSize[] = {sub_width,sub_height};
		double gapSize[] = {gap,gap};
		//memset(pos_all1,-1,POS_ALL_INIT * sizeof(double));
		memset(pos_all1,0,POS_ALL_INIT * sizeof(double));
		imgblockindex(ImgSize1,blockSize,gapSize,pos_all1);//MARK:在64x64的情况下出错
		int dim_pos = 0;
		while(pos_all1[dim_pos] != -1)//实际得到的数组中非元素都变为了-1
			dim_pos++;//mark,此处调试发现得到正确的下标2916[0~2915]的结果都是正确的。
		TempDim[cross_scale] = dim_pos/sub_height/sub_width;//首先获得循环次数
		pos_num[cross_scale] = dim_pos;	//每一个pos_num都标记了大小，这样就可以计算出来每一个的地址
		//将得到的pos_all1拷贝到pos_all中
		memcpy(pos_temp + flag,pos_all1,dim_pos * sizeof(double));
		flag += dim_pos;
		if(cross_scale <= 6)
		{
			pos_buffer[cross_scale+1] = flag;
		}
	}
	delete []pos_all1;
	//MARK:此处就是将上面生成的所有MATLAB转换为VC下标，后面直接使用VC下标访问		
	for(int row = 0; row < flag; row++)
	{
			pos_all[row] = indexAll[ (int)(pos_temp[row]-1) ];
	}
	delete []pos_temp;
	delete []indexAll;
}

BIF::~BIF()
{

	delete []InputImgData;
	delete []pos_all;
	pos_all = NULL;
	InputImgData = NULL;
}


//处理之后的就是1576 * 94,而每一张图像都是1576的，94表示的是图片的张数。
void BIF::BifTransform(double *ImgData, int ImgDataSize,double *outputGaborFeature,int &size)
{
	 dim = ImgDataSize;		//显示每一张图像的行数(1024 *94)，则dim就是1024，而94表示图片数量，这里只传进来一张图像所有信息
	 InputImgData = new double [ImgDataSize];
	 int i = 0;
	 for(i = 0; i < ImgDataSize; i++)
     	InputImgData[i] = ImgData[i];//ImgData为原来的每一列，是一个一维数组，存放在InputImgData中
	 CGaborFilter Gabor(m_nOrientation,Scale);
	 CGaborFilter Gabor_next(m_nOrientation,Scale);
	 CString strPath_InputImage; 
	 strPath_InputImage.Format("%s","D:\\");
	 float *pImage  = new float[HeiWid];
	 for( i = 0; i < HeiWid; i++)
		pImage[i] = float(InputImgData[i]);
	vector<double> GaborFeatureAll;
	int index_begin_GaborFeatureAll = 0;
	int index_end_GaborFeatureAll = 0;
	double *GaborFeatureTmp = new double [HeiWid * m_nOrientation ]; //(每一个尺度都重新赋值)存放每一张图片提取的所有特征(后来会reshape)
	float *pBuffer1 = new float[HeiWid];
	float *pBuffer2 = new float[HeiWid];
	float *pBufferMax = new float[HeiWid];	//用pBuffer来存放其中的较大值

	int xFlag = 0;
	if(64 == Height )
	{
		xFlag = 4;
	}
	else if( 32 == Height)
	{
		xFlag = 3;
	}
	for(int cross_scale = 0; cross_scale < Scale / 2 ; cross_scale++)
	{
		//mark:要做8次才可以，也就是说GaborFeatureTmp和MATLAB代码中的不一样，要做8次才相当于MATLAB中的一次GaborExtraction
		int filtersize = 4 * cross_scale + 5;
		int filtersize_next = 4 * cross_scale + 7;
		//mark:为提高效率将这两个设定参数放在外面，因为参数不变(检验发现结果相同)
		Gabor.SetGaborKernelParas(filtersize,filtersize,Scale,m_nOrientation,2*pi,2*pi,pi*0.7888,sqrt(2),strPath_InputImage);
		Gabor_next.SetGaborKernelParas(filtersize_next,filtersize_next,Scale,m_nOrientation,2*pi,2*pi,pi*0.7888,sqrt(2),strPath_InputImage);
		for(int j = 0; j < m_nOrientation ; j++)
		{
			Gabor.SetImageData(pImage, Width, Height, cross_scale, j);
			Gabor.GetTransFormData(pBuffer1,HeiWid,0);
			
			Gabor_next.SetImageData(pImage, Width, Height, cross_scale, j);
			Gabor_next.GetTransFormData(pBuffer2,HeiWid,0);
			
			for(int k =0; k < HeiWid; k++)
					pBufferMax[k] = max(pBuffer1[k],pBuffer2[k]);  //此处获得的才是最终的元素，然后设定GaborFeature

			for (int ii = 0 ;ii < HeiWid;ii++) //WidHei是1024 = 32 x 32 大小的,这里的大小应该是Scale*Orientation*WidHei=131072
			{
				GaborFeatureTmp[j * HeiWid + ii ] = double(pBufferMax[ii]);
			}
		
		}//end Orientation	(此部分为完全抽取特征用的，8192维度的特征都要抽取)
	
		int sizeNum = m_nOrientation * HeiWid / dim;
		int gap = cross_scale + xFlag; //cross_scale+2
		int sub_width = gap * 2;
		int sub_height = sub_width;
		int sub_heiwid = sub_height * sub_width;
		double  blockSize[] = {sub_width,sub_height};
		double ImgSize[] = {Width,Height};
		double gapSize[] = {gap,gap};

		int *baseindex = new int [sub_heiwid];//每次循环取的都是第一列的下标，后面可以依据偏移量求出来 
		double *Result = new double [TempDim[cross_scale] * sizeNum];
		int *index = new int [sub_heiwid];  //每一列结果要先取出索引
		double *getNum = new double [sub_heiwid];  //取出对应索引的数 
		for(int cross_block = 0; cross_block < TempDim[cross_scale] ; cross_block++)   //一共有这么多次循环 
		{
			int index_begin = cross_block * sub_heiwid + 1;
			int index_end = (cross_block+1) * sub_heiwid;

			for(int jj = 0; jj < sub_heiwid; jj++)
			{
				baseindex[jj] = *(pos_all + pos_buffer[cross_scale] + index_begin+ jj - 1);//每次都是36个的取，后面的都有规律 
			}     
			for(int j = 0; j < sizeNum; j++)    //一共有这么多列，每一列产生一个结果 
			{
			
				for(int k = 0; k < sub_heiwid; k++) //每一列的结果都是由这么多个数的标准差 
				{
					index[k] = baseindex[k] + j * dim;//第一次肯定是index[k]，后面的就要算上列的偏移 
					getNum[k] = GaborFeatureTmp[index[k] - 1];/////直接使用VC下标的特征
				}
				double result = stard_deviation(getNum,sub_heiwid);
				Result[cross_block * sizeNum + j] = result;//注意这里得到的是行序为主序的一位向量，和MATLAB的reshape之后的不同			
			}	
		}
		if(cross_scale == 0)
		{
			index_end_GaborFeatureAll = 0;
		}
		index_begin_GaborFeatureAll = index_end_GaborFeatureAll + 1;
		index_end_GaborFeatureAll = index_begin_GaborFeatureAll + TempDim[cross_scale] * sizeNum - 1;
		for(int i = index_begin_GaborFeatureAll; i <= index_end_GaborFeatureAll; i++)//mark，注意不能少元素，是648个，要取等号。
		{
			GaborFeatureAll.push_back(Result[i-index_begin_GaborFeatureAll]);
		}
		delete []Result;
		delete []baseindex;
		delete []getNum;
		delete []index;
	}//end Scale
		size = GaborFeatureAll.size();					//用size带回去最后的下界
		for( i = 0; i < size; i++)
			outputGaborFeature[i] = GaborFeatureAll[i];		//最后将数据传递回去
		index_end_GaborFeatureAll = 0;


		delete []pBuffer1;
		delete []pBuffer2;
		delete []pBufferMax;
		delete []GaborFeatureTmp;	//移到后面
		delete []pImage;
		vector<double>().swap(GaborFeatureAll);
}//end


//////////////////////////////////////////////////////////////////////////
//MATLAB原型：pos_all = imageblockindex(ImgSize, blockSize,gapSize)
//% 对图像取块的索引，并对索引排序
// Input: 
//       ImgSize:  图像的尺寸，height = ImgSize(2);width  = ImgSize(1);
//       blockSize: 块的尺寸, sub_height = blockSize(2);sub_width  = blockSize(1);
//       gapSize： 块间隔，gap_height = gapSize(2), gap_width = gapSize(1);   
// Output:
//       pos_all: 块的索引
//
//注记：这里pos_all的大小在函数体中先设置了一下，不过后来取的实际大小更小。现在考虑代码中
//以后是否会溢出，所以后面要注意设定大小，因为是一个循环，所以可能会超过。
void BIF::imgblockindex(double *ImgSize,double *blockSize,double *gapSize,double *output_pos_all)
{
	double height = ImgSize[1];
	double width = ImgSize[0];
	double sub_height = blockSize[1];
	double sub_width = blockSize[0];
	double gap_height = gapSize[1];
	double gap_width = gapSize[0];
	double sub_heiwid = sub_height * sub_width ;
	int index = 0;
	ImgSize[0] = height; ImgSize[1] = width;
	double *ImgData = new double[width * height];
	memset(ImgData,0,width * height * sizeof(double));	//ImgData = zeros(width*height,1);
//	memset(output_pos_all,-1,POS_ALL_INIT * sizeof(double));//pos_all = zeros(sub_width*sub_height*height/gap*width/gap,1);
	memset(output_pos_all,0,POS_ALL_INIT * sizeof(double));
	double cross_x,cross_y;
	int index_begin,index_end;
	double Pos[4];
	double *output_newImgData = new double[SIZEONE];
	int *output_pos = new int [SIZEONE];
	for(cross_x = 1; cross_x <= width-sub_width+1; cross_x+=gap_width)
	{
		for (cross_y = 1; cross_y <= height-sub_height+1; cross_y+=gap_height)
		{
			index = index + 1;
			Pos[0] = cross_x; Pos[1] = cross_y;
			Pos[2] = sub_height; Pos[3] = sub_width;
			memset(output_newImgData,0,SIZEONE * sizeof(double));
		//	memset(output_pos,-1,SIZEONE * sizeof(int));memset是对字节操作，赋值为-1不会得到-1数，应该初始化都为0
			memset(output_pos,0,SIZEONE * sizeof(int));
			segmentimage(ImgData,ImgSize,Pos,output_newImgData,output_pos);//调用这个函数时另外引入参数,[newImgData, pos] = segmentimage(ImgData,Imgsize,Pos)
			index_begin = (index - 1) * sub_heiwid + 1;
			index_end = index * sub_heiwid;	
			int mySize = index_end - index_begin + 1;//求得pos的大小并全部复制给pos_all
			for(int kk = 0; kk < mySize; kk++)
				output_pos_all[index_begin-1+kk] = output_pos[kk];			
		}
	}
		int dim_pos = index_end;
		for(int jj = dim_pos; jj < POS_ALL_INIT; jj++)//pos_all(dim_pos+1:end)= [] ;将dim_pos(2916)后面的数据不要了，太多了，实际结果为1~2916，后面的都不要了(实际上无用，因为传递的是指针)。
			output_pos_all[jj] = -1;
		delete []ImgData;
		delete []output_newImgData;
		delete []output_pos;
		return ;
}


//MATLAB原型：[newImgData, pos] = segmentimage(ImgData,Imgsize,Pos)
//取图像的一部分，组成新的数据
// Input:
//       Imgsize:ImgData中图像数据的[height width]。ImgData为[dim,num]的数据
//       Pos: [x,y,width,height]的四维向量。x,y 为矩阵块的起始点，width,height为要取得块的大小
// Output:
//       newImageData: 从ImgData中所取出来的块的数据。
/////注记：在改写代码中，调用此函数的代码是imgblockindex,而调用的参数是一个一维的ImgData,所以这里也只取一维的.
////那么ImgData,output_newImgData都是一维的!![行数,1]（仅仅有一列）
/********************************Version 1.1（改进版）**********************************************/
////P.S:此函数在2011/3/21测试，多次测试无误，和MATLAB运行结果相同。但是newImgData数据结果不对，但是最后并没有用到
void BIF::segmentimage(double *ImgData, double *ImgSize, double *Pos, double *output_newImgData, int *output_pos)
{
	double x = Pos[0];
	double y = Pos[1];
	double subwidth = Pos[2];
	double subheight = Pos[3];
	double height = ImgSize[1];
	double width = ImgSize[0];
	double col_end = width < (x+subwidth-1) ? width:(x+subwidth-1);
	subheight = subheight < (height-y+1)?subheight:(height-y+1);
	double dim_begin,dim_end;
	int flag = 0;//用flag来表示pos数组实际数据的大小
	for(double cross_col=x; cross_col <= col_end; cross_col++)
	{
		dim_begin = (cross_col-1)*height + y;
		dim_end = dim_begin + subheight - 1;
		int num = (int)(dim_end - dim_begin + 1); //表示数量，这样更直观，虽然值是为subheight
		//pos = [pos dim_begin:dim_end]
		for(int ii = 0; ii < num; ii++)
		{
			output_pos[flag+ii] = (int)dim_begin + ii ;
		}
		flag += num;
	}
	//newImgData = ImgData(pos,:)，对ImgData的pos内容行(pos[i])，分别取出来所有的列
	//这里由于只有一列，所以仅仅取出来一个值放进去。
	for(int jj = 0; jj < flag; jj++)
	{
		output_newImgData[jj] = ImgData[output_pos[jj]];//此处发生错误，ImgData的数据传递进来不对，根本没有传递进来。
	}
	return;
}///mark:2011/3/21重新改写，测试






//////BUG终于知道了，哈哈，纠结了两天，发现原来是偏移量的问题，怎么不知道和前面一样的做法呢？注意一个是偏移量，一个是每
//个数组的大小，虽然这里数组没有告诉大小，但是通过多次计算也是可以求出来的！前面有pos_num和pos_buffer两个来分别指示大小
//偏移量，所以没有出错，大小是指每一个数组的大小，而偏移量则是指前面的所有的数组的和啊！
void BIF::DataConverse(double *inputGabor, double *outputGabor)
{
	int sizeNum = m_nOrientation * HeiWid / dim;
	int result_num[8];		//result_num用来指示数组的大小，每一个大小都要计算，并不知道，注意不要和前面下标搞混了，那个是
	int result_buffer[8];	//提取特征时候的下标，这里要对最终运算结果的大小找到位置，然后每次取出来变换
	result_buffer[0] = 0;	//result_buffer指示偏移量，注意前面数组要累加起来才是偏移量。
	int i = 0;
	result_buffer[0] = 0;//BUG
	int flag = 0;
	for( i = 0; i < Scale / 2; i++)
	{
		result_num[i] = TempDim[i] * sizeNum;
		if( i >= 1 )
		{
			result_buffer[i] = flag; 
		}
		flag += result_num[i];
	}
	for(int cross_scale = 0; cross_scale < Scale / 2; cross_scale++)
	{
		
		double *Result_reverse = new double [TempDim[cross_scale] * sizeNum];
		double *Result = new double [TempDim[cross_scale] * sizeNum];
		memcpy(Result,inputGabor+result_buffer[cross_scale],TempDim[cross_scale] * sizeNum * sizeof(double));
		// 		for( i = 0; i < TempDim[cross_scale] * sizeNum; i++)
		// 		{
		// 			Result[i] = *(inputGabor+result_buffer[cross_scale] + i); 
		// 		}
		for ( i = 0; i < sizeNum; i++)
		{
			for(int j = 0; j < TempDim[cross_scale]; j++)
			{
				Result_reverse[i * TempDim[cross_scale] + j] = Result[j * sizeNum + i];
			}
		}
		memcpy(outputGabor+result_buffer[cross_scale],Result_reverse,TempDim[cross_scale] * sizeNum * sizeof(double));
		// 		for(i = 0; i < TempDim[cross_scale] * sizeNum; i++)
		// 		{
		// 			*(outputGabor + result_buffer[cross_scale]+ i)= Result_reverse[i];
		// 		}
		delete []Result_reverse;
		delete []Result;
	}
}
