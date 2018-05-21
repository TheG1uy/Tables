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

void printTable(int maxLenght,string *table, TTable<string,string> *tb, int *count) {
	int j;
	int k;
	*count = 0;
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
		(*count)++;
	}
	for (j = 0; j < (maxLenght + 6) * 3 + 3; j++) {
		if (!(j % (maxLenght + 7))) table[k] += "+";
		else table[k] += "-";
	}
	table[k] += "+";
}
void entryTable(int size, string *mas, TTable<string, string> *tb) {
	TRecord<string, string> record;
	for (int j = 0; j < size; j++) {
		record.key = mas[j];
		record.value = mas[j];
		record.periodicity = 0;
		tb->Insert(record);
	}
}
void getMaxSize(int *maxLenght, TTable<string, string> *tb) {
	for (tb->Reset(); !tb->isEnd(); tb->goNext()) {
		if (tb->getCurr().key.size() > *maxLenght)
			*maxLenght = tb->getCurr().key.size();
	}
}


int main() {
	TTable<string, string> *usedata;
	TScanTable<string, string> *a;
	TSortTable<string, string> *b;
	TArrayHash<string, string> *c;
	TTreeTable<string, string> *d;
	FILE *file;
	string tmpMas[1000];
	string table[1000];
	string instruction;
	int i = 0;
	int maxLenght = 0;
	int counter;
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


	while (true) {
		cout << "instruction : ";
		std::getline(cin, instruction);
		string tmp = instruction.substr(0 , instruction.find_first_of(" "));
		
		if (instruction.size()) {
			if (tmp == "help") {
				string help = "SHOW  -- show databases\nUSE 'database'  -- use databese\nFIND 'key'  -- find record\nDELETE 'key'  -- delete record\nINSERT'Key'  -- insert record\nPRINT -- print database";
				cout << help << endl;
			}
			if (tmp == "show" || tmp == "Show" || tmp == "SHOW") {
				string show = "SCANTABLE\nSORTTABLE\nHASHTABLE\nTREETABLE";
				cout << show << endl;
			}

			if (tmp == "use" || tmp == "Use" || tmp == "USE") {
				a->clear();
				b->clear();
				c->clear();
				d->clear();
				tmp = instruction.substr(instruction.find_first_of(" ")+1, instruction.size());
				if (tmp == "scanTable" || tmp == "ScanTable" || tmp == "scantable" || tmp == "SCANTABLE") {
					entryTable(i, tmpMas, a);
					getMaxSize(&maxLenght, a);
					printTable(maxLenght, table, a ,&counter);
					usedata = a;
				}
				if (tmp == "sortTable" || tmp == "SortTable" || tmp == "sorttable" || tmp == "SORTTABLE") {
					entryTable(i, tmpMas, b);
					getMaxSize(&maxLenght, b);
					printTable(maxLenght, table, b, &counter);
					usedata = b;
				}

				if (tmp == "hashTable" || tmp == "HashTable" || tmp == "hashtable" || tmp == "HASHTABLE") {
					entryTable(i, tmpMas, c);
					getMaxSize(&maxLenght, c);
					printTable(maxLenght, table, c, &counter);
					usedata = c;
				}

				if (tmp == "treeTable" || tmp == "TreeTable" || tmp == "treetable" || tmp == "TREETABLE") {
					entryTable(i, tmpMas, d);
					getMaxSize(&maxLenght, d);
					printTable(maxLenght, table, d, &counter);
					usedata = d;
				}

				for (int j = 0; j < counter + 4; j++) {
					cout << table[j] << endl;
					table[j] = "";
				}
				cout <<"Building efficiency : "<< usedata->getEff() << endl<<endl;
				usedata->setEff(0);
			}
			else if (tmp == "find" || tmp == "Find" || tmp == "FIND") {
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				bool tmpb = usedata->Find(tmp);
				cout << "Record found : " << tmpb << " Find efficiency : " << usedata->getEff() << endl;
				usedata->setEff(0);
			}
			else if (tmp == "delete" || tmp == "Delete" || tmp == "DELETE") {
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				bool tmpb = usedata->Find(tmp);
				usedata->setEff(0);
				usedata->Delete(tmp);
				cout << "Record delete : " << tmpb << " Delete efficiency : " << usedata->getEff() << endl;
			}
			else if (tmp == "print" || tmp == "Print" || tmp == "PRINT") {
				getMaxSize(&maxLenght, usedata);
				printTable(maxLenght, table, usedata, &counter);
				for (int j = 0; j < counter + 4; j++) {
					cout << table[j] << endl;
					table[j] = "";
				}
				usedata->setEff(0);
			}
			else if (tmp == "insert" || tmp == "Insert" || tmp == "INSERT") {
				tmp = instruction.substr(instruction.find_first_of(" ") + 1, instruction.size());
				usedata->setEff(0);
				TRecord<string, string> tmpR;
				tmpR.key = tmp;
				tmpR.value = tmp;
				tmpR.periodicity = 0;
				usedata->Insert(tmpR);
				cout << "Insert efficiency : " << usedata->getEff() << endl;
				usedata->setEff(0);
			}
		}
	}



	

	//entryTable(i, tmpMas , b);
	//getMaxSize(&maxLenght, b);
	//printTable(maxLenght, table, b);

	
	return 0;
}