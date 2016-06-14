#include "MyTable.h"
#include "pass1.h"

/*****	�զX�y���P�t�ε{�� �����@�~
**	�@�̡G�P�͡A�Ǹ��G4103056035
**	�����ɶ��G2016/06/12(��)
**/

using namespace std;

// function
void makeOpTab();

//	extern variable form OpTable.h
extern OPTAB OpTable[59];
extern SYMTAB SymTable[MAX];

int main(){
	makeOpTab();
	pass1();
	getchar();
	return 0;
}

void makeOpTab(){
	ifstream infile("SIC Opcode.txt");
	char x[15];
	const char *delim = " ";
	char *p;
	int cnt = 0, i = 0;
	while (infile){
		infile.getline(x, 15);
		char * pch;
		pch = strtok_s(x, delim, &p);
		while (pch != NULL)
		{
			if (i){
				i = 0;
				OpTable[cnt++].opcode = 16 * Hex2Dec(pch[2]) + Hex2Dec(pch[3]);
			}
			else{
				OpTable[cnt].name = pch;
				i++;
			}
			pch = strtok_s(NULL, delim, &p);
		}
	}
}
