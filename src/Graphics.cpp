//
// Created by david on 20.06.2021.
//

#include <menu.h>
#include "Graphics.h"
#include <string>

void print_menu(WINDOW *w, int highlight, std::vector<std::string> &choices)
{
    int x = 2;
    int y = 2;
    box(w, 0, 0);

    for(int i = 0; i < choices.size() ; i++)
    {
        const char *a = choices[i].c_str();
        if(highlight == i + 1)
        {
            wattron(w, A_REVERSE);
            mvwprintw(w, y, x, "%s", a);
            wattroff(w, A_REVERSE);
        }
        else
            mvwprintw(w, y, x, "%s", a);
        y++;

   }
    wrefresh(w);
}


void printBox(WINDOW *w , const string &text, int yoffset , int xoffset ){

    box(w, 0, 0);

    wattron(w, A_REVERSE);
    mvwprintw(w, 2+yoffset, 2+xoffset, "%s", text.c_str());
    wattroff(w, A_REVERSE);

    wrefresh(w);
}


void drawCardMenu (WINDOW *w, int highlight, vector<shared_ptr<CCard>> &src , int gold , int mana){



    int x = 4;
    int y = 4;
    box(w, 0, 0);

    WINDOW *desc = newwin(20, 60, 5, 40);
    box(desc,0,0);

    start_color();
    init_pair(0, COLOR_BLACK , COLOR_WHITE );
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_BLUE);

    if(src.empty()){
        wrefresh(w);
        return;
    }
    for(int i = 0 ; i < src.size() ; i++){
        const char *a = src[i]->getName().c_str();
        if(highlight == i + 1)
        {
            wattron(w, A_REVERSE);
            mvwprintw(w, y, x, "%s", a);
            wattroff(w, A_REVERSE);
        }
        else
            if(src[i]->canBePlayed(mana, gold)){
                if(src[i]->price() == "Gold")
                    wattron(w, COLOR_PAIR(1));
                else
                    wattron(w, COLOR_PAIR(2));
                mvwprintw(w, y, x, "%s", a);
                wattroff(w, COLOR_PAIR(1));
                wattroff(w, COLOR_PAIR(2));
            }
            else
                mvwprintw(w, y, x, "%s", a);
        y++;
    }

    drawCardDesc(desc, src[highlight-1]->getDesc() , src[highlight-1]->getEffect(), src[highlight-1]->price());

    wrefresh(w);
    wrefresh(desc);
}

void drawCardDesc (WINDOW *w, const string &desc, const SEffect &eff, const string &price){
    int cnt=0;

    string formated;

    string word = "";
    for (auto x : desc)
    {
        if (x == ' ' || x == '\0')
        {
            cnt+=word.length();
            formated += word + " ";
            if(cnt>40){
                cnt=0;
                formated += '\n';
                formated += "  ";
            }
            word = "";
        }
        else {
            word = word + x;
        }
    }

    if(cnt>45){
        formated += '\n';
        formated += "  ";
    }
    formated += word + " ";


    mvwprintw(w, 2, 2, "%s\n\n  %s:%d, yourHP:%d, selfPOW:%d, enemyHP:%d, enemyPOW:%d" ,formated.c_str(),price.c_str() ,-eff.price, eff.hpSelf, eff.dmgSelf, eff.hpEnemy, eff.dmgEnemy);

}

