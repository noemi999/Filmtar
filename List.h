#ifndef LISTA_H
#define LISTA_H

#include <iostream>


template<typename T>
class List {
    struct Node {
        T elem;
        Node *next;

        Node(const T &name) : elem(name) {
            next = nullptr;
        }

    };

    Node *first;
public:

    List() {
        first= nullptr;
    }

   List(List<T> &m) {
       first = nullptr;
        *this = m;
    }


    ~List() {
        removeList();}

    List<T> &operator=(const List<T> &m) {
        Node *current = m.first;
        removeList();
        while (current != nullptr) {
            add(current->elem);
            current = current->next;
        }
        return *this;
    }


    void add(const T &nev) {
        Node *uj = new Node(nev);
        if (first == nullptr) {
            first = uj;
            return;
        }

        Node *current = first;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = uj;

    }





    void removeList() {
        Node *current = first;
        Node *tobedeleted;

        while (current != nullptr) {
            tobedeleted = current;
            current = current->next;
            delete tobedeleted;

        }

        first= nullptr;
        if(first != nullptr){
            throw "failed to delete the list";
        }

    }

    class iterator {
        Node *current;

        iterator(Node *uj) {
            current = uj;
        }

    public:


        iterator() {
            current = nullptr;
        }



        iterator &operator++() {
            current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator it = *this;
            current = current->next;
            return it;
        }

        bool operator==(const iterator &name) const {
            return this->current == name.current;
        }

        bool operator!=(const iterator &name) const {
            return !(*this == name);
        }

        T &operator*() {
            return current->elem;
        }


        friend List;

    };

    iterator begin() {
        return iterator(first);
    }

    iterator end() {
        return iterator(NULL);
    }

    iterator removeElement(iterator elementtodelete) {
        Node *current = first;
        if (current == nullptr) {
            return elementtodelete;
        }


        while (current->next != elementtodelete.current && current != nullptr && current != elementtodelete.current) { // a mozgora azert nezem meg a torlendo elemet, mert lehetseges hogy csak egy elemet tarol a tarolo amit torolni szeretnek
                current = current->next;
        }

        if (current == nullptr) {
            throw ("not existing element");
        }


        current->next = elementtodelete.current->next;
        current = current->next;
        delete elementtodelete.current;
        return iterator(current);
    }

    size_t length() {
        size_t Length = 0;
        for (iterator it = begin(); it != end(); it++) {
            Length++;
        }
        return Length;
    }


};



#endif // LISTA_H
