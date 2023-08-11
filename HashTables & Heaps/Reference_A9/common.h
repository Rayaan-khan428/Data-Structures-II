/*--------------------------------------------------
Project: cp264-a6
File:    common.h
Description: node structure and common functions
Author:  HBF  
Version: 2023-02-16
--------------------------------------------------
*/
#ifndef COMMON_H
#define COMMON_H

/** NODE  -  a structure represents the element of an arithmetic expression
 *  data  -  represents operand, operator ASCII code, or parenthesis ASCII code 
 *  type  -  0 for operand; 1 for operator; 2 for left parenthesis 3 for right parenthesis 
*/ 
typedef struct node {
	int data;  
	int type;  
	struct node *next;
} NODE;

NODE *new_node(int data, int type);
void clean(NODE **startp);
void display(NODE *start);

#endif
