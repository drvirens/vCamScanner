//
//  linked_list.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/6/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "linked_list.hpp"
#include "trace.h"

static vsNode* SortedMerge(vsNode* a, vsNode* b, vsCallBackCompare compare);
static void FrontBackSplit(vsNode* source, vsNode** frontRef, vsNode** backRef);
static void MergeSort(vsNode** headRef, vsCallBackCompare compare);

// ---------------------------------------
struct vsNode
    {
public:
vsNode(void* aData)
    : iData(aData)
    , iNext(0)
    { TRACE }
~vsNode()
    { TRACE
    iData = 0;
    iNext = 0;
    }
public:
    void* iData;
    vsNode* iNext;
    };
// ---------------------------------------
vsLinkedListBase::vsLinkedListBase()
    : iHead(0)
    { TRACE
    }
vsLinkedListBase::~vsLinkedListBase()
    { TRACE
    }
void vsLinkedListBase::add(void* aData)
    { TRACE
    vsNode* node = new vsNode(aData);
    if (!iHead)
        {
        iHead = node;
        }
    else 
        {
        node->iNext = iHead;
        iHead = node;
        }
    }
void vsLinkedListBase::traverse(vsCallBack aCallback)
    { TRACE
    vsNode* tmp = iHead;
    while (tmp)
        {
        aCallback(tmp->iData);
        tmp = tmp->iNext;
        }
    }
    
void vsLinkedListBase::mergeSort(vsCallBackCompare compare)
    { TRACE
    MergeSort(&iHead, compare);
    }
    
// --------------------------------------- sort

/* sorts the linked list by changing next pointers (not data) */
static void MergeSort(vsNode** headRef, vsCallBackCompare compare)
{
  vsNode* head = *headRef;
  vsNode* a;
  vsNode* b;
 
  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->iNext == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b); 
 
  /* Recursively sort the sublists */
  MergeSort(&a, compare);
  MergeSort(&b, compare);
 
  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b, compare);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this 
   function */
static vsNode* SortedMerge(vsNode* a, vsNode* b, vsCallBackCompare compare)
{
  vsNode* result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  /* Pick either a or b, and recur */
//  if (a->data <= b->data)
  if ( compare(a->iData, b->iData) )
  {
     result = a;
     result->iNext = SortedMerge(a->iNext, b, compare);
  }
  else
  {
     result = b;
     result->iNext = SortedMerge(a, b->iNext, compare);
  }
  return(result);
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
static void FrontBackSplit(vsNode* source,
          vsNode** frontRef, vsNode** backRef)
{
  vsNode* fast;
  vsNode* slow;
  if (source==NULL || source->iNext==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->iNext;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->iNext;
      if (fast != NULL)
      {
        slow = slow->iNext;
        fast = fast->iNext;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->iNext;
    slow->iNext = NULL;
  }
}

