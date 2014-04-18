function plotProp(heading,save,dist,ok,egli,cost)
hold on
% Defaults for presentation
width = 10;     % Width in inches
height = 10;    % Height in inches
alw = 1;    % AxesLineWidth
fsz = 14;      % Fontsize
lw = 2;      % LineWidth
msz = 14;       % MarkerSize

figure(1);
%pos = get(gcf, 'Position');
pos = [0,0];
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); %<- Set size
set(gca, 'FontSize', fsz, 'LineWidth', alw); %<- Set properties
%plot(dmn,f(dmn),'b-',dmn, g(dmn),'r--',xeq,f(xeq),'g*','LineWidth',lw,'MarkerSize',msz); %<- Specify plot properites
plot(dist, ok, 'b-' ,'LineWidth',lw)
plot(dist, egli, 'k--' ,'LineWidth',lw)
plot(dist, cost, 'r-.' ,'LineWidth',lw)
xlim([0 20]);
legend('Okumura-Hata (1500 MHz)', 'Egli (2000 MHz)', 'Cost231-Hata (2000 MHz)', 'Location', 'NorthEast');
xlabel('Distance (km)');
ylabel('Path Loss (dB)');
title(heading);

print(save,'-depsc','-r300');