///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
////This file contains the implentaion of the interface, and  the CLL_node classes
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
//The CLL_node class has many functionilty the CLL class with help to creating and choicing
//the right drived class like facebook to ensure dynimic binding occurance. The class "is a"
//which, sumilates the the useage of Dynimic binding in simple if sataments and RTTI to 
//be in yet another simole if statments. This help run time overhead and get direct access
//to dirved class or dynamic binding. As for the imterface the class olse purpose is to 
//handle the CLL nodes by maing CLL and help the user to pick the right functions to 
//app or opration to be done.
//
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//interface -"Has a"-> CLL_node 
//CLL_node_node -"Is a"-> Name 
//CLL_node -"Has a"-> Name and generic_communication pointer
/////////////////////////////////////////////////////////////////////////////////////////

#include "interface_CLL.h"
using namespace std;
//Defalut constructor
CLL_node::CLL_node(): account_name(NULL), app(NULL), next(NULL)
{
}
//Copy  constructor
//step 1: check current name is equil to one of the names passed in
//step 2: if one of them matched
//step 3: allocates the app pointer to the drived class newly alloacted object
//step 4: call copy the account name with the copy constructor 
CLL_node::CLL_node(const CLL_node & to_copy): name(to_copy), account_name(NULL), app(NULL), next(NULL)
{
    if(compare("Facebook"))
    {
        facebook * ptr = dynamic_cast<facebook*>(to_copy.app);
        if(ptr)
            app = new facebook(*ptr); 
    }
    else if(compare("Snapchat"))
    {
        snapchat * ptr = dynamic_cast<snapchat*>(to_copy.app);
        if(ptr)
            app = new snapchat(*ptr); 
    }
    else if(compare("Line"))
    {
        line * ptr = dynamic_cast<line*>(to_copy.app);
        if(ptr)
            app = new line(*ptr); 
    }
    else
    {
        phone * ptr = dynamic_cast<phone*>(to_copy.app);
        if(ptr)
            app = new phone(*ptr); 
    }
    account_name = new name(*to_copy.account_name);
}
//Copy  constructor
//step 1: check the passed in aurgments is equal to one the choices
//step 2: allocate new drived class and set the name of the CLL node
//step 3: if app app exist - than allocate account name and pass in full name to copy
CLL_node::CLL_node(unsigned int to_add, const char * last, const char * first): account_name(NULL), app(NULL), next(NULL)

