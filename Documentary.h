#ifndef DOKUMENTUM_H
#define DOKUMENTUM_H

#include "Film.h"
#include <iostream>
#include <fstream>


class Documentary : public Film {
    std::string content_;
public:
    Documentary(std::string title, int year, int length = 0, std::string content = "") : Film("Documentary", title, year, length), content_(content) {}

    ~Documentary(){}

    Documentary(std::string row) {
        setgenre("Documentary");
        std::string::size_type last = 0;
        int a = 0;
        for (std::string::size_type i = row.find(';', last + 1); i != std::string::npos; i = row.find(';', last + 1)) {
            std::string data = row.substr(last == 0 ? 0 : last + 1, i - last - (last == 0 ? 0 : 1));
            switch (a) {
                case 0:
                    settitle(data);
                    break;
                case 1:
                    setyear(stoi(data));
                    break;
                case 2:
                    setlength(stoi(data));
                    break;
                case 3:
                    setcontent(data);
                    break;
                default:
                    throw "too much data";
                    break;

            }
            a++;
            last = i;
        }
        if(a<4){
            throw "not enough data";
        }
    }

    void setcontent(std::string content) { content_ = content; }

    std::string getcontent() const { return content_; }

    void write() {
        Film::write();
        std::cout << " content:" << getcontent() << std::endl << std::endl;
    }


    std::ostream &save(std::ostream &os) {
        os << genre_ << ";" << title_ << ";" << year_ << ";" << length_ << ";" << content_ << ";" ;
        return os;
    }


};

#endif // DOKUMENTUM_H
