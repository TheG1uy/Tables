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

void printTable(int maxLenght,string *table) {
	int j;
	//TRecord<string,string> record
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) 
		if (!(j % (maxLenght + 7))) table[0] += "+";
		else table[0] += "-";
	table[0] += "+";
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) 
		if (!(j % (maxLenght + 7))) table[1] += "|";
		else table[1] += " ";
	table[1] += "|";
	
		
}

int main() {
	TScanTable<string, string> a;
	TSortTable<string, string> b;
	TArrayHash<string, string> c;
	TTreeTable<string, string> d;
	FILE *file;
	string tmpMas[100];
	string table[100];
	int i = 0;
	int maxLenght = 0;
	
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
	
	for (a.Reset(); !a.isEnd(); a.goNext()) {
		if (a.getCurr().key.size() > maxLenght)
			maxLenght = a.getCurr().key.size();
	}
	printTable(maxLenght, table);
	for (int j = 0; j < 10; j++) {
		cout << table[j] << endl;
	}
	return 0;
}