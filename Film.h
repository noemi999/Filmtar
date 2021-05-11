#ifndef FILM_H
#define FILM_H

#include <string>
#include <iostream>
#include <fstream>


class Film {
protected:
    std::string title_;
    int year_;
    int length_;
    std::string genre_;
public:

    Film() : title_(""), year_(0), length_(0), genre_("") {}

    Film(std::string genre, std::string title, int year, int length = 0) : title_(title), year_(year), length_(length),
                                                                           genre_(genre) {}

    Film(std::string title, int year, int length = 0) : title_(title), year_(year), length_(length) {}

    virtual ~Film(){}





    Film(std::string row) {
        std::string::size_type last = 0;
        int a = 0;
        for (std::string::size_type i = row.find(';', last + 1); i != std::string::npos; i = row.find(';', last + 1)) {
            std::string data = row.substr(last == 0 ? 0 : last + 1, i - last - (last == 0 ? 0 : 1));
            switch (a) {
                case 0:
                    setgenre(data);
                    break;
                case 1:
                    settitle(data);
                    break;
                case 2:
                    setyear(stoi(data));
                    break;
                case 3:
                    setlength(stoi(data));
                    break;
                default:
                    //throw "too much data";
                    break;

            }
            a++;
            last = i;
        }
        if (a < 4) {
            throw "not enough data";
        }
    }


    void settitle(std::string title) { title_ = title; }

    void setyear(int year) { year_ = year; }

    void setlength(int length) { length_ = length; }

    void setgenre(std::string genre) { genre_ = genre; }

    std::string gettitle() const { return title_; }

    int getyear() const { return year_; }

    int getlength() const { return length_; }

    std::string getgenre() const { return genre_; }

    virtual void write() {
        std::cout << " Genre: " << getgenre() << " Title: " << gettitle() ;
        std::cout << " Length: " << getlength() ;
        std::cout << " Year: " << getyear() << std::endl << std::endl;
    }


    Film operator=(Film f) {
        genre_ = f.getgenre();
        title_ = f.gettitle();
        length_ = f.getlength();
        year_ = f.getyear();
        return *this;
    }


    virtual std::ostream &save(std::ostream &os) {
        os << genre_ << ";" << title_ << ";" << year_ << ";" << length_ << ";";
        return os;
    }



};

#endif // FILM_H
