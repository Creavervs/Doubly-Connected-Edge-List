// Execute main
#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <fstream>
#include<string>
#include<string.h>

using namespace std;

char file[] = "file.txt";



void makeNewPoint() {

}

void readIn(char* file) {
	ifstream inFile;
	inFile.open(file);
	//File fails to open
	if (inFile.fail()) {
		cerr << "Failed to open file. Please check filename and location";
		exit(1);
	}

	int x, y;
	char buffer[]="";
	

	while (!inFile.eof()) {
		inFile >> buffer;
		char *token = strtok(buffer, ",");
		x = std::stoi(token);
	
		// Keep printing tokens while one of the
		// delimiters present in str[].
		
			token = strtok(NULL, ",");
			y =std::stoi(token);
		
		//x = (int)token[0];
		//y = (int)token[1];
			std::cout << "x is: ";
		std::cout <<  x;
		std::cout << "\n";
		std::cout << "y is: ";
		std::cout << y;
		std::cout << "\n";
		makeNewPoint();
		std::cout <<"\n";
		
	}
	std::cout << "here";
	
	inFile.close();
}
int main(){
	
	readIn(file);
	return 0;

}