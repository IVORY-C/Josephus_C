#include <stdio.h>
#include <string.h>

char *remove_spaces(char *input){
	int input_len = strlen(input);
	char *output = (char *)malloc(input_len*sizeof(char));
	char index;

	int count = 0;
	for(int i=0; i<input_len; i++){
		index = input[i];
		if(index != ' '){
			output[count] = index;
			count++;
		}
	}
	return output;
}

char *split(char *input, char *separator){
	int input_len = strlen(input);
	char *output = (char *)malloc(input_len*sizeof(char));

	char *index;
    index = strtok(input, ",");
    while(index){
        printf("%s\n", index);
        index = strtok(NULL, ",");
    }
	return output;
} 