function plotErrorBars(heading,save,times,av,bars,optav,optbars)
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
%plot(dmn,f(dmn),'b-',dmn, g(dmn),'r--',xeq,f(xeq),'g*','LineWidth',lw,'MarkerSize',msz); %<- Specify plot properites
errorbar(times, av, bars, 'b:' ,'LineWidth',lw)
errorbar(times, optav, optbars, 'r-' ,'LineWidth',lw)
xlim([0 200000]);
legend('Non-Optimised', 'Optimised', 'Location', 'NorthEast');
xlabel('Time (s)');
ylabel('Drop Ratio (%)');
title(heading);

print(save,'-depsc','-r300');