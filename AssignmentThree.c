//
//  Assignment 3
//  COP3502
//
//  Created by Joseph Orlando on 3/25/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//

// include all libraries
#include <stdio.h>
#include <string.h>

// declare some basic definitions
typedef enum { false, true } bool;
// global counter
int CurrentCount = 0;

// function to swap two chars, required by @findPermutations
void swapChars(char* x, char* y) {
   char tmp = *x;
   *x = *y;
   *y = tmp;
   
}

// function to find all permutations of given string
void findPermutations(char* String, int pos, FILE * OutputFile) {
   if (pos >= (strlen(String)-1)) {
      // increase current count
      CurrentCount++;
      // output current permutation to file <3
      fprintf(OutputFile,"%s\n",String);
   } else {
      for (int i = pos; i < strlen(String); i++) {
         // swap chars and find permutations
         swapChars(&String[pos], &String[i]);
         findPermutations(String, pos+1, OutputFile);
         // reverse swap, back to original
         swapChars(&String[pos], &String[i]);
      }
   }
}

// start your engines
int main(){
   // declare ImportBuffer w/ BUFSIZE (GNU)
   char ImportBuffer[BUFSIZ];
   // output program header
   printf("COP3502 - Assignment III\n@Author: Joseph Orlando\n\n");
   // open output file for writing
   FILE *OutputFile=fopen("AssignmentThreeOutput.txt","w");
   if(OutputFile==NULL){
      printf("File Error :(");
   }
   // begin reading input file to char array
   FILE *InputFile=fopen("AssignmentThreeInput.txt", "r");
   if(InputFile==NULL){
      printf("File Error :(");
   }
   while (fgets(ImportBuffer, sizeof(ImportBuffer), InputFile)) {
      // reset permutations found
      CurrentCount = 0;
      // remove newline from each word, if any
      if(ImportBuffer[strlen(ImportBuffer)-1] == '\n'){
         ImportBuffer[strlen(ImportBuffer)-1] = 0;
      }
      // print input text
      printf("Currently Permuting: %s\n", ImportBuffer);
      // find permutations
      findPermutations(ImportBuffer, 0, OutputFile);
      // and print tha count <3
      printf("Found %d Total!\n\n", CurrentCount);
   }
   fclose(OutputFile);
   return 1;
}
