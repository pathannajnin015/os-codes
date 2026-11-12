#include <stdio.h>

int main()
{
    int n, m, i, j, k = 0;
    int alloc[10][10], max[10][10];
    int need[10][10], avail[10];
    int finish[10] = {0}, safe[10];

    printf("Enter processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter Allocation Matrix:\n");
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for(j=0; j<m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(finish[j] == 0)
            {
                for(k=0; k<m; k++)
                    if(need[j][k] > avail[k])
                        break;

                if(k == m)
                {
                    for(k=0; k<m; k++)
                        avail[k] += alloc[j][k];

                    safe[i] = j;
                    finish[j] = 1;
                    break;
                }
            }
        }
    }

    // Check Safe State
    for(i=0; i<n; i++)
        if(finish[i] == 0)
            break;

    if(i == n)
    {
        printf("\nSystem is in SAFE STATE\n");
        printf("Safe Sequence: ");

        for(i=0; i<n; i++)
            printf("P%d ", safe[i]);
    }
    else
        printf("\nSystem is in UNSAFE STATE");

    return 0;
}