//新建的mexFunction 函数的空白模板
#include "stdafx.h"
#include <math.h>
#include "mex.h"
// link    libmx.lib libmat.lib libmex.lib  //bpma

#include "GaborFilter.h"
#include "BIF.h"
#include <stdlib.h>
#include "stdafx.h"
#include <vector>
using namespace std;


#define  IndexImgData 0
#define  IndexImgSize 1
#define  IndexOutputPath 1
#define pi 3.1415926



#pragma  warning(disable:4305)
//function GaborFeatureAll  = bif2(ImgData,ImgSize,m_nScale)
//void bif2(double **ImgData,int dim1,int num1,double *ImgSize,int m_nScale,vector<vector<double> > outputGaborFeatureAll)
//mexFunction调用简单的版本(ImgData,ImgSize,Scale);
//DLL调用方式：outputGaborFeature = bif2(ImgData,ImgSize,m_nScale);


//DLL调用方式：outputGaborFeature = BIF::BifTransform(ImgData,ImgSize,m_nScale),其中都是一维的。
void mexFunction(
				 int nlhs, // 左边(输出)参量的个数
				 mxArray *plhs[], // 左边参量的数组
				 int nrhs, // 右边(输入)参量的个数
				 const mxArray *prhs[] // 右边参量的数组
				 )
{	
	if(nlhs != 1)
		mexPrintf("the output must be two parameter\n");
	if(nrhs != 3)
		mexPrintf("the input must be three parameters\n");
	int dim = mxGetM(prhs[0]);//ImgData的行数
	int Width = mxGetPr(prhs[1])[0];
	int Height = mxGetPr(prhs[1])[1];
	int WidHei = Width * Height;
	int m_nScale = mxGetPr(prhs[2])[0];
	double ImgSize[2] = {Width,Height};
//	const int DIM = 5000;		//MARK:此处在64x64的时候尺度过小
	const int DIM = 10000;
	BIF mybif(ImgSize,m_nScale);
	int outputSize= 0;

	double *tmpGabor = new double [DIM];
	mybif.BifTransform(mxGetPr(prhs[0]),dim,tmpGabor,outputSize);

	plhs[0] = mxCreateDoubleMatrix(outputSize,1, mxREAL);

	mybif.DataConverse(tmpGabor,mxGetPr(plhs[0]));

	delete []tmpGabor;
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


void C_reshape_OneToTwo(double *v,double **v1,int row,int col)
{
	for(int ii = 0; ii < row; ii++)
        for(int jj = 0; jj < col; jj++)
            v1[ii][jj] = v[ jj * row + ii];
}

void C_reshape_TwoToOne(double ** v,int row,int col, double *v1)//二维到一维
{

    for(int j = 0; j < col ; j++)
        for(int i = 0; i < row ; i++) 
        {
            v1[j * row + i] = v[i][j];
        }
}

void WriteFileDouble(double *data, int size,char *s)//将double类型数据写入文件，命名为s，并保存在当前文件夹
{
	///////mark:此处为测试代码，测试是否正确，吸入001.txt
		int i = 0;
		FILE *fp = fopen(s,"w");
		if(fp == NULL)
			fprintf(fp,"error!");
		while(i < size)
		{
			fprintf(fp,"%lf\n",data[i]);
			i++;
		}
}














