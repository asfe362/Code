#ifndef Tools_h
#define Tools_h
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>
#include <array>
#define useprsolve "使用时用#include "Tools.h""
#define allhead "万能头:#include <bits/stdc++.h>" 
//真偏浓卡死
//使用时用#include "Tools.h" 
//2026/8/18 13:02
/*
	Name:Tools.h 
	Copyright:2026 Forest? 
	Author:apple cat 
	Date: 18/08/26 13:02
	Description:A definitely useful toolbox programme. 
*/ 
class Tool
{
public:
    bool leap(long year)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            return true;
        else
            return false;
    }

    int pow(int num1, int num2)
    {
        long long sum = 1;
        for (long long i = 0; i < num2; i++)
        {
            sum *= num1;
        }
        return (int)sum;
    }

    int min(int c[], int n)
    {
        int t;
        if (n == 1)
            t = c[0];
        else
        {
            if (min(c, n - 1) < c[n - 1])
                t = min(c, n - 1);
            else
                t = c[n - 1];
        }
        return t;
    }

    int max(int num[], long n)
    {
        int t;
        if (n == 1)
            t = num[0];
        else
        {
            if (max(num, n - 1) > num[n - 1])
                t = max(num, n - 1);
            else
                t = num[n - 1];
        }
        return t;
    }

    long long randint(long long a, long long b)
    {
        return rand() % (b - a + 1) + a;
    }

    bool even(int d)
    {
        if (d % 2 == 0)
            return true;
        else
            return false;
    }

    bool odd(int a)
    {
        if (a % 2 == 1)
            return true;
        else
            return false;         
    }

    void line(char func)
    {
        if (func == '-')
        {
            for (int i = 1; i < 147; i++)
                std::cout << "-";
        }
        else
        {
            for (int j = 1; j < 147; j++)
                std::cout << "=";
        }
    }

    void greet(char t)
    {
        std::cout << "Hello user,this is a " << t << "programme." << std::endl;
        std::cout << "Hello World!" << std::endl;
    }
    bool triangle(int a[3])
    {
        if ((a[0] + a[1] > a[2]) && (a[0] + a[2] > a[1]) && (a[1] + a[2] > a[0]))
        {
            if (max(a, 3) == a[0])
            {
                if ((a[0] - a[1] < a[2]) && (a[0] - a[2] < a[1]))
                {
                    return true;
                }
            }
            else if (max(a, 3) == a[1])
            {
                if ((a[1] - a[0] < a[2]) && (a[1] - a[2] < a[0]))
                {
                    return true;
                }
            }
            else if (max(a, 3) == a[2])
            {
                if ((a[2] - a[0] < a[1]) && (a[2] - a[1] < a[0]))
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    long long level(long n)
    {
        if (n <= 0)
            return 1;
        long long result = 1;
        for (int i = 1; i <= n; i++)
        {
            result *= i;
        }
        return result;
    }
    int* range(int start,int stop,int stride)
    {
    	int* ip=new int[stop];
    	if(start==0)
    	{
    		for(int i=start;i<=stop;i++)
    			ip[i]=i;
    	}
    	else
    	{
			for(int i=start;i<=stop;i++)
				ip[i-1]=i;
		}
		return ip;
	}
	void outlist(std::string s[],bool enter)
	{
		if(enter)
		{
			for(int i=0;i<(int)s->size();i++)
				std::cout<<s[i]<<std::endl;
		}
		else
		{
			for(int i=0;i<(int)s->size();i++)
				std::cout<<s[i]<<" ";
		}
	}
	int len(int lis[]) 
	{
		int lenx=0,now=1,i=0; 
		while(now!=0) 
		{
			now=lis[i]; 
			i++; 
			lenx++; 
		}
		return lenx; 
	}
	int len(char lit[])            
	{
		int lenx=0,i=0;
		char now='f';
		while(now!='\0')
		{
			now=lit[i];
			lenx++;
			i++;
		}
		return lenx;
	}
	long long gcd(long long a,long long b)
	{
		if (b == 0)
			return a < 0 ? -a : a;
		return gcd(b, a % b);
	}
	std::array<int,2> chicken_rabbit(int jiao,int tou)
	{
	    int tu=(jiao-tou*2)/2;
	    int ji=tou-tu;
	    std::array<int,2> ret;
	    ret[0] = ji;
	    ret[1] = tu;
	    return ret;
	}
	double triarea(double bian[])
	{
		double p=0.5*(bian[0]+bian[1]+bian[2]);
		double area=sqrt(p*(p-bian[0])*(p-bian[1])*(p-bian[2]));
		return area;
	}
};

#endif
