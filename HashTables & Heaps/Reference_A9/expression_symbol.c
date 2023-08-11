/*
 ============================================================================
 Name        : expression_symbol.c
 Author      : Ryan Mood
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression_symbol.h"

int get_priority(char op) {

	if (op == '/' || op == '*' || op == '%') {
		return 1;
	}
	else if (op == '+' || op == '-') {
		return 0;
	}
	else {
		return -1;
	}
}

int type(char c) {
	if (c >= '0' && c <= '9') {
		return 0;
	}
	else if (c == '/' || c == '*' || c == '%' || c == '+' || c == '-') {
		return 1;
	}
	else if (c == '(') {
		return 2;
	}
	else if (c == ')') {
		return 3;
	}
	else if (c >= 'A' && c <= 'Z') {
		return 4;
	}
	else if (c >= 'a' && c <= 'z') {
		return 5;
	}
	else {
		return 6;
	}
}

QUEUE infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht) {

	QUEUE queue = { 0 };
	STACK stack = { 0 };

	char *p = infixstr;
	int sign = 1;
	int num = 0;
	char symbol[20] = { 0 };

	while (*p) {
		if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
			sign = -1;
		}
		else if (type(*p) == 0) {
			num = *p - '0';

			while (type(*(p + 1)) == 0) {
				num = (num * 10) + (*(p + 1) - '0');
				p++;
			}

			enqueue(&queue, new_node((sign * num), 0));
			sign = 1;

		}
		else if (type(*p) == 2) {
			push(&stack, new_node(*p, 2));

		}
		else if (type(*p) == 3) {

			while ((stack.top) && (stack.top->type != 2)) {
				enqueue(&queue, stack.top);
				pop(&stack);
			}

			pop(&stack);

		}
		else if (type(*p) == 1) {

			while (stack.top && get_priority(stack.top->data) > get_priority(*p)) {
				enqueue(&queue, stack.top);
				pop(&stack);
			}

			push(&stack, new_node(*p, 1));

		}
		else if (type(*p) == 4 || type(*p) == 5) {
			char *sp = symbol;
			*sp = *p;

			while (type(*(p + 1)) == 4 || type(*(p + 1)) == 5|| type(*(p + 1)) == 0) {
				p++;
				sp++;
				*sp = *p;
			}

			*(sp + 1) = '\0';
			HASHNODE *temp = search(ht, sp);

			if (temp != NULL) {
				enqueue(&queue, new_node(temp->value, 0));
			}

		}
		p++;
	}

	while (stack.top) {
		enqueue(&queue, stack.top);
		pop(&stack);
	}

	return queue;
}

int evaluate_infix_symbol(char *infixstr, HASHTABLE *ht) {

	QUEUE eval_queue = infix_to_postfix_symbol(infixstr, ht);

	return evaluate_postfix(eval_queue);
}

int evaluate_postfix(QUEUE queue) {

	NODE *nodeP = queue.front;
	STACK stk = { 0 };

	int type = 0;
	int o1, o2, val;

	while (nodeP) {
		type = nodeP->type;

		if (type == 0) {
			push(&stk, new_node(nodeP->data, 0));
		}
		else if (type == 1) {
			o1 = stk.top->data;
			pop(&stk);
			o2 = stk.top->data;
			pop(&stk);

			switch (nodeP->data) {
			case '+':
				val = o2 + o1;
				break;
			case '-':
				val = o2 - o1;
				break;
			case '/':
				val = o2 / o1;
				break;
			case '%':
				val = o2 % o1;
				break;
			case '*':
				val = o2 * o1;
				break;
			}
			push(&stk, new_node(val, 0));
		}
		nodeP = nodeP->next;
	}

	int result = stk.top->data;
	clean_stack(&stk);

	return result;

}
