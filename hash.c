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

typedef struct HashTableNode {
    const char *key;
    queue_t *qp;
} HashTableNode;

typedef struct ihashtable {
    uint32_t size;
    HashTableNode **table;
} ihashtable_t;

hashtable_t *hopen(uint32_t hsize) {
    ihashtable_t *newHashTable = (ihashtable_t *)malloc(sizeof(ihashtable_t));
    newHashTable->size = hsize;
    newHashTable->table = (HashTableNode **)malloc(sizeof(HashTableNode *) * hsize);

    for (int i = 0; i < hsize; i++) {
        newHashTable->table[i] = NULL; // Initialize each slot to NULL
    }

    return (hashtable_t *)newHashTable;
}

void hclose(hashtable_t *htp) {
    ihashtable_t *ihtp = (ihashtable_t *)htp;
    if (ihtp == NULL) {
        return;
    }

    for (int i = 0; i < ihtp->size; i++) {
        if (ihtp->table[i] != NULL) {
            qclose(ihtp->table[i]->qp);
            free(ihtp->table[i]);
        }
    }

    free(ihtp->table);
    free(ihtp);
}

int32_t hput(hashtable_t *htp, void *ep, const char *key, int keylen) {
    ihashtable_t *ihtp = (ihashtable_t *)htp;
    if (ihtp == NULL || key == NULL || ep == NULL) {
        return -1;
    }

    uint32_t hashCode = SuperFastHash(key, keylen, ihtp->size);

    HashTableNode *newNode = (HashTableNode *)malloc(sizeof(HashTableNode));
    if (newNode == NULL) {
        return -1;
    }

    newNode->key = key;
    newNode->qp = qopen();
    qput(newNode->qp, ep);

    if (ihtp->table[hashCode] != NULL) {
        // If it's already using that key
        qconcat(ihtp->table[hashCode]->qp, newNode->qp);
        free(newNode); // Free the unused node
    } else {
        ihtp->table[hashCode] = newNode;
   }

    return 0;
}

void happly(hashtable_t *htp, void (*fn)(void *ep)) {
    ihashtable_t *ihtp = (ihashtable_t *)htp;
    for (int i = 0; i < ihtp->size; i++) {
        if (ihtp->table[i] != NULL) {
            qapply(ihtp->table[i]->qp, fn);
        }
    }
}

void *hsearch(hashtable_t *htp, bool (*searchfn)(void *elementp, const void *searchkeyp), const char *key, int32_t keylen) {
    ihashtable_t *ihtp = (ihashtable_t *)htp;
    uint32_t hashCode = SuperFastHash(key, keylen, ihtp->size);
    if (ihtp->table[hashCode] == NULL) {
        return NULL;
    }
    return qsearch(ihtp->table[hashCode]->qp, searchfn, key);
}

void *hremove(hashtable_t *htp, bool (*searchfn)(void *elementp, const void *searchkeyp), const char *key, int32_t keylen) {
    ihashtable_t *ihtp = (ihashtable_t *)htp;
    uint32_t hashCode = SuperFastHash(key, keylen, ihtp->size);
    if (ihtp->table[hashCode] == NULL) {
        return NULL;
    }
    return qremove(ihtp->table[hashCode]->qp, searchfn, key);
}
                                                                                                                                                                                                              
  
