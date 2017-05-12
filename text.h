///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//Massager in once app
//Homework # 2
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file manges text class. The class does espacific tasks in the program.
//The OOP design sumulates the connections from paper to actual program. 
//
//Descriptions:
//
//Text Class:
//The text class is the one of the key elemnets of the program. It purpose is to save 
//text for all platforms like facebook or line apps. The class semulates the container
//of text, amkes it eary for the user to read.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//TEXT = Superbase class
/////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#ifndef TEXT_H
#define TEXT_H
class text
{
    public:
        text();
        text(const text & to_copy);
        text(const char * to_copy);
        ~text();

        void add_text(const char * to_add);
        void display();
        void connect_next(text * to_connect); 
        bool compare(const char * to_comp);

    private:
        void copy(const text * src, text *& dest);
        void destroy(text *& head);
        void display(const text * head, int counter);

        char * _text;
        text * next;
};
#endif
