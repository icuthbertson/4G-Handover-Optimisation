function [fper] = resultsDrop(path)
str0 = strcat(path,'/basestation0/drop.txt');
str1 = strcat(path,'/basestation1/drop.txt');
str2 = strcat(path,'/basestation2/drop.txt');
str3 = strcat(path,'/basestation3/drop.txt');
str4 = strcat(path,'/basestation4/drop.txt');
str5 = strcat(path,'/basestation5/drop.txt');
str6 = strcat(path,'/basestation6/drop.txt');
str7 = strcat(path,'/basestation7/drop.txt');
str8 = strcat(path,'/basestation8/drop.txt');
formatSpec = '%f';
fileID0 = fopen(str0,'r');
fileID1 = fopen(str1,'r');
fileID2 = fopen(str2,'r');
fileID3 = fopen(str3,'r');
fileID4 = fopen(str4,'r');
fileID5 = fopen(str5,'r');
fileID6 = fopen(str6,'r');
fileID7 = fopen(str7,'r');
fileID8 = fopen(str8,'r');
dropB0 = fscanf(fileID0,formatSpec);
dropB1 = fscanf(fileID1,formatSpec);
dropB2 = fscanf(fileID2,formatSpec);
dropB3 = fscanf(fileID3,formatSpec);
dropB4 = fscanf(fileID4,formatSpec);
dropB5 = fscanf(fileID5,formatSpec);
dropB6 = fscanf(fileID6,formatSpec);
dropB7 = fscanf(fileID7,formatSpec);
dropB8 = fscanf(fileID8,formatSpec);
fclose(fileID0);
fclose(fileID1);
fclose(fileID2);
fclose(fileID3);
fclose(fileID4);
fclose(fileID5);
fclose(fileID6);
fclose(fileID7);
fclose(fileID8);

str0 = strcat(path,'/basestation0/handover.txt');
str1 = strcat(path,'/basestation1/handover.txt');
str2 = strcat(path,'/basestation2/handover.txt');
str3 = strcat(path,'/basestation3/handover.txt');
str4 = strcat(path,'/basestation4/handover.txt');
str5 = strcat(path,'/basestation5/handover.txt');
str6 = strcat(path,'/basestation6/handover.txt');
str7 = strcat(path,'/basestation7/handover.txt');
str8 = strcat(path,'/basestation8/handover.txt');
formatSpec = '%f';
fileID0 = fopen(str0,'r');
fileID1 = fopen(str1,'r');
fileID2 = fopen(str2,'r');
fileID3 = fopen(str3,'r');
fileID4 = fopen(str4,'r');
fileID5 = fopen(str5,'r');
fileID6 = fopen(str6,'r');
fileID7 = fopen(str7,'r');
fileID8 = fopen(str8,'r');
handoverB0 = fscanf(fileID0,formatSpec);
handoverB1 = fscanf(fileID1,formatSpec);
handoverB2 = fscanf(fileID2,formatSpec);
handoverB3 = fscanf(fileID3,formatSpec);
handoverB4 = fscanf(fileID4,formatSpec);
handoverB5 = fscanf(fileID5,formatSpec);
handoverB6 = fscanf(fileID6,formatSpec);
handoverB7 = fscanf(fileID7,formatSpec);
handoverB8 = fscanf(fileID8,formatSpec);
fclose(fileID0);
fclose(fileID1);
fclose(fileID2);
fclose(fileID3);
fclose(fileID4);
fclose(fileID5);
fclose(fileID6);
fclose(fileID7);
fclose(fileID8);

total_drop = [dropB0;dropB1;dropB2;dropB3;dropB4;dropB5;dropB6;dropB7;dropB8];
total_drop = sort(total_drop);

total_handover = [handoverB0;handoverB1;handoverB2;handoverB3;handoverB4;handoverB5;handoverB6;handoverB7;handoverB8];
total_handover = sort(total_handover);

[per,times] = dropPerformance(total_drop,total_handover);

[sper] =  smooth(times,per);

fper = sper;

