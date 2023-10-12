/*                                                                                                                                                                                                          
 * hash.c -- implements a generic hash table as an indexed set of queues.                                                                                                                                   
 *                                                                                                                                                                                                          
 */                                                                                                                                                                                                         
#include <stdint.h>                                                                                                                                                                                         
#include "queue.h"
#include "hash.h"

#include <inttypes.h>                                                                                                                                                                                       
#include <stddef.h>                                                                                                                                                                                         
#include <stdlib.h>                                                                                                                                                                                         
                                                                                                                                                                                                            
#include <stdio.h>                                                                                                                                                                                          
                                                                                                                                                                                                            
/*                                                                                                                                                                                                          
 * SuperFastHash() -- produces a number between 0 and the tablesize-1.                                                                                                                                      
 *                                                                                                                                                                                                          
 * The following (rather complicated) code, has been taken from Paul                                                                                                                                        
 * Hsieh's website under the terms of the BSD license. It's a hash                                                                                                                                          
 * function used all over the place nowadays, including Google Sparse                                                                                                                                       
 * Hash.                                                                                                                                                                                                    
 */                                                                                                                                                                                                         
#define get16bits(d) (*((const uint16_t *) (d)))                                                                                                                                                            
                                                                                                                                                                                                            
static uint32_t SuperFastHash (const char *data,int len,uint32_t tablesize) {                                                                                                                               
  uint32_t hash = len, tmp;                                                                                                                                                                                 
  int rem;                                                                                                                                                                                                  
                                                                                                                                                                                                            
  if (len <= 0 || data == NULL)                                                                                                                                                                             
    return 0;                                                                                                                                                                                               
  rem = len & 3;                                                                                                                                                                                            
  len >>= 2;                                                                                                                                                                                                
  /* Main loop */                                                                                                                                                                                           
  for (;len > 0; len--) {                                                                                                                                                                                   
    hash  += get16bits (data);                                                                                                                                                                              
    tmp    = (get16bits (data+2) << 11) ^ hash;                                                                                                                                                             
    hash   = (hash << 16) ^ tmp;                                                                                                                                                                            
    data  += 2*sizeof (uint16_t);                                                                                                                                                                           
    hash  += hash >> 11;                                                                                                                                                                                    
  }                                                                                                                                                                                                         
  /* Handle end cases */                                                                                                                                                                                    
  switch (rem) {                                                                                                                                                                                            
  case 3: hash += get16bits (data);                                                                                                                                                                         
    hash ^= hash << 16;                                                                                                                                                                                     
    hash ^= data[sizeof (uint16_t)] << 18;                                                                                                                                                                  
    hash += hash >> 11;                                                                                                                                                                                     
    break;                                                                                                                                                                                                  
  case 2: hash += get16bits (data);                                                                                                                                                                         
    hash ^= hash << 11;                                                                                                                                                                                     
    hash += hash >> 17;                                                                                                                                                                                     
    break;                                                                                                                                                                                                  
  case 1: hash += *data;                                                                                                                                                                                    
    hash ^= hash << 10;                                                                                                                                                                                     
    hash += hash >> 1;                                                                                                                                                                                      
 }                                                                                                                                                                                                          
  /* Force "avalanching" of final 127 bits */                                                                                                                                                               
  hash ^= hash << 3;                                                                                                                                                                                        
  hash += hash >> 5;                                                                                                                                                                                        
  hash ^= hash << 4;                                                                                                                                                                                        
  hash += hash >> 17;                                                                                                                                                                                       
  hash ^= hash << 25;                                                                                                                                                                                       
  hash += hash >> 6;                           
  return hash % tablesize;                                                                                                                                                                                  
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
                                                                                                                                                                                                            
typedef struct HashTableNode{                                                                                                                                                                               
  const char *key;                                                                                                                                                                                          
  queue_t *qp;                                                                                                                                                                                                                                                                                                                                                                                                        
}HashTableNode;   
                                                                                                                                                                                          

typedef struct ihashtable{                                                                                                                                                                                   
  uint32_t size;                                                                                                                                                                                                                                                                                                                             
  HashTableNode** table;                                                                                                                                                                                    
} ihashtable_t;                                                                                                                                                                                               
                                                                                                                                                                                                            
hashtable_t *hopen(uint32_t hsize) {                                                                                                                                                                    
  ihashtable_t* newHashTable = (ihashtable_t*)malloc(sizeof(ihashtable_t));                                                                                                                                    
  newHashTable -> size = hsize;                                                                                                                                                                             
  //should this be int?                                                                                                                                                                                     
  uint32_t spaceForAllNodes = sizeof(HashTableNode) * (hsize);                                                                                                                                                   
  newHashTable -> table = (HashTableNode**)malloc(spaceForAllNodes);                                                                                                                                        
                                                                                                                                                                                                            
  //loop through each node created and give it an empty queue                                                                                                                                               
  for(int i = 0; i < hsize; i++) {
    newHashTable->table[i] = (HashTableNode*)malloc(sizeof(HashTableNode));
    newHashTable->table[i]->key = NULL;
    newHashTable->table[i]->qp = qopen();
}                                                                                                                                                                                                   
                                                                                                                                                                                                            
  return (hashtable_t*) newHashTable;                                                                                                                                                                                      
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
void hclose(hashtable_t *htp) {
	ihashtable_t* ihtp = (ihashtable_t*) htp; 
	if (ihtp == NULL) {
        return; // Nothing to close
    }

   //Iterate through the table and free each entry
    for (int i = 0; i < ihtp->size; i++) {
        HashTableNode *node = ihtp->table[i];
        if (node != NULL) {
            qclose(node->qp); // Close the queue
            free(node); // Free the HashTableNode
        }
    }
    free(ihtp->table); // Free the table arrays
    free(ihtp); // Free the hashtable
}
                                                                                                                                                                                                                           
                                                                                                                                                                                                            
int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen) {
                                                                                                                                                                                                           
  //printf("Htp is: %p\n", (void*) htp);                                                                                                                                                                    
  //printf("Ep is: %p\n", ep);                                                                                                                                                                              
  //printf("Key is: %p\n", key);                                                                                                                                                                            
	ihashtable_t* ihtp = (ihashtable_t*) htp;                                                                                        
  //argument issue                                                                                                                                                                                          
  if (ihtp == NULL || key == NULL || ep == NULL) {                                                                                                                                                           
    return -1;                                                                                                                                                                                              
  }                                                                                                                                                                                                         
                                                                                                                                                                                                            
  printf("I'm here\n");                                                                                                                                                                                     
  HashTableNode* newNode = (HashTableNode*)malloc(sizeof(HashTableNode));                                                                                                                                   
                                                                                                                                                                                                            
  //memory allocation issue                                                                                                                                                                                 
  if (newNode == NULL) {                                                                                                                                                                                    
    return -1;                                                                                                                                                                                              
  }                                                                                                                                                                                                         
                                                                                                                                                                                                            
  newNode -> key = key;                                                                                                                                                                                     
  uint32_t hashCode = SuperFastHash(key, keylen, ihtp->size);                                                                                                                                                
  //printf("Hashcode is: %d\n", hashCode);                                                                                                                                                                  
  ihtp -> table[hashCode] = newNode;                                                                                                                                                                         
  queue_t* qpNode = qopen();                                                                                                                                                                                
  newNode -> qp = qpNode;                                                                                                                                                                                   
  qput(qpNode, ep);                                                                                                                                                                                         
                                                                                                                                                                                                            
  //still need return statement for when it's wrong                                                                                                                                                         
  return 0;                                                                                                                                                                                                 
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
void happly(hashtable_t *htp, void (*fn)(void* ep)) {

	ihashtable_t* ihtp = (ihashtable_t*) htp;
	
  uint32_t size = ihtp->size;                                                                                                                                                                                
  for (int i=0; i<size; i++) {                                                                                                                                                                              
    //not sure if i put in the functiion properly in the argument                                                                                                                                           
    qapply(ihtp->table[i]->qp,fn);                                                                                                                                                                           
  }                                                                                                                                                                                                         
}                                                                          

void* hsearch(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen) {                                                                                
	ihashtable_t* ihtp = (ihashtable_t*) htp; 
	uint32_t hashCode = SuperFastHash(key, keylen, ihtp -> size);                                                                                                                                              
  //not sure if im filliing in the qsearch properly                                                                                                                                                         
  void* found = qsearch(ihtp -> table[hashCode] -> qp, searchfn, key);                                                                                                                                       
  return found;                                                                                                                                                                                             
                                                                                                                                                                                                            
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
void *hremove(hashtable_t *htp, bool (*searchfn)(void* elementp, const void* searchkeyp), const char *key, int32_t keylen) {
	ihashtable_t* ihtp = (ihashtable_t*) htp;
	
	if (ihtp == NULL || ihtp->table == NULL || key == NULL) {
        return NULL; // Invalid input or empty hashtable
    }
	int32_t hashCode = SuperFastHash(key, keylen, ihtp->size);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	void* removed = qremove(ihtp-> table[hashCode] -> qp, searchfn,key);      
	return removed;                                                                                                                                                                                           
}      
  
