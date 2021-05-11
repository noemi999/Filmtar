//
// Created by noncs on 2021. 04. 01..
//

#ifndef PROG2HF2021_DATABASE_H
#define PROG2HF2021_DATABASE_H

#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
#include "Film.h"
#include "Documentary.h"
#include "Family.h"
#include "List.h"


class Database {
    List<Film*> films;
public:
    Database(std::string filename) {
        std::ifstream fs;
        fs.open(filename);
        if (!fs.is_open()) {
            throw "not existing file";
        }

        std::string str = " ";
        if (!(fs.peek() == std::ifstream::traits_type::eof())) {
            while (!fs.eof()) {
                std::getline(fs, str);
                std::string::size_type n = str.find(';');
                std::string oszt = str.substr(0, n);
                if (oszt == "Family") {
                    films.add(new Family(str.substr(n + 1, str.length() - n - 1)));
                }
                else if (oszt == "Documentary") {
                    films.add(new Documentary(str.substr(n + 1, str.length() - n - 1)));
                } else {
                    films.add(new Film(str.substr(0, str.length())));
                }
            }

        }

        fs.close();
    }

    List<Film *> &getfilms() { return films; }

    void setlist(List<Film *> &list) { films = list; }


    void save(std::string filename, List<Film*> list) {

        std::ofstream of;
        of.open(filename);

        for (List<Film *>::iterator it = list.begin(); it != list.end();) {
            (*it)->save(of);
            it++;
            if (it != list.end()) { of << std::endl; }
        }


        of.close();


    }

   ~Database(){
       films.removeList();
            }









};


#endif //PROG2HF2021_FAJLKEZELES_H
