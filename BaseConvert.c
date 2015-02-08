//
//  BaseConvert.c
//  COP3502
//
//  Created by Joseph Orlando on 2/2/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// helper functions
char *strrev(char *str){
    char *p1, *p2;
    if (!str || !*str){
        return str;
    }
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}
void clearBuffer(){
    fseek(stdin,0,SEEK_END);
}


// from decimal to hex, octal, binary
void fromDecimal(int base, int value){
    // from decimal to alternate base
    char *HEX[] = {"A", "B", "C", "D", "E", "F", '\0'};
    char output[50] = "";
    int i = 0;
    while(value > 0){
        // add remainder to ouput string
        if((value % base) > 9){
            int z = ((value % base) - 10);
            strcat(&output[i], HEX[z]);
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
        if(output[i] != '\277'){
            printf("%c", output[i]);
        }
    }
}

// from hexidecimal to decimal
void fromHex(int base, char *a){
    // get char length
    long len = strlen(a);
    int i;
    // output value
    unsigned long val = 0;
    for(i=0;i<len;i++){
        if(a[i] <= 57){
            val += (a[i]-48)*(1<<(4*(len-1-i)));
        }else{
            val += (a[i]-55)*(1<<(4*(len-1-i)));
        }
    }
    if(base == 10){
        // to decimal
        printf("Converted Value: %lu", val);
    }else{
        // to octal / binary
        fromDecimal(base, val);
    }
}

// from octal to decimal
void fromOctal(int base, int n){
    int decimal=0, i=0, remainder;
    while (n!=0){
        remainder = n%10;
        n/=10;
        decimal += remainder*pow(8,i);
        ++i;
    }
    if(base == 10){
        // to decimal
        printf("Converted Value: %d", decimal);
    }else{
        // to octal / hexidecimal
        fromDecimal(base, decimal);
    }
}

// from binary to decimal
void fromBinary(int base, char value[50]){
    // reverse char array to start at the end of binary
    strrev(value);
    int decimal = 0;
    char currentval;
    double placevalue;
    for(int i=0;i<=strlen(value);i++){
        placevalue = 0;
        placevalue = pow(2, i);
        currentval = value[i];
        if(value[i] == '1' && value[i] != '\0' && value[i] != '0'){
            decimal = (decimal + placevalue);
        }
    }
    if(base == 10){
        // to decimal
        printf("Converted Value: %d", decimal);
    }else{
        // to octal / hexidecimal
        fromDecimal(base, decimal);
    }
}

int main(){
    char original[50] = "";
    int baseBefore;
    int baseAfter;
    printf("Original Number: ");
    scanf("%s", original);
    clearBuffer();
    printf("Original base: ");
    scanf("%d", &baseBefore);
    clearBuffer();
    printf("Converting to base: ");
    scanf("%d", &baseAfter);
    if(baseBefore == 16){
        // from hex
        fromHex(baseAfter, original);
    }else if(baseBefore == 10){
        // from decimal
        fromDecimal(baseAfter, atoi(original));
    }else if(baseBefore == 8){
        // from octal
        fromOctal(baseAfter, atoi(original));
    }else if(baseBefore == 2){
        // from binary
        fromBinary(baseAfter, original);
    }
    return 1;
}
