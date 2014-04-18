function [av,bars] = pingAverage(path)
str0 = strcat(path,'0');
str1 = strcat(path,'1');
str2 = strcat(path,'2');
str3 = strcat(path,'3');
str4 = strcat(path,'4');
str5 = strcat(path,'5');
str6 = strcat(path,'6');
str7 = strcat(path,'7');
str8 = strcat(path,'8');
str9 = strcat(path,'9');
[fper0] = resultsPing(str0);
[fper1] = resultsPing(str1);
[fper2] = resultsPing(str2);
[fper3] = resultsPing(str3);
[fper4] = resultsPing(str4);
[fper5] = resultsPing(str5);
[fper6] = resultsPing(str6);
[fper7] = resultsPing(str7);
[fper8] = resultsPing(str8);
[fper9] = resultsPing(str9);

%times = 0:400:200000;

%plot(times,fper0)
%hold on
%plot(times,fper1)
%plot(times,fper2)
%plot(times,fper3)
%plot(times,fper4)
%plot(times,fper5)
%plot(times,fper6)
%plot(times,fper7)
%plot(times,fper8)
%plot(times,fper9)

av = average(fper0,fper1,fper2,fper3,fper4,fper5,fper6,fper7,fper8,fper9);
bars = ebars(fper0,fper1,fper2,fper3,fper4,fper5,fper6,fper7,fper8,fper9);