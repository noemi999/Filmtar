#ifndef FAMILY_H
#define FAMILY_H

#include "Film.h"
#include <iostream>
#include <fstream>



class Family : public Film {
    int limit_;
public:

    Family(std::string title, int year, int length = 0, int limit = 0) : Film("Family", title, year, length), limit_(limit) {}



    Family(std::string row) {
        setgenre("Family");
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
                    setlimit(stoi(data));
                    break;
                default:
                    throw "tul sok data";
                    break;

            }
            a++;
            last = i;
        }
        if(a<4){
            throw "not enough data Family";
        }
    }

    ~Family(){}

    void setlimit(int limit) { limit_ = limit; }

    int getlimit() const { return limit_; }

    void write() {
        Film::write();
        std::cout << " Age limit: +" << getlimit() << std::endl << std::endl;
    }

    std::ostream &save(std::ostream &os) {
        os << genre_ << ";" << title_ << ";" << year_ << ";" << length_ << ";" << limit_ << ";" ;
        return os;
    }


};

#endif // FAMILY_H
