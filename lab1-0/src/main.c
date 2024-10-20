#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PAGESIZE 1024


void PrintBM (unsigned char *page, unsigned char *sample, unsigned int *shifts, int sampleLen, int plen, size_t* shift, long unsigned int *lastPos)    
{                                                     
   int i=0;  
   int sh=*shift;                        
   while(i<=plen)  
   {
      //fprintf(stderr, "boyermoore ");
      if((i+sampleLen)>plen) {return;}
      if(sample[sampleLen-1]!=page[i+sampleLen-1] ) {printf("%i ", i+sampleLen+sh);/*fprintf(stderr,"%i ", i+sampleLen+sh);*/}
      else {
         for(int j=sampleLen-1;j>=0;j--)   
         {
            if(sample[j]==page[i+j]) {printf("%i ", i+j+1+sh);/*fprintf(stderr,"%i ", i+j+1+sh);*/}
            else {printf("%i ", i+j+1+sh);/*fprintf(stderr,"%i ", i+j+1+sh);*/break;} 
         }
      }
      *shift = *shift + shifts[page[i+sampleLen-1]];
      *lastPos=*lastPos+ shifts[page[i+sampleLen-1]];
      i=i+shifts[page[i+sampleLen-1]];
   } 
}

int main()
{
   unsigned char sample[18];
   if (!fgets((char*)sample, 18, stdin)) {exit(0);}
   sample[strlen((char*)sample)-1]=0;
   size_t sampleLen = strlen((char*)sample);
   unsigned int shifts[256]; 
   for(int i=0;i<256;i++)
   {
      shifts[i]=sampleLen;
   }
   for(unsigned int i=0;i<sampleLen-1;i++)
   {
      shifts[sample[i]]=sampleLen-1-i;
   }
   unsigned char page[PAGESIZE];                                 
   size_t plen = 0;
   size_t rlen;
   size_t shift=0;
   while (1) {
      size_t lastPos=0;
      if ( sampleLen> plen) {
         rlen = fread(page + plen, 1, PAGESIZE - plen, stdin);
         if (!rlen) {
            break;
         }
         plen += rlen;
         //fprintf(stderr, "\nBUFFER UPDATE\n");
      }
      PrintBM(page,sample,shifts,sampleLen,plen, &shift, &lastPos);
      //fprintf(stderr, "\nRIGHT AFTER BM\n");
      //lastPos=shift;
      //fprintf(stderr, "lastPos && plen %li %li\n", lastPos, plen);
      if(lastPos<=plen) {memcpy(page, page + lastPos, plen - lastPos);           
      plen = plen - lastPos;}
      else{break;}
   }
    printf("\n");
    return 0;
   }


