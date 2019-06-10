#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void MyPrint(char* array); 

char * Multiply(char *num_str1, char *num_str2){
    int len1 = strlen(num_str1);
    int len2 = strlen(num_str2);
    char* res = (char*)malloc(sizeof(char) * (len1+len2+1));
    if(res == NULL) 
    	return NULL;

    for(int i = 0; i < len1 + len2; i++)
        res[i] = '0';
    res[len1+len2] = '\0';

    if(len1 > 0 && len2 > 0){
        int* tmp = (int*) malloc(sizeof(int)*(len1+len2));
        if(tmp == NULL)
        	return NULL;
        for(int i = 0; i < len1 + len2; i++)
            tmp[i] = 0;

        for(int idx1 = 0; idx1 < len1; idx1++){
            for(int idx2 = 0; idx2 < len2; idx2++){
                tmp[idx1+idx2+1] += (num_str1[idx1]-'0')*(num_str2[idx2]-'0');
            }
        }

        int carry = 0;
        int i = len1 + len2 - 1;
        for(; i > 0; i--){
            int sum = tmp[i] + carry;
            carry = sum/10;
            tmp[i] = sum%10;
            res[i] = '0' + tmp[i];
        }
        if(carry > 0){
            tmp[i] = carry;
            res[i] = '0' + carry;
        }

        MyPrint(res);

        free(tmp);
        tmp = NULL;
    }
    return res;
}

void MyPrint(char* res)
{
    bool is_zero = true;
    int i = 0, j = 0;
    while(res[i] != '\0'){
        if(is_zero && res[i] != '0')
            is_zero = false;

        if(!is_zero){
            if(i == j)
                break;
            res[j++] = res[i];
        }

        i++;
    }
    if(res[i] == '\0')
        res[j] = '\0';	
}

void TestCase(char* num1, char* num2)
{
    char* res = Multiply(num1, num2);
    printf("%s\n", res);
    if(res != NULL)
    	free(res);
    res = NULL;	
}

int main()
{
	TestCase("12","3456");
	TestCase("11123456666666666666666666","456");
    return 0;
}
