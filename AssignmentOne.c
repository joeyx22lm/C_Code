//
//  Assignment 1
//  COP3502
//
//  Created by Joseph Orlando on 1/26/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define booleans
typedef int bool;
#define true 1
#define false 0

struct node {
    char name[50];
    int id;
    struct node *next;
}*head;


// compare two chars
bool compare(char a[50], char b[50])
{
    if (strlen(a) != strlen(a))
        // strings are different
        return false;
    for (int i = 0; i < strlen(a); i++)
    {
        if (a[i] != b[i]){
            // strings are different
            return false;
        }
    }
    // strings are the same
    return true;
}

// drop console lines for asthetic purposes
void dropLines(){
    printf("\n\n\n\n");
}

// add node to linked list
int addNode(char name[50], int id){
    struct node *temp;
    temp =(struct node *)malloc(sizeof(struct node));
    strcpy(temp->name, name);
    temp->id = id;
    
    if (head == NULL){
        head = temp;
        head->next = NULL;
    }else{
        temp->next = head;
        head = temp;
    }
    return 1;
}

// display all nodes in linked list
int displayNode(){
    if(head->name == NULL){
        // no data
        printf("No data has been saved to the node(s).");
    }else{
        // data has been saved to the node(s)
        // output head info first
        printf("Student Name:%50s\n", head->name);
        printf("Student ID:%52d\n", head->id);
        struct node *temp = head->next;
        while(1){
            if(temp->name == NULL){
                // no more data
                break;
            }else{
                printf("Student Name:%50s\n", temp->name);
                printf("Student ID:%52d\n", temp->id);
                temp = temp->next;
            }
        }
    }
    return 1;
}

// delete node by student id
bool deleteByID(int ID){
    struct node *temp, *prev;
    temp = head;
    
    while(temp != NULL)
    {
        // temp is not empty
        if(temp->id == ID)
        {
            if(temp == head)
            {
                head = temp->next;
                free(temp); // free existing memory
                printf("Student has been deleted!");
                return true;
            }
            else
            {
                // push the list back one node
                prev->next = temp->next;
                free(temp);
                printf("Student has been deleted!");
                return true;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
    printf("Student ID was not found!");
    return true;
}

// delete node by student name, exact match
bool deleteByName(char name[50]){
    struct node *temp, *prev;
    temp = head;
    
    while(temp != NULL)
    {
        // temp is not empty
        if(compare(temp->name, name))
        {
            if(temp == head)
            {
                head = temp->next;
                free(temp); // free existing memory
                printf("Student has been deleted!");
                return true;
            }
            else
            {
                // push the list back one node
                prev->next = temp->next;
                free(temp);
                printf("Student has been deleted!");
                return true;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
    printf("Student Name was not found!");
    return true;
}

// populate nodes with pre-populated assignment data
int prepopulate(){
    char line[50];
    FILE datafile;
    datafile = *fopen ("AssignmentOneData.txt", "r");
    
    while(fgets(line, 50, &datafile) != NULL)
    {
        addNode(strtok(line, ","), atoi(strtok(NULL, ",")));
    }
    fclose(&datafile);
    return true;
}

int main(int argc, const char * argv[]) {
    head = NULL;
    prepopulate();
    while(1){
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Delete by ID\n");
        printf("4. Delete by Name\n");
        printf("5. Exit\n\n");
        printf("Select an option: ");
        int menu;
        scanf("%d", &menu);
        if(menu == 1){
            dropLines();
            char inputName[50];
            int inputID;
            printf("\nStudent Name: ");
            fseek(stdin,0,SEEK_END); // clear input buffer
            fgets(inputName, sizeof(inputName), stdin);
            printf("\nStudent ID: ");
            scanf("%d", &inputID);
            addNode(inputName, inputID);
            dropLines();
        }else if(menu == 2){
            dropLines();
            displayNode();
            dropLines();
        }else if(menu == 3){
            dropLines();
            int deleteID;
            printf("\nDelete ID: ");
            fseek(stdin,0,SEEK_END); // clear input buffer
            scanf("%d", &deleteID);
            deleteByID(deleteID);
            dropLines();
        }else if(menu == 4){
            dropLines();
            char delName[50];
            printf("\nDelete Name (EXACT): ");
            fseek(stdin,0,SEEK_END); // clear input buffer
            fgets(delName, sizeof(delName), stdin);
            deleteByName(delName);
            dropLines();
        }else if(menu == 5){
            printf("Have a great day!");
            return 1; // exit program
        }else{
            printf("%d is not a valid choice! Please try again\n\n", menu);
            menu = 0; // so while loop doesnt go out of control
        }
    }
    return 0;
}
