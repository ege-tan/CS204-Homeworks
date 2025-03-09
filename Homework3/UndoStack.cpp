// Created by Ege Tan on 26.03.2024.
#include "UndoStack.h"

//constructor interms of creating an empty stack
UndoStack::UndoStack()
{
    top= nullptr;
}
//this function provides user to push an element inside the stack
void UndoStack::push(char operation, string name, string project, int priority)
{
    StackNode* new_node;
    //if the stack is empty
    if (isEmpty())
    {
        //assign top to a new node
        top = new StackNode(operation,name,project,priority, nullptr);
    }
    //if the stack is not empty
    else
    {
        //creates new node as next is previoıus head
        //this application provide user to apply lifo method
        new_node = new StackNode(operation,name,project,priority,top);
        top = new_node;
    }
}
//this function checks wheter stack is empty or not
bool UndoStack::isEmpty() {
    if (top == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//this function deletes the last entered node from the stack
//at the same time it returns the values of the node as reference parameters
void UndoStack::pop(char & operation, string & name, string & project, int & priority)
{
    StackNode* deleted;
    deleted = top;
    top = top->next;
    operation = deleted->operation;
    name = deleted->employee_name;
    project = deleted->project_name;
    priority = deleted->project_priority;
    delete deleted;
}
//this function clears all allocated dynamic memories.
void UndoStack::clear()
{
    StackNode* deleted;
    deleted = top;
    while (deleted != nullptr)
    {
        //move top to the next of top and delete previous top
        top=top->next;
        delete deleted;
        deleted = top;
    }
}
