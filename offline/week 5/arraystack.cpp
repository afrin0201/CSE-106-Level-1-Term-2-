#include "stack.h"
#include <iostream>

// Constructor implementation
ArrayStack::ArrayStack(int initial_capacity) {
    // TODO: Initialize data members (data, capacity, current_size)
    capacity=initial_capacity;
    current_size=0;
    // TODO: Allocate memory for the array with the specified initial capacity
    data=new int [capacity];
}

// Destructor implementation
ArrayStack::~ArrayStack() {
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Push implementation
void ArrayStack::push(int item) {
    // TODO: Check if the array is 50% full (current_size >= capacity/2)
    if (current_size>=capacity/2) 
     { capacity*=2;
      resize(capacity);}
    // TODO: If 50% full, resize the array to double its current capacity

    // TODO: Add the new element to the top of the stack and increment current_size
    data[current_size++]=item;

}

// Pop implementation
int ArrayStack::pop() {
    if (current_size==0) {
       // std::cout<<"STACK is empty"<<std::endl;
        return -1;
    }
    // TODO: Check if the stack is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the top of the stackint
    current_size--;
    int pop_elem=data[current_size];
    // TODO: If the array is less than 25% full, resize it to half its current capacity
    if ( current_size>0 &&current_size<capacity*.25) 
    {capacity=capacity/2;
    resize(capacity);}
    // TODO: Return the popped element
    return pop_elem;
}

// Clear implementation
void ArrayStack::clear() {
    // TODO: Reset the stack to be empty (set current_size to 0)
    current_size=0;
    // TODO: No need to free memory, just logically clear the stack
}

// Size implementation
int ArrayStack::size() const {
    // TODO: Return the number of elements currently in the stack (current_size)
    return current_size;
}

// Top implementation
int ArrayStack::top() const {
    // TODO: Check if the stack is empty, display error message if it is
    if (current_size==0) {
        //std::cout<<"STACK is empty"<<std::endl;
        return -1;
    }
    else{
    // TODO: Return the element at the top of the stack without removing it
    return data[current_size-1];
    }
}

// Empty implementation
bool ArrayStack::empty() const {
    // TODO: Return whether the stack is empty (current_size == 0)
    if (current_size==0) return true;
    return false;
}

// Print implementation
void ArrayStack::print() const {
 
    // TODO: Print stack elements from top to bottom in the format: |elem1, elem2, ..., elemN>
    for (int i=current_size-1;i>=0;i--){
         std::cout<<data[i]<<" ";
    }
}

// Resize implementation
void ArrayStack::resize(int new_capacity) {
    // TODO: Create a new array with the new capacity
     int* new_data=new int [new_capacity];
    // TODO: Copy elements from the old array to the new array
    for(int i=0;i<current_size;i++){
        new_data[i]=data[i];
    }
    // TODO: Delete the old array
    delete[] data;
    // TODO: Update the data pointer and capacity
    data=new_data;
    capacity=new_capacity;
}