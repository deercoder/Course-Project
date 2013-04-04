function GaborFeatureAll  = bif2(ImgData,ImgSize,m_nScale)
%对图像提取生物特征的Gabor代码
% Input：
%       Img: 图像的数据，为【hei×wid，num】的数据，图像数据的排列方式要按照列先存储的方式
%       ImgSize： 图像的尺寸，width = ImgSize(1);height = ImgSize(2);
%       sigma: 文章中公式2的sigma
%       kernelsize:
% Output:
%       GaborFeature：提取特征后的Gabor特征，为【hei×wid×40，1】的数据
% Notes:
%       参考文献，Laurenz Wiskott, Jean-Marc Fellous,Norbert Kruger, and Christoph von der Malsburg,
%               "Face Recognition by Elastic Bunch Graph Matching"
% * 当前版本：1.0
% * 作    者：马丙鹏
% * 完成日期：2010年03月29日

%%补充注记：m_nOrientation = 8;固定了方向，而尺度则可以灵活设定为5或16
%%这里只是另外定义一个变量名GaborFeature_temp，与前面的无关，最后还是clear掉了。不会修改到之前生成的量。

%%%新的理解：test.m的功能：
%%对于每一张图片(cross从1到num=94)，都进行一次GaborExtraction_Scale16来提取特征，最终reshape为1024*
%%128的大小和尺寸。
%而是用mybif（进入函数体内发现功能），发现它做的工作就是，每一张图片，每次都设定一个filtersize，然后再提取特征
%最终每次都放入到结果中，最后返回。
%而bif2算法（函数体）则不同，它负责每个图片的相邻尺寸的提取特征，然后比较最大值，然后其他的处理，最后才处理结果。
%而且最终生成的是1576*94的大小和尺寸，和前面的不同（因为处理不同）。
%%%%最后说明，mybif和你的dll(mexGaborExtraction_Scale16)作用是相同的，都是紧紧提取特征而已。(用于比较发现精度)
%



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%此处处理的是64x64维度，为此，把那个blocksize针对于32x32增加1个，就是每一次循环在原来的基础上加1
%原来是加2,现在加3. gap = cross_scale + 3;% 64x64时候需要再增加blocksize的大小，为此再加1



[dim, num] = size(ImgData);%%num表示图像的数量，而dim表示的是32*32=1024(即返回行数和列数)
if nargin<4 %nargin表示输入变量的个数,如果输入参数个数小于4个
    kernelsize = [32 32];
end
if nargin<3 %如果输入参数个数小于3个（此句没有执行）
    sigma = 2;
    m_nScale = 5;
end
m_nOrientation = 8;
width = ImgSize(1);%%ImgSize是指示了图像的大小，比如32*32，所以分别类取出长和宽
height = ImgSize(2);
heiwid = height * width;
numGabor = m_nScale * m_nOrientation;%%Gabor的数量是尺度和方向的乘积，这里是5*8的数目（40个）

SxSy = 32;
newdim = numGabor * dim;
% newImgData = zeros(newdim,num);

