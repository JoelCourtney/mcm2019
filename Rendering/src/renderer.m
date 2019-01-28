clear all; close all; clc;

f0 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\0.jpg'),-90),0.5);
f1 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\1.jpg'),-90),0.5);
f2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\2.jpg'),-90),0.5);
f_1= imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_1.jpg'),-90),0.5);
f_2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_2.jpg'),-90),0.5);
F={f_2,f_1,f0,f1,f2};

ufile=inputdlg('Enter File Name:'); %Will add path name through imports\. No .csv necessary.
simfile=strcat('C:\Users\Wil Boshell\mcm2019\Rendering\imports\',ufile{1},'.csv');
M=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterNodes.csv');
R=csvread(simfile);
nt=size(R,1);
% RAM=1.2*10^10;
% dmin=ceil(850*1150*3*nt*5/RAM);
d=str2num(cell2mat(inputdlg('Enter Step Size:')));
ns=floor((nt-1)/d)+2;
t(1)=1;
for i=1:ns-2
    t(i+1)=d*i;
end
t(ns)=nt;
nf=5;

I=zeros([850,1100,3,ns,nf],'uint8');
for l=1:5
    ib=F{l};
    N=[];
    for i=1:size(M,1)
        if M(i,4)==l-3
            N=[N;M(i,:)];
        end
    end
    nnodes=size(N,1);
    for r = 1:nnodes
        shape = reshape(untwist([N(r,8:11);N(r,12:15)]),[1,8]);
        if sum(shape) == 0
            ib = insertText(ib, [N(r,2) N(r,3)], ['E' num2str(N(r,1))],'AnchorPoint','Center','BoxOpacity',0);
        else
            ib = insertShape(ib, 'FilledPolygon', shape);
        end
    end
    for i=1:ns
        im=ib;
        for r=1:nnodes
            im = insertText(im, [mean(N(r,8:11)) mean(N(r,12:15))], num2str(R(t(i),N(r,1))),'AnchorPoint','Center','BoxOpacity',0);
        end
        I(:,:,:,i,l)=im;
    end
end


function [shape] = untwist(shape)
sides = [];
for i = 1:3
    sides(:,i) = shape(:,i)-shape(:,i+1);
end
sides(:,4) = shape(:,4)-shape(:,1);
angles = [];
for i = 1:3
    a = [sides(:,i);0];
    b = [sides(:,i+1);0];
    c = cross(a,b);
    angles(i) = sign(c(3))*180/pi*atan2(norm(c),dot(a,b));
end
angles = sign(angles);
if ~all(angles==angles(1))
    hold = shape(:,1);
    shape(:,1) = shape(:,2);
    shape(:,2) = hold;
end
end