//Ege Tan 00030977 Homework2
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//likes linked list struct
struct NodeLike
{
    string subject;
    string object;
    NodeLike *next;

    //parametrized constructor.
    NodeLike(string _subject , string _object,NodeLike* _next = nullptr){
        subject = _subject;
        object = _object;
        next = _next;
    }
};
//taken linked list struct
struct NodeTaken
{
    string name;
    NodeTaken *next;

    //parametrized constructor.
    NodeTaken(string _name , NodeTaken* _next = nullptr){
        name = _name;
        next = _next;
    }
};
//takes nodelike pointer as a parameter
//print the whole list in requested format
void printlikes (NodeLike* likes)
{
    cout << "Likes list:";
    while(likes != nullptr)
    {
        cout << " (" << likes->subject << ", "<<likes->object<<")";
        likes=likes->next;
    }
    cout << endl;
}
//takes nodetaken pointer as a parameter
//print the whole list in requested format
void printtaken (NodeTaken* taken)
{
    cout << "Taken list:";
    while(taken != nullptr)
    {
        cout << " " << taken->name;
        taken=taken->next;
    }
    cout << endl << endl;
}
//takes nodetaken pointer and string name as a parameter
//if name exist in taken list , returns true ,otherwise false
bool is_in_taken_list (NodeTaken* taken,const string &_name)
{
    while(taken != nullptr)
    {
        if(taken->name == _name)
        {
            return true;
        }
        taken = taken->next;
    }
    return false;
}
//takes nodelikes pointer and string subject ,object as a parameter
//if name exist in taken list , returns true ,otherwise false
bool is_in_likes_list (NodeLike* likes,const string &_subject,const string &_object = "*")
{
    //object takes "*" as a default parameter
    //according to provided parameter value ,function behaves
    if (_object == "*")
    //this part searchs for subject occurence in linked list.
    //if exist , return true
    {
        while (likes != nullptr)
        {
            if (likes->subject == _subject)
            {
                return true;
            }
            likes = likes->next;
        }
        return false;
    }
    else
    {
        //this part searchs for subject and both object (in same node) occurence in linked list.
        //if exist , return true
        while (likes != nullptr)
        {
            if (likes->subject == _subject && likes->object == _object)
            {
                return true;
            }
            likes = likes->next;
        }
        return false;
    }
}
//takes nodelikes pointer and string subject ,object as a parameter
//this function adds node to linked list
void add_to_list (NodeLike* &likes,const string &_subject,const string &_object)
{
    if (likes == nullptr)
    //if list is empty
    {
        likes = new NodeLike(_subject, _object, nullptr);
        //creates new node and assigns subject , object to it
    }
    else {
        //if list is not empty , adds node to the last index of linked list
        NodeLike* head = likes;
        while (head != nullptr) {
            if (head->next == nullptr) {
                head->next = new NodeLike(_subject, _object, nullptr);
                return;
            }
            head = head->next;
        }
    }
}
//takes nodelikes pointer and string subject ,object as a parameter
//this function adds node to likes list according to the last occurence of subject in the list
bool insert_likes_list(NodeLike* likes,const string &_subject,const string &_object)
{
    while(likes->next != nullptr)
    {
        if (likes->subject == _subject && likes->next->subject != _subject)
            //checks the current and next node's subject
            //add the new node between these nodes accordingly
        {
            NodeLike* temp = likes->next;
            likes->next = new NodeLike(_subject,_object,temp);
            return true;
        }
        likes = likes->next;
        //iterate over list
    }
    return false;
}
//this function takes nodelikes pointer and string which is any object (means: also subject)
//and deletes subject-object occurence and also each occurence of subject and object seperately.
void delete_from_likes_list(NodeLike* &likes ,const string & any_object )
{
    while (likes != nullptr && (likes->object == any_object || likes->subject == any_object)) {
        //delets when deleting item is in the beggining of the list
        NodeLike* toDelete = likes;
        likes = likes->next;
        delete toDelete;
    }
    if (likes == nullptr)
        //finish the process when list is empty
        return;

    NodeLike* current = likes;

    while (current != nullptr && current->next != nullptr)
    //delets when deleting item is not in the beginning (it can be in the middle or end).
    {
        if (current->next->subject == any_object || current->next->object == any_object)
        {
            NodeLike* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
        else
        {
            current = current->next;
            //iterate over list
        }
    }
}
//this function takes nodetaken pointer and string name
//and insert this name as a new node to taken list in ascending order.
void insert_taken_list(NodeTaken* &taken , const string & name)
{
    NodeTaken* newNode = new NodeTaken(name);

    // Check if the list is empty or if the new node should be inserted at the beginning.
    if (taken == nullptr || taken->name >= name) {

        // Point the new node's next to the current head of the list.
        newNode->next = taken;
        taken = newNode;
    }
    else
    {
        NodeTaken* current = taken;
        // Traverse the list until we reach the end or find a node with a name greater than the new node's name.
        while (current->next != nullptr && current->next->name < name) {
            current = current->next;
        }
        // Insert the new node after the current node and before the next larger node.
        newNode->next = current->next;
        current->next = newNode;
    }
    cout <<"Added to taken list: "<<name<<endl;
}
//this function takes nodetaken pointer and nodelike pointer as their default value is nullptr
//the reason is to understand to be deleted function (in terms of writing two different functions)
//as a result they deallocate each memory locations that we allocated for linked list before.
void deletelist(NodeTaken* taken = nullptr , NodeLike* likes = nullptr )
{
    if (likes == nullptr)
    //delete the nodetaken list
    {
        NodeTaken* temp;
        while(taken != NULL) {
            temp = taken;
            taken = taken->next;
            delete temp;
        }
    }
    else
    //delete the nodelikes list
    {
        NodeLike* temp;
        while(likes != NULL) {
            temp = likes;
            likes = likes->next;
            delete temp;
        }
    }
}

int main() {
    NodeLike* like_head = nullptr;
    NodeTaken* taken_head = nullptr;
    ifstream file_input;
    string file_name,line,object,verb,subject;
    int line_counter = 1;
    bool check;
    cout << "Please enter the file name:"<<endl;
    //input file check part.
    do
    {
        cin >> file_name;
        file_input.open(file_name.c_str());
        if (file_input.fail())
        {
            cout << "Could not open the file. Please enter a valid file name:"<<endl;
            check = true;
        }
        else
        {
            check = false;
            //reading the each line at the file.
            while(getline(file_input,line))
            {
                stringstream ss(line);
                cout << "Read line number ("<<line_counter<<"): "<< line << endl;
                //splitting the words according the space.
                ss>>subject>>verb>>object;
                //if line counter is 1 , this means we can add anything to the list without considering any issue.
                if (line_counter == 1)
                {
                    like_head = new NodeLike(subject,object);
                    cout << line << " relation has been added to the likes list."<<endl;
                }
                //if line counter is different from 1
                else {
                    //checks wheter object or subject is in taken list
                    if (!is_in_taken_list(taken_head, subject) && !is_in_taken_list(taken_head, object))
                    {
                        //if not checks if subject-object relation occurs in likes list or not
                        if (!is_in_likes_list(like_head, subject, object))
                        {
                            // if not check if reverse (object-subject) relation occurs in likes list
                            if (is_in_likes_list(like_head, object, subject))
                            {
                                cout << "Match found: "<<subject<<" likes " << object <<" and "<< object<<" likes " << subject << "."<<endl;
                                //delete object-subject occurrence in the likes list.
                                //if there is also occurrences of object and subject , delete those ones too
                                delete_from_likes_list(like_head,object);
                                delete_from_likes_list(like_head,subject);
                                //insert this relationship to taken list (ascending order).
                                insert_taken_list(taken_head,subject);
                                insert_taken_list(taken_head,object);
                                cout << "Any node that has "<<subject<<" or "<<object<<" or both in it is removed from the likes list."<< endl;
                            }
                            //reverse relation is not in list
                            else
                            {
                                //checks wheter there is allready another subject in the likes list
                                if (is_in_likes_list(like_head, subject))
                                {
                                    //insert the subject to the last occurence of the subject that allready exist in the list
                                    if (!insert_likes_list(like_head, subject, object)) {
                                        add_to_list(like_head, subject, object);
                                    }
                                }
                                //if there is no any occurence of subject in the list
                                else
                                {
                                    //add subject to the end of the list.
                                    add_to_list(like_head, subject, object);
                                }
                                cout << line << " relation has been added to the likes list."<<endl;
                            }
                        }
                        //if subject-object relation is allready in likes list.
                        else
                        {
                            cout << line <<" relation already exists in the likes list, so it is not added to it."<<endl;
                        }
                    }
                    else
                    {
                        cout << "Either "<<subject<<" or "<<object<<" or both is/are already taken, so the like relation is not added."<<endl;
                    }
                }
                //increase the line number
                line_counter++;
                //print both likes and taken lists
                printlikes(like_head);
                printtaken(taken_head);
            }
        }
    }while(check);
    //deallocate each memory allocation at the end of the code
    deletelist(taken_head);
    deletelist(nullptr,like_head);
    cout << "Lists are deleted and the program ends successfully."<<endl;
    return 0;
}
