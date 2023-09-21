/*
Data Structures
Project 2
Driver: Max Aubuchon
Navigator: Dawson Murphy
*/

#include "NotationConverter.hpp"

List::List(){  //constructor
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}

List::~List(){  //destructor
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}

//is list empty
bool List::empty() const{
    return (header->next == trailer);
}

//front of list
const Elem& List::front() const{
    return header->next->elem;
}

//back of list
const Elem& List::back() const{
    return trailer->prev->elem;
}

//add to list
void List::add(Node* v, const Elem& e) {
    Node* u = new Node;  
    u->elem = e; 
    u->next = v; 
    u->prev = v->prev; 
    v->prev->next = u;
    v->prev = u;
}

//add to front of list
void List::addFront(const Elem& e){
    add(header->next, e);
}

//add to back of list
void List::addBack(const Elem& e){
    add(trailer, e);
}

//remove from list
void List::remove(Node* v) { 
    Node* u = v->prev; 
    Node* w = v->next; 
    u->next = w; 
    w->prev = u;
    delete v;
}

//remove from front of list
void List::removeFront(){
    remove(header->next);
}

//remove from back of list
void List::removeBack(){
    remove(trailer->prev);
}

Deque::Deque() : D(), n(0) { }  //constructor

//size of deque
int Deque::size() const {
    return n;
}

//is deque empty
bool Deque::empty() const{
    return n==0;
}

//front of deque
const Elem& Deque::front(){
    if (empty()){
        throw "empty deque";
    }
    return D.front();
}

//back of deque
const Elem& Deque::back(){
    if (empty()){
        throw "empty deque";
    }
    return D.back();
}

//adds e to the front of deque D
void Deque::addFront(const Elem& e){
    D.addFront(e);
    n++;
}

//adds e to the end of deque D
void Deque::addBack(const Elem& e){
    D.addBack(e);
    n++;
}

//removes first node in deque D
void Deque::removeFront(){
    if (empty()){
        throw "empty deque";
    }
    D.removeFront();
    n--;
}

//removes last node in deque D
void Deque::removeBack(){
    if (empty()){
        throw "empty deque";
    }
    D.removeBack();
    n--;
}

//tests if string is a letter
bool isLetter(std::string x){
    return (x >= "a" && x <= "z") || (x >= "A" && x <= "Z");
}

//tests if string is an operator
bool isOperator(std::string x){
    return (x == "+") || (x == "-") || (x == "*") || (x == "/");
}

//converts from postfix to infix
std::string NotationConverter::postfixToInfix(std::string inStr){
    //creates deque called Deque
    Deque Deque;

    //Empties out the deque
    while(Deque.empty() == false){     
        Deque.removeFront();
    }

    //creates string to act as placeholder
    std::string temp;
    temp = inStr[0];

    //iterates through the string
    for(int i=0; inStr[i] != '\0'; i++){
        temp = inStr[i];

        //checks if temp is a letter
        if (isLetter(temp) == true){
            Deque.addFront(temp);
        }
        //checks if temp is an operator
        else if (isOperator(temp)){
            std::string one = Deque.front();
            Deque.removeFront();
            std::string two = Deque.front();
            Deque.removeFront();
            Deque.addFront("(" + two + " " + temp + " " + one + ")");
        }
        //checks if temp is a space
        else if (temp == " "){
            continue;
        }
        //throws if temp is not any of those
        else{
            throw("Invalid character.\n");
        }
    }
    //the front of the deque contains the solution
    return Deque.front();
}

//converts from postfix to prefix
std::string NotationConverter::postfixToPrefix(std::string inStr){
    //creates deque
    Deque Deque;

    //Empties out the deque
    while(Deque.empty() == false){    
        Deque.removeFront();
    }

    //creates string as placeholder
    std::string temp;
    temp = inStr[0];

    //iterates through the string
    for(int i=0; inStr[i] != '\0'; i++){
        temp = inStr[i];

        //checks if temp is a letter
        if (isLetter(temp)){
            Deque.addBack(temp);
        }
        //checks if temp is an operator
        else if (isOperator(temp)){
            std::string one = Deque.back();
            Deque.removeBack();
            std::string two = Deque.back();
            Deque.removeBack();
            if (Deque.empty()){
                Deque.addBack(temp + " " + two + " " + one);
            }
            else{
                Deque.addBack(temp + " " + two + " " + one);
            }
        }
        //checks if temp is a space
        else if (temp == " "){
            continue;
        }
        //throws if temp is none of those
        else{
            throw("Invalid character.\n");
        }
    }
    //the front of the deque contains the solution
    return Deque.front();
}

//converts from infix to postfix
std::string NotationConverter::infixToPostfix(std::string inStr){
    //creates deque
    Deque Deque;

    //Empties out the deque
    while(Deque.empty() == false){     
        Deque.removeFront();
    }

    //creates a new string
    std::string pf;

    //creates string as placeholder
    std::string temp;
    temp = inStr[0];

    //iterates through the string
    for(int i=0; inStr[i] != '\0'; i++){
        temp = inStr[i];

        //checks if temp is a letter
        if (isLetter(temp)){
            pf.append(temp);
            pf.append(" ");
        }
        //checks if temp is an operator
        else if (isOperator(temp)){
            Deque.addFront(temp);
        }
        //checks if temp is a space
        else if (temp == " "){
            continue;
        }
        //checks if temp is a (
        else if (temp == "("){
            Deque.addFront(temp);
        }
        //checks if temp is a )
        else if (temp == ")"){
            pf.append(Deque.front());
            pf.append(" ");
            Deque.removeFront();
            Deque.removeFront();
        }
        //throws if temp is none of those
        else{
            throw("Invalid character.\n");
        }
    }

    pf.erase(std::prev(pf.end()));

    //pf is the solution
    return pf;
}

//converts from prefix to postfix
std::string NotationConverter::prefixToPostfix(std::string inStr){
    //creates deque
    Deque Deque;

    //Empties out the deque
    while(Deque.empty() == false){     
        Deque.removeFront();
    }

    //reverses the string
    reverse(inStr.begin(), inStr.end());

    //creates a placeholder string
    std::string temp;
    temp = inStr[0];

    //iterates through the string
    for(int i=0; inStr[i] != '\0'; i++){
        temp = inStr[i];

        //is temp a letter
        if (isLetter(temp)){
            Deque.addBack(temp);
        }
        //is temp an operator
        else if (isOperator(temp)){
            std::string one = Deque.back();
            Deque.removeBack();
            std::string two = Deque.back();
            Deque.removeBack();
            if (Deque.empty()){
                Deque.addBack(one + " " + two + " " + temp);
            }
            else{
                Deque.addBack(" " + one + " " + two + " " + temp);
            }
        }
        //is temp a space
        else if (temp == " "){
            continue;
        }
        //throws otherwise
        else{
            throw("Invalid character.\n");
        }
    }
    //the front of the deque contains the solution
    return Deque.front();
}

//converts from infix to prefix
std::string NotationConverter::infixToPrefix(std::string inStr){

    //converts from infix to postfix
    std::string str2 = NotationConverter::infixToPostfix(inStr);

    //converts from postfix to prefix
    std::string str3 = NotationConverter::postfixToPrefix(str2);

    //str3 contains the solution
    return str3;
}

//converts from prefix to infix
std::string NotationConverter::prefixToInfix(std::string inStr){

    //converts from prefix to postfix
    std::string str2 = NotationConverter::prefixToPostfix(inStr);

    //converts from postfix to infix
    std::string str3 = NotationConverter::postfixToInfix(str2);

    //str3 contains the solution
    return str3;
}