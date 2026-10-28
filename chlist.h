#ifndef CHLIST_H
#define CHLIST_H
//Includes
#include <cstdio>
#include <iostream>
#include <conio.h>
#include <cstring>
using namespace std;
/*
	Name:chlist.h 
	Copyright:2026 apple cat 
	Author:apple cat 
	Date: 2026/10/26 13:28
	Description:a char array header file.
	(class&namespace) 
*/
typedef long long ll;
typedef unsigned short us;
typedef unsigned long long ull;
//class
class chlist
{
	public:
		ll len(char str[]) {
			return strlen(str); }
		
		void chget(char *pstr)
		{
			ull i=0ull;
			while((pstr[i]=getchar())!='\n') i++;
			pstr[i]='\0';
		}
		void chget(char *pstr, ull buf_size)    //buf_size用sizeof() 
		{
		    if (buf_size == 0) return;
		    ull i = 0ull;
		    int ch; // getchar 返回 int！必须用int存，区分EOF
	    	// 最多读到 buf_size-2，留一个位置给 '\0'
    		while ((ch = getchar()) != '\n' && ch != EOF && i < buf_size - 1)
    		{
        		pstr[i] = static_cast<char>(ch);
        		i++;
    		}
    		pstr[i] = '\0'; // 加上结束符
		}
		void copy(const char *src, char *dest)
		{
    		strcpy(dest, src);
		}
		void chput(char str[])
		{
			puts(str);
		}
		void chfget(char *pstr,int maxstr)
		{
		    ull i = 0ull;
		    int ch;
		    bool prevEnter = false;  // 标记上一个字符是不是换行
		
		    while (i < maxstr - 1)
		    {
		        ch = getchar();
		        if (ch == EOF) break;
		
		        if (ch == '\n')
		        {
		            if (prevEnter)
		            {
		                // 连续两个回车 → 停止录入，吃掉第二个换行
		                break;
		            }
		            prevEnter = true;
		        }
		        else
		        {
		            prevEnter = false;
		        }
		        pstr[i] = static_cast<char>(ch);
		        i++;
		    }
		    pstr[i] = '\0';
		}
};

namespace chlistn
{
	//#ai
	ll len(char str[]) {
			return strlen(str); }
		
		void chget(char *pstr)
		{
			ull i=0ull;
			while((pstr[i]=getchar())!='\n') i++;
			pstr[i]='\0';
		}
		void chget(char *pstr, ull buf_size)    //buf_size用sizeof() 
		{
		    if (buf_size == 0) return;
		    ull i = 0ull;
		    int ch; // getchar 返回 int！必须用int存，区分EOF
	    	// 最多读到 buf_size-2，留一个位置给 '\0'
    		while ((ch = getchar()) != '\n' && ch != EOF && i < buf_size - 1)
    		{
        		pstr[i] = static_cast<char>(ch);
        		i++;
    		}
    		pstr[i] = '\0'; // 加上结束符
		}
		void copy(const char *src, char *dest)
		{
    		strcpy(dest, src);
		}
		void chput(char str[])
		{
			puts(str);
		}
		void chfget(char *pstr,int maxstr)
		{
		    ull i = 0ull;
		    int ch;
		    bool prevEnter = false;  // 标记上一个字符是不是换行
		
		    while (i < maxstr - 1)
		    {
		        ch = getchar();
		        if (ch == EOF) break;
		
		        if (ch == '\n')
		        {
		            if (prevEnter)
		            {
		                // 连续两个回车 → 停止录入，吃掉第二个换行
		                break;
		            }
		            prevEnter = true;
		        }
		        else
		        {
		            prevEnter = false;
		        }
		        pstr[i] = static_cast<char>(ch);
		        i++;
		    }
		    pstr[i] = '\0';
		}
}

#endif 
