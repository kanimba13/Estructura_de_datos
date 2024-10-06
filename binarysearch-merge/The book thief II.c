#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXT 14142


int binarySearch (int TN[], int i, int j, int k){

    int r = -1, m;

    while(i <= j){

        m =(i + j)/2;
        if (k==TN[m]){
            r = m;
            break;
        }
        else{
            if(k > TN[m])
                i = m + 1;
            else
                j= m - 1;
        }
    }
    if(r== -1)
        r= -1 * i - 1;
    return r;
}

int main(){

  int TN[MAXT + 1], i, totalCases, idCase, s, pages,forgottenPage;
  int index;

  TN[0] = 0;
  for(i = 1; i <=MAXT; i++)
    TN[i] = (i * (i + 1)) / 2;

    scanf("%d", &totalCases);
    for(idCase = 1; idCase <= totalCases; idCase++)
    {
    scanf("%d",&s);
    index = binarySearch(TN, 1, MAXT, s);
    if(index >= 1)
    {
        pages = index + 1;
        forgottenPage = index + 1;
    }
    else
    {
        pages = -1 * index -1;
        forgottenPage = TN[pages] - s;
    }
    printf("%d %d\n", forgottenPage, pages);
}

return 0;

}