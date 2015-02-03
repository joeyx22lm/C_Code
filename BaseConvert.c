//
//  BaseConvert.c
//  COP3502
//
//  Created by Joseph Orlando on 2/2/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//

#include <stdio.h>

// convert between alternate bases
int baseConvert(int base, int value){
    char HEX[] = {'A', 'B', 'C', 'D', 'E', 'F', '\0'};
    char output[50] = "";
    int i = 0;
    while(value > 0){
        // add remainder to ouput string
        if((value % base) > 9){
            // check for hexidecimal conversion
            strcat(&output[i], &HEX[((value % base) - 10)]);
        }else{
            sprintf(&output[i], "%d", (value % base));
        }
        i++;
        // decrement the testing value
        value = (value / base);
    }
    printf("Converted Value: ");
    for(i=sizeof(output);i>=0;i--){
        // print back output string one by one
        printf("%c", output[i]);
    }
    return 1;
}

int main(){
    int decimal,base=0;
    printf("Decimal number: ");
    scanf("%d",&decimal);
    fseek(stdin,0,SEEK_END);
    printf("Convert to base: ");
    scanf("%d",&base);
    baseConvert(base, decimal);
    return 1;
}
