#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include "List.h"
#include "Film.h"
#include "Documentary.h"
#include "Family.h"
#include "Database.h"


class Menu
{
public:

    Menu(){}

    void searchtitle(std::string search, List<Film*> films, bool test=false) {
        bool exist=false;

        for(List<Film*>::iterator it=films.begin(); it != films.end(); it++){
            if((*it)->gettitle().compare(search) == 0){
                (*it)->write();
                exist=true;
            }
        }
        if(exist == false){
            std::cout << "not existing element"<<std::endl;
            if(test!=false){
                throw "not existing movie";
            }
        }

    }

    void searchlength(int search, List<Film*> films, bool test=false){
        bool exist=false;
        for(List<Film*>::iterator it=films.begin(); it != films.end(); it++){
            if((*it)->getlength() == search){
                (*it)->write();
                exist=true;
            }
        }
        if(exist == false){
            std::cout << "not existing element in the database"<<std::endl;
            if(test!=false){
                throw "not existing movie";
            }
        }
    }

    void searchyear(int search, List<Film*> films, bool test=false){
        bool exist=false;
        for(List<Film*>::iterator it=films.begin(); it != films.end(); it++){
            if((*it)->getyear() == search){
                (*it)->write();
                exist=true;
            }
        }
        if(exist == false){
            std::cout << "not existing element in the database"<<std::endl;
            if(test!=false){
                throw "not existing movie";
            }
        }
    }

    void searchgenre(std::string search, List<Film*> films, bool test=false){
        bool exist=false;
        for(List<Film*>::iterator it=films.begin(); it != films.end(); it++){
            if((*it)->getgenre().compare(search) == 0){
                (*it)->write();
                exist=true;
            }
        }
        if(exist == false){
            std::cout << "not existing element in the database"<<std::endl;
            if(test!=false){
                throw "not existing movie";
            }
        }
    }

    void searching(List<Film*> films) {
        std::cout << "searching based on (push the appropriate button):" << std::endl << " title: 0" << std::endl
                  << " genre: 1" << std::endl << " year: 2" << std::endl << "length: 3"
                  << std::endl << std::endl;
        int n;
        std::cin >> n;

        switch (n) {
            case 0:{
                std::string search;
                std::cout << "title:";
                std::getline(std::cin, search);
                if(search.empty()) getline(std::cin, search);
                searchtitle(search, films);
                break;}
            case 1: {
                std::string search;
                std::cout << "genre: ";
                std::getline(std::cin, search);
                if(search.empty()) getline(std::cin, search);
                searchgenre(search, films);
                break;
            }
            case 2:{
                int search;
                std::cout << "year: ";
                std::cin >> search;
                searchyear(search, films);
                break;
            }
            case 3:{
                int search;
                std::cout << "length: ";
                std::cin >> search;
                searchlength(search, films);
                break;
            }
            default:
                break;





        }
    }



    void mainmenu(Database film){
        bool run=true;


            while(run) {
                std::cout << "What do you want to do? (push the appropriate button)" << std::endl << " searching: 0 " << std::endl
                          << " remove element from the list: 1 " << std::endl << " add element to the list: 2 "<< std::endl << "close the window: 3 " << std::endl;

                int n;
                std::cin >> n;
                run=false;
                switch (n) {
                    case 0: {
                        searching(film.getfilms());
                        run= true;
                        break;
                    } //kereses fuggveny
                    case 1: {
                        if(film.getfilms().begin() == film.getfilms().end()){
                            std::cout<<"the database is empty";
                            run=true;
                            break;
                        }
                        std::string titletodelete;
                        int yeartodelete;
                        std::cout << "title:  " << std::endl;
                        std::getline(std::cin, titletodelete);
                        if(titletodelete.empty()) getline(std::cin, titletodelete);
                        std::cout << "year: " << std::endl;
                        std::cin >> yeartodelete;
                        bool exist=false;

                        List<Film*>::iterator it=film.getfilms().begin();
                        List<Film*>::iterator elementtodelete;
                        while(it != film.getfilms().end()) {
                            if((*it)->gettitle().compare(titletodelete) == 0 && (*it)->getyear() == yeartodelete){
                                it = film.getfilms().removeElement(it);

                                exist=true;
                            }

                            else
                                ++it;
                        }
                        if(exist == false){
                            std::cout <<"you try to delete a not existing movie from the database" << std::endl;
                        }
                        run= true;
                        break;
                    } //torles fuggveny
                    case 2: {
                        std::string genre;
                        std::string title;
                        int length;
                        int year;
                        run=false;
                        std::cout << "genre: ";
                        std::getline(std::cin, genre);
                        if(genre.empty()) getline(std::cin, genre);
                        std::cout << "title: ";
                        std::getline(std::cin, title);
                        if(title.empty()) getline(std::cin, title);
                        std::cout << "length: ";
                        std::cin >> length;
                        std::cout << "year: ";
                        std::cin >> year;
                        if(genre.compare("Documentary") == 0){
                            std::string content;
                            std::cout << "content: ";
                            std::getline(std::cin, content);
                            if(content.empty()) getline(std::cin, content);
                            film.getfilms().add(new Documentary(title, year, length, content));
                            run= true;
                        }
                        else if(genre.compare("Family") == 0){
                            int limit;
                            std::cout << "age limit: ";
                            std::cin >> limit;
                            film.getfilms().add(new Family(title, year, length, limit));
                            run= true;
                        }
                        else {
                            film.getfilms().add(new Film(genre, title, year, length));
                            run= true;
                        }
                        if(run == true){
                            std::cout << "film added to the database" << std::endl;

                        }
                        else{
                            std::cout << "couldn't add the film to the database"<< std::endl;
                        }

                        break;
                    } //hozzaadas fuggveny
                    case 3:
                        run = false;
                        break;
                    default:
                        break;
                }

            }
        film.save("filmtar.txt", film.getfilms());

    }

    ~Menu(){}











};

#endif // MENU_H