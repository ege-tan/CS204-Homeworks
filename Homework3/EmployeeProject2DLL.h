// Created by Ege Tan on 26.03.2024.
#ifndef HOMEWORK3_EMPLOYEEPROJECT2DLL_H
#define HOMEWORK3_EMPLOYEEPROJECT2DLL_H
#include <string>
#include <iostream>

using namespace std;

struct ProjectNode
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;

    //parametrized and default constructor for ProjectNode struct
    ProjectNode(string _project_name = "", int _project_priority = 0, ProjectNode* _next = nullptr, ProjectNode* _prev = nullptr)
    {
        project_name = _project_name;
        project_priority = _project_priority;
        next = _next;
        prev = _prev;
    }
};
struct EmployeeNode
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;

    //parametrized and default constructor for EmployeeNode struct
    EmployeeNode(string _employee_name = "" , ProjectNode* _head = nullptr , ProjectNode* _tail = nullptr, EmployeeNode* _down= nullptr)
    {
        employee_name = _employee_name;
        head = _head;
        tail = _tail;
        down = _down;
    }
};

class EmployeeProject2DLL {
private:
    EmployeeNode* head_2dhll;
    EmployeeNode* cpy_head_emp;
    ProjectNode* cpy_head_proj;
    bool priority_existance_check(const string & , const int &);
    bool same_priority_check(const string & , const string & , const int &);
    bool change_priority(const string & , const string & , int &);
    void sort(const string &);
    void check_free_employee(const string &);
public:
    EmployeeProject2DLL();
    bool isEmployeeAssignedToProject(const string &,const string &);
    bool updateProjectPriority(const string & , const string & , int &);
    bool assignEmployeeToProject(const string & , const string & , const int &);
    void withdrawEmployeeFromProject(const string & , const string & , int &);
    const void printTheEntireList();
    const void printEmployeeProjects(const string & , const int &);
    void undo(const char & ,const string & ,const string &,int &);
    void clear();
};

#endif
