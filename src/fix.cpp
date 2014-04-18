#include <fstream>
//This code was used to generate the actions array seen in the actions.h file.
int main() {
	std::ofstream fixFile ("fix.txt");

  	for(int i=0; i<336;i++) {
  		fixFile << "int actions" << i << "[] " << "=" << " {";
  		if(i%21 == 0) {
  			if (i-21 >=0) {
				fixFile << (i-21);
  			} else {
				fixFile << "-1";
  			}
  			if (i-20 >=0) {
				fixFile << "," << (i-20);
  			} else {
				fixFile << ",-1";
  			}
			if (i+1 <336) {
				fixFile << "," << (i+1);
  			} else {
				fixFile << ",-1";
  			}
			if (i+22 <336) {
				fixFile << "," << (i+22);
  			} else {
				fixFile << ",-1";
  			}
			if (i+21 <336) {
				fixFile << "," << (i+21);
  			} else {
				fixFile << ",-1";
  			}
  			fixFile << ",-1,-1,-1";
  		} else if(i%21==20) {
  			if (i-21 >=0) {
				fixFile << (i-21);
  			} else {
				fixFile << "-1";
  			}
  			if (i-22 >=0) {
				fixFile << "," << (i-22);
  			} else {
				fixFile << ",-1";
  			}
			if (i-1 >0) {
				fixFile << "," << (i-1);
  			} else {
				fixFile << ",-1";
  			}
			if (i+20 <336) {
				fixFile << "," << (i+20);
  			} else {
				fixFile << ",-1";
  			}
			if (i+21 <336) {
				fixFile << "," << (i+21);
  			} else {
				fixFile << ",-1";
  			}
  			fixFile << ",-1,-1,-1";
  		} else {
  			if (i-22 >=0) {
				fixFile << (i-22);
  			} else {
				fixFile << "-1";
  			}
			if (i-21 >=0) {
				fixFile << "," << (i-21);
  			} else {
				fixFile << ",-1";
  			}
			if (i-20 >=0) {
				fixFile << "," << (i-20);
  			} else {
				fixFile << ",-1";
  			}
			if (i-1 >=0) {
				fixFile << "," << (i-1);
  			} else {
				fixFile << ",-1";
  			}
			if (i+1 <336) {
				fixFile << "," << (i+1);
  			} else {
				fixFile << ",-1";
  			}
			if (i+22 <336) {
				fixFile << "," << (i+22);
  			} else {
				fixFile << ",-1";
  			}
			if (i+21 <336) {
				fixFile << "," << (i+21);
  			} else {
				fixFile << ",-1";
  			}
			if (i+20 <336) {
				fixFile << "," << (i+20);
  			} else {
				fixFile << ",-1";
  			}
  		}

		fixFile << "};\n";
  	}

  	fixFile.close();

  	std::ofstream qd ("qDrop.txt");
  	std::ofstream qp ("qPing.txt");
  	std::ofstream q ("q.txt");

  	for(int i=0; i<(336*336);i++) {
 		qd << "0\n";
 		qp << "0\n";
 		q << "0\n";
  	}

  	qd.close();
  	qp.close();

}