//
//  linked_list.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/6/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

struct vsNode;

typedef void(*vsCallBack)(void*);
typedef bool(*vsCallBackCompare)(void*, void*); //returns a->data <= b->dat

class vsLinkedListBase
    {
public:
    vsLinkedListBase();
    virtual ~vsLinkedListBase();
    void add(void* aData);
    void traverse(vsCallBack aCallback);
    void reverseTraverse(vsCallBack aCallback);
    void mergeSort(vsCallBackCompare compare);
    void deleteAll( void(*cb)(void*) );
private:
    vsNode* iHead;
    vsNode* iTail;
    };
    
template <typename T>
class vsLinkedList : private vsLinkedListBase
    {
public:
    vsLinkedList() : vsLinkedListBase() {}
    ~vsLinkedList() {}
    void add(T* aData)
        {
        vsLinkedListBase::add( (void*)aData );
        }
    void traverse(vsCallBack aCallback)
        {
        vsLinkedListBase::traverse(aCallback);
        }
    void reverseTraverse(vsCallBack aCallback)
        {
        vsLinkedListBase::reverseTraverse(aCallback);
        }
    void deleteAll( void(*cb)(void*) )
        {
        vsLinkedListBase::deleteAll(cb);
        }
    void mergeSort(vsCallBackCompare compare)
        {
        vsLinkedListBase::mergeSort(compare);
        }
    };

#endif /* linked_list_hpp */
