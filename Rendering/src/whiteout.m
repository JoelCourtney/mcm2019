clear all; close all; clc;

path='C:\Users\Wil Boshell\mcm2019\Rendering\assets\';
f0 = imresize(imrotate(imread(strcat(path,'0orig.jpg')),-90),0.5);
f1 = imresize(imrotate(imread(strcat(path,'1orig.jpg')),-90),0.5);
f2 = imresize(imrotate(imread(strcat(path,'2orig.jpg')),-90),0.5);
f_1= imresize(imrotate(imread(strcat(path,'_1orig.jpg')),-90),0.5);
F={f_1,f0,f1,f2};
im=image(F{1})
[x,y]=ginput(4);
for i=floor(min(y)):ceil(max(y))
    for j=floor(min(x)):ceil(max(x))
        for k=1:3
        F{1}(i,j,k)=uint8(255);
        end
    end
end
imwrite(F{1},strcat(path,'_1.jpg'))
for l=2:4
    for i=floor(min(y)):ceil(max(y))
        for j=floor(min(x)):ceil(max(x))
            for k=1:3
            F{l}(i,j,k)=uint8(255);
            end
        end
    end
    imwrite(F{l},strcat(path,num2str(l-2),'.jpg'))
end
