#include "TTable.h"
#include "TScanTable.h"
#define _CRT_SECURE_NO_WARNINGS

#include "TSortTable.h"
#include "TArrayHash.h"
#include "TTreeTable.h"
#include "TTable.h"
#include <string>
#include <stdio.h>
#include <fstream> 
#include<iostream>

using namespace std;

void printTable(int maxLenght,string *table, TTable<string,string> *tb) {
	int j;
	int k;
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[0] += "+";
		else table[0] += "-";
		
		if (!(j % (maxLenght + 7))) table[2] += "+";
		else table[2] += "-";

	}

	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[1] += "|";
		else {
			if (j == 2) {
				table[1] += "Key";
				j += 2;
			}
			else if (maxLenght + 9 == j) {
				table[1] += "Value";
				j += 4;
			}
			else if ((maxLenght + 8) * 2 == j) {
				table[1] += "Periodicity";
				j += 10;
			}
			else table[1] += " ";
		}
	}

	table[0] += "+";
	table[1] += "|";
	table[2] += "+";
	k = 3;
	for (tb->Reset(); !tb->isEnd(); tb->goNext()) {
		for (j = 0; j < ((maxLenght + 6) * 3 + 3); j++) {
			if (!(j % (maxLenght + 7))) table[k] += "|";
			else {
				if (j == 2) {
					table[k] += tb->getCurr().key;
					j += tb->getCurr().key.size() - 1;
				}
				else if (maxLenght + 9 == j) {
					table[k] += tb->getCurr().value;
					j += tb->getCurr().value.size() - 1;
				}
				else if ((maxLenght + 8) * 2 == j) {
					table[k] += to_string(tb->getCurr().periodicity);
					j += to_string(tb->getCurr().periodicity).size() - 1;
				}
				else table[k] += " ";
			}
		}
		table[k] += "|";
		k++;
	}
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[k] += "+";
		else table[k] += "-";
	}
	table[k] += "+";
}
int main() {
	TScanTable<string, string> *a;
	TSortTable<string, string> *b;
	TArrayHash<string, string> *c;
	TTreeTable<string, string> *d;
	FILE *file;
	string tmpMas[100];
	string table[100];
	int i = 0;
	int maxLenght = 0;
	a = new TScanTable<string, string>();
	b = new TSortTable<string, string>();
	c = new TArrayHash<string, string>();
	d = new TTreeTable<string, string>();
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
		a->Insert(record);
	}
	
	for (a->Reset(); !a->isEnd(); a->goNext()) {
		if (a->getCurr().key.size() > maxLenght)
			maxLenght = a->getCurr().key.size();
	}
	printTable(maxLenght, table, a);
	for (int j = 0; j < 10; j++) {
		cout << table[j] << endl;
	}
	return 0;
}