for cross_num = 1 : 1%num   %%这里对于每一张图片都进行处理，num表示图片数量94张。
    ImgData_temp = ImgData(:,cross_num );  %%这里是采用每一列，也就是一张张图片取出来，因为列数即为图片数，每一列表示一张图片。
   
    for cross_scale = 1 : m_nScale/2 %%对于Scale的任何相邻两个之间比较求最大值，每一个Scale都有处理，用for循环来一个个处理的。
        filtersize = cross_scale *4+1;%%%%%严重注意：这里设置核心的时候采用尺度为cross_scale，但是在VC中如何设置为动态变化就出错了。//ps:但是mybif说明参数固定时候是可以的,数据相同。
        [GaborReal,GaborConj]= KernelCreate1(filtersize,filtersize,cross_scale,m_nOrientation,2*pi,2*pi,0.7888*pi,sqrt(2));
        Gabor = GaborReal  + 1i * GaborConj;
        GaborFeature_odd  = GaborExtraction1(ImgData_temp, ImgSize, Gabor,filtersize,filtersize);%%GaborFeature_odd==8192*1(32*32*8)
        filtersize = cross_scale *4+3;
        [GaborReal,GaborConj]= KernelCreate1(filtersize,filtersize,cross_scale,m_nOrientation,2*pi,2*pi,0.7888*pi,sqrt(2));
        Gabor = GaborReal  + 1i * GaborConj;
        GaborFeature_even  = GaborExtraction1(ImgData_temp, ImgSize, Gabor,filtersize,filtersize);%%GaborFeature_even==8192*1
        GaborFeature = max(GaborFeature_even,GaborFeature_odd);%%GaborFeature=8192*1，max表示从两个数组中取出来每一个中的较大值组成一个新的数组。
   
        clear GaborFeature_even GaborFeature_odd GaborReal GaborConj;
    
        GaborFeature = reshape(GaborFeature,dim,size(GaborFeature,1)/dim);%%对于8192*1变化为1024*8，重新处理。size(X,1)获得行数
        %gap = cross_scale + 1;% 同文章中的gap起始点不同。
        %gap = cross_scale + 2;% 同文章中的gap起始点不同。
        gap = cross_scale + 3;% 64x64时候需要再增加blocksize的大小，为此再加1
        sub_width = gap * 2;
        sub_height = sub_width;
        sub_heiwid = sub_height * sub_width;
        pos_all = imageblockindex(sub_width,sub_height, gap,width, height);%%第一个函数imageblockindex需要自己写
        dim_pos = length(pos_all);
        GaborFeature_temp = zeros(dim_pos/sub_width/sub_height, size(GaborFeature,2));
        for cross_block = 1 : dim_pos/sub_width/sub_height;
            index_begin = (cross_block - 1) * sub_heiwid +1;
            index_end = cross_block * sub_heiwid;
            index = pos_all(index_begin: index_end);%%第二个函数pos_all需要自己写
            GaborFeature_temp(cross_block,:) = std(GaborFeature(index,:));    %%此处就是进行std处理,表示取出来index内容为索引的GaborFeature的列！    
        end
        clear index index_begin index_end pos_all;
        GaborFeature_temp = reshape(GaborFeature_temp, dim_pos/sub_width/sub_height *size(GaborFeature_temp,2),1);%彻底懂了，是从列开始累积的。（先第一列，然后第二列连起来为一列）
        
        if cross_num == 1 && cross_scale == 1;%第一次执行的时候会运行到这个地方，以后就不会。因为两者都是变化的，都是从1开始。(肯定会执行)
           newDim = length(GaborFeature_temp);%newDim = 648,m_nScale = 16
           GaborFeatureAll = zeros(newDim * m_nScale/4,num); %2592*94这么多的GaborFeatureAll
           index_end_GaborFeatureAll= 0;      
        end
        index_begin_GaborFeatureAll =  index_end_GaborFeatureAll + 1;
        index_end_GaborFeatureAll =  index_begin_GaborFeatureAll + dim_pos/sub_width/sub_height *size(GaborFeature,2)-1;
        GaborFeatureAll(index_begin_GaborFeatureAll:index_end_GaborFeatureAll, cross_num) = GaborFeature_temp;
        clear GaborFeature_temp GaborFeature;
    end  
    if cross_num == 1 
           GaborFeatureAll(index_end_GaborFeatureAll+1:end,:) = [] ; %第一次处理（开始的时候处理第一张图像的时候）的时候，将多余的行数置为为0（本来是2592，现在置为1576）
    end
    index_end_GaborFeatureAll = 0;
    %     GaborFeature = GaborExtraction1(ImgData_temp, ImgSize, Gabor,5,5);
    %     GaborFeature = reshape(GaborFeature, dim, numGabor);
    %     GaborFeature_even = GaborFeature(:,1:2:end);
    %     GaborFeature_odd = GaborFeature(:,2:2:end);
