function [TTT,hys] = stateDecode(state)
echo on

TTTArray = [0.0 0.04 0.064 0.08 0.1 0.128 0.16 0.256 0.32 0.48 0.512 0.64 1.024 1.280 2.56 5.12];
hysArray = [0.0 0.5 1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0 5.5 6.0 6.5 7.0 7.5 8.0 8.5 9.0 9.5 10.0];

tempTTT=[];
temphys=[];

for i = 1:(length(state))
    if (state(i) >= 0) & (state(i) < 21)
		tempTTT = [tempTTT TTTArray(1)];
		temphys = [temphys hysArray((state(i)-0)+1)];
    elseif state(i) >= 21 & state(i) < 42
		tempTTT = [tempTTT TTTArray(2)];
		temphys = [temphys hysArray((state(i)-21)+1)];
    elseif state(i) >= 42 & state(i) < 63
		tempTTT = [tempTTT TTTArray(3)];
		temphys = [temphys hysArray((state(i)-42)+1)];
    elseif state(i) >= 63 & state(i) < 84
		tempTTT = [tempTTT TTTArray(4)];
		temphys = [temphys hysArray((state(i)-63)+1)];
    elseif state(i) >= 84 & state(i) < 105
		tempTTT = [tempTTT TTTArray(5)];
		temphys = [temphys hysArray((state(i)-84)+1)];
    elseif state(i) >= 105 & state(i) < 126
		tempTTT = [tempTTT TTTArray(6)];
		temphys = [temphys hysArray((state(i)-105)+1)];
	elseif state(i) >= 126 & state(i) < 147
		tempTTT = [tempTTT TTTArray(7)];
		temphys = [temphys hysArray((state(i)-126)+1)];
    elseif state(i) >= 147 & state(i) < 168
		tempTTT = [tempTTT TTTArray(8)];
		temphys = [temphys hysArray((state(i)-147)+1)];
    elseif state(i) >= 168 & state(i) < 189
		tempTTT = [tempTTT TTTArray(9)];
		temphys = [temphys hysArray((state(i)-168)+1)];
    elseif state(i) >= 189 & state(i) < 210
		tempTTT = [tempTTT TTTArray(10)];
		temphys = [temphys hysArray((state(i)-189)+1)];
    elseif state(i) >= 210 & state(i) < 231
		tempTTT = [tempTTT TTTArray(11)];
		temphys = [temphys hysArray((state(i)-210)+1)];
    elseif state(i) >= 231 & state(i) < 252
		tempTTT = [tempTTT TTTArray(12)];
		temphys = [temphys hysArray((state(i)-231)+1)];
    elseif state(i) >= 252 & state(i) < 273
		tempTTT = [tempTTT TTTArray(13)];
		temphys = [temphys hysArray((state(i)-252)+1)];
    elseif state(i) >= 273 & state(i) < 294
		tempTTT = [tempTTT TTTArray(14)];
		temphys = [temphys hysArray((state(i)-273)+1)];
    elseif state(i) >= 294 & state(i) < 315
		tempTTT = [tempTTT TTTArray(15)];
		temphys = [temphys hysArray((state(i)-294)+1)];
    elseif state(i) >= 315 & state(i) < 336
		tempTTT = [tempTTT TTTArray(16)];
		temphys = [temphys hysArray((state(i)-315)+1)];
    end
end

TTT = tempTTT;
hys = temphys;