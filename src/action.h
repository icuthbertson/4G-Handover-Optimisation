#if !defined(_ACTION_H_)
#define _ACTION_H_

class action {
private:
	int actionIndex[2];
public:
	action(int TTT, int hys);
	int actionTTT();
	int actionhys();
};

#endif