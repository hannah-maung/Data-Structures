#README for assignment 5



struct pq:
defined en element struct priority and num. One holds the priorities and one holds the actual number

pq_create:
allocated and initialized an empty priority queue which I used malloc for and made it the size of the pq.
created a dynamic array from priority and num by calling dynarray_create and returned p.

pq_free:
freed the memory to a priority and the priority queue using dynarray_free and free

pq_isempty:
I return one if the pq is empty. I called dynarray_length to check the length of one of the arrays, in this case priority, because num and priority are always going to be the same length. If that length was 0, then the function returned 1, else it returned false

pq_insert:
This function inserted an element into a pq with that specific priority value. I found the end priority number using dynarray_length and inserted that 

pq_max_priority:
uses dynarray get in the first index to find the priority value of the first item in a pq, returns that priority value of the first item in the pq 

pq_max_dequeue:
first using dynarray_get(), the function finds the number at the first index which is the item with the highest priority value, and uses dynarray_remove to remove from the queue. returns the value of the first item in the pq. calls swap numbers to swap the two enitries with a different index. if the length of the num array is greater than zero, it calls percolate_down to start at the top of the tree and move to the end index (0) where it sorts the priorities. 

swap_numbers:
This function takes the number along with its priority that was out of place and swaps it with the one it was compared to. all the dynarray set functino calls are the ones that are in charge of swaping the number along with its priority in the pq so that the number with the highest priority is on top, hence sorted with max priority. 

percolate_down:
This function starts from the top of the tree amd moves to the bottom, sorting the priorities in order from biggest to smallest. It calls the swap function if a priority comparision is found to be out of order, so whever there is a higher priority below a lower one, it swaps the number so that is it in order. This function is called from dequeue. 

percolate_up:
This function starts from the bottom of the tree and moves to the very top, sorting the priorities from highest to smallest. This function starts from the bottom because you call it when you insert a value at the end so it has to go all the way up, ponentially moving that value to the top. It calls the swap function as well if a priority comparision is found to be out of order. 
