#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

int main(){
	
	
	ofstream test_file;
	test_file.open("F:/Dokumente und Einstellungen/vip2/Desktop/data.txt");
	
	int counter= 0;
	while(1){
		
		test_file << counter << endl;
		counter += 1;
		sleep(1);
	}
	
	test_file.close();
}
