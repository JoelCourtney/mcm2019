clear all; close all; clc;

f = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\0.jpg'),-90),0.5); %f0

M=[csvread('nodes_2_official.csv');csvread('nodes_1_lifts.csv');csvread('nodes_1_rooms.csv');csvread('nodes0l.csv');csvread('nodes0_r1.csv');csvread('nodes0_r2.csv');csvread('nodes0_r3.csv');csvread('nodes1l.csv');csvread('nodes1_r1.csv');csvread('nodes1_r2.csv');csvread('nodes1_r3.csv');csvread('nodes2_official.csv')];
[m,n]=size(M)
z=0;
image(f);
hold on
plot(M(127,2),M(127,3),'b*')
t=-2;
nc=4;
[x,y,b]=ginput(nc);
xc=mean(x);
yc=mean(y);
plot(xc,yc,'r*')
dw=2;
A=polyarea(x,y);
nid=m+1;
M(nid,1:15)=[nid,xc,yc,z,t,dw,A,x',y'];

csvwrite('masternodes.csv',M)