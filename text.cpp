///////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework: # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the text class. It contains every
//function that the programs would nedd. The comments in the file will descripe
//the functionalty step by step to ensure the grader's understanding of all 
//the functions.
//
//As I immplented all of the classes, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//I implemented This class solely for saveing the user text messages sent by 
//the user of the program. The program is text based with no interaction with
//other users or sources. In the real word this calss woild get both the user
//textes and thier friends, contacys, or from a random number. I think the class
//has all the needed functilaty for the porpose of the program. However, If i 
//were to use in the real world, I would have implemented something that catch 
//other's users text. The text class will be used in every app added in the program.
//
///////////////////////////////////////////////////////////////////////////////
////Hierarchy Connections:
//TEXT = Superbase class
///////////////////////////////////////////////////////////////////////////////


#include "text.h"
using namespace std;
//Default constructor
text::text(): _text(NULL), next(NULL)
{
}
//Copy constrcutor
//step 1: call add text 
//Step 3: call copy function to copy recusivliy the to_copy next texts list 
text::text(const text & to_copy): _text(NULL), next(NULL)
{
    add_text(to_copy._text);
    copy(to_copy.next, next);
}
//step 1: call add text 
text::text(const char * to_copy): _text(NULL), next(NULL)
{
    add_text(to_copy);
}
//Step 1: check is the source is NULL
//step 2: allcate dest and pass address of source to it to copy
//step 3: call the function recursivliy 
void text::copy(const text * src, text *& dest)
{
    if(!src)
        return;
    dest = new text(*src);
    copy(src->next, dest->next);
}
//step 1: check if copy's text exsist
//step 2: allccate current text to the size of copy's text
//step 3: copy from copy's text to current's text
void text::add_text(const char * to_add)
{
    if(to_add)
    {
        _text = new char[strlen(to_add) + 1];
        strcpy(_text, to_add);
    }
}
//step 1: compare the cuurent data with passed in arguments
//step 2: return is the same or not
bool text::compare(const char * to_comp)
{
    return !strcmp(_text, to_comp);
}
//step 1: connect the nex pointer the passed argument
void text::connect_next(text * to_connect)
{
    next = to_connect;
}
//step 1: call display recurvilly  
void text::display() 
{
    display(this, 1);
}
//step 1: check if head is NULL
//step 2: call it self recursivly with next pointer
//step 3: display all contant
void text::display(const text * head, int counter)
{
    if(!head)
        return;
    cout<<"\n"<<counter<<" - "
        <<head->_text<<"\n\n";
    ++counter;
    display(head->next, counter);
}
//step 1: check if head is NULL
//step 2: call it self recurvily
//step 3: delete head and set it to NULL
void text::destroy(text *& head)
{
    if(!head)
        return;
    destroy(head->next);
    delete head;
    head = NULL;
}
//Destrcutor
//Step 1: call destory on head
//step 2: delete text arrays
//step 4: set them to NULL
text::~text()
{
    destroy(next);
    delete [] _text;
    _text = NULL;
}