end
return;

function  pos_all = imageblockindex(sub_width,sub_height, gap,width, height)
sub_heiwid = sub_height * sub_width;
index = 0 ;ImgSize = [height width] ;
ImgData = zeros(width*height,1);
pos_all = zeros(sub_width*sub_height*height/gap*width/gap,1);
for cross_x = 1:gap:width-sub_width+1
    for cross_y = 1: gap : height-sub_height+1
        index= index +1;
        Pos = [cross_x cross_y sub_height sub_width] ; % 每次循环中都对cross_x,cross_y有变化，而sub_height,sub_width不变。所以调用segmentimag不同。
        [newImgData, pos] = segmentimage(ImgData,ImgSize,Pos); %每一次循环中都要调用到segmentimage函数，而每次的参数Pos都是变化的。
        index_begin = (index - 1) * sub_heiwid +1;
        index_end = index * sub_heiwid;
        pos_all(index_begin:index_end)  = pos ;
    end
end
dim_pos = index_end;
pos_all(dim_pos+1:end)= [] ;
clear index_begin  index_end pos newImgData index;
return;

function GaborFeature  = GaborExtraction1(Img,ImgSize,gaborK,KernelWidth,KernelHeight)
%对图像提取的Gabor特征 。
% Input：
%       Img: 图像的数据，为【hei×wid，1】的数据，图像数据的排列方式要按照列先存储的方式
%       ImgSize： 图像的尺寸，width = ImgSize(2);height = ImgSize(1);
%       gaborK: gabor核,【numGabor×dim】
% Output:
%       GaborFeature：提取特征后的Gabor特征，为【hei×wid×40，1】的数据

%Notes:
%       40个Gabor的滤波器的顺序是先方向后尺度.

% * 当前版本：1.0
% * 作    者：马丙鹏
% * 完成日期：2009年12月21日

width = ImgSize(1);
height = ImgSize(2);
heiwid = height * width;
numGabor = size(gaborK,2); %得到的是行的值还是列的值呢？25*8得到的是8(第二个参数)
Img = reshape(Img, height, width);
GaborFeature = zeros(heiwid*numGabor,1);
for k = 1 : numGabor
    idx = heiwid*(k-1);
    eachK = reshape(gaborK(:,k), KernelHeight, KernelWidth); %选择每一列（numbGabor），对于每一列的数据进行reshape为核心的高和宽
    GaborFeature_temp = gaborwavelets(Img, eachK);%%返回值为32*32
    GaborFeature(idx+1 : idx+heiwid, 1) = reshape(GaborFeature_temp,heiwid,1); %%把得到的每一个32*32展开为一维的1024个，然后在赋值为一维的GaborFeature中。
end
return;

%%img为32*32，G为5*5
function Gaborout  = gaborwavelets(img, G)
% 利用gaborwaveletskernelcreat产生的卷积核计算图像的Gabor小波
% Input:
%       img: 图像数据，为[width, height]的矩阵
%       G: gaborwaveletskernelcreat产生的卷积核
% Output:
%
% Notes:
%       参考文献，Laurenz Wiskott, Jean-Marc Fellous,Norbert Kruger, and Christoph von der Malsburg,
%               "Face Recognition by Elastic Bunch Graph Matching"
% * 当前版本：1.0
% * 作    者：马丙鹏
% * 完成日期：2009年12月21日

if isa(img,'double')~=1
    img = im2double(img);
end
%%Imgabout,Regabout,Gaborout都是32*32
Imgabout = conv2(img,double(imag(G)), 'same');
Regabout = conv2(img,double(real(G)), 'same');
% Imgabout = conv2(img,double(imag(G)), 'full');
% Regabout = conv2(img,double(real(G)), 'full');
Gaborout = sqrt(Imgabout.*Imgabout + Regabout.*Regabout);
return;
