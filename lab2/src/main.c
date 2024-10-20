#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int bad_input()
{
    printf("bad input\n");
    exit(0);
}
void BadInputIfSymbolsAreNotGood(char *s, unsigned int len)
{
    for (unsigned int i=0;i<len;i++)
    {
        if (s[i]>'9' || s[i]<'0') bad_input();
    }
}
void BadInputIfStringHasRepeats(char *s, unsigned int len)               
 {
    for (unsigned int i=0;i<(len-1);i++)    
    {
       for (unsigned int j=(i+1);j<len;j++)    
       {
         if (s[i]==s[j]) bad_input();   
       }
    }
 }
void NumIsGood(int n)
{
   if(n<0) bad_input();
}
int NumWithABiggerNeighbor(char * s, unsigned int len)         
{
    for (int i=(len-2);i>=0;i--)
    {
      if (s[i]<s[i+1]) return i;
    }
    return 0;
}
int FirstBigNumber(char * s, int a, unsigned int len)
{
    a=NumWithABiggerNeighbor(s,len);
    for(int i=(len-1);i>=0;i--)
    {
        if(s[i]>s[a]) return i;
    }
    return 0;
}
void Swap(char *s, int i, int j)
{
    char tmp=s[i];
    s[i]=s[j];
    s[j]=tmp;
} 
void Reverse (char *s,int a,int b)      
{      int c=b;        
       int j=0;           
       for (int i=a;i<=(b+a)/2;i++)   
       {  
         Swap(s,i,c-j);
         j++;
       }
}
int StringIsWrong (char * s, char * v)
{
    if( atoi(s)>atoi(v)) return 1;
    else return 0;
}
int CreateNextPermutation(char * s,char * v, unsigned int len)
{
       unsigned int d=strlen(s);
       strcpy(v,s);
       int m=NumWithABiggerNeighbor(s,len);
       Swap(s, m, FirstBigNumber(s,m,len));
       if(strlen(s)==d) {
       Reverse(s,(m+1),(strlen(s)-1));
       if(StringIsWrong(s,v)==1 ) return 1;} 
       return 0;
}
int main()
{
    char s[11];
    if( !scanf("%10[^\n]s", s)) {bad_input();}
    unsigned int len=strlen(s);
    int n;
    if( !scanf("%i", &n)) {bad_input();}
    BadInputIfSymbolsAreNotGood(s,len);
    BadInputIfStringHasRepeats(s,len);
    NumIsGood(n);
    char v[11];
    memset(v,0,strlen(v));

    for( int i=0;i<n;i++)
    {
        int nextPermutationCreated = CreateNextPermutation(s,v, len);
        if (nextPermutationCreated==1) { 
         printf("%s\n", s);} 
         else { break;} 
    } 
}
