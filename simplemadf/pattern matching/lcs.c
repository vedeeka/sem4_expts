#include<stdio.h>

int L[12][12];


int lsc(char x[],char y[]){

    for (int i=0;i<=12;i++){
        L[i][0]=0;
    }
    for (int i=0;i<=10;i++){
        L[0][i]=0;
    }

    for(int i=0;i<12;i++){
        for(int j=0;j<10;j++){
            if(x[i]==y[j]){
                L[i][j]=L[i-1][j-1]+1;

            }else{
                int max;
                if(L[i-1][j]>L[i][j-1]){
                    max=L[i-1][j];
                }else{
                     max=L[i][j-1];
                }
                L[i][j]=max;
            }
        }
    }

    for(int i=0;i<12;i++){
        for(int j=0;j<10;j++){
            printf("%d ",L[i][j]);
        }
        printf(" \n");
    }
    return 0;
}


int main(){
    char t1[10]={'g','t','t','c','c','t','a','a','t','a'};
    char t2[12]={'c','g','a','t','a','a','t','t','g','a','g','a'};

    lsc(t1,t2);
}