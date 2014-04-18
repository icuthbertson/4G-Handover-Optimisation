function [av,bars] = resultsAverage(path)
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
[fper0] = resultsDrop(str0);
[fper1] = resultsDrop(str1);
[fper2] = resultsDrop(str2);
[fper3] = resultsDrop(str3);
[fper4] = resultsDrop(str4);
[fper5] = resultsDrop(str5);
[fper6] = resultsDrop(str6);
[fper7] = resultsDrop(str7);
[fper8] = resultsDrop(str8);
[fper9] = resultsDrop(str9);

times = 0:400:200000;

plot(times,fper0)
hold on
plot(times,fper1)
plot(times,fper2)
plot(times,fper3)
plot(times,fper4)
plot(times,fper5)
plot(times,fper6)
plot(times,fper7)
plot(times,fper8)
plot(times,fper9)

av = average(fper0,fper1,fper2,fper3,fper4,fper5,fper6,fper7,fper8,fper9);
bars = ebars(fper0,fper1,fper2,fper3,fper4,fper5,fper6,fper7,fper8,fper9);