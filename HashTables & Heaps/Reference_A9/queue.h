/*--------------------------------------------------
Project: cp264-a6q1
File:    queue.h
Description: header of queue ds
Author:  HBF  
Version: 2023-02-16
--------------------------------------------------
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

typedef struct queue {
  int length;
  NODE *front;
  NODE *rear;
} QUEUE;	

void enqueue(QUEUE *qp, NODE *np);
// return and remove the front node, don't free.
NODE *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

#endif
