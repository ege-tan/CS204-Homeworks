// Created by Ege Tan on 26.03.2024.
#include "EmployeeProject2DLL.h"

using namespace std;

//default constructor for creating an empty 2DLL list.
EmployeeProject2DLL::EmployeeProject2DLL()
{
    head_2dhll = nullptr;
}
//this function clears all allocated dynamic memories.
void EmployeeProject2DLL::clear()
{
    ProjectNode* deleted_proj;
    EmployeeNode * deleted_emp;
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        cpy_head_proj = cpy_head_emp->head;
        while (cpy_head_proj != nullptr)
        {
            //deletion starts from first employe's first assigned project
            //and continues till the tail
            deleted_proj = cpy_head_proj;
            cpy_head_emp->head = cpy_head_proj->next;
            cpy_head_proj = cpy_head_proj->next;
            delete deleted_proj;

        }
        //after deleting all assigned projects
        //employe node is deleting
        deleted_emp = cpy_head_emp;
        head_2dhll = cpy_head_emp->down;
        cpy_head_emp = cpy_head_emp->down;
        delete deleted_emp;

    }
}
//this function prints entire list.
const void EmployeeProject2DLL::printTheEntireList()
{
    cpy_head_emp = head_2dhll;
    //if list is not empty
    if (head_2dhll != nullptr)
    {
        while (cpy_head_emp != nullptr)
        {
            cout << cpy_head_emp->employee_name << ":";
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                cout << " ("<<cpy_head_proj->project_name<<", "<<cpy_head_proj->project_priority<<")";
                cpy_head_proj = cpy_head_proj->next;
            }
            cout << endl;
            cpy_head_emp = cpy_head_emp->down;
        }
    }
    //if list is empty
    else
    {
        cout << "The list is empty."<<endl;
    }
}
//this function prints the specific employe's assigned projects.
const void EmployeeProject2DLL::printEmployeeProjects(const string & name, const int & order)
{
    cpy_head_emp = head_2dhll;
    //if list is not empty
    if (cpy_head_emp != nullptr)
    {
        while (cpy_head_emp != nullptr)
        {
            //find the specific employe's node in the list and iterate inside.
            if (cpy_head_emp->employee_name == name)
            {
                cpy_head_proj = cpy_head_emp->head;
                if (order == 1)
                {
                    //Print from head to tail
                    while (cpy_head_proj != nullptr)
                    {
                        cout << "("<<cpy_head_proj->project_name<<", "<<cpy_head_proj->project_priority<<") ";
                        cpy_head_proj = cpy_head_proj->next;
                    }
                    cout << endl;
                    return;
                }
                else if(order == 0)
                {
                    //Print from tail to head
                    while (cpy_head_proj->next != nullptr)
                    {
                        //first go to the end
                        cpy_head_proj = cpy_head_proj->next;
                    }
                    //coming back to the head from end
                    while (cpy_head_proj != nullptr)
                    {
                        cout << "("<<cpy_head_proj->project_name<<", "<<cpy_head_proj->project_priority<<") ";
                        cpy_head_proj = cpy_head_proj->prev;
                    }
                    cout << endl;
                    return;
                }
            }
            cpy_head_emp = cpy_head_emp->down;
        }
        cout << "The employee is not in the list." << endl;
    }
    //if list is empty
    else
    {
        cout << "There are no employees in the list." << endl;
    }
}
//this function sorts the projects assigned to the employees.
void EmployeeProject2DLL::sort(const string & name)
{
    ProjectNode* ptr;
    string _name;
    int _priority;
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        //find the employee in the list and sort projects.
        if (cpy_head_emp->employee_name == name) {
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                ptr = cpy_head_proj->next;
                while (ptr != nullptr)
                {
                    //comparison condition (priority)
                    if (cpy_head_proj->project_priority > ptr->project_priority)
                    {
                        //change the information of two node without changing the node's connection.
                        _priority = cpy_head_proj->project_priority;
                        _name = cpy_head_proj->project_name;
                        cpy_head_proj->project_priority = ptr->project_priority;
                        cpy_head_proj->project_name = ptr->project_name;
                        ptr->project_priority = _priority;
                        ptr->project_name = _name;
                    }
                    ptr = ptr->next;
                }
                cpy_head_proj = cpy_head_proj->next;
            }
        }
        cpy_head_emp = cpy_head_emp->down;
    }
}
//this function checks wheter there is an empty employee or not.
//this function is used after withdrawing projects from an employee.
void EmployeeProject2DLL::check_free_employee(const string & name)
{
    EmployeeNode* deleted;
    cpy_head_emp = head_2dhll;
    if (cpy_head_emp->down != nullptr)
    {
        //checks the condition for the first employee to be empty.
        if (cpy_head_emp->employee_name == name && cpy_head_emp->head == nullptr)
        {
            deleted = cpy_head_emp;
            head_2dhll = cpy_head_emp->down;
            delete deleted;
            return;
        }
        //checks other conditions such as deleting employee from middle or from the end.
        else
        {
            //We are checking one node after because of deletion pattern
            while (cpy_head_emp->down != nullptr)
            {
                if (cpy_head_emp->down->employee_name == name && cpy_head_emp->down->head == nullptr)
                {
                    if (cpy_head_emp->down->down == nullptr)
                    {
                        //delete the last node of the employees
                        deleted = cpy_head_emp->down;
                        cpy_head_emp->down = nullptr;
                    }
                    else
                    {
                        //delete employee from midle
                        deleted = cpy_head_emp->down;
                        cpy_head_emp->down = deleted->down;
                    }
                    delete deleted;
                    return;
                }
                cpy_head_emp = cpy_head_emp->down;
            }
        }
    }
    else
    {
        if (cpy_head_emp->head == nullptr)
        {
            deleted = cpy_head_emp;
            head_2dhll = nullptr;
            delete deleted;
        }
    }
}
//this function changes the priority of assigned project to a specific employee.
//this function uses sort function as a helper function.
bool EmployeeProject2DLL::change_priority(const string & name, const string & project, int & priority)
{
    int temp_priority;
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        //find specific employee to change the priority of a project
        if (cpy_head_emp->employee_name == name )
        {
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                //find the specific project to be changed
                if (cpy_head_proj->project_name == project)
                {
                    //change the priority of that project
                    temp_priority = cpy_head_proj->project_priority;
                    cpy_head_proj->project_priority = priority;
                    //sort the list according to new priorities.
                    sort(name);
                    //return the previous priority as a reference
                    priority = temp_priority;
                    return true;
                }
                cpy_head_proj = cpy_head_proj->next;
            }
        }
        cpy_head_emp = cpy_head_emp->down;
    }
    return false;
}
//this function checks wheter there is a specific project that has a same name and same priority.
bool EmployeeProject2DLL::same_priority_check(const string & name, const string & project, const int & priority)
{
    ProjectNode* projtemp;
    EmployeeNode* emptemp;
    projtemp=cpy_head_proj;
    emptemp=cpy_head_emp;
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        //find the employee from the list
        if (cpy_head_emp->employee_name == name )
        {
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                //checks the condition (to be same).
                if (cpy_head_proj->project_name == project && cpy_head_proj->project_priority == priority)
                {
                    cpy_head_emp = emptemp;
                    cpy_head_proj = projtemp;
                    return true;
                }
                cpy_head_proj = cpy_head_proj->next;
            }
        }
        cpy_head_emp = cpy_head_emp->down;
    }
    //because of this function changes the values of cpy_head_emp and cpy_head_down
    //I save the values and reassign after iterating through the list
    //this behaviour stems from using this function in other iterating functions!!!
    cpy_head_emp = emptemp;
    cpy_head_proj = projtemp;
    return false;
}
//this function checks wheter there is allready a priority exist or not.
bool EmployeeProject2DLL::priority_existance_check(const string & name, const int & priority)
{
    ProjectNode* projtemp;
    EmployeeNode* emptemp;
    projtemp=cpy_head_proj;
    emptemp=cpy_head_emp;
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        if (cpy_head_emp->employee_name == name )
        {
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                //checking condition
                if (cpy_head_proj->project_priority == priority)
                {
                    cpy_head_emp = emptemp;
                    cpy_head_proj = projtemp;
                    return true;
                }
                cpy_head_proj = cpy_head_proj->next;
            }
        }
        cpy_head_emp=cpy_head_emp->down;
    }
    //same behaviour as in 'same_priority_check'!!
    cpy_head_emp = emptemp;
    cpy_head_proj = projtemp;
    return false;
}
//this function checks wheter a project is allready assigned to a specific employee or not
bool EmployeeProject2DLL::isEmployeeAssignedToProject(const string & name, const string & project)
{
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        //find the specific employee from the list
        if (cpy_head_emp->employee_name == name )
        {
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                //find the specific project from the list
                //if the project exist , this means allready assigned
                if (cpy_head_proj->project_name == project)
                {
                    return true;
                }
                cpy_head_proj = cpy_head_proj->next;
            }
        }
        cpy_head_emp = cpy_head_emp->down;
    }
    //if there is no project , return false.
    return false;
}
//this function changes the priority and uses 'change_priority' and 'same_priority_check' , 'priority_existance_check' as helper functions
bool EmployeeProject2DLL::updateProjectPriority(const string & name , const string & project, int & priority)
{
    //checks wheter there is a project with same priority and same name
    if (!same_priority_check(name,project,priority))
    {
        //checks only wheter there is a same priority
        if (!priority_existance_check(name,priority))
        {
            //if two condition is not met , change the priority
            change_priority(name,project,priority);
            return true;
        }
        else
        {
            //specifi message
            cout << "The project priority has not been updated because there is another project with the same priority." << endl;
            return false;
        }
    }
    else
    {
        //specifi message
        cout << "The project priority is already the same as the new priority." << endl;
        return false;
    }

}
//this function assigns a new project to employee
//in addition to that if there is no employee , it adds new employee to the list and assigns that new project
bool EmployeeProject2DLL::assignEmployeeToProject(const string & name, const string & project, const int & priority)
{
    EmployeeNode* temp;
    cpy_head_emp = head_2dhll;
    //if employee list is not empty
    if (cpy_head_emp != nullptr)
    {
        //iterate over the employee list
        while (cpy_head_emp != nullptr)
        {
            //fins the specific employee
            if (cpy_head_emp->employee_name == name)
            {
                cpy_head_proj = cpy_head_emp->head;
                //if the project list of that employee is not empty
                if (cpy_head_proj != nullptr)
                {
                    //checks for the priority existance
                    if (!priority_existance_check(name,priority))
                    {
                        //iterate over the project list of a specific employee
                        while (cpy_head_proj->next != nullptr)
                        {
                            cpy_head_proj = cpy_head_proj->next;
                        }
                        //add new node to the end of the list
                        cpy_head_proj->next = new ProjectNode(project, priority, nullptr, cpy_head_proj);
                        cpy_head_emp->tail = cpy_head_proj->next;
                        //sort the list
                        sort(name);
                        return true;
                    }
                    //accurate error message
                    else
                    {
                        cout<< "The project has not been added because there is another project with the same priority."<< endl;
                        return false;
                    }
                }
                //if the project list of that employee is empty
                else
                {
                    //create new project node and make it the head of that projects list of that employee
                    cpy_head_emp->head = new ProjectNode(project, priority, nullptr, nullptr);
                    //make the connections
                    cpy_head_emp->tail = cpy_head_emp->head;
                    return true;
                }
            }
            cpy_head_emp = cpy_head_emp->down;
        }
        cpy_head_emp = head_2dhll;
        //if there is no employee with that name in the list
        //and if there is only one employee in the list
        if (cpy_head_emp->down == nullptr)
        {
            //insert new employee node as a head of employee list
            if (cpy_head_emp->employee_name > name)
            {
                head_2dhll = new EmployeeNode(name, nullptr, nullptr, cpy_head_emp);
                head_2dhll->head = new ProjectNode(project,priority, nullptr, nullptr);
                head_2dhll->tail = head_2dhll->head;
            }
            //insert new employee node as a next of head of employee list
            else
            {
                cpy_head_emp->down = new EmployeeNode(name, nullptr, nullptr, nullptr);
                cpy_head_emp->down->head = new ProjectNode(project,priority, nullptr, nullptr);
                cpy_head_emp->down->tail = cpy_head_emp->down->head;
            }
            return true;
        }
        //if there is no employee with that name in the list
        //and if there is more than one employee in the list
        else
        {
            //insert new employee node as a head of employee list
            if (cpy_head_emp->employee_name > name)
            {
                head_2dhll = new EmployeeNode(name, nullptr, nullptr, cpy_head_emp);
                head_2dhll->head = new ProjectNode(project,priority, nullptr, nullptr);
                head_2dhll->tail = head_2dhll->head;
                return true;
            }
            //checks the condition fot adding new employee to the middle
            while (cpy_head_emp->down != nullptr)
            {
                if (cpy_head_emp->employee_name < name && cpy_head_emp->down->employee_name > name)
                {
                    temp = cpy_head_emp->down;
                    cpy_head_emp->down = new EmployeeNode(name, nullptr, nullptr, temp);
                    cpy_head_emp->down->head = new ProjectNode(project,priority, nullptr, nullptr);
                    cpy_head_emp->down->tail = cpy_head_emp->down->head;
                    return true;
                }
                cpy_head_emp = cpy_head_emp->down;
            }
            //adds new employee node to the end of the list
            cpy_head_emp->down = new EmployeeNode(name, nullptr, nullptr, nullptr);
            cpy_head_emp->down->head = new ProjectNode(project,priority, nullptr, nullptr);
            cpy_head_emp->down->tail = cpy_head_emp->down->head;
            return true;
        }
    }
    //if employee list is empty
    else
    {
        //creates new employee as a head of the list
        head_2dhll = new EmployeeNode(name, nullptr, nullptr, nullptr);
        //and assign new project to that employee
        head_2dhll->head = new ProjectNode(project,priority, nullptr, nullptr);
        //make the connections
        head_2dhll->tail = head_2dhll->head;
        return true;
    }
}
//this function deletes project that assigned to the employee
void EmployeeProject2DLL::withdrawEmployeeFromProject(const string & name, const string & project, int & priority)
{
    ProjectNode* deleted;
    cpy_head_emp = head_2dhll;
    while (cpy_head_emp != nullptr)
    {
        //find the matching employee from employee list
        if (cpy_head_emp->employee_name == name )
        {
            cpy_head_proj = cpy_head_emp->head;
            while (cpy_head_proj != nullptr)
            {
                //find the searching project from project list
                if (cpy_head_proj->project_name == project )
                {
                    //specify the deleting node
                    deleted = cpy_head_proj;
                    priority = deleted->project_priority;
                    if(cpy_head_proj == cpy_head_emp->head && cpy_head_proj->next == nullptr)
                    {
                        //delete the head of projects(but last item in the list)
                        cpy_head_emp->head = nullptr;
                        cpy_head_emp->tail = nullptr;
                    }
                    else if(cpy_head_proj == cpy_head_emp->head)
                    {
                        //delete the node from the head of the list
                        cpy_head_emp->head = deleted->next;
                        deleted->next->prev = nullptr;
                    }
                    else if(cpy_head_proj->next == nullptr)
                    {
                        //delete the last node of projects
                        cpy_head_emp->tail = deleted->prev;
                        deleted->prev->next = nullptr;
                    }
                    else
                    {
                        //delete something from middle
                        ProjectNode* behind;
                        ProjectNode* front;
                        behind = deleted->prev;
                        front = deleted->next;
                        behind->next = front;
                        front->prev = behind;
                    }
                    delete deleted;
                }
                cpy_head_proj = cpy_head_proj->next;
            }
        }
        cpy_head_emp = cpy_head_emp->down;
    }
    //this function additionally uses this function in terms of checking
    //wheter there occur an empty employee after deletion of the projects or not.
    check_free_employee(name);
}
//this function helps to use lifo method to apply undo operation
void EmployeeProject2DLL::undo(const char &operation, const string &name, const string &project,int &priority)
{
    if (operation == 'u')
    {
        cout<< "Undoing the update of a project priority." << endl;
        updateProjectPriority(name,project,priority);
    }
    else if (operation == 'a')
    {
        cout<< "Undoing the assignment of a project." << endl;
        withdrawEmployeeFromProject(name,project,priority);
    }
    else if (operation == 'w')
    {
        cout<< "Undoing the withdrawal of a project." << endl;
        assignEmployeeToProject(name,project,priority);
    }
}

