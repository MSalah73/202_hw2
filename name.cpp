///////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework: # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the name, LLL_poke_node, and LLL_node.
//It contains every function that the programs would nedd. The comments in 
//the file will descripe the functionalty step by step to ensure the grader's 
//understanding of all the functions.
//
//As I immplented all of the classes, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//This file contains twp of the main classes in the programsm without them the 
//program would be nonfunctional. The name class is the base class for mlost every
//class in the prpgram. I have made it such that every "Is a" relashionship with 
//this class makes sence in the real world. Since the program is a messager container
//of apps like facebook, and snapchat. these all names, user have names , not
//to mentions even the conacts have names. 
//
//The Poke Node class is a names that have a conter of number of poked times. 
//the class is facebook spcific. It does not apply toother classes. I made the 
//coinnection such that i can reuse the name class in mutiple applications.
//
//The LLL_node class is the stores all the contacts that has the same last name.
//The class help with orginaze and make our search procces faster.
///////////////////////////////////////////////////////////////////////////////
////Hierarchy Connections:
//LL_poke_node -"Is a"-> Name
//LLL_node -"Is a"-> Name
//LLL_node -"Has a"-> text
///////////////////////////////////////////////////////////////////////////////

#include "name.h"

using namespace std;
//NAME CLASS
//Default constructor
name::name(): _name(NULL)
{
}
//Copy constuctor
//Step 1: Call name's change name function
//and pass the const char as an arguments.
name::name(const char * to_add): _name(NULL)
{
    change_name(to_add);
}
//Copy constuctor
//Step 1: Call name's set name function
//and pass the const object of name as an arguments.
name::name(const name & to_copy): _name(NULL)
{
    set_name(to_copy);
}
//This fuction will change the name of current object' name 
//to the passed in char.
//Step 1: check if the passed in value is NULL
//Step 2: check if name data memeer has data in it
//Step 2a: if so, delete the name data
//Step 3: set cuBST_noderrent object's name to the size of passed in name
//Step 4:copy the the data from passed in name to the current object's name
void name::change_name(const char * to_change)
{
    if(!to_change)
        return;
    if(_name)
        delete [] _name;
    _name = new char[strlen(to_change)+1];
    strcpy(_name, to_change);
}
//Step 1: display's current object' name
void name::display() const
{
    cout<<"Name: "<<_name<<endl;
}
//Step 1: check if the passed in object of name's name data member is not NULL
//step 2: if not NULL than call change name function
void name::set_name(const name & to_set)
{
    if(to_set._name)
        change_name(to_set._name);
}
//Step 1: return the value from comparing the passed in data with the object data
int name::compare(const name & to_comp) const
{
    return strcmp(_name, to_comp._name);
}
//Step 1: return the value from comparing the passed in data with the object data
int name::compare(const char * to_comp) const
{
    return strcmp(_name, to_comp);
}
//Destructor
//Step 1: delete array names object 
//Step 2: set it to NULL
name::~name()
{
    delete [] _name;
    _name = NULL;
}
//LLL_POKE_NODE CLASS
//Default constructor
LLL_poke_node::LLL_poke_node(): next(NULL), times(0)
{
}
//Copy constructor
LLL_poke_node::LLL_poke_node(const LLL_poke_node & to_copy):name(to_copy), next(NULL), times(0)
{
}
//Copy constructor
//step 1: incurment times by one
LLL_poke_node::LLL_poke_node(const char * to_copy): name(to_copy), next(NULL), times(0)
{
    ++times;
}
//step 1: return the next pointer
LLL_poke_node *& LLL_poke_node::go_next()
{
    return next;
}
//step 1: incurment times by one 
void LLL_poke_node::add_aPoke()
{
    ++times;
}
//step 1: assign next to the passed in arguments 
void LLL_poke_node::connect_next(LLL_poke_node * to_connect)
{
    next = to_connect;
}
//step 1: display the name of the poked person
//step 2: display the times they got poked
void LLL_poke_node::display()
{
    name::display();
    cout<<"poked "<<times<<" times\n";
}
//Destructor
LLL_poke_node::~LLL_poke_node()
{
    next = NULL;
}
//LLL_NODE CLASS
//Constructor
LLL_node::LLL_node(): text_stack(NULL), next(NULL)
{
}
//Copy constructor
LLL_node::LLL_node(const name & to_copy):name(to_copy), text_stack(NULL), next(NULL)
{
}
//Copy constructor
LLL_node::LLL_node(const char * to_copy):name(to_copy), text_stack(NULL), next(NULL)
{
}
//Copy constructor
LLL_node::LLL_node(const LLL_node & to_copy):name(to_copy), text_stack(NULL), next(NULL)
{
    text_stack = new text(*to_copy.text_stack);
}
//step 1: connect next to the next poiter
LLL_node *& LLL_node::go_next()
{
    return next;
}
//step 2: connect the nect pointer to the passed in argument
void LLL_node::connect_next(LLL_node * to_connect)
{
    next = to_connect;
}
//step 1:display the name of the person the user texting
//step 2: display all of the texts history 
void LLL_node::display()
{
    name::display();
    cout<<"------Texts-----";
    if(text_stack)
        text_stack->display();
    else
        cout<<"Text box is Empty!\n";
}
//step 1: allocate memory for text and pass in arguments to call copy constuctor 
//step 2: connect its nect to the text head 
//step 3: update head ;
void LLL_node::add_text(const char * to_add)
{
    text * temp = new text(to_add);
    temp->connect_next(text_stack);
    text_stack = temp;
}
//Destructor
//step 1: Delete all text
//step 2: set text and next to null
LLL_node::~LLL_node()
{
    delete text_stack;
    text_stack = NULL;
    next = NULL;
}
