//
//  AssignmentFour.c
//  COP3502
//
//  Created by Joseph Orlando on 4/17/15.
//  Copyright (c) 2015 Joseph Orlando. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

// define constants
const char APP_HEADER[] = "COP3502 - Assignment IV\n@Author: Joseph Orlando\n\n";
const char MENU_STRING[] = "1) Generate BST\n2) Print BST Preorder\n3) Print BST Inorder\n4) Print BST Postorder\n5) Print BST Breadth-first\n6) Find Value in BST\n7) Find Minimum Value\n8) Find Maxmimum Value\n9) Calculate Average of BST\n10) Find Median Value\n11) Sum of BST\n12) Count Number of Nodes\n13) Delete a Value\n14) Exit Program";

// define global vars
int medianT[100];
int medianTa = -1;

// define required data types
typedef enum { false, true } bool;
struct binaryNode {
   int data;
   int level;
   struct binaryNode *left;
   struct binaryNode *right;
};

// function prototypes
float safeDivide(int a, int b); // divide, safely :)
bool findInTree(struct binaryNode *root, int value); // find int value in tree
struct binaryNode* insert(struct binaryNode *root, int value, int level); // insert int into tree, append current level data (for breadth-first)
struct binaryNode* levelChange(struct binaryNode *root, bool levelUp); // change tree's levels, !levelUp == decrement
void printTree(struct binaryNode *root, int order);
struct binaryNode* updateLevels(struct binaryNode *input, int level); // update all node's current level (for breadth-first)
int numberOfNodes(struct binaryNode *root); // count nodes in tree
int sumOfNodes(struct binaryNode *root); // calculate sum of nodes in tree
struct binaryNode* minOfNode(struct binaryNode *input); // minimum value of nodes in tree
int cfOfNodes(struct binaryNode *root, bool ceiling); // floor / ceiling of nodes in tree
int greator(int a, int b); // are you greator than?
int bsort(const void *xx, const void *yy); // compare funkay <3
int treeHeight(struct binaryNode *root); // height of a tree
struct binaryNode* deleteValue(struct binaryNode *root, int value); // omg so many comments, delete a val from a tree, duhhh
void rowTraverse(struct binaryNode *root, int level); // row traverse, help print bfs
void globTraverse(struct binaryNode *root); // glob traverse, for calculating + sorting for median

// define global functions
float safeDivide(int a, int b){
   if(b == 0){
      return b;
   }else{
      return (a/b);
   }
}

bool findInTree(struct binaryNode *root, int value){
   if(root == NULL){
      return false;
   }else if(root->data == value){
      return true;
   }
   return (findInTree(root->left, value) || findInTree(root->right, value));
}

struct binaryNode* insert(struct binaryNode *root, int value, int level){
   if(root == NULL){
      struct binaryNode *temp = (struct binaryNode*)malloc(sizeof(struct binaryNode));
      temp->data = value;
      temp->level = level;
      temp->left = NULL;
      temp->right = NULL;
      root = temp;
   }else if(root->data < value){
      root->right = insert(root->right, value, (level+1));
   }else{
      root->left = insert(root->left, value, (level+1));
   }
   return root;
}

struct binaryNode* levelChange(struct binaryNode *root, bool levelUp){
   if(root != NULL){
      if(levelUp){
         root->level = (root->level + 1);
      }else{
         root->level = (root->level - 1);
      }
      levelChange(root->left, levelUp);
      levelChange(root->right, levelUp);
   }
   return root;
}

void printTree(struct binaryNode *root, int order){
   if(root != NULL){
      if(order == 1){
         // inorder
         printTree(root->left, order);
         printf("%d ", root->data, root->level);
         printTree(root->right, order);
      }else if(order == 2){
         // postorder
         printTree(root->left, order);
         printTree(root->right, order);
         printf("%d ", root->data, root->level);
      }else{
         // preorder
         printf("%d ", root->data, root->level);
         printTree(root->left, order);
         printTree(root->right, order);
      }
   }
}

struct binaryNode* updateLevels(struct binaryNode *input, int level){
   if(input == NULL){
      return input;
   }
   input->level = level;
   input->left = updateLevels(input->left, (level+1));
   input->right = updateLevels(input->right, (level+1));
   return input;
}

