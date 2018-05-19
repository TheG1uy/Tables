#include "TTable.h"
#include "TScanTable.h"
#define _CRT_SECURE_NO_WARNINGS

#include "TSortTable.h"
#include "TArrayHash.h"
#include "TTreeTable.h"
#include <string>
#include <stdio.h>
#include <fstream> 
#include<iostream>

using namespace std;

void printTable() {
	cout << "*-----------*-----------*" << endl;
	cout << "|    Key    |   Value   |" << endl;
	cout << "|-----------|-----------|" << endl;
	cout << "|                       |" << endl;
}

int main() {
	TScanTable<string, string> a;
	TSortTable<string, string> b;
	TArrayHash<string, string> c;
	TTreeTable<string, string> d;
	FILE *file;
	string tmpMas[100];
	int i = 0;

	
	fopen_s(&file,"text.txt", "r");
	ifstream ifs(file);
	while (!ifs.eof()) {
		ifs >> tmpMas[i];
		i++;
	}
	TRecord<string, string> record;
	for (int j = 0; j < i; j++) {
		record.key = tmpMas[j];
		record.value = tmpMas[j];
		a.Insert(record);
	}
	printTable();
	for (a.Reset();!a.isEnd();a.goNext())
		cout << "|  "<<a.getCurr().key<<"   |    "<<a.getCurr().value <<"     |" << endl;
	return 0;
}