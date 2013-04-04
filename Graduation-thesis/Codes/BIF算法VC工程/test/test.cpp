#include "GaborFilter.h"
#include "BIF.h"
#pragma comment(lib,"TOOL.lib")

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#define pi 3.1415926

#pragma  warning(disable:4305)
//function GaborFeatureAll  = bif2(ImgData,ImgSize,m_nScale)
//void bif2(double **ImgData,int dim1,int num1,double *ImgSize,int m_nScale,vector<vector<double> > outputGaborFeatureAll)
//mexFunction调用简单的版本(ImgData,ImgSize,Scale);
//DLL调用方式：outputGaborFeature = bif2(ImgData,ImgSize,m_nScale);


//DLL调用方式：outputGaborFeature = BIF::BifTransform(ImgData,ImgSize,m_nScale),其中都是一维的。

void ReadFileDouble(char *s,double *ImgData)//读取文件数据，因为要输入图像数据
{
	int i = 0;
	FILE *fp;
	char buf[1024];
	if( (fp = fopen(s,"r")) == NULL )
	{
		printf("ERROR! Open the file failed!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		
		fgets(buf,1024,fp);
		double result =  atof(buf);
		ImgData[i++] = result;	
	}
	
// 	for(int k = 0; k < i-1; k++)
// 	{
// 		printf("%f\n",ImgData[k]);
// 	}
// 	printf("%d\n",i-1);
	fclose(fp);		
	
}

void WriteFileDouble(double *data, int size,char *s)//保存生成的文件数据，因为要保存生成的数据
{
	int i = 0;
	FILE *fp = fopen(s,"w");
	if(fp == NULL)
		fprintf(fp,"error!");
	while(i < size)
	{
		fprintf(fp,"%lf\n",data[i]);
		i++;
	}
	fclose(fp);
}


void BIF_32()
{
	int Width = 32;
	int Height = 32;
	int WidHei = Width * Height;
	int m_nScale = 16;
	double ImgSize[2] = {Width,Height};
	const int DIM = 10000;
	
	double *ImgData = new double [WidHei];
	int dim = WidHei;
	
	BIF mybif(ImgSize,m_nScale);
	int outputSize= 0;
	
	ReadFileDouble("data_32.txt",ImgData);		//读入尺寸为32时候的VC格式图像数据
	
	double *outputGabor = new double [DIM];
	mybif.BifTransform(ImgData,dim,outputGabor,outputSize);
	
	WriteFileDouble(outputGabor,outputSize,"RealResult_32.txt");//保存产生的VC格式的特征图像结果
	
	double *RealGabor  = new double [outputSize];	
	mybif.DataConverse(outputGabor,RealGabor);
	
	WriteFileDouble(RealGabor,outputSize,"TransformResult_32.txt");//保存转置后MATLAB格式的特征图像结果
	
	delete []outputGabor;
	delete []RealGabor;
//	delete []ImgData;

}


void BIF_64()
{
	////下面是对64x64尺寸时候做的测试。
	int Width = 64;
	int Height = 64;
	int WidHei = Width * Height;
	int m_nScale = 16;
	double ImgSize[2] = {Width,Height};
	const int DIM = 10000;
	
	double *ImgData = new double [WidHei];
	int dim = WidHei;
	
	BIF mybif(ImgSize,m_nScale);
	int outputSize= 0;
	
	ReadFileDouble("data_64.txt",ImgData);		//读入尺寸为32时候的VC格式图像数据
	
	double *outputGabor = new double [DIM];
	mybif.BifTransform(ImgData,dim,outputGabor,outputSize);
	
	WriteFileDouble(outputGabor,outputSize,"RealResult_64.txt");//保存产生的VC格式的特征图像结果
	
	double *RealGabor  = new double [outputSize];	
	mybif.DataConverse(outputGabor,RealGabor);
	
	WriteFileDouble(RealGabor,outputSize,"TransformResult_64.txt");//保存转置后MATLAB格式的特征图像结果
	
	delete []outputGabor;
	delete []RealGabor;
//	delete []ImgData;
}


int main()
{	
//	BIF_32();	//经多次测试没有问题!
	
	BIF_64();	//经多次测试也没有问题!

	return 0;
}



























