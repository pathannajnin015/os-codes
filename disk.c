#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[50], v[50]={0}, n, i, j, head;
    int total, min, pos, k, t;

    printf("Enter number of requests: ");
    scanf("%d",&n);

    printf("Enter disk requests: ");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

    printf("Enter initial head position: ");
    scanf("%d",&head);

    // Sort requests
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(a[i]>a[j])
            {
                t=a[i];
                a[i]=a[j];
                a[j]=t;
            }

    // SSTF
    pos=head;
    total=0;
    printf("\nSSTF: ");

    for(i=0;i<n;i++)
    {
        min=9999;
        k=-1;

        for(j=0;j<n;j++)
        {
            if(v[j]==0 && abs(a[j]-pos)<min)
            {
                min=abs(a[j]-pos);
                k=j;
            }
        }

        v[k]=1;
        total+=min;
        pos=a[k];
        printf("%d ",pos);
    }

    printf("\nTotal Seek = %d\n",total);

    // SCAN
    pos=head;
    total=0;
    printf("\nSCAN: ");

    for(i=0;i<n;i++)
    {
        if(a[i]>=head)
        {
            printf("%d ",a[i]);
            total+=abs(a[i]-pos);
            pos=a[i];
        }
    }

    total+=abs(199-pos);
    pos=199;

    for(i=n-1;i>=0;i--)
    {
        if(a[i]<head)
        {
            printf("%d ",a[i]);
            total+=abs(a[i]-pos);
            pos=a[i];
        }
    }

    printf("\nTotal Seek = %d\n",total);

    // C-LOOK
    pos=head;
    total=0;
    printf("\nC-LOOK: ");

    for(i=0;i<n;i++)
    {
        if(a[i]>=head)
        {
            printf("%d ",a[i]);
            total+=abs(a[i]-pos);
            pos=a[i];
        }
    }

    for(i=0;i<n;i++)
    {
        if(a[i]<head)
        {
            total+=abs(pos-a[i]);
            pos=a[i];
            printf("%d ",a[i]);
        }
    }

    printf("\nTotal Seek = %d\n",total);

    return 0;
}