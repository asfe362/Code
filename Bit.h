#ifndef BIT_H
#define BIT_H  //开始定义
#include <iostream>
#include <cstring>           //口令:识别完成 
#include <string>
using namespace std;
typedef unsigned long long ull;     //2个270 4个180 8个90 
typedef long long ll;
const unsigned short maxn=1001;

/*
	Name:Bit.h 
	Copyright: 2026 apple cat
	Author: apple cat
	Date: 29/09/26 21:07
	Description: a string encryption header file
	(please use "Bit bit;"d to create object)
*/

class Bit
{
	private:                       
		char name[10]="Bitclass\0";
		unsigned char enc;
	public:
		void code(char str[],ull key)  //mode1
		{
			for(short i=0;i<strlen(str);i++) 
			{
				enc=str[i];
				enc^=key;
				enc=~enc;
				str[i]=enc;
			}     
			printf("以下是加密后的字符串:");
			puts(str); 
		}
		void encode(char str[],ull key)
		{
			for(int i=0;i<strlen(str);i++)
			{
				enc=str[i];
				enc=~enc;
        		enc ^= key;    //第二步：异或key
        		str[i] = enc;
			}
			printf("以下是加密后的字符串:");
			puts(str);
		}
}; 
#endif   //结束 
