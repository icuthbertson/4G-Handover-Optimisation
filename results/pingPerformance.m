function [performance,times] = pingPerformance(ping,handover)
echo on
i = 1;
j = 1;
totping = 0;
tothand = 0;
y=[];
z=[];
newP = ping;
newH = handover;

for r = 1:(length(newP)+length(newH))
    disp(newP(i))
    disp(newH(j))
    if (newP(i) <= newH(j)) & (i <= length(newP))
        totping=totping+1;
        x=totping/(tothand+totping);
        y=[y x];
        z=[z newP(i)];
        if i <= length(newP)
            i=i+1;
        end
        if i > length(newP)
            i = length(newP);
            newP(i)=9999999;
        end
    elseif(newH(j) < newP(i)) & (j <= length(newH))
        tothand=tothand+1;
        x=totping/(tothand+totping);
        y=[y x];
        z=[z newH(j)];
        if j <= length(newH)
            j=j+1;
        end
        if j > length(newH)
            j=length(newH);
            newH(j)=9999999;
        end
    end
end

performance = y;
times = z;