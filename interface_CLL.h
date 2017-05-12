///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
///This file manges interface , and CLL_node. Each class has a
//Porpuse and they have their own "Job" in the program. The OOP design 
//sumulates the connections from paper to actual program. 
//
//Descriptions:
//
///CLL_node Class:
//The CLL_node handles manayy thing, one of such is allcoacting the current type of drived
//class to the app pointer.The CLL have the RTTI and dynamic binding all in this class. Its 
//in a from of CLL_node so we can have and expanding list of apps that ould like to choses
//The CLL also have the special funnctions for evevry class that needs it for example. facebook
//have a special functions to eather poke a person , removed a poked person, and other more 
//funtions. even thought this class is a node, it have the fuctionaliy to orginazed the functions 
//depeding on the type. The name is the base class for each CLL_node thats because I wanted to minimize
//the useage of RTTI. The name help me to use the right function right away.
//
//interface Class
//The interface class is very important, as its the class that manges all operations and 
//orginaize them. The class communcate with the user to fits thier needs. It connects all
//the lines from place to anothers.
//
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//interface -"Has a"-> CLL_node 
//CLL_node_node -"Is a"-> Name 
//CLL_node -"Has a"-> Name and generic_communication pointer
/////////////////////////////////////////////////////////////////////////////////////////

#include "communication_types.h"

class CLL_node: public name
{
    public:
        CLL_node();
        CLL_node(const CLL_node & to_copy);
        CLL_node(unsigned int to_add, const char * last, const char * first);
        ~CLL_node();

        CLL_node *& go_next();
        void connect_next(CLL_node * to_connect);
        
        void display();
        void send_message(const char * to_send, const char * last, const char * first);
        void add_contact(const char * last, const char * first);
        void remove_inContact(const char * last, const char * first);
        void retrieve_inContact(const char * last, const char * first);
        bool compare_account_name(const char * last, const char * first);
        void display_account_name();
        void special_functions();
    protected:
        bool contained();
        void special_snap();
        void special_facebook();
        void special_line(const char * to_send, const char * last, const char * first);
        void special_phone();
        void name_prompt(char * last, char * first);
        void concat(char * full_name, const char * last, const char * first);
        name * account_name;
        generic_communication * app;
        CLL_node * next;

};
class interface
{
    public:
        interface();
        interface(const interface & to_copy);
        interface(const char * to_copy);
        ~interface();

        void manager();
    private:
        void add_menu();
        void remove_retrieve_menu(int request);
        void app_interactions_menu(CLL_node * to_interact, const char * app_name);
        void name_prompt(char * last, char * first);
        void display_apps(CLL_node * to_display);
        int remove_app(CLL_node *& to_remove, CLL_node * prev, const char * app_name, const char * last, const char * first);
        int add_app(CLL_node *& rear, unsigned int to_add, const char * last, const char * first);
        void retrieve_app(CLL_node * to_retrieve, const char * app_anme, const char * last, const char * first);
        bool inList(CLL_node * rear, const char * app_name, const char * last, const char * first);
        void copy(CLL_node * src, CLL_node *& dest, CLL_node * stop);
        void concat(char * full_name, const char * last, const char * first);
        void destroy(CLL_node *& remove);
        CLL_node * rear;
        char ** apps;
};
