#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 10

struct Node{
    int dist[MAX_NODES];
    int from[MAX_NODES];
} rt[MAX_NODES];

int main() {
    int nodes, i, j, k, updated, cost[MAX_NODES][MAX_NODES];

    printf("Enter the number of nodes in a network: ");
    scanf("%d", &nodes);
    
    printf("Enter the cost Matrix use 999 for no connection: \n");
    for ( i = 0; i < nodes; i++) {
        for ( j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);
            cost[i][i] = 0;
            rt[i].dist[j] = cost[i][j];
            rt[i].from[j] = j;
        }
    }

    do {
        updated = 0;

        for ( i = 0; i < nodes; i++) {
            for ( j = 0; j < nodes; j++) {
                for (k = 0; k < nodes; k++) {
                    if (rt[i].dist[j] > cost[i][k] + rt[k].dist[j]) {
                        rt[i].dist[j] = cost[i][k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        updated = 1;
                    }
                }
            }
        }

    } while (updated) ; 

    for (i = 0; i < nodes; i++) {
        printf("\nRouting table for Node `N`: %d\n", i);
        printf("Destination \tNext Hop\tDistance\n");

        for (j = 0; j < nodes; j++) {
            printf("%d\t\t%d\t\t%d\n", j, rt[i].from[j], rt[i].dist[j]);

        }
    }

    return 0;
}
