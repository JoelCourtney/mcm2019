clear all; close all; clc;

M=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterNodes.csv');
E=csvread('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterEdges.csv');
j=0;
for i=11:468
   if M(i,5)==-1
       j=j+1;
       s(j)=i;
   end
end
ns=j;

for i=11:13
    M(i,6)=6;
end
M(126,6)=4;
M(86,6)=10;
M(18,6)=10;

ne=size(E,1);
for i=1:ne
   a=E(i,1);
   b=E(i,2);
   for j=1:ns
      if a==s(j) && M(b,5)==-1 && M(a,6)~=M(b,6)
          disp([a b M(a,6) M(b,6)])
      elseif b==s(j) && M(a,5)==-1 && M(a,6)~=M(b,6)
          disp([b a M(b,6) M(a,6)])
      end
   end
end


csvwrite('C:\Users\Wil Boshell\mcm2019\Rendering\exports\MasterNodes.csv',M)