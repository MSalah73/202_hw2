///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the generic communication, Facebook, Snapchat,
//Line, and Phone classes. It contains every function that the programs would nedd. 
//The comments in the file will descripe the functionalty step by step to ensure the grader's 
//understanding of all the functions.
//
//As I immplented all of the classes, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//This file contain all the classes nessaray to preform a dynamic binding opration and RTTI
//The abstract base class is contains virtual funtions that help make the dynamic binding 
//possible. Once the user picks the app like facebook or snapchat the pointer of the generic 
//commincation will be allocate. This concept makes the program way shorter and efficant. 
//Every drived class has a specific function which will be called using the run time type 
//idification.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//Generic_communication -"Has a"-> BST node
//Facebook -"Is a"-> Generic communication
//Facebook -"Has a"-> LLL_poke_node
//Snapchat -"Is a"-> Generic communication
//Line -"Is a"-> Generic communication
//Phone -"Is a"-> Generic communication
/////////////////////////////////////////////////////////////////////////////////////////
#include "communication_types.h"
#include <fstream>
using namespace std;
//ABSTRACT BASE CLASS
//GENERIC COMMUNICATION CLASS
//Default constructor
generic_communication::generic_communication(): root(NULL)
{
}
//copy constrctor
//Step 1: call copy with to_copy root  and root `
generic_communication::generic_communication(const generic_communication & to_copy): root(NULL)
{
    copy(to_copy.root, root);
}
//copy constrctor
//step 1: call add_contacts function with passed arguments
generic_communication::generic_communication(const char * last, const char * first): root(NULL)
{
    add_contact(last, first);
}
//step 1: if not root - return 
//step 2: call self with left child of root
//step 3: call display
//step 4: call self with right child of root
void generic_communication::display(BST_node * to_display)
{
    if(!to_display)
        return;

    display(to_display->go_left());
    cout<<"\n---------------------------\n";
    to_display->display();
    display(to_display->go_right());
}
//step 1: if the requested name is not in the root than display a mesaage and return 
//step 2: call send message and display message
void generic_communication::send_message(const char * to_send, const char * last, const char * first)
{
    if(!inContact(root, last, first))
    {
        cout<<"\n\33[0;31mCan not send message because "<<first<<" "<<last<<" is not in contact\33[0m\n";
        return;
    }
    send_message(root, to_send, last, first);
    cout<<"\n\n\33[0;31mMessage sent!\33[0m\n";
}
//step 1: if root is null - return 
//step 2: if root data is equal to the last name - call add message with first name as arguments
//step 3: call it self with lrft and right pointer
void generic_communication::send_message(BST_node * root, const char * to_send, const char * last, const char * first)
{
    if(!root)
        return;
    if(!root->compare(last))
        root->add_text(to_send, first);
    else if(root->compare(last) > 0)
        send_message(root->go_left(), to_send, last, first);
    else
        send_message(root->go_right(), to_send, last, first);
}
//step 1: call add contacts
//step 2: display message
void generic_communication::add_contact(const char * last, const char * first)
{
    add_contact(root, last, first);
    cout<<"\n\n\33[0;31m"<<first<<" "<<last<<" is added to contacts!\33[0m\n";
}
//step 1: if root is null - allocate root and pass in arguments for copy constructor
//step 2: if root last name is equal - call add contacts
//step 3: call it self with left and right pointer
void generic_communication::add_contact(BST_node *& root, const char * last, const char * first)
{
    if(!root)
    {
        root = new BST_node(last, first);
        return;
    }
    if(!root->compare(last))
        root->add_contact(last, first);
    else if(root->compare(last) > 0)
        add_contact(root->go_left(), last, first);
    else
        add_contact(root->go_right(), last, first);
}
//step 1: if root is null - return root
//setp 2: if root left child is null - return root
//step 3: call it self with left child pointer
BST_node * generic_communication::successor(BST_node *& root)
{
    if(!root)
        return root;
    if(!root->go_left())
        return root;
    return successor(root->go_left());
}
//step 1: check if root data is equal to passed last name
//step 1a: not than display error message and return
//step 2: call it self recurively
//step 3: display added message
void generic_communication::remove_all_last(const char * last)
{
    if(!inContact(root, last))
    {
        cout<<"\n\33[0;31mLast name: "<<last<<" do not exsist in contacts\33[0m\n";
        return;
    }
    remove_all_last(root, last);
    cout<<"\n\n\33[0;31mRequest successfully removed!\33[0m\n";
}
//step 1: check if root is null - return
//step 2: if root last names is equal to the passed in last name 
//step 2a: check if root is a leaf - delete root
//step 2b: check is root right or left is null - go to the next right or left and delete and update root
//step 2c: if root's both left and right exist find successor and delete root  and update
//step 2d: return
//step 3: call it self with right and left pointer 
void generic_communication::remove_all_last(BST_node *& root, const char * last)
{
    if(!root)
        return;
    if(!root->compare(last))
    {
        if(!root->go_left() && !root->go_right())
        {
            delete root;
            root = NULL;
        }
        else if(!root->go_left())
        {
            BST_node * right = root->go_right();
            delete root;
            root = right;
        }
        else if(!root->go_right())
        {
            BST_node * right = root->go_right();
            delete root;
            root = right;
        }
        else
        {
            BST_node * lhold = root->go_left(),
                     * rhold = root->go_right();
            delete root;
            root = successor(rhold);
            if(root != rhold)
            {
                rhold->go_left() = root->go_right();
                root->go_right() = rhold;
            }
            root->go_left() = lhold;
        }
        return;
    }
    else if(root->compare(last) > 0)
        remove_all_last(root->go_left(), last);
    else
        remove_all_last(root->go_right(), last);
}
//step 1: check if the request is in the the tree container - if not display message and return
//step 2: call remove recurive in it
//step 3: display message 
void generic_communication::remove_inContact(const char * last, const char * first)
{
    if(!inContact(root, last, first))
    {
        cout<<"\33[0;31m"<<first<<" "<<last<<" does not exsist in contacts\33[0m\n";
        return;
    }
    remove_inContact(root, last, first); 
    cout<<"\n\n\33[0;31mRequest successfully removed!\33[0m\n";
}
//step 1: if not root - return
//step 2: if root equal to the passed in data - call remove with first name passed in 
//step 3: call it self with the right and left child
void generic_communication::remove_inContact(BST_node * root, const char * last, const char * first)
{
    if(!root)
        return;
    if(!root->compare(last))
        root->remove_contact(first);
    if(root->compare(last) > 0)
        remove_inContact(root->go_left(), last, first);
    else
        remove_inContact(root->go_right(), last, first);
}
//step 1: check if root is null - return 
//step 2: call it self with the right and left childs
//step 3: delete root
void generic_communication::remove_all(BST_node *& root)
{
    if(!root)
        return;
    remove_all(root->go_left());
    remove_all(root->go_right());
    delete root;
}
//step 1: if root is null - return 
//step 2: if root data is equal to the last name - call retrieve WITh first name as arguments
//step 3: call it self with lrft and right pointer
void generic_communication::retrieve_inContact(BST_node * root, const char * last, const char * first)
{
    if(!root)
        return;
    if(!root->compare(last))
    {
        root->retrieve(first);
        return;
    }
    retrieve_inContact(root->go_left(), last, first);
    retrieve_inContact(root->go_right(), last, first);
}
//step 1: if root is null - return 
//step 2: if root data is equal to the last name - call display  with first name as arguments
//step 3: call it self with lrft and right pointer
void generic_communication::retrieve_all_last(BST_node * root, const char * last)
{
    if(!root)
        return;
    if(!root->compare(last))
    {
        root->display();
        return;
    }
    retrieve_all_last(root->go_left(), last);
    retrieve_all_last(root->go_right(), last);
}
//step 1: if root is null - return false  
//step 2: if root data is equal to the last name - return true
//step 3: call it self with lrft and right pointer
bool generic_communication::inContact(BST_node * root, const char * last, const char * first)
{
    if(!root)
        return false;
    if(!root->compare(last) && root->inList(first))
        return true;
    return inContact(root->go_left(), last, first) || inContact(root->go_right(), last, first);
}
//step 1: if root is null - return false 
//step 2: if root data is equal to the last name - retur true
//step 3: call it self with lrft and right pointer
bool generic_communication::inContact(BST_node * root, const char * last)
{
    if(!root)
        return false;
    if(!root->compare(last))
        return true;
    return inContact(root->go_left(), last) || inContact(root->go_right(), last);
}
//step 1: check if shource is null - return 
//step 2: allocate dest and pass souce and a refrance
//step 3: call it self on left and right child
void generic_communication::copy(BST_node * src, BST_node *& dest)
{
    if(!src)
        return;
    dest = new BST_node(*src);
    copy(src->go_left(), dest->go_left());
    copy(src->go_right(), dest->go_right());
}
//Destcurtor
//step 1: call remove all on root
generic_communication::~generic_communication()
{
    remove_all(root);
}
//FACEBOOK CLASS
//Defulat constructor 
facebook::facebook(): head(NULL)
{
}
//copy constcutotr
//step 1: call copy passing in head and copy's head 
facebook::facebook(const facebook & to_copy): generic_communication(to_copy), head(NULL)
{
    copy(head, to_copy.head);
}
//copy constcutotr
facebook::facebook(const char * last, const char * first): generic_communication(last, first), head(NULL)
{
}
//step 1: diplay a meesage
//step 2: if root is null
//step 2a: display a message 
//step 3: call recusive funtion from base 
void facebook::display()
{
    cout<<"\n----------Facebook----------\n";
    if(!root)
        cout<<"\n\33[0;31mContacts list is empty\33[0m\n";
    generic_communication::display(root);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void facebook::retrieve_inContact(const char * last, const char * first)
{
    if(!inContact(root, last, first))
    {
        cout<<"\n\33[0;31m"<<first<<" "<<last<<" is not in contact\33[0m\n";
        return;
    }
    cout<<"\n----------Facebook----------\n";
    generic_communication::retrieve_inContact(root, last, first);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void facebook::retrieve_all_last(const char * last)
{
    if(!inContact(root, last))
    {
        cout<<"\n\33[0;31mLast name: "<<last<<"\nDo not exsist in your contact\33[0m\n";
        return;
    }
    cout<<"\n----------Facebook----------\n";
    generic_communication::retrieve_all_last(root, last);
}
//step 1: check if last and first are in the tree list - if not display a message and return 
//step 2: call a poke someone fuction which returns bool value  if the poked person already exist
//step 3: if added return - else allciate a new poke node to that someone
void facebook::poke_someone(const char * last, const char * first)
{
    char _name[100] = {0};
    concat(_name, last, first);
    if(!inContact(root, last, first))
    {
        cout<<"\n\33[0;31m"<<_name<<" is not your friend :(\33[0m\n";
        return;
    }
    if(poke_someone(head, _name))
        return;
    LLL_poke_node * temp = new LLL_poke_node(_name);
    temp->go_next() = head;
    head = temp;
}
//step 1: if haed is null - return false 
//step 2: if haed data is equal to the name - add a poke to the head - return true 
//step 3: call it self with lrft and right pointer
bool facebook::poke_someone(LLL_poke_node * head, const char * _name)
{
    if(!head)
        return false;
    if(!head->compare(_name))
    {
        head->add_aPoke();
        return true;
    }
    return poke_someone(head->go_next(), _name);
}
//step 1: display a message and display the contant of head
void facebook::display_poke_list()
{
    cout<<"\n----------Facebook pokes----------\n";
    display_poke_list(head);
}
//step 1: if is null - return 
//step 2: call it self with next pointer 
//step 3: display all head data 
void facebook::display_poke_list(LLL_poke_node * head)
{
    if(!head)
        return;
    display_poke_list(head->go_next());
    head->display();
}
//step 1: if root is null - return 
//step 2: if root data is equal to the last name and first - display message and return
//step 3: retrieved poked with passed in arguments
void facebook::retrieve_poked(const char * last, const char * first)
{
    char _name[100] = {0};
    concat(_name, last, first);
    if(!inContact(root, last, first))
    {
        cout<<"\n\33[0;31m"<<_name<<" is not your friend :(\33[0m\n";
        return;
    }
    cout<<"\n----------Facebook pokes----------\n";
    retrieve_poked(head,_name);
}
//step 1: if head is null - display message and return 
//step 2: if root data is equal to the name - display head
//step 3: call it self with head next pointer 

void facebook::retrieve_poked(LLL_poke_node * head, const char * _name)
{
    if(!head)
    {
        cout<<"\n\33[0;31m"<<_name<<" can not be retrieved, becuse you have not poked them yet\33[0m\n";
        return;
    }
    if(!head->compare(_name))
        head->display();
    retrieve_poked(head->go_next(), _name);
}
//step 2: if root data is not equal to the last and first  -  display message and return
//step 3: call it self with next pointer
void facebook::delete_poked(const char * last, const char * first)
{
    char _name[100] = {0};
    concat(_name, last, first);
    if(!inContact(root, last, first))
    {
        cout<<"\n\33[0;31m"<<_name<<" is not your friend :(\33[0m\n";
        return;
    }
    delete_poked(head,_name);
}
//step 1: if head is null - diplay message and return 
//step 2: if head data is not equal to the last name - call it self with next pointer 
//step 3: delete head and update return 
void facebook::delete_poked(LLL_poke_node *& head, const char * _name)
{
    if(!head)
    {
        cout<<"\n\33[0;31m"<<_name<<" can not be deleted, becuse you have not poked them yet\n\33[0m\n";
        return;
    }
    if(!head->compare(_name))
    {
        LLL_poke_node * temp = head->go_next();
        delete head;
        head = temp;
        return;
    }
    delete_poked(head->go_next(), _name);
}
//step 1: copy the first name and than concate the last 
void facebook::concat(char * to_copy, const char * last, const char * first)
{
    strcpy(to_copy, first);
    strcat(to_copy, " ");
    strcat(to_copy, last);
}
//step 1: if not sorce - return
//step 2: allocate head abd pass in source's address
//step 3: call it self recursively 
void facebook::copy(LLL_poke_node *& head, LLL_poke_node * src)
{
    if(!src)
        return;
    head = new LLL_poke_node(*src);
    copy(head->go_next(), src->go_next());
}
//step 1: if not head - return 
//step 2: call it selft recusievly 
//step 3: delete head
void facebook::destroy(LLL_poke_node *& head)
{
    if(!head)
        return;
    destroy(head->go_next());
    delete head;
}
//Destructor 
//step 1: destory with head passed in
facebook::~facebook()
{
    destroy(head);
}
//SNAPCHAT CLASS
//Defualt constuctor
snapchat::snapchat(): story(NULL)
{
}
//copy constructor 
snapchat::snapchat(const char * last, const char * first): generic_communication(last, first), story(NULL)
{
}
//copy constructor 
//step 1: call add story and pass to copy as arguments
snapchat::snapchat(const snapchat & to_copy): generic_communication(to_copy), story(NULL)
{
    add_story(to_copy.story);
}
//step 1: diplay a meesage
//step 2: if root is null
//step 2a: display a message 
//step 3: call recusive funtion from base 
void snapchat::display()
{
    cout<<"\n----------Snapchat----------\n";
    if(!root)
        cout<<"\n\33[0;31mContacts list is empty\33[0m\n";
    generic_communication::display(root);
}
//step 1: if story display story
//step 2: if not display error message
void snapchat::display_story()
{
    if(story)
        cout<<"\n------your Snapchat's story------\n"
            <<story<<endl;
    else
        cout<<"\n\33[0;31mYou haven't included a story - Please add a story to view.\33[0m\n";
}
//step 1: if the passed story is empty - return 
//step 2: if story - delete
//step 3: if allocate story
//step 4: copy from passed story to know story 
void snapchat::add_story(const char * _story)
{
    if(!_story)
        return;
    if(story)
        delete [] story;
    story = new char[strlen(_story) + 1];
    strcpy(story,_story);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void snapchat::retrieve_inContact(const char * last, const char * first)
{
    if(!inContact(root, last, first))
    {
        cout<<endl<<first<<" "<<last<<" is not in contact\n";
        return;
    }
    cout<<"\n----------Snapchat----------\n";
    generic_communication::retrieve_inContact(root, last, first);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void snapchat::retrieve_all_last(const char * last)
{
    if(!inContact(root, last))
    {
        cout<<"\n\33[0;31mLast name: "<<last<<"\nDo not exsist in your contact\33[0m\n";
        return;
    }
    cout<<"\n----------Snapchat----------\n";
    generic_communication::retrieve_all_last(root, last);
}
//Destructor
//step 1: delete story
snapchat::~snapchat()
{
    delete [] story;
}
//LINE CLASS
//Defalt constuctor 
//step 1: set the number of emojies
//setp 2: read the emojies from the file 
line::line(): emojis(NULL)
{
    emojis = new char * [5];
    read();
}
//step 1: call generic communication with tocopy as agment in initialztion list
//step 2: set the number of emojies
//setp 3: read the emojies from the file 
line::line(const line & to_copy): generic_communication(to_copy), emojis(NULL)
{
    emojis = new char * [5];
    read();
}

//step 1: call generic communication with tocopy as agment in initialztion list
//step 2: set the number of emojies
//setp 3: read the emojies from the file 
line::line(const char * last, const char * first): generic_communication(last, first), emojis(NULL)
{
    emojis = new char * [5];
    read();
}
//step 1: diplay a meesage
//step 2: if root is null
//step 2a: display a message 
//step 3: call recusive funtion from base 
void line::display()
{
    cout<<"\n----------Line----------\n";
    if(!root)
        cout<<"\n\33[0;31mContacts list is empty\33[0m\n";
    generic_communication::display(root);
}
//step 1: prompt the user to enter an emoji from choice they have 
//step 2: resize the current message and copy the emoji to the text 
//step 3: send the message
void line::send_emojis(const char * text, const char * last, const char * first)
{
    char to_send[10000];
    strcpy(to_send, text);
    int choice(0), limit(0);
    do
    {
        cout<<"\nWhat emoji would you like to add to your text?\n";
        cout<<"Please pick a number associated with choices below\n"
            <<"1 - send message\n";
        for(int i = 0; i < 5; ++i)
            cout<<2 + i<<" - "<<emojis[i]<<endl;

        cin>>choice;
        cin.ignore(100,'\n');

        if((choice < 7 && choice > 1))
        {
            char temp[10000];
            strcpy(temp, to_send);
            strcat(temp, " ");
            strcat(temp, emojis[choice -2]);
            strcpy(to_send, temp);
            cout<<"\n\nCurrent text:\n"<<to_send<<endl;
            ++limit;
        }
        else if(choice != 1)
            cout<<"\n\33[0;31mInvaild choice!\33[0m\n";
        if(limit == 20) 
        {
            cout<<"\n\n\33[0;31mLIMIT REACHED AUTO SEND!!!\33[0m\n";
            choice = 1;
        }
    }while(choice != 1);

    generic_communication::send_message(to_send, last, first);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void line::retrieve_inContact(const char * last, const char * first)
{
    if(!inContact(root, last, first))
    {
        cout<<endl<<first<<" "<<last<<" is not in contact\n";
        return;
    }
    cout<<"\n----------Line----------\n";
    generic_communication::retrieve_inContact(root, last, first);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void line::retrieve_all_last(const char * last)
{
    if(!inContact(root, last))
    {
        cout<<"\n\33[0;31mLast name: "<<last<<"\nDo not exsist in your contact\33[0m\n";
        return;
    }
    cout<<"\n----------Line----------\n";
    generic_communication::retrieve_all_last(root, last);
}
//step 1: make an object of read
//step 2: connect it with txt file 
//step 3: copy the txt contants into the emoji pointers 
void line::read()
{
    ifstream load;
    char array[100];
    int counter(0);
    load.open("emoji.txt");
    if(load)
    {
        while(!load.eof())
        {
            load.get(array,100,'\n');
            load.ignore(100,'\n');
            if(!load.eof())
            {
                emojis[counter] = new char[strlen(array) + 1];
                strcpy(emojis[counter], array);
            }
            ++counter;
        }
    }
    load.clear();
    load.close();
}
//Destructor
//step 1: delete saved emojies 
line::~line()
{
    for(int i = 0; i < 5; ++i)
        delete [] emojis[i];
    delete [] emojis;
}
//PHONE CLASS
phone::phone():number(NULL)
{
}
//Copy constructor
//step 1: size for number copy it to number
phone::phone(const phone & to_copy): generic_communication(to_copy), number(NULL)
{
    number = new char[10];
    strcpy(number, to_copy.number);
}
//Copy constrctor
//step 1: call generic coomunications in initzalation list
phone::phone(const char * last, const char * first): generic_communication(last,first), number(NULL)
{
}

//step 1: diplay a meesage
//step 2: if root is null
//step 2a: display a message 
//step 3: call recusive funtion from base 
void phone::display()
{
    cout<<"\n----------Phone----------\n";
    if(!root)
        cout<<"\n\33[0;31mContact list is empty\33[0m\n";
    generic_communication::display(root);
}
//step 1: check if number is allocated - delete number
//step 2: alloacte number 
//step 3: insert from int to char by manuplating ascii values and using 
//the mode oprator
void phone::update_phone_number(long unsigned int to_add)
{
    if(number)
        delete [] number;
    number = new char[10];
    for(int i = 9; i > -1; --i)
    {
        number[i] = (to_add % 10) + 48;
        to_add /= 10;
    }
}
//step 1: check is number is null - return
//step 2: display the phone number with a certain format
void phone::display_phone_number()
{
    if(!number)
    {
        cout<<"\n\33[0;31mThere is no phone number to display!\33[0m\0";
        return;
    }
    cout<<"\nYour Phone number is (";
    for(int i = 0; i < 10; ++i)
    {
        if(i == 3)
            cout<<") ";
        else if(i == 6)
            cout<<"-";
        cout<<number[i];
    }
    cout<<endl;
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void phone::retrieve_inContact(const char * last, const char * first)
{
    if(!inContact(root, last, first))
    {
        cout<<"\n\33[0;31m"<<first<<" "<<last<<" is not in contact\33[0m\n";
        return;
    }
    cout<<"\n----------Phone----------\n";
    generic_communication::retrieve_inContact(root, last, first);
}
//step 1: if not in contacts list - display message and return 
//step 2: display message
//step 3: call recusive funtion from base 
void phone::retrieve_all_last(const char * last)
{
    if(!inContact(root, last))
    {
        cout<<"\n\33[0;31mLast name: "<<last<<"\nDo not exsist in your contact\33[0m\n";
        return;
    }
    cout<<"\n----------Phone----------\n";
    generic_communication::retrieve_all_last(root, last);
}
//destructor
//step 1: delete number
phone::~phone()
{
    delete [] number;
}
