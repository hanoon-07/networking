#include <stdio.h>
#include <limits.h>  // For INT_MAX

struct node {
    unsigned dist[20];
    unsigned from[20];
} rt[20];  // Increased size to 20

int main() {
    int costmat[20][20]; 
    int nodes, i, j, k, count = 0;

    printf("\nEnter the number of nodes: ");
    scanf("%d", &nodes);

    printf("\nEnter the cost matrix (use -1 for no connection):\n");
    for(i = 0; i < nodes; i++) {
        for(j = 0; j < nodes; j++) {
            printf("enter for %d%d:",i,j);
            scanf("%d", &costmat[i][j]);
            if(i == j) costmat[i][j] = 0;  // Distance to itself is always 0
            if(costmat[i][j] == -1) costmat[i][j] = 9999;  // No connection treated as infinity
            rt[i].dist[j] = costmat[i][j];  // Initialize distances
            rt[i].from[j] = j;  // Directly reachable
        }
    }

    do {
        count = 0;
        for(i = 0; i < nodes; i++) {
            for(j = 0; j < nodes; j++) {
                for(k = 0; k < nodes; k++) {
                    if(costmat[i][k] != 9999 && rt[i].dist[j] > costmat[i][k] + rt[k].dist[j]) {
                        rt[i].dist[j] = costmat[i][k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while(count != 0);

    for(i = 0; i < nodes; i++) {
        printf("\n\nFor router %d\n", i + 1);
        for(j = 0; j < nodes; j++) {
            printf("\nNode %d via %d Distance %d", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
        }
    }

    printf("\n\n");
    return 0;  
}
