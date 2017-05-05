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

string GetLastLine(ifstream& in)
{
    string line;
    while (in >> ws && getline(in, line)); //while (in >> ws && getline(in, line)); skip empty lines
     

    return line;
}

int main(){
	
	
	ifstream test_file;
	test_file.open("F:/Dokumente und Einstellungen/vip2/Desktop/data.txt");
	
	string dummie;
	
	dummie = GetLastLine(test_file);
	
	cout << dummie << endl;
	
	test_file.close();
}
