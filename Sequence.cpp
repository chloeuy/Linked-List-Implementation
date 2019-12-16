//
//  Sequence.cpp
//  Project 2
//
//  Created by Chloe Uy on 4/21/19.
//  Copyright © 2019 Chloe Uy. All rights reserved.
//

//
#include "Sequence.h"
#include <string>
#include <iostream>
using namespace std;

Sequence::Sequence() //default constructor
{
    m_size = 0;
    head = new Node;
    head->next = head;
    head->prev = head;
}


Sequence::~Sequence()
{
    while(head->next != head)
    {
        Node * newNode = head->prev;
        newNode->prev->next = head;
        head->prev = newNode->prev;
        delete newNode;
    }
    delete head;//delete dummy node
}

Sequence& Sequence::operator = (const Sequence& other) //assignment operator
{
    if (this != &other)
    {
        Sequence temp(other);
        swap(temp);
    }
    return (*this);
}

Sequence::Sequence(const Sequence& other) //copy constructor
{
    m_size = 0;
    head = new Node;
    head-> next = head;
    head -> prev = head;
    for (int k = 0; k < other.size(); k++)
    {
        ItemType temp;
        other.get(k,temp);
        insert(k,temp);
    }
}


bool Sequence::empty() const
{
    if (m_size == 0)
        return true;
    else
        return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos <0 || m_size <0 || pos > size() )
    {
        return -1;
    }
    else
    {
        Node *p = head -> next;
        Node *latest = new Node; //make new node
        for (int i=0; i<pos; i++)
        {
            p = p -> next;
        }
        latest->m_value = value; //set the value of node to value
        latest->next = p; //set next to p
        latest->prev = p->prev; //set previous of latest to p's previous node
        (p->prev)-> next = latest; //link the node before our new node (aka p's previous node) to our new node
        p->prev = latest; //link previous node of p to new node
        m_size++; //increment size by one
    }
    return pos;
}


// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the  value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.


int Sequence::insert(const ItemType& value)
{
    int counter = 0;
    Node* temp = head -> next;
    if (m_size >= 0 )
    {
        for (int i=0; i<size();i++)
        {
            if ( value <= temp->m_value)
            {
                break;
            }
            counter++;
            temp = temp -> next;
        }
        insert(counter,value); //in case this doesnt work, try putting a break then insert line + return p line outside for loop
        return counter;
    }
    if (empty()==true) //if it is empty, execute this. Just in case it is empty
    {
        Node* Pp = new Node;
        Pp->m_value = value;
        Pp->next = head;
        Pp->prev = head;
        head -> next = Pp;
        head -> prev = Pp;
        m_size++;
        return counter;
    }
    return -1;
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).


bool Sequence::erase(int pos)
{
    if (pos >= 0 && pos < size())
    {
        Node* p;
        p = head -> next;
        for (int i=0; i< size(); i++)
        {
            if (i == pos)
            {
                Node* killMe = p; //create pointer kill me that stores the address of p
                (p -> prev) -> next = p -> next; //relink previous and next accordingly
                (p -> next) -> prev = p -> prev;
                p=p->next;
                delete killMe;
                m_size--;
                return true;
            }
            else
                p = p -> next;
        }
    }
    return false;
}


// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
//
int Sequence::remove(const ItemType& value)
{
    int count = 0;
    if (m_size > 0)
    {
        Node* p = head -> next;
        for (int i=0; i<size();i++)
        {
            if(value == p -> m_value)
            {
                Node* killMe = p;
                (p -> prev) -> next = p -> next; //we want to relink the previous and next accordingly
                (p -> next) -> prev = p -> prev;
                p=p->next;
                delete killMe; //delete the node at position
                m_size--; //decrement size
                count++;
                
            }
            else
                p=p->next;
        }
        return count;
    }
    return -1;
}




// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value) const
{
    Node* p = head -> next;

    if (pos >= 0 && pos < size())
    {
        for (int i=0; i < pos; i++)
        {
            p = p -> next;
        }
        value = p -> m_value;
        return true;
    }
    else
    {
        return false;
    }
}

// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value)
{
    Node* p = head -> next;
    int counter = 0;
    if (pos >= 0 && pos <size())
    {
        while (counter != pos)
        {
            p = p -> next;
            counter++;
        }
        p -> m_value = value;
        return true;
    }
    return false;
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value) const
{
    Node* tempP = head -> next;
    int p =0;
    if (head -> m_value == value )
    {
        return p;
    }
    if (size()>0)
    {
        while (tempP -> m_value != value )
        {
            tempP = tempP -> next;
            p++;
        }
        if (tempP -> m_value == value)
        {
            return p;
        }
    }
    return -1;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

void Sequence::swap(Sequence& other)
{
    Node* temp = other.head;
    other.head  = head;
    head = temp;
    // switch pointers but we have to first save the value of one pointer to be able to switch the other one
    // otherwise we'll literally be switching the same thing

    int switchsize = other.m_size;
    other.m_size = m_size;
    m_size= switchsize;
}


void Sequence::dump() const{
    Node * p = head->next;
    while(p != head){
        std::cerr << p->m_value << ", ";
        p = p->next;
    }
    std::cerr << std::endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq1.size()==0 || seq2.size()==0 || seq2.size()>seq1.size()){
        return -1;
    }
    ItemType v1; //item in position will be copied into this
    ItemType v2;//item in position will be copied into this
    for (int i=0; i<seq1.size();i++){ //find when item in sequence1 matches with first item in sequence2
        int store = 0;
        int x= 0;
        seq1.get(i, v1); //loops
        seq2.get(x, v2); //get first item in sequence 2 // does not loop //
        if (v1==v2){
            store = i;//gets position of i and stores it so we can return in in the very end
            while (v1==v2){
                i++;
                x++;
                seq1.get(i, v1);
                seq2.get(x,v2);
                if (v1 != v2)
                {
                    break;
                }
                if (x==seq2.size()-1)
                    return store;
            }
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    ItemType v1;
    ItemType v2;
    int k = 0;
    int x = 0;
    int t=0;
    if (result.empty() == false)
    {
        for (int i=0; i< result.size();i++)
            result.erase(i);
    }
    if (seq2.empty())
        result = seq1;
    if (seq1.empty())
        result = seq2;
    if (seq1.size()>seq2.size())
    {
        for (int i=0; i<seq1.size();i++)
        {
            seq1.get(x,v1);
            result.insert(k,v1);
            x++;
            k++;
            seq2.get(t,v2); // do not want to insert it at position ex: 0. want to insert it after position of item from seq1
            result.insert(k,v1);
            t++;
            k++;
            
        }
    }

    if (seq2.size()>seq1.size())
    {
        for (int i=0; i<seq2.size();i++)
        {
            seq1.get(x,v1);
            result.insert(k,v1);
            x++;
            k++;
            seq2.get(t,v2); // do not want to insert it at position ex: 0. want to insert it after position of item from seq1
            result.insert(k,v1);
            t++;
            k++;
        }
    }
}


// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.



