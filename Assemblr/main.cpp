#include "MyTable.h"
#include "pass1.h"

/*****	組合語言與系統程式 期末作業
**	作者：周彤，學號：4103056035
**	完成時間：2016/06/12(日)
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
