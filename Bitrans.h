#ifndef BITRANS_H
#define BITRANS_H
#include <bits/stdc++.h>
class bitrans
{   
	private:
		const char stnp[37]="0123456789abcdefghijklmnopqrstuvwxyz"; 
	public:
		void fturn(int jz,int n)    //'0'-1=47;  由于不能返回数组,直接输出 
		{
			int ab,idx=0,l=0,r;
			char ret[100],t;
			while(n!=0)
			{
				ab=n%jz;
				ret[idx]=stnp[ab];
				n=n/jz;
				idx++;
			}
			ret[idx]='\0';
			r=idx-1;
			while(l<r)
			{
				t=ret[l];
				ret[l]=ret[r];
				ret[r]=t;
				l++;r--;
			}
			puts(ret);
		}
		void strturn(int a, char *s, int c)
	    {
	        unsigned long long p = 0ull;
	        int len = strlen(s);
	        for(int i = 0; i < len; i++)
	        {
	            int val;
	            char ch = s[i];
	            if(isdigit(ch))
	                val = ch - '0';
	            else
	                val = ch - 'a' + 10;
	            p = p * a + val;
	        }
	        fturn(c, p); // 复用上面的 fturn，不用重复写反转代码！
	    }
		void fturn(int jz, unsigned long long n, char *out)
	    {
	        if(n == 0)
	        {
	            out[0] = '0';
	            out[1] = '\0';
	            return;
	        }
	        int ab,idx=0,l=0,r;
	        char ret[100],t;
	        while(n!=0)
	        {
	            ab=n%jz;
	            ret[idx]=stnp[ab];
	            n=n/jz;
	            idx++;
	        }
	        ret[idx]='\0';
	        r=idx-1;
	        while(l<r)
	        {
	            t=ret[l];
	            ret[l]=ret[r];
	            ret[r]=t;
	            l++;r--;
	        }
	        // 拷贝结果到外部out
	        strcpy(out, ret);
	    }

    /**
     * @brief a进制字符串s 转 c进制，结果存入out数组
     * @param a 原进制
     * @param s 原进制字符串
     * @param c 目标进制
     * @param out 输出字符缓冲区
     */
    void strturn(int a, char *s, int c, char *out)
    {
        unsigned long long p = 0ull;
        int len = strlen(s);
        for(int i = 0; i < len; i++)
        {
            char ch = tolower(s[i]); // 兼容大写输入
            int val;
            if(isdigit(ch))
                val = ch - '0';
            else
                val = ch - 'a' + 10;
            p = p * a + val;
        }
        fturn(c, p, out);
    }
};

#endif
