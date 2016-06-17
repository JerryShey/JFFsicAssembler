#ifndef MyTable_H
#define MyTable_H

#define MAX 100
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

//string otherCode[7] = { "START", "BASE", "BYTE", "WORD", "RESB", "RESW", "END" };
struct OPTAB{
	char name[10];
	int opcode;
};

struct SYMTAB{
	char name[10];
	int loc;
};

OPTAB OpTable[59];
SYMTAB SymTable[MAX];

int cnt = 0;

int isOpcode(char *mnemonic){
	for (int i = 0; i < 59; i++){
		if (!strcmp(mnemonic, OpTable[i].name)){
			return i + 1;
			break;
		}
	}
	return 0;
}

int getOpcode(int num){
	return num;
}

void add(char *name, int loc){
	
	char_traits<char>::copy(SymTable[cnt].name, name, strlen(name));
	SymTable[cnt++].loc = loc;
}

int isExist(char *name){
	bool find = false;
	for (int i = 0; i < cnt; i++){
		if (!strcmp(name, SymTable[i].name)){
			return i + 1;
		}
	}
	return 0;

}
void pritfOPTAB(){
	for (int i = 0; i < 59; i++){
		printf("%s, %X\n", OpTable[i].name, OpTable[i].opcode);
	}
}
void printSYMTAB(){
	for (int i = 0; i < cnt; i++){
		printf("%s, %X\n", SymTable[i].name, SymTable[i].loc);
		//cout << SymTable[i].name << ", " << SymTable[i].loc << endl;
	}
}
#endif