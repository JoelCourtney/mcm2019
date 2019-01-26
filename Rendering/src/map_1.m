clear all; close all; clc;

f0 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\0.jpg'),-90),0.5);
f1 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\1.jpg'),-90),0.5);
f2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\2.jpg'),-90),0.5);
f_1 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_1.jpg'),-90),0.5);
f_2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_2.jpg'),-90),0.5);

f=f_1;
z=-1;
image(f);
hold on
nid=11;
while 1
    t=str2num(cell2mat(inputdlg('Enter Node Type:')));
    if t
        nc=4;
        [x,y,b]=ginput(nc);
        xc=mean(x);
        yc=mean(y);
    else
        nc=1;
        [xc,yc,b]=ginput(nc);
        x=zeros(4,1);
        y=x;
    end
    if sum(b)~=nc
        break
    end
    plot(xc,yc,'r*')
    A=polyarea(x,y);
    M_1(nid-10,1:14)=[nid,xc,yc,z,t,A,x',y'];
    nid=nid+1;
end
csvwrite('nodes_1.csv',M_1)