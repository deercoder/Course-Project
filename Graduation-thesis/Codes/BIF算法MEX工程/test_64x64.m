%此文件用于测试64x64尺寸的图像的VC和MATLAB代码的精度。
%
%
%
height = 64;
width = 64;
heiwid = 64 * 64;
index = zeros(1, heiwid);
ImgSize = [64,64];

for cross_h = 1: height
    for cross_w =  1 : width
        index((cross_w-1)*height + cross_h) = (cross_h-1)* width +  cross_w;
    end
end
% num = size(ImgData,2);
for cross =5 :5%num
      ImgData_temp = ImgData(:,cross );
      GaborFeature_bif  = bif2_64x64(ImgData_temp,ImgSize,16);
    ImgData_temp(index) = ImgData_temp;%MATLAB数据转成VC的数据，因为之前导入的ImgData是MATLAB的。。。
    %c1= b1(index,:);%由于MATLAB和VC对于图像的表示不同，一个是行序，一个是列序，所以之前先要转置下。   
    %%mexGaborExtraction为Scale为16的情况，因为下面调用的reshape就是变为1024*128=131072
    %%注意，这里输出的特征是一维的，而后面处理的时候是输出二维的，所以在dll处理之后要重新用MATLAB来改变行列
    tic;
    GaborFeature_temp1 = BIF_Scale16_neat(ImgData_temp,ImgSize,16);%此处调用的是dll文件，处理16*8的方向尺度
    %GaborFeature_temp  = BIF_Scale16(ImgData_temp,ImgSize,16);
    toc;
   %GaborFeature_temp = reshape(GaborFeature_temp, heiwid, 128);%16*8参数(变为1024*128)
   % GaborFeature_temp = GaborFeature_temp (index,:);%1024*128

end