#include <fstream>

int main() {
	std::ofstream qFile ("q.txt");
	if (qFile.is_open()) {
		for(int i=0; i<300; i++) {
			for(int j=0; j<300; j++) {
    			qFile << 0 << "\n";
  			}
  		}
  	}

  	qFile.close();
}