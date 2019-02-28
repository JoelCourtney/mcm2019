clear all; close all; clc;

%f0 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\0.jpg'),-90),0.5);
f = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\1.jpg'),-90),0.5); %f1
%f2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\2.jpg'),-90),0.5);
%f_1= imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_1.jpg'),-90),0.5);
%f_2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_2.jpg'),-90),0.5);

z=1;
image(f);
hold on
nid=286;
while 1
    t=str2num(cell2mat(inputdlg('Enter Node Type:')));
    if t
        nc=4;
        [x,y,b]=ginput(nc);
        xc=mean(x);
        yc=mean(y);
        plot(xc,yc,'r*')
        if t>0
            [xd,yd]=ginput(2);
            dw=max(abs(xd(1)-xd(2)),abs(yd(1)-yd(2)));
        else
            dw=str2num(cell2mat(inputdlg('Enter Door Width:','Input',[1 20],{'2'})));
        end
    else
        nc=1;
        dw=0;
        [xc,yc,b]=ginput(nc);
        plot(xc,yc,'r*')
        x=zeros(4,1);
        y=x;
    end
    if sum(b)~=nc
        break
    end
    A=polyarea(x,y);
    M1(nid-285,1:15)=[nid,xc,yc,z,t,dw,A,x',y'];
    nid=nid+1;
end
csvwrite('nodes1.csv',M1)