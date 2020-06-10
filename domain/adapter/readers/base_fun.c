#include <stdio.h>

void remove_spaces(char *ch){
	char *c;
	while (*ch != ' '){
		if (*ch == '\0')
			return;
		ch++;
	}
	c = ch + 1;
	while (c == " ")
		c++;

	while (*c != '\0'){
		if (*c != ' '){
			*ch = *c;
			*c = ' ';
			ch++;
		}
		c++;
	}
	*ch = '\0';
	return;
}

void split(char *src,const char *separator,char **dest) {
	/*
		src 源字符串的首地址(buf的地址) 
		separator 指定的分割字符
		dest 接收子字符串的数组
	*/
    char *pNext;
    int count = 0;
    if (src == NULL || strlen(src) == 0) 
        return;
    if (separator == NULL || strlen(separator) == 0)  
        return;
    pNext = (char *)strtok(src,separator); 
    while(pNext != NULL) {
        *dest++ = pNext;
        ++count;
        pNext = (char *)strtok(NULL,separator);  
    }  
} 