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

class vsLinkedListBase
    {
public:
    vsLinkedListBase();
    virtual ~vsLinkedListBase();
    void add(void* aData);
    void traverse(vsCallBack aCallback);
private:
    vsNode* iHead;
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
    void deleteAll( void(*cb)(void*) )
        {
        vsLinkedListBase::traverse(cb);
        }
    };

#endif /* linked_list_hpp */
