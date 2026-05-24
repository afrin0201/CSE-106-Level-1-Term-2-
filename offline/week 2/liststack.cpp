#include "stack.h"
#include <iostream>

// Constructor implementation
ListStack::ListStack() {
    // TODO: Initialize head to nullptr
    head=nullptr;
    // TODO: Initialize current_size to 0
    current_size=0;
}

// Destructor implementation
ListStack::~ListStack() {
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear();
}

// Push implementation
void ListStack::push(int item) {
    // TODO: Create a new node with the given item
    Node * new_node=new Node(item);
    // TODO: Make the new node point to the current head
    new_node->next=head;
    // TODO: Update head to point to the new node
    head=new_node;
    // TODO: Increment current_size
    current_size++;
}

// Pop implementation
int ListStack::pop() {
    // TODO: Check if the stack is empty, display error message if it is
    if (current_size==0){
        //std::cout<<"STACK is empty"<<std::endl;
        return -1;
    }
    else{
    // TODO: Store the data from the head node
    int val=head->data;
    Node * temp=head;
    // TODO: Update head to point to the next node
    head=head->next;
    // TODO: Delete the old head node
    delete temp;
    // TODO: Decrement current_size
    current_size--;
    // TODO: Return the stored data
    return val;
    }
}

// Clear implementation
void ListStack::clear() {
    // TODO: Traverse the linked list, deleting each node
    while (head!=nullptr){
        Node* temp=head;
        head=head->next;
        delete temp;
    }
    // TODO: Reset head to nullptr
    head=nullptr;
    // TODO: Reset current_size to 0
    current_size=0;
}

// Size implementation
int ListStack::size() const {
    // TODO: Return the current size (current_size)
    return current_size;
}

// Top implementation
int ListStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    if (current_size==0) 
    {
        //std:: cout<<"STACK is empty"<<std::endl;
        return -1;
    }
    else{
    // TODO: Return the data from the heaheadd node without removing it
    return head->data;}
}

// Empty implementation
bool ListStack::empty() const {
    if (head==nullptr)
    {
        return true;
    }
    return false;
    // TODO: Return whether head is nullptr
}

// Print implementation
void ListStack::print() const {
    if (current_size==0){
        std::cout<<"STACK is empty"<<std::endl;
    }
    else{
        std::cout<<"| ";
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    Node* temp=head;
    while(temp!=nullptr){
        if (temp->next==nullptr)
            std::cout<<temp->data<<">"<<std::endl;
            else
            std::cout<<temp->data<<" , ";
            temp=temp->next;
    }
    // TODO: Traverse the linked list from head, printing each node's data
}
}