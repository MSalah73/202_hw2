///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file manges BST node class. The class does espacific tasks in the program.
//The OOP design sumulates the connections from paper to actual program. 
//
//Descriptions:
//
///BST Node Class:
//The name class is the core of main hub base class of the program. It 
//manages the contast with similar last names. The class is a name becouse each node
//has a a spasific last name. This class is the core orgonazior of the program. 
//The class can be considered as the main core of the program as 
//it is the bisis of the data stcutoure of the tree of contasts.
//
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//BST_node -Is a"-> name
//BST_node -"Has a-> LLL_node
/////////////////////////////////////////////////////////////////////////////////////////
#include "name.h"
class BST_node : public name //Last name
{
    public:
        BST_node();
        BST_node(const BST_node & to_copy);
        BST_node(const char * _last, const char * first);
        ~BST_node();

        BST_node *& go_right();
        BST_node *& go_left();
        void connect_right(BST_node * to_connect);
        void connect_left(BST_node * to_connect);
        void add_contact(const char * _last, const char * first);
        void display() const;
        void retrieve(const char * first);
        bool remove_contact(const char * first);
        void add_text(const char * to_add, const char * first);
        bool inList(const char * first);

    protected:
        LLL_node * head;
        BST_node * right;
        BST_node * left;

        void concat_names(char * full_name, const char * first);
        void retrieve(const char * to_comp, LLL_node * to_find) const;
        void copy(LLL_node * src, LLL_node *& dest);
        void display(LLL_node * to_display) const;
        bool remove_contact(const char * to_comp, LLL_node *& to_remove);
        void destroy_list(LLL_node *& head);
        bool inList(const char * _name, LLL_node * to_comp);
        void add_text(const char * to_add, const char * _name, LLL_node *& find);
};