int numberOfNodes(struct binaryNode *root){
   if(root == NULL){
      return 0;
   }else if(root->right == NULL && root->left == NULL){
      return 1;
   }else if(root->left == NULL){
      return (1+numberOfNodes(root->right));
   }else if(root->right == NULL){
      return (1+numberOfNodes(root->left));
   }
   return (1+numberOfNodes(root->left)+numberOfNodes(root->right));
}

int sumOfNodes(struct binaryNode *root){
   if(root == NULL){
      return 0;
   }else if(root->right == NULL && root->left == NULL){
      return root->data;
   }else if(root->left == NULL){
      return (root->data+sumOfNodes(root->right));
   }else if(root->right == NULL){
      return (root->data+sumOfNodes(root->left));
   }
   return (root->data+sumOfNodes(root->left)+sumOfNodes(root->right));
}

struct binaryNode* minOfNode(struct binaryNode *input){
   while(input->left != NULL){
      input = input->left;
   }
   return input;
}

int cfOfNodes(struct binaryNode *root, bool ceiling){
   if(root == NULL){
      return 0;
   }
   int current = root->data;
   int tmp = current;
   if(ceiling){
      if(root->left == NULL && root->right == NULL){
         return current;
      }else if(root->left == NULL){
         tmp = cfOfNodes(root->right, true);
         if(current > tmp){
            return current;
         }else{
            return tmp;
         }
      }else if(root->right == NULL){
         tmp = cfOfNodes(root->left, true);
         if(current > tmp){
            return current;
         }else{
            return tmp;
         }
      }
      tmp = cfOfNodes(root->left, true);
      if(tmp > current){
         current = tmp;
      }
      tmp = cfOfNodes(root->right, true);
      if(tmp > current){
         current = tmp;
      }
   }else{
      if(root->left == NULL && root->right == NULL){
         return current;
      }else if(root->left == NULL){
         tmp = cfOfNodes(root->right, false);
         if(current < tmp){
            return current;
         }else{
            return tmp;
         }
      }else if(root->right == NULL){
         tmp = cfOfNodes(root->left, false);
         if(current < tmp){
            return current;
         }else{
            return tmp;
         }
      }
      tmp = cfOfNodes(root->left, false);
      if(tmp < current){
         current = tmp;
      }
      tmp = cfOfNodes(root->right, false);
      if(tmp < current){
         current = tmp;
      }
   }
   return current;
}

int greator(int a, int b){
   if(a > b){
      return a;
   }
   return b;
}

int bsort(const void *xx, const void *yy){
   const int *x = xx, *y = yy;
   if(*x < *y){
      return -1;
   }else if(*x > *y){
      return 1;
   }
   return 0;
}

int treeHeight(struct binaryNode *root){
   int height = 0;
   if(root == NULL){
      return height;
   }else if(root->left == NULL && root->right == NULL){
      return ++height;
   }else if(root->left == NULL){
      return (++height + treeHeight(root->right));
   }else if(root->right == NULL){
      return (++height + treeHeight(root->left));
   }
   return (++height + greator(treeHeight(root->left), treeHeight(root->right)));
}

struct binaryNode* deleteValue(struct binaryNode *root, int value){
   if(root == NULL){
      return root;
   }else if(value < root->data){
      root->left = deleteValue(root->left, value);
   }else if(value > root->data){
      root->right = deleteValue(root->right, value);
   }else if(root->left == NULL && root->right == NULL){
      root = NULL;
   }else if(root->left == NULL){
      // decrement all level values in right
      root = levelChange(root->right, false);
   }else if(root->right == NULL){
      // decrement all level values in left
      root = levelChange(root->left, false);
   }else{
      struct binaryNode *temp = minOfNode(root->right);
      root->data = temp->data;
      root->right = deleteValue(root->right, temp->data);
   }
   return root;
}

void rowTraverse(struct binaryNode *root, int level){
   if(root == NULL || root->level > level){
      return;
   }
   if(root->level == level){
      printf("%d ", root->data);
   }else if(root->level < level){
      rowTraverse(root->left, level);
      rowTraverse(root->right, level);
   }
}

