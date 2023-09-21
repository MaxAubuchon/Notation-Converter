/*
Data Structures
Project 2
Driver: Max Aubuchon
Navigator: Dawson Murphy
*/

//includes all the files we need
#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H
#include "NotationConverterInterface.hpp"
#include <string>
#include <iostream>
#include <algorithm>

//defines the type Elem
typedef std::string Elem;

//class for the nodes
class Node{
    private:
        Elem elem;
        Node* prev;
        Node* next;
        friend class List;
};

//class for the doubly linked list
class List{
    public:
        List(); //constructor
        ~List(); //destructor
        bool empty() const; //tests if empty
        const Elem& front() const;  //gives first element
        const Elem& back() const;   //gives last element
        void addFront(const Elem& e);   //adds element to the front
        void addBack(const Elem& e);    //adds element to the back
        void removeFront();     //removes element from the front
        void removeBack();      //removes element from the back

    private:
        Node* header;       //creates the header
        Node* trailer;      //creates the trailer

        friend class Deque;    
        friend class NotationConverter;
    
    protected:
        void add(Node* v, const Elem& e);   //adds a node after e
        void remove(Node* v);       //removes a node
};

//class for the deque
class Deque{
    public:
        Deque(); //constructor
        int size() const;       //gives size of deque
        bool empty() const;     //is deque empty
        const Elem& front();    //gives front of deque
        const Elem& back();     //gives back of deque

        void addFront(const Elem& e);   //adds element to front of deque
        void addBack(const Elem& e);    //adds element to back of deque
        void removeFront();     //removes front of deque
        void removeBack();      //removes back of deque

    private:
        List D;
        int n;

        friend class NotationConverter;
};

//Class that does the functions
class NotationConverter:public NotationConverterInterface{
    public:
        //Converts from postfix
        std::string postfixToInfix(std::string inStr);
        std::string postfixToPrefix(std::string inStr);

        //Converts from infix
        std::string infixToPostfix(std::string inStr);
        std::string infixToPrefix(std::string inStr);

        //Converts from prefix
        std::string prefixToInfix(std::string inStr);
        std::string prefixToPostfix(std::string inStr);
};

#endif