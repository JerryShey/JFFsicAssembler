#ifndef Pass1_H
#define Pass1_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "MyTable.h"
#include <fstream>

using namespace std;

extern SYMTAB SymTable[MAX];

// Function
void pass1();
int isOtherCode(char *);
int RESX(char *, char *);
int Hex2Dec(char);
int BorW(char*, char*);
void cutWord(char*, int);
int setStart(char*);

//global variable
int Loc = NULL;
char *B;
char *BWvalue[2];

void pass1(){
	const int len = 80;
	char buffer[len] = "";
	const char *delim = "	";
	char *code[5];
	char *p;

	// 開啟要讀取的檔案 
	ifstream infile("test.txt");
	while (infile) {
		// 從檔案讀資料
		infile.getline(buffer, len);
		printf("%4X	", Loc);
		cout << buffer << endl;
		char * pch;
		int cnt = 0;
		pch = strtok_s(buffer, delim, &p);
		while (pch != NULL)
		{
			code[cnt++] = pch;
			pch = strtok_s(NULL, delim, &p);
		}

		int offset = 0;
		int num;
		if (cnt == 3){
			add(code[0], Loc);
			if (num = isOtherCode(code[1])){
				if (num == 3){
					offset = RESX(code[1], code[2]);
				}
				else if (num == 2){
					offset = BorW(code[1], code[2]);
				}
				else{
					if (!strcmp(code[1], "START"))
						Loc = setStart(code[2]);
					else if (!strcmp(code[1], "BASE")){
						B = code[2];
					}
					else
					{
						break;
					}
				}
			}
			else{
				offset = 0x03;
			}
		}
		else if (cnt == 2){
			if (num = isOtherCode(code[0])){
				if (num == 3){
					offset = RESX(code[0], code[1]);
				}
				else if (num == 2){
					offset = BorW(code[0], code[1]);
				}
				else{
					if (!strcmp(code[1], "START"))
						Loc = atoi(code[2]);
					else if (!strcmp(code[1], "BASE")){
						B = code[2];
					}
				}
			}
			else{
					offset = 0x03;	//format 3 長度為3 bytes
			}
		}
		else
			offset = 0x03;
		Loc += offset;
		
	}
}

/*	isOtherCode
**	START, BASE, END return 1
**	BYTE, WORD return 2
**	RESB, RESW return 3
**/
int isOtherCode(char *code){
	if (!strcmp(code, "START")){
		return 1;
	}
	else if (!strcmp(code, "BASE")){
		return 1;
	}
	else if (!strcmp(code, "WORD")){
		return 2;
	}
	else if (!strcmp(code, "BYTE")){
		return 2;
	}
	else if (!strcmp(code, "RESW")){
		return 3;
	}
	else if (!strcmp(code, "RESB")){
		return 3;
	}
	else if (!strcmp(code, "END")){
		return 1;
	}
	else
		return 0;
	return 0;
}

/*	RESX
**	RESW store a variable using 3 bytes
**	RESB 1.X, store a variable by Hex
**		 2.C, store a variable by ASCII code
**/
int RESX(char* code, char *value){
	if (!strcmp(code, "RESB")){
		return (atoi(value) * 1);
	}
	else{
		return (atoi(value) * 3);
	}
}

/*	Hex2Dec
**	change Hex number to Dec number
**/
int Hex2Dec(char chara){
	switch (chara)
	{
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		break;
	}
	return 0;
}

int BorW(char *code, char *val){
	if (!strcmp(code, "WORD")){
		return 0x03;
	}
	else{
		cutWord(val, 2);
		if (!strcmp(BWvalue[0], "X"))
			return 0x01;
		else{
			return strlen(BWvalue[1]);
		}
	}
}

/*	cutWord
**	cut word by ' and store in BWvalue (Byte or Wors' value)
**/
void cutWord(char *temp, int i){
	int cnt = 0;
	const char *delim = "\'";
	char *p = NULL;
	char *pch;
	char *word = NULL;
	pch = strtok_s(temp, delim, &p);
	while (i > 0)
	{
		BWvalue[cnt++] = pch;
		pch = strtok_s(NULL, delim, &p);
		i--;
	}
}

/*	setStart
**	to set the strat location
**/
int setStart(char *startLoc){
	int len = strlen(startLoc);
	int start = 0;
	for (int i = 0; i < len; i++){
		int x = 1;
		for (int j = i; j > 0; j--){
			x *= 16;
		}
		start += x*Hex2Dec(startLoc[len - (i + 1)]);
	}
	return start;
}
#endif