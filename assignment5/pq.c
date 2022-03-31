/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Hannah Maung
 * Email: maungh@oregonstate.edu
 */

#include <stdlib.h>
#include "dynarray.h"
#include "pq.h"
void percolate_up(struct pq* pq, int end);
void percolate_down(struct pq* pq, int end);
void swap_numbers(struct pq* pq, int n1,int n2);
/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * in addition, you want to define an element struct with both data and priority, 
 * corresponding to the elements of the priority queue. 
 */
struct pq {
	
	struct dynarray* priority;
	struct dynarray* num;

};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {

	struct pq* p = malloc(sizeof(struct pq));
	p->priority = dynarray_create();
	p->num = dynarray_create();

	return p;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {

	dynarray_free(pq->priority);
	dynarray_free(pq->num);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {

	if (dynarray_length(pq->priority) == 0) {
		return 1;

	} 	
	else{

		return 0;
	}

}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, higher priority
 * values are given precedent, and higher place in the queue.  In other words, the
 * element in the priority queue with the highest priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   data - the data value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, higher priority values
 *     should correspond to the first elements.  In other words,
 *     the element in the priority queue with the highest priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* data, int priority) {

	int end = dynarray_length(pq->priority);
	
	int* prior = malloc(sizeof(int));
	*prior = priority;
	
	dynarray_insert(pq->priority,end,prior);
	dynarray_insert(pq->num,end,data);
	
	percolate_up(pq,end);
}


/*
 * This function should return the data of the first element in a priority
 * queue, i.e. the data associated with the element with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the data of the first item in pq, i.e. the item with
 *   max priority value.
 */
void* pq_max(struct pq* pq) {
 
	return dynarray_get(pq->num,0);
	
	

}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with highest priority value.
 */
int pq_max_priority(struct pq* pq) {
  

	int n = *((int*)dynarray_get(pq->priority,0));


	return n;


}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with highest priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   highest priority value.
 */
void* pq_max_dequeue(struct pq* pq) {
 
	void* number;
	number = dynarray_get(pq->num, 0);
	
	int end;
	end = dynarray_length(pq->num) - 1;

	swap_numbers(pq,0,end);
	
	dynarray_remove(pq->num,end);
	dynarray_remove(pq->priority,end);
	
	if(dynarray_length(pq->num) > 0) {
		percolate_down(pq,0);
	}

	
 return number;
}

void swap_numbers(struct pq* pq, int n1,int n2) {

	void* temp1 = dynarray_get(pq->priority,n1);
	void* temp2 = dynarray_get(pq->num,n1);
	
	
	dynarray_set(pq->priority,n1,dynarray_get(pq->priority,n2));
	dynarray_set(pq->num,n1,dynarray_get(pq->num,n2));
	dynarray_set(pq->priority,n2,temp1);
	dynarray_set(pq->num,n2,temp2);
}



void percolate_down(struct pq* pq, int end) {

	int r;
	int l;
	r = 2 * end + 2;
	l = 2* end + 1;
	int highest;

	if(r >= dynarray_length(pq->num)) {
		if(l >= dynarray_length(pq->num)) {
			return;
	}
		else{ 

			highest = l;
		}
	}

	else{

		int r_priority = *((int*)dynarray_get(pq->priority, r));
		int l_priority = *((int*)dynarray_get(pq->priority,l));
		
		if(r_priority > l_priority){
			highest = r;
		}
		else{ 
			highest = l;

		}	

	}

	if((*((int*) dynarray_get(pq->priority,end))) < (*((int*) dynarray_get(pq->priority,highest)))) {

		swap_numbers(pq,end,highest);
		percolate_down(pq,highest);
	}

}



void percolate_up(struct pq* pq, int end) {

	if (end > 0) {
			
		int parent = (end-1) / 2;
		int priority_end = (*((int*)dynarray_get(pq->priority,end)));
		int priority_parent = (*((int*)dynarray_get(pq->priority,parent)));

	
		if(priority_end>priority_parent) {
			swap_numbers(pq,parent,end);
			percolate_up(pq,parent);

		}


	}
}





