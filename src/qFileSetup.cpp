#include <fstream>
//This file was used to make text files with all zeros for the q arrays in the q-learning files
int main() {
	std::ofstream qFile ("q.txt");
	if (qFile.is_open()) {
		for(int i=0; i<336; i++) {
			for(int j=0; j<336; j++) {
    			qFile << 0 << "\n";
  			}
  		}
  	}

  	qFile.close();
}