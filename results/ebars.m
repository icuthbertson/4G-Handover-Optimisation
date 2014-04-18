function [errorbars] = ebars(per0,per1,per2,per3,per4,per5,per6,per7,per8,per9)
bars = zeros(1,10);
temp = zeros(1,10);
finalbars = zeros(1,401);

for  i=1:10
     temp(1) = per0(i*50+1);
     temp(2) = per1(i*50+1);
     temp(3) = per2(i*50+1);
     temp(4) = per3(i*50+1);
     temp(5) = per4(i*50+1);
     temp(6) = per5(i*50+1);
     temp(7) = per6(i*50+1);
     temp(8) = per7(i*50+1);
     temp(9) = per8(i*50+1);
     temp(10) = per9(i*50+1);
     %disp('values')
     %disp(temp)
     x = std(temp);
     %disp('std')
     %disp(x)
     %disp('confidence intervals')
     bars(i) = 1.96*(x/(10^0.5));
end
index = 1;
for j=1:401
   if mod(j,index*50+1) == 0
       finalbars(j) = bars(index);
       index = index+1;
   else
       finalbars(j) = NaN;
   end
end
%finalbars(end) = [];
errorbars = finalbars*100;