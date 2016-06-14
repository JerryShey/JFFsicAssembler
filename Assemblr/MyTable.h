#ifndef MyTable_H
#define MyTable_H

#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

//string otherCode[7] = { "START", "BASE", "BYTE", "WORD", "RESB", "RESW", "END" };
struct OPTAB{
	char *name;
	int opcode;
};

struct SYMTAB{
	char *name;
	int loc;
};

OPTAB OpTable[59];
SYMTAB SymTable[MAX];

int cnt = 0;
int check = -1;

bool isOpcode(char *mnemonic){
	bool find = false;
	for (int i = 0; i < 59; i++){
		if (!strcmp(mnemonic, OpTable[i].name)){
			find = true;
			check = i;
			break;
		}
	}
	return find;
}

int getOpcode(){
	int loc = check;
	check = -1;
	return (loc);
}

void add(char *name, int loc){
	SymTable[cnt++] = { name, loc };
}

bool isExist(char *name){
	bool find = false;
	for (int i = 0; i < cnt; i++){
		if (!strcmp(name, SymTable[i].name)){
			find = true;
			check = i;
			break;
		}
	}
	return find;

}
#endif