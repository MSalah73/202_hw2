///////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework: # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the BST node class. It contains every 
//function that the programs would nedd. The comments in the file will descripe
//the functionalty step by step to ensure the grader's understanding of all the 
//functions.
//
//As I immplented all of the classes, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//This class have many functionality which is very critical to the program. 
//With out this class the contacts would not be saved nor orginazed. Each root
//node represned a a container that hold all of the contacts with name last name
//This help the program to find contacts easliy and effiectly.
//
///////////////////////////////////////////////////////////////////////////////
////Hierarchy Connections:
//BST_node -Is a"-> name
//BST_node -"Has a-> LLL_node
///////////////////////////////////////////////////////////////////////////////


#include "address_book.h"
using namespace std;
//Defualt constructor
BST_node::BST_node(): head(NULL), right(NULL), left(NULL)
{
}
//copy constructor 
//step 1: call copy to cop all the head data
BST_node::BST_node(const BST_node & to_copy): name(to_copy), head(NULL), right(NULL), left(NULL)
{
    copy(to_copy.head, head);
}
//copy constructor 
//step 1: call add a contact to the list of contacts with the same last name 
BST_node::BST_node(const char * last, const char * first): name(last), head(NULL), right(NULL), left(NULL)
{
    add_contact(last, first);
}
//step 1: return the right pointer
BST_node *& BST_node::go_right()
{
    return right;
}
//step 1: return the left pointer
BST_node *& BST_node::go_left()
{
    return left;
}
//step 1: if not source return
//step 2: allocate dest with passed in source as anrrgument
//step 3: call it self with the next pointers
void BST_node::copy(LLL_node * src, LLL_node *& dest)
{
    if(!src)
        return;
    dest = new LLL_node(*src);
    copy(src->go_next(), dest->go_next());
}
//step 1: set right to the passed in arguments 
void BST_node::connect_right(BST_node * to_connect)
{
    right = to_connect;
}
//step 1: set left to the passed in arguments 
void BST_node::connect_left(BST_node * to_connect)
{
    left = to_connect;
}
//Step 1: copy the data for the first array to the full name array 
//step 2: concatnate with a space and than the last name
void BST_node::concat_names(char * full_name, const char * first)
{
    strcpy(full_name, first);
    strcat(full_name, " ");
    strcat(full_name, _name);
}
//step 1: if the name of the bst node is null set it to the passed arguments
//step 2: check if the passed in first name in the list
//step 2a: yes - display a message and return 
//step 3: allocate memeory for it and place in the stack of LLL_node pointers
void BST_node::add_contact(const char * last, const char * first)
{
    if(!_name)
        change_name(last);
    if(inList(first))
    {
        cout<<"Can not add duplicates! "<<first<<" "<<last<<" already in list\n";
        return;
    }
    char full_name[strlen(_name) + strlen(first) +2];
    concat_names(full_name, first);
    LLL_node * temp = new LLL_node(full_name);
    temp->go_next() = head;
    head = temp;
}
//display all of the contacts from the head stacks
void BST_node::display() const
{
    display(head);
}
//step 1: check if the list is empty 
//step 2: call display 
//step 3: call it self with next pointer
void BST_node::display(LLL_node * to_display) const
{
    if(!to_display)
        return;
    to_display->display();
    display(to_display->go_next());
}
//step 1 if name does not exist return false
//step 2: allocate memeory for full from the passed in arguments 
//step 3: call concate name to cate the name passed in arugmuments 
//step 4: call the recurive function with the arugments 
bool BST_node::remove_contact(const char * first)
{
    if(!_name)
        return false;
    char full_name[strlen(_name) + strlen(first) +2];
    concat_names(full_name, first);
    return remove_contact(full_name, head);
}
//step 1: check if head root is null
//step 2: if root data equal to the apped in arguments - than
//step 2a: delet allocate remove 
//step 3: call it self with the next pointer
bool BST_node::remove_contact(const char * to_comp, LLL_node *& to_remove)
{
    if(!to_remove)
        return false;
    if(!to_remove->compare(to_comp))
    {
        LLL_node * hold = to_remove->go_next();
        delete to_remove;
        to_remove = hold;
        return true;
    }
    return remove_contact(to_comp, to_remove->go_next());
}
//step 1 if name does not exist return false
//step 2: allocate memeory for full from the passed in arguments 
//step 3: call concate name to cate the name passed in arugmuments 
//step 4: call the recurive function with the arugments 
bool BST_node::inList(const char * first)
{
    if(!_name)
        return false;
    char full_name[strlen(_name) + strlen(first) +2];
    concat_names(full_name, first);
    return inList(full_name, head);
}
//step 1: head is null rerurn 
//step 2: head's dara equal to the passed in arugments - return true
//step 3: call the recurive function with the arugments 
bool BST_node::inList(const char * _name, LLL_node * to_comp)
{
    if(!to_comp)
        return false;
    if(!to_comp->compare(_name))
        return true;
    return inList(_name, to_comp->go_next());
}
//step 1 if name does not exist return false
//step 2: allocate memeory for full from the passed in arguments 
//step 3: call concate name to cate the name passed in arugmuments 
//step 4: call the recurive function with the arugments 
void BST_node::retrieve(const char * first)
{
    if(!_name)
        return;
    char full_name[strlen(_name) + strlen(first) +2];
    concat_names(full_name, first);
    retrieve(full_name, head);
}
//step 1: head is null rerurn 
//step 2: head's dara equal to the passed in arugments 
//step 3: display data - rerurn 
//step 4: call the recurive function with the arugments 
void BST_node::retrieve(const char * to_comp, LLL_node * to_find) const
{
    if(!to_find)
        return;
    if(!to_find->compare(to_comp))
    {
        to_find->display();
        return;
    }
    retrieve(to_comp, to_find->go_next());
}
//step 1 if name does not exist return false
//step 2: allocate memeory for full from the passed in arguments 
//step 3: call concate name to cate the name passed in arugmuments 
//step 4: call the recurive function with the arugments 
void BST_node::add_text(const char * to_add, const char * first)
{
    if(!_name)
        return;
    char full_name[strlen(_name) + strlen(first) +2];
    concat_names(full_name, first);
    add_text(to_add, full_name, head);
}
//step 1: head is null rerurn 
//step 2: head's dara equal to the passed in arugments 
//step 3: add data - rerurn 
//step 4: call the recurive function with the arugments 
void BST_node::add_text(const char * to_add, const char * _name, LLL_node *& find)
{
    if(!find)
        return;
    if(!find->compare(_name))
    {
        find->add_text(to_add);
        return;
    }
    add_text(to_add, _name, find->go_next());
}
//step 1: head is null rerurn 
//step 2: call the recurive function with the arugments 
//step 3: delete the all the nodes 
void BST_node::destroy_list(LLL_node *& head)
{
    if(!head)
        return;
    destroy_list(head->go_next());
    delete head;
}
//Destructor
//step 1: deallacote head
//step 2: set pointers to NULL
BST_node::~BST_node()
{
    destroy_list(head);
    head = NULL;
    right = left = NULL;
}
