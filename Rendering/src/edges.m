clc;

spec = [
468

];

z=2;
files = {'../MasterNodes.csv'};
pre = '../MasterEdges.csv';
pre = csvread(pre);

floor = [];
for file = 1:length(files)
    floor = [floor; csvread(files{file})];
end

im = imresize(imrotate(imread('../assets/2.jpg'),-90),0.5);


for r = 1:size(floor,1)
    if floor(r,4) == z
        if ismember(floor(r,1),spec)
            shape = reshape(untwist([floor(r,8:11);floor(r,12:15)]),[1,8]);
            if sum(shape) == 0
                im = insertText(im, [floor(r,2) floor(r,3)], ['E' num2str(floor(r,1))],'AnchorPoint','Center','BoxOpacity',0);
            else
                im = insertShape(im, 'FilledPolygon', shape);
                im = insertText(im, [mean(floor(r,8:11)) mean(floor(r,12:15))], num2str(floor(r,1)),'AnchorPoint','Center','BoxOpacity',0);
            end
        end
    end
end

for r = 1:length(pre)
    first = pre(r,1);
    second = pre(r,2);
    disp(first)
    disp(second)
    firstShape = -1;
    secondShape = -1;
    for i = 1:size(floor,1)
        if floor(i,1) == first && floor(i,4) == z
            firstShape = [mean(floor(i,8:11)), mean(floor(i,12:15))];
        end
        if floor(i,1) == second && floor(i,4) == z
            secondShape = [mean(floor(i,8:11)), mean(floor(i,12:15))];
        end
    end
    if all(firstShape ~= -1) && all(secondShape ~= -1)
        disp("asdf")
        im = insertShape(im, 'Line', [firstShape, secondShape],'Color','black');
    end
end

image(im);

edgeList = [];

first = input("Enter first node: ");
while first ~= -1 && first ~= -2
    second = input("Enter second node: ");
    edgeList(size(edgeList,1)+1,:) = [first second];
    firstShape = []; secondShape = [];
    for r = 1:size(floor,1)
        if floor(r,1) == first
            firstShape = [mean(floor(r,8:11)), mean(floor(r,12:15))]
        end
        if floor(r,1) == second
            secondShape = [mean(floor(r,8:11)), mean(floor(r,12:15))]
        end
    end
    im = insertShape(im, 'Line', [firstShape, secondShape],'Color','black');
    image(im)
    first = input("Enter first node: ");
end

if first == -1
    name = input("Filename: ",'s');
    csvwrite(name, edgeList);
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