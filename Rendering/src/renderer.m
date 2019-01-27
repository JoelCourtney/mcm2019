clear all; close all; clc;

f0 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\0.jpg'),-90),0.5);
f1 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\1.jpg'),-90),0.5);
f2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\2.jpg'),-90),0.5);
f_1= imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_1.jpg'),-90),0.5);
f_2 = imresize(imrotate(imread('C:\Users\Wil Boshell\mcm2019\Rendering\assets\_2.jpg'),-90),0.5);

%R=csvread()