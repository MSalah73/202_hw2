///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
///This file manges name, LLL_Poke_node , and LLL_node. Each class has a
//Porpuse and they have their own "Job" in the program. The OOP design 
//sumulates the connections from paper to actual program. 
//
//Descriptions:
//
///Name Class:
//The name class is the core of main hub base class of the program. It 
//manages the name of apps, users, contacts, and many classes. This class is the most connect
//class in the prigram. The class can be considered as the main core of the program as 
//it is the base class for almost every class.
//
//LLL_Poke_Node Class
//The LLL poke class manages the all poked firends list. This class is spicifly for facebook
//app. Facebooks special function would iteracts with this class. The class can insert, remove
//,retrived and many more funtions.
//
//LLL_Node Class
//The LLL_node class is the list contacts with the same last name. Each node in the tree 
//can store mutile eople with the same name. This help for faster traversal to get the 
//data/contacs in the last easly and not as expensive as have a tree only.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//LLL_poke_node -"Is a"-> Name
//LLL_node -"Is a"-> Name 
//LLL_node -"Has a"-> Name 
/////////////////////////////////////////////////////////////////////////////////////////
#include "text.h" 
#ifndef NAME_H
#define NAME_H
class name
{
    public:
        name();
        name(const char * to_add);
        name(const name & to_copy);
        ~name();

        void display() const;
        void change_name(const char * to_change);
        void set_name(const name & to_set);
        int compare(const name & to_comp) const;
        int compare(const char * to_comp) const; 

    protected:
        char * _name; 
};
class LLL_poke_node: public name
{
    public:
        LLL_poke_node();
        LLL_poke_node(const LLL_poke_node & to_copy);
        LLL_poke_node(const char * to_copy);
        ~LLL_poke_node();

        LLL_poke_node *& go_next();
        void add_aPoke();
        void connect_next(LLL_poke_node * to_connect);
        void display();

    protected:
         LLL_poke_node * next;
         int times;
};

class LLL_node: public name 
{
    public:
        LLL_node();
        LLL_node(const LLL_node & to_copy);
        LLL_node(const name & to_copy);
        LLL_node(const char * to_copy);
        ~LLL_node();

        LLL_node *& go_next();
        void connect_next(LLL_node * to_connect);
        void display();
        void add_text(const char * to_add);

    protected:
         text * text_stack;
         LLL_node * next;
         
};
#endif
