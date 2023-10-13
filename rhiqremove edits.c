void* qremove(queue_t *qp, bool (*searchfn)(void* elementp, const void* keyp), const void* skeyp) {
  iqueue_t *iqp = (iqueue_t*) qp;  
  
if (iqp == NULL || searchfn == NULL || skeyp == NULL) {
        return NULL; // Invalid input
    }

    node_t *current = iqp->front;
    node_t* prev = NULL; 

    while (current != NULL) {
        
        if (searchfn(current->elementp, skeyp)) {

          if (prev !=NULL) {
            prev -> next = current -> next;
          }
          if (iqp->front == current) {
            iqp->front = current -> next; 
          }
          if (iqp->back == current) {
            iqp->back = prev;
          }
          void* removedElement = current->elementp;
          free(current);
          return removedElement; // Found a matching element
        }
        prev = current;
        current = current->next;
    }

    return NULL; // Element not found
}
