#include <stdio.h>
#include <stdlib.h>

#include "..\..\domain\use_cases\josephus.c"

int main() {
    
    int size, start, step;
    printf("Input the number of people,star,step:\n");
    scanf("%d,%d,%d", &size, &start, &step);

    output_josephus_order(size, start, step);

}