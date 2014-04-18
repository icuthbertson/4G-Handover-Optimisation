function [sper] =  smooth(times,per)
newper = [];
index = 0;
t = 1;
for i = 0:400:200000
    if i >= times(t);
        if index ~= length(per)
            index = index+1;
        end
        disp(t)
        disp(length(times))
        if t ~= (length(times)-1)
            t = t+1;
        end
    end
    if index > 0
        newper = [newper per(index)];
    else
        newper = [newper 0];
    end
end

sper = newper;