void globTraverse(struct binaryNode *root){
   if(root == NULL){
      return;
   }else if(root->right == NULL && root->left == NULL){
      medianT[++medianTa] = root->data;
      return;
   }else if(root->left == NULL){
      medianT[++medianTa] = root->data;
      return globTraverse(root->right);
   }else if(root->right == NULL){
      medianT[++medianTa] = root->data;
      return globTraverse(root->left);
   }
   medianT[++medianTa] = root->data;
   globTraverse(root->left);
   return globTraverse(root->right);
}

// start your engines <3
int main(){
   struct binaryNode *binaryTree = NULL;
   // print menu
   printf("%s%s", APP_HEADER, MENU_STRING);
   while(true){
      printf("\n\nMENU SELECTION: ");
      // reset menu selection
      int MENU_SELECTION = 0;
      // accept menu selection input + parse
      scanf("%d", &MENU_SELECTION);
      if(MENU_SELECTION == 14){
         // exit program
         printf("Jeez... Goodbye :/");
         return 1;
      }else if(MENU_SELECTION == 1){
         // generate BST
         FILE *InputFile=fopen("AssignmentFourInput.txt", "r");
         if(InputFile==NULL){
            printf("An unexpected exception occurred while loading input file! :(");
            return 1;
         }
         char ImportBuffer[100];
         while (fgets(ImportBuffer, 100, InputFile)) {
            char *Delimeter = strtok(ImportBuffer, " ");
            while (Delimeter != NULL) {
               binaryTree = insert(binaryTree, atoi(Delimeter), 0);
               Delimeter = strtok(NULL, " ");
            }
         }
         printf("Input data has been imported successfully!");
      }else if(MENU_SELECTION == 2){
         printf("Preorder: ");
         printTree(binaryTree, 0);
      }else if(MENU_SELECTION == 3){
         printf("Inorder: ");
         printTree(binaryTree, 1);
      }else if(MENU_SELECTION == 4){
         printf("Postorder: ");
         printTree(binaryTree, 2);
      }else if(MENU_SELECTION == 5){
         printf("Breadth-First: ");
         for(int i =0; i<treeHeight(binaryTree);i++){
            printf("%d ", (i+1));
            rowTraverse(binaryTree, i);
         }
         printf("\n");
      }else if(MENU_SELECTION == 6){
         printf("Find value in tree: ");
         int findVal = 0;
         scanf("%d", &findVal);
         if(findInTree(binaryTree, findVal)){
            printf("Value `%d` was found in the tree!", findVal);
         }else{
            printf("Value `%d` was not found in the tree!", findVal);
         }
      }else if(MENU_SELECTION == 7){
         printf("Minimum Value: %d",cfOfNodes(binaryTree, false));
      }else if(MENU_SELECTION == 8){
         printf("Maximum Value: %d",cfOfNodes(binaryTree, true));
      }else if(MENU_SELECTION == 9){
         printf("Average of Nodes: %f", safeDivide(sumOfNodes(binaryTree), numberOfNodes(binaryTree)));
      }else if(MENU_SELECTION == 10){
         memset(medianT, 0, sizeof(medianT));
         medianTa = -1;
         globTraverse(binaryTree);
         qsort(medianT, medianTa, sizeof(int),bsort);
         if((medianTa % 2) == 0){
            printf("Median: %d", medianT[(medianTa/2)]);
         }else{
            printf("Median: %d", ((medianT[medianTa/2] + medianT[(medianTa/2)+1])/2));
         }
      }else if(MENU_SELECTION == 11){
         printf("Sum of Nodes: %d", sumOfNodes(binaryTree));
      }else if(MENU_SELECTION == 12){
         printf("Node Count: %d", numberOfNodes(binaryTree));
      }else if(MENU_SELECTION == 13){
         printf("Delete value from tree: ");
         int deleteVal = 0;
         scanf("%d", &deleteVal);
         int sum = numberOfNodes(binaryTree);
         binaryTree = deleteValue(binaryTree, deleteVal);
         if(numberOfNodes(binaryTree) == sum){
            printf("Value `%d` was not found in the tree!", deleteVal);
         }else{
            printf("Value `%d` was deleted from the tree!", deleteVal);
         }
         binaryTree = updateLevels(binaryTree, 0);
      }
   }
   return 1;
}
