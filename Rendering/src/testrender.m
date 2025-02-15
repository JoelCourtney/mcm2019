clear all; close all; clc;

f0 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\0.jpg'),-90),0.5);
f1 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\1.jpg'),-90),0.5);
f2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\2.jpg'),-90),0.5);
f_1= imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_1.jpg'),-90),0.5);
f_2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_2.jpg'),-90),0.5);
F={f_2,f_1,f0,f1,f2};

M=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterNodes.csv');
R=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\imports\NaiveSetup.csv',15000-1,0);
nt=size(R,1);
%d=10;
%ns=floor((nt-1)/d)+2;
%t(1)=1;
%for i=1:ns-2
%     t(i+1)=d*i;
% end
% t(ns)=nt;
%I=uint8(zeros(850,1100,3,ns));
for l=1:5
    ib=F{l};
    N=[];
    for i=1:size(M,1)
        if M(i,4)==l-3;
            N=[N;M(i,:)];
        end
        for r = 1:size(N,1)
            shape = reshape(untwist([N(r,8:11);N(r,12:15)]),[1,8]);
            if sum(shape) == 0
                ib = insertText(ib, [N(r,2) N(r,3)], ['E' num2str(N(r,1))],'AnchorPoint','Center','BoxOpacity',0);
            else
                
                ib = insertShape(ib, 'FilledPolygon', shape);
                
            end
        end
    end %23
   
        %ib=ib;
        for r=1:size(N,1)
            
            ib = insertText(ib, [mean(N(r,8:11)) mean(N(r,12:15))], num2str(R(475-r)),'AnchorPoint','Center','BoxOpacity',0);
            
            end
        %Mov(i)=im2frame(im);
        %I(:,:,:,i)=ib;
    figure
    image(ib)
end

%image(im)


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