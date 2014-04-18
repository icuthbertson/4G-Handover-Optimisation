function plotQuality(heading,save,x,y,xticks,yticks,markers)
hold on
% Defaults for presentation
width = 10;     % Width in inches
height = 10;    % Height in inches
alw = 1;    % AxesLineWidth
fsz = 14;      % Fontsize
lw = 2;      % LineWidth
msz = 12;       % MarkerSize

figure(1);
%pos = get(gcf, 'Position');
pos = [0,0];
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); %<- Set size
set(gca, 'FontSize', fsz, 'LineWidth', alw); %<- Set properties
set(gca,'XTick',xticks,'YTick',yticks)
%plot(dmn,f(dmn),'b-',dmn, g(dmn),'r--',xeq,f(xeq),'g*','LineWidth',lw,'MarkerSize',msz); %<- Specify plot properites
plot(x, y, markers ,'LineWidth',lw,'MarkerSize',msz)
xlim([0 15]);
legend('TTT Value', 'Location', 'NorthWest');
xlabel('Index');
ylabel('TTT (s)');
title(heading);

print(save,'-depsc','-r300');