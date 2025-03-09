// Created by Ege Tan on 26.03.2024.
#ifndef HOMEWORK3_UNDOSTACK_H
#define HOMEWORK3_UNDOSTACK_H
#include <string>
#include <iostream>

using namespace std;

struct StackNode
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;

    //parametrized constructor for StackNode struct
    StackNode(const char & _operation ,const string & _employee_name ,const string & _project_name , const int & _project_priority , StackNode* _next)
    {
        operation = _operation;
        employee_name = _employee_name;
        project_name = _project_name;
        project_priority = _project_priority;
        next = _next;
    }
};
class UndoStack {
private:
    StackNode* top;
public:
    UndoStack();
    void push(char ,string,string,int);
    bool isEmpty();
    void pop(char &,string &,string &,int &);
    void clear();
};


#endif