{
    if(to_add == 1)
    {
        app = new facebook; 
        change_name("Facebook");
    }
    else if(to_add == 2)
    {
        app = new snapchat;
        change_name("Snapchat");
    }
    else if(to_add == 3)
    {
        app = new line;
        change_name("Line");
    }
    else
    {
        app = new phone;
        change_name("Phone");
    }
    if(app)
    {
        char full_name[1000] ={0};
        concat(full_name, last, first); 
        account_name = new name(full_name);
    }
}
//step 1: return the next pointer
CLL_node *& CLL_node::go_next()
{
    return next;
}
//step 1: connect the next pointer to the passed in argument
void CLL_node::connect_next(CLL_node * to_connect)
{
    next = to_connect;
}
//step 1: if not return of function call contained 
//step 2: call display
void CLL_node::display()
{
    if(!contained())
        return;
    app->display();
}
//step 1: murge names and pass it to the function all account_name compare  
bool CLL_node::compare_account_name(const char * last, const char * first)
{
    char to_comp[1000];
    concat(to_comp, last, first);
    return account_name->compare(to_comp);
}
//step 1: display the data for account name 
void CLL_node::display_account_name()
{
    account_name->display();
}
//step 1: check if the app is line app
//step 1a: prompt user if they want to add emojis
//step 1b: if yes - call sepcial function of line
//step 2: if not - than send the message
void CLL_node::send_message(const char * to_send, const char * last, const char * first)
{
    if(!compare("Line"))
    {
        char ans;
        cout<<"\nWould you like to send emojies? - \33[0;31mY/N\33[0m\n";
        cin>>ans;
        cin.ignore(100,'\n');
        if(toupper(ans) == 'Y')
             return special_line(to_send, last, first);
    }
    app->send_message(to_send, last, first);
}
//step 1: if not contained than call the add contacts function
void CLL_node::add_contact(const char * last, const char * first)
{
    if(!contained())
        return;
    app->add_contact(last, first);
}
//step 1: if not contained than call the remove contacts function
void CLL_node::remove_inContact(const char * last, const char * first)
{
    if(!contained())
        return;
    app->remove_inContact(last, first);

}
//step 1: if not contained than call the retrieve contacts function
void CLL_node::retrieve_inContact(const char * last, const char * first)
{
    if(!contained())
        return;
    app->retrieve_inContact(last, first);
}
//step 1: check if app is null - yes display message and reurn false
//step 2: else return true
bool CLL_node::contained()
{
    if(!app)
    {
        cout<<"\n\33[0;31mEmpty container! Please add a contact to this container for this function to be executable\n\33[0m";
        return false;
    }
    return true;
}
//step 1: copy the first name to the full name array 
//step 2: strcat the rest of the items
void CLL_node::concat(char * full_name, const char * last, const char * first)
{
    strcpy(full_name,first);
    strcat(full_name, " ");
    strcat(full_name, last);
}
//step 1: in not contained - return
//step 2: if current name is equal to the if statments 
//step 2a:call the special functions
void CLL_node::special_functions()
{
    if(!contained())
        return;
    if(!compare("Facebook"))
        special_facebook();
    else if(!compare("Snapchat"))
        special_snap();
    else if(!compare("Phone"))
        special_phone();
}
//step 1: Do RTTI - if not null
//step 2: prompt the user 
//step 3: depending on the choice the right function will be picked
//step 4: prompt the user for names of the friends to do operation upon
void CLL_node::special_facebook()
{
    facebook * facebook_ptr = dynamic_cast<facebook*>(app);
    if(facebook_ptr)
    {
        int choice(0);
        do{
            cout<<"\nWhat would you like to do ?\n";
            cout<<"Please pick a number associated with choices below\n"
                <<"1 - Previous menu\n"
                <<"2 - Poke a friend\n"
                <<"3 - Display Poked friends\n"
                <<"4 - Delete a poked friend\n"
                <<"5 - Retrieve a poked friend\n";
            cin>>choice;
            cin.ignore(100, '\n');

        }while(!(choice < 6 && choice > 0));
        if(choice == 1)
            return;
        else if(choice == 2)
        {
            char last[100], first[100];
            cout<<"\nWho would you like to poke ?\n";
            name_prompt(last, first);
            facebook_ptr->poke_someone(last, first);
        }
        else if(choice == 3)
            facebook_ptr->display_poke_list();
        else if(choice == 4)
        {
            char last[100], first[100];
            cout<<"\nWho would you like to delete ?\n";
            name_prompt(last, first);
            facebook_ptr->delete_poked(last, first);
        }
        else
        {
            char last[100], first[100];
            cout<<"\nWho would you like to retrieve ?\n";
            name_prompt(last, first);
            facebook_ptr->retrieve_poked(last, first);
        }
    }
}
//step 1: Do RTTI - if not null
//step 2: prompt the user 
//step 3: depending on the choice the right function will be picked
//step 4: prompt the user for story to enter
void CLL_node::special_snap()
{
    snapchat * snapchat_ptr = dynamic_cast<snapchat*>(app);
    if(snapchat_ptr)
    {
        int choice(0);
        do{
            cout<<"\nWhat would you like to do ?\n";
            cout<<"Please pick a number associated with choices below\n"
                <<"1 - Previous menu\n"
                <<"2 - Add/Change your story\n"
                <<"3 - Display your story\n";
            cin>>choice;
            cin.ignore(100, '\n');

          }while(!(choice < 4 && choice > 0));
        if(choice == 1)
            return;
        else if(choice == 2)
        {
            char story[10000];
            cout<<"\nPlease enter your story:\n";
            cin.get(story,10000, '\n');
            cin.ignore(10000, '\n');
            snapchat_ptr->add_story(story);
        }
        else
            snapchat_ptr->display_story();
    }
}
//step 1: Do RTTI - if not null
//step 2: call the function
void CLL_node::special_line(const char * to_send, const char * last, const char * first)
{
   line * line_ptr = dynamic_cast<line*>(app);
    if(line_ptr)
        line_ptr->send_emojis(to_send, last, first);
}
//step 1: Do RTTI - if not null
//step 2: prompt the user 
//step 3: depending on the choice the right function will be picked
//step 4: prompt the user for phone number 
void CLL_node::special_phone()
{
    phone * phone_ptr = dynamic_cast<phone*>(app);
    if(phone_ptr)
    {
        int choice(0);
        do{
            cout<<"\nWhat would you like to do ?\n";
            cout<<"Please pick a number associated with choices below\n"
                <<"1 - Previous menu\n"
                <<"2 - Add/Update your phone number\n"
                <<"3 - Display your phone number\n";
            cin>>choice;
            cin.ignore(100, '\n');

        }while(!(choice < 4 && choice > 0));
        if(choice == 1)
            return;
        else if(choice == 2)
        {
            long unsigned int number(0);
            do
            {
                cout<<"\nPlease a phone number (10 digits):\n";
                cin>>number;
            }while(!(number < 10000000000 && number > 999999999));
            phone_ptr->update_phone_number(number);
        }
        else
            phone_ptr->display_phone_number();
    }
}
//step 1: prompt the user for names
void CLL_node::name_prompt(char * last, char *first)
{
    cout<<"\nPlease enter the their first name: ";
    cin.get(first, 100, '\n');
    cin.ignore(100, '\n');
    cout<<"\nPlease enter the their last name: ";
    cin.get(last, 100, '\n');
    cin.ignore(100, '\n');
}
//destructore
//step 1: delete account name and the app
//step 2: set next to NULL
CLL_node::~CLL_node()
{
    delete account_name;
    delete app;
    next = NULL;
}
//INTERFACE CLASS
//step 1: allocate multidemensional array
//step 2: allocate ech array to the right app name
interface::interface(): rear(NULL), apps(NULL)
{
    apps = new char * [4];
    apps[0] = new char[9];
    strcpy(apps[0], "Facebook");
    apps[1] = new char[9];
    strcpy(apps[1], "Snapchat");
    apps[2] = new char[5];
    strcpy(apps[2], "Line");
    apps[3] = new char[6];
    strcpy(apps[3], "Phone");
}
//step 1: allocate multidemensional array
//step 2: allocate ech array to the right app name
//step 3: if source os not null - call copy 
interface::interface(const interface & to_copy): rear(NULL), apps(NULL)
{
    apps = new char * [4];
    apps[0] = new char[9];
    strcpy(apps[0], "Facebook");
    apps[1] = new char[9];
    strcpy(apps[1], "Snapchat");
    apps[2] = new char[5];
    strcpy(apps[2], "Line");
    apps[3] = new char[6];
    strcpy(apps[3], "Phone");
    if(!to_copy.rear)
        copy(to_copy.rear->go_next(), rear, to_copy.rear);
}
//step 1: prompt the user
//step 2: depnding on the asnwer the right funtion will be called
void interface::manager()
{
    int choice(0);
    cout<<"\nWelcome to app to the communication app";
        do{
            cout<<"\nWhat would you like to do ?\n"
                <<"Please pick a number associated with the choices below\n"
                <<"\33[0;31mNOTE: Once the app is retrieved, a menu will pop up for further interactions\33[0m\n"
                <<"1 - Add an application\n"
                <<"2 - Display all applications\n"
                <<"3 - Remove an application\n"
                <<"4 - Retrieve an application\n"
                <<"5 - Quit\n" 
                <<"Choice #: ";
            cin>>choice;
            cin.ignore(100, '\n');

            if(choice == 1)
                add_menu();
            else if(choice == 2)
            {
                if(rear)
                {
                    cout<<"\n\33[0;31m----------All registered apps----------\33[0m\n";
                    display_apps(rear->go_next());
                }
                else
                    cout<<"\n\33[0;31mNo apps to display!\33[0m\n";
            }
            else if(choice == 3)
                remove_retrieve_menu(0);
            else if(choice == 4)
                remove_retrieve_menu(1);
        }while(choice != 5);
        cout<<"\n\33[0;31mThank you for using this application\n---------GOOD BYE----------\33[0m\n";
}
//step 1: prompt the user
//step 2: if not 5 - prompt the user for username
//step 3: depnding on the choce the right funtion will be called
void interface::add_menu()
{
    int choice(0);
    char last[100] = {0}, first[100] = {0}, full_name[100];
    do{
        cout<<"What would you like add ?\n"
            <<"Please pick a number associated with the choices below\n"
            <<"1 - Facebook\n"
            <<"2 - Snapchat\n"
            <<"3 - Line\n"
            <<"4 - Phone\n"
            <<"5 - Previous menu\n" 
            <<"Choice #: ";
        cin>>choice;
        cin.ignore(100, '\n');
    }while(!(choice < 6 && choice > 0));
    if(choice == 5)
        return;

    cout<<"\nPlease enter the account username\n";
    name_prompt(last, first);
    concat(full_name, last, first);
    if(!rear)
        if(add_app(rear, choice, last, first))
        {
            cout<<"\n\33[0;31mRequest added\33[0m\n";
            return;
        }

    if(inList(rear->go_next(),apps[choice-1], last, first))
    {
        cout<<"\n\33[0;31mAdd request denied! "<<apps[choice - 1]
            <<" with user name "<<full_name
            <<" already exist\33[0m\n";
            return;
    }
    if(add_app(rear, choice, last, first))
        cout<<"\n\33[0;31mRequest added\33[0m\n";
}
//step 1: if the list is empty - a message will pop and return
//step 2: prompt the user
//step 2: if not 5 - prompt the user for username
//step 3: depnding on the choce the right funtion will be called
void interface::remove_retrieve_menu(int request)
{
    if(!rear)
    {
        if(!request)
            cout<<"\n\33[0;31mNo apps to remove!\33[0m\n";
        else
            cout<<"\n\33[0;31mNo apps to retrieve!\33[0m\n";
        return;
    }
    int choice(0);
    char last[100] = {0}, first[100] = {0}, full_name[100];
    do{
        if(!request)
            cout<<"What would you like remove ?\n";
        else
            cout<<"What would you like retrieve ?\n";
        cout<<"Please pick a number associated with the choices below\n"
            <<"1 - Facebook\n"
            <<"2 - Snapchat\n"
            <<"3 - Line\n"
            <<"4 - Phone\n"
            <<"5 - Previous menu\n" 
            <<"Choice #: ";
        cin>>choice;
        cin.ignore(100, '\n');
    }while(!(choice < 6 && choice > 0));

    if(choice == 5)
        return;

    --choice;
    if(!request)
        cout<<"\nPlease enter the account username to remove\n";
    else
        cout<<"\nPlease enter the account username to retrieve\n";
    name_prompt(last, first);
    concat(full_name, last, first);

        if(inList(rear->go_next(),apps[choice], last, first))
        {
            if(!request)
                if(remove_app(rear->go_next(), rear, apps[choice], last, first))
                {
                    cout<<"\n\33[0;31mRequest removed\33[0m\n";
                    return;
                }
            return retrieve_app(rear->go_next(), apps[choice],last, first);
        }
    cout<<"\n\33[0;31mRequest does not exist!\33[0m\n";
}
//step 1: display the name ofthe application name 
//step 2: display the account name
//steo 3: call it self with the next pointer
void interface::display_apps(CLL_node * to_display)
{
    cout<<"\nApplication ";
    to_display->name::display();
    cout<<"User ";
    to_display->display_account_name();
    if(to_display == rear)
        return;
    display_apps(to_display->go_next());
}
//step 1: check if the node have the same passed in agriments app name and app name.
//step 2: if same delete, connect, and return return
//step 3: if rear is not the same as to_remove 
//step 4: call it self  with next pointer of rear
int interface::remove_app(CLL_node *& to_remove, CLL_node * prev, const char * app_name, const char * last, const char * first)
{
    if(!to_remove->compare(app_name) && !to_remove->compare_account_name(last, first))
    {
        CLL_node * hold = to_remove;
        if(to_remove == prev)
        {
            delete rear;
            rear = NULL;
        }
        else
        {
            to_remove = prev;
            to_remove->go_next() = hold->go_next();
            delete hold;
        }
        return 1;
    }
    if(to_remove == rear)
        return 0;
    return remove_app(to_remove->go_next(),to_remove, app_name, last, first);
}
//step 1: allocate temp with passed argumets 
//step 2: if rear is null than assign temp to rear and rear to it self
//step 3: insert at the bootom of the list and connect
int interface::add_app(CLL_node *& rear, unsigned int to_add, const char * last, const char * first)
{
    CLL_node * temp = new CLL_node(to_add, last, first);
    if(!rear)
    {
        rear = temp;
        rear->go_next() = rear;
        return 1;
    }
    CLL_node * hold = rear->go_next();
    temp->go_next() = hold;
    rear->go_next() = temp;
    rear = temp;
    return 1;
}
//step 1: check if the passed in arguments are the same as the rear data
//step 2: if yes - display and display the app name and the user name
//step 3: prompt the user if they wan to lunch the app
//step 4: else if to_retrieve is equal ti rear and return 
//step 5: call it self recusivley with the next pointer
void interface::retrieve_app(CLL_node * to_retrieve, const char * app_name, const char * last, const char * first)
{
    if(!to_retrieve->compare(app_name) && !to_retrieve->compare_account_name(last, first))
    {
        cout<<"\n\33[0;31m----------Application found----------\33[0m\n";
        to_retrieve->name::display();
        cout<<"Username: ";
        to_retrieve->display_account_name();
        char choice(0);
        cout<<"\nDo you want to lunch the app ? \33[0;31mY/N\33[0m\n";
        cin>>choice;
        cin.ignore(100, '\n');
        if(toupper(choice) == 'Y')
            app_interactions_menu(to_retrieve, app_name);
        return;
    }
    if(to_retrieve == rear)
        return;
    retrieve_app(to_retrieve->go_next(), app_name, last, first);
}
//step 1: prompt the user
//step 2: if not 7 - prompt the user for username
//step 3: depnding on the choce the right funtion will be called
void interface::app_interactions_menu(CLL_node * to_interact, const char * app_name)
{
    int choice(0);
    do{
        do{
            cout<<"\nWhat would you like to do ?\n"
                <<"\33[0;31mNOTE: Line special funnction is called within send message!\33[0m\n"
                <<"Please pick a number associated with the choices below\n"
                <<"1 - Send a message\n"
                <<"2 - Display all contacts/friends\n"
                <<"3 - Add a contact/friend\n"
                <<"4 - Remove a contact/friend\n"
                <<"5 - Retrieve a contact/friends\n";
            if(app_name[0] == 'L')
            {
                cout<<"6 - Quit app\n" 
                <<"Choice #: ";
            }
            else
            {
                cout<<"6 - App special functions\n"
                <<"7 - Quit app\n" 
                <<"Choice #: ";
            }
            cin>>choice;
            cin.ignore(100, '\n');
            if(app_name[0] == 'L' && choice == 6)
                ++choice;
        }while(!(choice < 8 && choice > 0));
        
        char last[100] = {0}, first[100] = {0};
        if(choice == 1)
        {
            char message[10000] = {0};
            cout<<"\nPlease write your message you want to send\n";
            cin.get(message, 10000, '\n');
            cin.ignore(100, '\n');
            cout<<"\nWho would you like to send it to ?\n";
            name_prompt(last, first);
            to_interact->send_message(message, last, first);
        }
        else if(choice == 2)
            to_interact->display();
        else if(choice == 3)
        {
            cout<<"Who would you like to add?\n";
            name_prompt(last, first);
            to_interact->add_contact(last, first);
        }
        else if(choice == 4)
        {
            cout<<"Who would you like to remove?\n";
            name_prompt(last, first);
            to_interact->remove_inContact(last, first);
        }
        else if(choice == 5)
        {
            cout<<"who would you like to retrieve?\n";
            name_prompt(last, first);
            to_interact->retrieve_inContact(last, first);
        }
        else if(choice == 6 && !(app_name[0] == 'L'))
            to_interact->special_functions();
    }while((choice != 7));

}
//step 1: check if the passed in arugemnts are the same as the data in to_comp - yes return true
//step 2: if comp is equal to rear - return false 
//step 3: call it self withthe next pointer
bool interface::inList(CLL_node * to_comp, const char * app_name, const char * last, const char * first)
{
    if(!to_comp->compare(app_name) && !to_comp->compare_account_name(last, first))
        return true;
    if(to_comp == rear)
        return false;
    return inList(to_comp->go_next(), app_name, last, first);
}
//step 1: allocate dest from source
//step 2: if not eaual to stop 
//step 3: call it self with the next pointer
void interface::copy(CLL_node * src, CLL_node *& dest, CLL_node * stop)
{
    dest = new CLL_node(*src);
    if(src == stop) 
        return;
    copy(src->go_next(), dest->go_next(), stop);
}
//step 1: prompt the user for both first and last name
void interface::name_prompt(char * last, char *first)
{
    cout<<"\nPlease enter the their first name: ";
    cin.get(first, 100, '\n');
    cin.ignore(100, '\n');
    cout<<"\nPlease enter the their last name: ";
    cin.get(last, 100, '\n');
    cin.ignore(100, '\n');
}
//step 1: copy the first name to the full name array 
//step 2: strcat the rest of the items
void interface::concat(char * full_name, const char * last, const char * first)
{
    strcpy(full_name,first);
    strcat(full_name, " ");
    strcat(full_name, last);
}
//step 1: call it self with the next pointer
//step 2: is rear == to remove
//step 3: delete on the back tracing
void interface::destroy(CLL_node *& remove)
{
    if(remove == rear)
        return;
    destroy(remove->go_next());
    delete remove;
}
//Destructir 
//step 1: delete all the apps allocated memory 
//step 2: delete rear if there is data
interface::~interface()
{
    for(int i = 0; i< 4; ++i)
        delete [] apps[i];
    delete [] apps;
    if(rear)
    {
        destroy(rear->go_next());
        delete rear;
    }
}
