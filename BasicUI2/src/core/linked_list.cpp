//
//  linked_list.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/6/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "linked_list.hpp"

// ---------------------------------------
struct vsNode
    {
public:
vsNode(void* aData)
    : iData(aData)
    , iNext(0)
    {}
~vsNode()
    {
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
    {
    }
vsLinkedListBase::~vsLinkedListBase()
    {
    }
void vsLinkedListBase::add(void* aData)
    {
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
    {
    vsNode* tmp = iHead;
    while (tmp)
        {
        aCallback(tmp->iData);
        tmp = tmp->iNext;
        }
    }
// ---------------------------------------
