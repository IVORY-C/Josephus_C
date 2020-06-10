#include <stdio.h>
#include <stdlib.h>

int *output_josephus_order(int size, int start, int step){
    int index = start % size;
    int current = 1;
    int count = 0;

    int flag[100] = {0};
    int *outs = (int *)malloc(size*sizeof(int));

    while(count < size){
        if(current == step){
            outs[count] = index;
            count++;
            current = 0;
            flag[index] = 1;
        }

        index = (++index) % size;
        if(flag[index] == 0){
            current++;
        }
    }

    return outs;

}