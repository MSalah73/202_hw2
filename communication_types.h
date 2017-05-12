///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
///This file manges generic communication, facebook, snapchat, line, and phone classes.
//Each class has a purpose and they have their own "Job" in the program. The OOP design 
//sumulates the connections from paper to actual program. 
//
//Descriptions:
//
///Generic communication Class:
//This class is the Abstract base class. Its purpose to enable the ability of dynamic binding 
//The class has some pure virtual function which allows us to have a pointer of base class 
//but depeding on the allocated object the right function of type virtual will be called.
//
//Facebook Class
//Facebook class contains the same virtual funtions as it base class and some unique functions
//to facebook. The unqiue functions are add, remove display , and retrieved a poked person.
//
//Snapchat Class
//Snapchat class contains the same virtual funtions as it base class and some unique functions
//to snapchat. The unqiue functions are add/change, and display a story.
//
//Line Class
//line class contains the same virtual funtions as it base class and some unique functions
//to line. The unqiue function is enable emojies so the user can send it to thier friends.
//
//Phone Class
//Phoen class contains the same virtual funtions as it base class and some unique functions
//to phone. The unqiue functions are add/ change, and display a phone number.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//Generic_communication -"Has a"-> BST node
//Facebook -"Is a"-> Generic communication
//Facebook -"Has a"-> LLL_poke_node
//Snapchat -"Is a"-> Generic communication
//Line -"Is a"-> Generic communication
//Phone -"Is a"-> Generic communication
/////////////////////////////////////////////////////////////////////////////////////////

#include "address_book.h"
class generic_communication //Abstrct base class 
{
    public:
        generic_communication();
        generic_communication(const generic_communication & to_copy);
        generic_communication(const char * last, const char * first);
        virtual ~generic_communication();

        virtual void display() = 0;
        virtual void retrieve_all_last(const char * last) = 0;
        virtual void retrieve_inContact(const char * last, const char * first) = 0;
        void send_message(const char * to_send, const char * last, const char * first);
        void add_contact(const char * last, const char * first);
        void remove_inContact(const char * last, const char * first);
        void remove_all_last(const char * last);

    protected:
        BST_node * successor(BST_node *& root);
        void retrieve_inContact(BST_node * root, const char * last, const char * first);
        void retrieve_all_last(BST_node * root, const char * last); 
        void display(BST_node * to_display);
        void remove_inContact(BST_node * root, const char * last, const char * first);
        void remove_all_last(BST_node *& root, const char * last);
        void remove_all(BST_node *& root);
        void add_contact(BST_node *& root, const char * last, const char * first);
        void send_message(BST_node * root, const char * to_send, const char * last, const char * first);
        bool inContact(BST_node * root, const char * last, const char * first);
        bool inContact(BST_node * root, const char * last);
        void copy(BST_node * src, BST_node *& dest);
        BST_node * root;
};
class facebook: public generic_communication // poke someone
{
    public:
        facebook();
        facebook(const facebook & to_copy);
        facebook(const char * last, const char * first);
        ~facebook();

        void display();
        void poke_someone(const char * last, const char * first);
        void display_poke_list();
        void retrieve_poked(const char * last, const char * first);
        void delete_poked(const char * last, const char * first);
        void retrieve_inContact(const char * last, const char * first);
        void retrieve_all_last(const char * last);
    private:
        void concat(char * to_copy, const char * last, const char * first);
        bool poke_someone(LLL_poke_node * head, const char * _name);
        void display_poke_list(LLL_poke_node * head);
        void retrieve_poked(LLL_poke_node * head, const char * _name);
        void delete_poked(LLL_poke_node *& head, const char * _name);
        void destroy(LLL_poke_node *& head);
        void copy(LLL_poke_node *& head, LLL_poke_node * src);

       LLL_poke_node * head; 
};
class snapchat: public generic_communication // story text wise  
{
    public:
        snapchat();
        snapchat(const snapchat & to_copy);
        snapchat(const char * last, const char * first);
        ~snapchat();
        
        void display();
        void display_story();
        void add_story(const char * _story);
        void retrieve_inContact(const char * last, const char * first);
        void retrieve_all_last(const char * last);
    private:
        char * story;
};
class line: public generic_communication // send emoji 
{
    public:
        line();
        line(const line & to_copy);
        line(const char * last, const char * first);
        ~line();

        void display();
        void send_emojis(const char * text, const char * last, const char * first);
        void retrieve_inContact(const char * last, const char * first);
        void retrieve_all_last(const char * last);
    private:
        void read();
        char ** emojis;
};
class phone: public generic_communication // display phone number 
{
    public:
        phone();
        phone(const phone & to_copy);
        phone(const char * last, const char * first);
        ~phone();

        void display();
        void update_phone_number(long unsigned int to_add); 
        void display_phone_number();
        void retrieve_inContact(const char * last, const char * first);
        void retrieve_all_last(const char * last);
    private:
        char * number;
};

