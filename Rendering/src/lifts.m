clear all; close all; clc;

files1 = {'../nodes_2_official.csv'};
files2 = {'../nodes0_official.csv'};

floor1 = [];
for file = 1:length(files1)
    floor1 = [floor1; csvread(files1{file})]
end
floor2 = [];
for file = 1:length(files2)
    floor2 = [floor2; csvread(files2{file})]
end

im1 = imresize(imrotate(imread('../assets/_2.jpg'),-90),0.5);
im2 = imresize(imrotate(imread('../assets/0.jpg'),-90),0.5);

for r = 1:size(floor1,1)
    shape = reshape(untwist([floor1(r,8:11);floor1(r,12:15)]),[1,8]);
    im1 = insertShape(im1, 'FilledPolygon', shape);
    im1 = insertText(im1, [mean(floor1(r,8:11)) mean(floor1(r,12:15))], num2str(floor1(r,1)),'AnchorPoint','Center','BoxOpacity',0);
end
for r = 1:size(floor2,1)
    shape = reshape(untwist([floor2(r,8:11);floor2(r,12:15)]),[1,8]);
    im2 = insertShape(im2, 'FilledPolygon', shape);
    im2 = insertText(im2, [mean(floor2(r,8:11)) mean(floor2(r,12:15))], num2str(floor2(r,1)),'AnchorPoint','Center','BoxOpacity',0);
end

edgeList = [];

figure(1);
image(im1);
fig1 = gcf;
figure(2);
image(im2);
fig2 = gcf;

first = input("Enter first node: ");
while first ~= -1 && first ~= -2
    second = input("Enter second node: ");
    edgeList(size(edgeList,1)+1,:) = [first second];
    firstShape = []; secondShape = [];
    for r = 1:size(floor1,1)
        if floor1(r,1) == first
            firstShape = [mean(floor1(r,8:11)), mean(floor1(r,12:15))]
        end
    end
    for r = 1:size(floor2,1)
        if floor2(r,1) == second
            secondShape = [mean(floor2(r,8:11)), mean(floor2(r,12:15))]
        end
    end
    im1 = insertShape(im1, 'FilledCircle', [firstShape, 5],'Color','black');
    figure(1)
    image(im1)
    im2 = insertShape(im2, 'FilledCircle', [secondShape, 5],'Color','black');
    figure(2)
    imagesc(im2)
    first = input("Enter first node: ");
end

if first == -1
    name = input("Filename: ",'s');
    csvwrite(name, edgeList);
end

function [shape] = untwist(shape)
sides = []
for i = 1:3
    sides(:,i) = shape(:,i)-shape(:,i+1);
end
sides(:,4) = shape(:,4)-shape(:,1)
angles = [];
for i = 1:3
    a = [sides(:,i);0];
    b = [sides(:,i+1);0];
    c = cross(a,b);
    angles(i) = sign(c(3))*180/pi*atan2(norm(c),dot(a,b));
end
angles = sign(angles);
if ~all(angles==angles(1))
disp("heloo")
    hold = shape(:,1);
    shape(:,1) = shape(:,2);
    shape(:,2) = hold;
end
end