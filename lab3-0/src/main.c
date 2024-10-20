#include <stdlib.h>
#include <stdio.h>

void SortByHeapBubble(int pos, int a[], int N)
{
     int max;
     for(;;)
     {
       int tmp;
       if((2*pos+1)>=N) return;
       else if((2*pos+2)>=N) max=(2*pos+1);
       else if(a[2*pos+1]>a[2*pos+2]) max=(2*pos+1);
       else max=(2*pos+2);

       if(a[pos]>a[max]) return;
        
       tmp=a[pos];
       a[pos]=a[max];
       a[max]=tmp;
       pos=max;
     }
}
void SortByHeap(int a[], int N)
{
      
    for (int i=N/2;i>=0;i--) {SortByHeapBubble(i,a,N);}
      for(int i=(N-1);i>0;i--)
      {
        int tmp;
        tmp = a[0];
        a[0]=a[i];
        a[i]=tmp;
        SortByHeapBubble(0,a,i);
      }
}

int main()
{
  int N;
  if(! scanf("%i", &N)) exit(0);
  int a[N];
  for(int i=0;i<N;i++)
  {
    if(!scanf("%i", &a[i])) exit(0);
    ;
  }
  SortByHeap(a,N);
  for(int i=0;i<N;i++)
  {
    printf("%i ", a[i]);
  }
  printf("\n");
}
