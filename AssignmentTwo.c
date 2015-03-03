//
//  Assignment 2
//  COP3502
//
//  Created by Joseph Orlando on 1/26/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// define constant strings
const char MENU_STRING[] = "\nList Operations\n==================\n1. Stock Produce Department\n2. Display Produce Inventory\n3. Reverse Order of Produce Inventory\n4. Export Produce Inventory\n5. Export Produce Inventory (CSV)\n6. Exit Program\nEnter your choice: ";
const char inputFilename[] = "AssignmentTwoInput.txt";
const char outputFilename[] = "AssignmentTwoOutput.txt";

// define booleans
typedef enum { false, true } bool;

struct produceItem {
   char produce[20];
   char type[20];
   char soldBy[20];
   float price;
   int quantityInStock;
   struct produceItem *next;
};

// round up to two decimal places
float ceiling(float input){
   return ceilf(input * 100) / 100;
}

// reverse inventory
void PRODUCE_INVENTORY_REV(struct produceItem** head){
   struct produceItem* first;
   struct produceItem* past;
   if (*head == NULL){
      return;
   }
   first = *head;
   past  = first->next;
   if(past == NULL){
      return;
   }
   PRODUCE_INVENTORY_REV(&past);
   first->next->next  = first;
   first->next = NULL;
   *head = past;
}

// export inventory to csv
bool PRODUCE_INVENTORY_EXPORT_CSV(struct produceItem parent){
   FILE *outputFile;
   printf("\nTrying to create file %s\n", outputFilename);
   outputFile=fopen(outputFilename, "w");
   if(outputFile == NULL){
      return false;
   }
   while(true){
      if(parent.price != 0 || parent.quantityInStock != 0){
         fprintf(outputFile, "%s, %s, %s, %f, %d\n", parent.produce, parent.type, parent.soldBy, ceiling(parent.price), parent.quantityInStock);
      }
      if(parent.next == NULL){
         break;
      }else{
         parent = *parent.next;
      }
   }
   fclose(outputFile);
   return true;
}

// export inventory to formatted text
bool PRODUCE_INVENTORY_EXPORT_FORMATTED(struct produceItem parent){
   FILE *outputFile;
   printf("\nTrying to create file %s\n", outputFilename);
   outputFile=fopen(outputFilename, "w");
   if(outputFile == NULL){
      return false;
   }
   int count = 0;
   fprintf(outputFile, "\n#################################################################\n");
   fprintf(outputFile, " %-3s %-15s %-15s %-10s %-7s %-10s\n", "#", "Produce", "Type", "Sold By", "Price", "In Stock");
   fprintf(outputFile, "#################################################################\n");
   while(true){
      if(parent.price != 0 || parent.quantityInStock != 0){
         count++;
         fprintf(outputFile, " %-3d %-15s %-15s %-10s %-7.2f %-10d\n", count, parent.produce, parent.type, parent.soldBy, ceiling(parent.price), parent.quantityInStock);
      }
      if(parent.next == NULL){
         break;
      }else{
         parent = *parent.next;
      }
   }
   fclose(outputFile);
   return true;
}

// create inventory item
struct produceItem* PRODUCE_ITEM_CREATE(char produce[20], char type[20], char soldBy[20], float price, int quantityInStock) {
   struct produceItem* temp = malloc(sizeof(struct produceItem));
   strcpy(temp->produce, produce);
   strcpy(temp->type, type);
   strcpy(temp->soldBy, soldBy);
   temp->price = price;
   temp->quantityInStock = quantityInStock;
   temp->next = NULL;
   return temp;
}

// display inventory item
void PRODUCE_ITEM_DISPLAY(struct produceItem parent){
   int count = 0;
   printf("\n#################################################################\n");
   printf(" %-3s %-15s %-15s %-10s %-7s %-10s\n", "#", "Produce", "Type", "Sold By", "Price", "In Stock");
   printf("#################################################################\n");
   while(true){
      if(parent.price != 0 || parent.quantityInStock != 0){
         count++;
         printf(" %-3d %-15s %-15s %-10s %-7.2f %-10d\n", count, parent.produce, parent.type, parent.soldBy, ceiling(parent.price), parent.quantityInStock);
      }
      if(parent.next == NULL){
         break;
      }else{
         parent = *parent.next;
      }
   }
}

// start your engines
int main(){
   // build initial variables
   struct produceItem * Inventory = malloc(sizeof(struct produceItem));;
   int InventoryCount = 0, MENU_SELECTION = 0;
   bool switchx = false;
   while(true){
      printf("%s", MENU_STRING);
      scanf("%d", &MENU_SELECTION);
      if(MENU_SELECTION >= 6 || MENU_SELECTION < 1){
         // exit program
         return 1;
      }else if(MENU_SELECTION == 1){
         // Stock Produce Department
         char ImportFilename[100];
         strcpy(ImportFilename, inputFilename);
         char ImportFileLine[50];
         //printf("File to Import: ");
         //scanf("%s", ImportFilename);
         printf("Trying to open file %s\n", ImportFilename);
         FILE datafile = *fopen (ImportFilename, "r");
         while(fgets(ImportFileLine, 50, &datafile) != NULL){
            char TEMP_produce[20];
            char TEMP_type[20];
            char TEMP_soldBy[20];
            float TEMP_price;
            int TEMP_quantityInStock;
            strcpy(TEMP_produce, strtok(ImportFileLine, ","));
            strcpy(TEMP_type, strtok(NULL, ","));
            strcpy(TEMP_soldBy, strtok(NULL, ","));
            TEMP_price = atof(strtok(NULL, ","));
            TEMP_quantityInStock = atoi(strtok(NULL, ","));
            
            struct produceItem* temp = malloc(sizeof(struct produceItem));
            temp = PRODUCE_ITEM_CREATE(TEMP_produce, TEMP_type, TEMP_soldBy, TEMP_price, TEMP_quantityInStock);
            temp->next = Inventory;
            Inventory = temp;
            //Inventory = PRODUCE_ITEM_ADDR(TEMP_produce, TEMP_type, TEMP_soldBy, TEMP_price, TEMP_quantityInStock, *Inventory);
            InventoryCount++;
         }
         // updated Inventory with data import
         printf("Successfully opened file %s\n\n", ImportFilename);
         continue;
      }else if(MENU_SELECTION == 2){
         // Display Produce Inventory
         if(!switchx){
            switchx = true;
            PRODUCE_INVENTORY_REV(&Inventory);
         }
         PRODUCE_ITEM_DISPLAY(*Inventory);
      }else if(MENU_SELECTION == 3){
         // Reverse Order of Produce Inventory
         PRODUCE_INVENTORY_REV(&Inventory);
         printf("\nReversing Inventory datastore\n");
      }else if(MENU_SELECTION == 4){
         // Export produce inventory
         if(PRODUCE_INVENTORY_EXPORT_FORMATTED(*Inventory)){
            printf("\nSuccessfully wrote out file %s\n", outputFilename);
         }else{
            printf("\nFailed to write file %s\n", outputFilename);
         }
      }else if(MENU_SELECTION == 5){
         // Export produce inventory
         if(PRODUCE_INVENTORY_EXPORT_CSV(*Inventory)){
            printf("\nSuccessfully wrote out file %s\n", outputFilename);
         }else{
            printf("\nFailed to write file %s\n", outputFilename);
         }
      }
   }
   return 1;
}

