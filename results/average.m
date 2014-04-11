function [av] =  average(per0,per1,per2,per3,per4,per5,per6,per7,per8,per9)
avarray = zeros(1, 401);
%avfinal = zeros(1, 200001);

for i = 1:1:401
    avarray(i) = ((per0(i)+per1(i)+per2(i)+per3(i)+per4(i)+per5(i)+per6(i)+per7(i)+per8(i)+per9(i))/10);
end
%index = 1;
%for j = 1:1:20000001
%   if mod(j,100) == 0
%       avfinal(index) = avarray(j);
%       index = index+1;
%   end
%end
%avfinal(end) = [];
%av = avfinal*100;
av = avarray*100;