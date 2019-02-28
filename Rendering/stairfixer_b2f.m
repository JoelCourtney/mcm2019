clear all; close all; clc;

M=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterNodes.csv');
E=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterEdges.csv');
disp('B2F Stairs, Capacity:')
for i=1:10
   if M(i,5)==-1
       disp([i M(i,6)])
   end
end

ne=size(E,1);
disp('Adjancency List:')
for i=1:ne
   a=E(i,1);
   b=E(i,2);
   for j=5:9
      if a==j && M(b,5)==-1
          disp([a b])
      else if b==j && M(a,5)==-1
          disp([b a])
      end
      end
   end
end
M(5,6)=6;
M(6,6)=6;
M(7,6)=6;
M(8,6)=4;
M(9,6)=3;
M(127,6)=4;
%csvwrite('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterNodes.csv',M)