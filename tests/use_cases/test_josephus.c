#include <stdio.h>
#include <stdlib.h>

#include "..\..\domain\use_cases\josephus.c"

int main() {
    
    int size, start, step;
    printf("Input the number of people,star,step:\n");
    scanf("%d,%d,%d", &size, &start, &step);

    int *outs = output_josephus_order(size, start, step);
    for(int i=0; i<size; i++)
        printf("%d ",outs[i]);
    
    free(outs);
}