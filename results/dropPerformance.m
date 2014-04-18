function [performance,times] = dropPerformance(drop,handover)
echo on
i = 1;
j = 1;
totdrop = 0;
tothand = 0;
y=[];
z=[];
newD = drop;
newH = handover;

for r = 1:(length(newD)+length(newH))
    if (newD(i) <= newH(j)) & (i <= length(newD))
        totdrop=totdrop+1;
        x=totdrop/tothand;
        y=[y x];
        z=[z newD(i)];
        if i <= length(newD)
            i=i+1;
            disp(i)
        end
        if i > length(newD)
            i = length(newD);
            newD(i)=9999999;
        end
    elseif(newH(j) < newD(i)) & (j <= length(newH))
        tothand=tothand+1;
        x=totdrop/tothand;
        y=[y x];
        z=[z newH(j)];
        if j <= length(newH)
            j=j+1;
            disp(j)
        end
        if j > length(newH)
            j=length(newH);
            newH(j)=9999999;
        end
    end
end

performance = y;
times = z;