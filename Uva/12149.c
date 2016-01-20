#include <stdio.h>
int main()
{
    int n,i,sum;
    while(scanf("%d",&n)==1){
        if(n==0)
            break;
        sum=0;
        for(i=n;i>=1;i--){
            sum=sum+i*i;
        }
        printf("%d\n",sum);
    }
    return 0;
}
