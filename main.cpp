#include <iostream>
#include "Film.h"
#include "Documentary.h"
#include "Family.h"
#include "List.h"
#include "Menu.h"
#include "Database.h"
#include "gtest_lite.h"

//#define DATABASE
#define TESTING

using namespace std;

int main()
{

#ifndef DATABASE

    Database filmtar("filmtar.txt");
    Menu menu;
    menu.mainmenu(filmtar);

#endif //DATABASE
#ifndef TESTING
    TEST(Test1,inheritance){
            Film newfilm("Aktion","Batman",2008, 120);
            Documentary newdocu("name",2010,134,"something");
            Family newfam("Instant Family",2019,120,12);

            std::string genre="Aktion";
            std::string title="Batman";

            EXPECT_EQ(newfilm.getgenre(),genre);
            EXPECT_EQ(newfilm.gettitle(),title);
            EXPECT_EQ(newfilm.getyear(),2008);
            EXPECT_EQ(newfilm.getlength(),120);
            genre="Documentary";
            title="name";
            std::string leiras="something";
            EXPECT_EQ(newdocu.getgenre(),genre);
            EXPECT_EQ(newdocu.gettitle(),title);
            EXPECT_EQ(newdocu.getyear(),2010);
            EXPECT_EQ(newdocu.getlength(),134);
            EXPECT_EQ(newdocu.getcontent(),leiras);
            title="Instant Family";
            genre="Family";

            EXPECT_EQ(newfam.getgenre(),genre);
            EXPECT_EQ(newfam.gettitle(),title);
            EXPECT_EQ(newfam.getyear(),2019);
            EXPECT_EQ(newfam.getlength(),120);
            EXPECT_EQ(newfam.getlimit(),12);

            Film operatorteszt;
            operatorteszt.settitle("Zack Snyder cut");
            operatorteszt.setgenre("Adventure");
            operatorteszt.setlength(130);
            operatorteszt.setyear(2021);
            newfilm=operatorteszt;
            title="Zack Snyder cut";
            genre="Adventure";
            EXPECT_EQ(newfilm.getgenre(),genre);
            EXPECT_EQ(newfilm.gettitle(),title);
            EXPECT_EQ(newfilm.getyear(),2021);
            EXPECT_EQ(newfilm.getlength(),130);


        } END

    TEST(Test2, List){
            List<int> newlist;
            newlist.add(1);
            newlist.add(9);
            newlist.add(11);
            newlist.add(99);
            long unsigned int eq= 4;
            EXPECT_EQ(newlist.length(), eq);
            List<int>::iterator it=newlist.begin(); //egyenloseg operatort is tesztelem ezzel
            EXPECT_EQ((*it),1);
            it++; //++ operatort is tesztelem ezzel
            EXPECT_EQ((*it),9);
            it++;
            EXPECT_EQ((*it),11);
            it++;
            EXPECT_EQ((*it),99);

            newlist.removeElement(it);

            for(List<int>::iterator iter=newlist.begin(); iter != newlist.end(); iter++){ //!= operatort is tesztelem ezzel
                if((*iter)==99){ //== is tesztelem ezzel, kiirna ha nem ismerne fel
                    throw "element was not deleted";
                }
            }
            EXPECT_NO_THROW(newlist.removeList());

        }END
    TEST(Test3, database){ //a test fajlt nem szabad modositani
            Database test("tesztfilmtar.txt");

            List<Film*>::iterator it=test.getfilms().begin();
            std::string title="Moana";
            std::string genre="Family";

            EXPECT_EQ((*it)->getgenre(), genre);
            EXPECT_EQ((*it)->gettitle(), title);
            EXPECT_EQ((*it)->getyear(),2019);
            EXPECT_EQ((*it)->getlength(),130);
            it++;
            genre="Documentary";
            title="name";
            EXPECT_EQ((*it)->getgenre(), genre);
            EXPECT_EQ((*it)->gettitle(), title);
            EXPECT_EQ((*it)->getyear(),2020);
            EXPECT_EQ((*it)->getlength(),110);
            it++;
            genre="Action";
            title="Batman";
            EXPECT_EQ((*it)->getgenre(), genre);
            EXPECT_EQ((*it)->gettitle(), title);
            EXPECT_EQ((*it)->getyear(),2008);
            EXPECT_EQ((*it)->getlength(),120);

            List<Film*> save=test.getfilms();

            List<Film*> set;
            set.add(new Film("Romantic","Love",2021,200));
            test.setlist(set);
            long unsigned int hossz=1;
            EXPECT_EQ(test.getfilms().length(), hossz);
            it=test.getfilms().begin();
            title="Love";
            genre="Romantic";
            EXPECT_EQ((*it)->getgenre(), genre);
            EXPECT_EQ((*it)->gettitle(), title);
            EXPECT_EQ((*it)->getyear(),2021);
            EXPECT_EQ((*it)->getlength(),200);
            test.setlist(save); //a visszamentest annyiban teszteli, hogy ha elinditom ujra a programot es a test jol lefut, akkor jol visszatoltotte a fajlokat
            it=set.begin();
            delete (*it); //ez egy specialis eset, mivel tudom, hogy csak egy elemet kell torolni

        } END


    TEST(Test4, Menu){
            List<Film*> teszt;
            teszt.add(new Film("Action","Batman",2008, 120));
            teszt.add(new Documentary("name",2010,134,"something"));
            teszt.add(new Family("Instant Family",2019,120,12));
            Menu test;
            std::string title="Batman";
            std::string genre="Action";
            EXPECT_NO_THROW(test.searchlength(120, teszt, 1));
            EXPECT_NO_THROW(test.searchlength(134, teszt, 1));
            EXPECT_NO_THROW(test.searchyear(2008, teszt, 1));
            EXPECT_NO_THROW(test.searchyear(2010, teszt, 1));
            EXPECT_NO_THROW(test.searchyear(2019, teszt, 1));
            EXPECT_NO_THROW(test.searchtitle(title, teszt, 1));
            title="name";
            EXPECT_NO_THROW(test.searchtitle(title, teszt, 1));
            title="Instant Family";
            EXPECT_NO_THROW(test.searchtitle(title, teszt, 1));
            EXPECT_NO_THROW(test.searchgenre(genre, teszt, 1));
            genre="Documentary";
            EXPECT_NO_THROW(test.searchgenre(genre, teszt, 1));
            genre="Family";
            EXPECT_NO_THROW(test.searchgenre(genre, teszt, 1));

            EXPECT_ANY_THROW(test.searchlength(300, teszt, 1));
            EXPECT_ANY_THROW(test.searchyear(2000, teszt, 1));
            title="hello";
            EXPECT_ANY_THROW(test.searchtitle(title, teszt, 1));
            genre="not existing";
            EXPECT_ANY_THROW(test.searchgenre(genre, teszt, 1));
            List<Film*>::iterator deleteit;
            List<Film*>::iterator it = teszt.begin();
            while ( it != teszt.end()) {
                deleteit = it;
                it++;
                delete (*deleteit);
            }

        }END
#endif








    return 0;
}
