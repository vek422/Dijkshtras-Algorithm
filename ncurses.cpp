#include<ncurses.h>
#include"Utility.h"
#include<fstream>
#include<iostream>
#include"shortest_path.cpp"
using namespace std;
void clean(WINDOW *win2)
{
            wmove(win2,15,3);wclrtoeol(win2);
            wmove(win2,16,3);wclrtoeol(win2);
            wmove(win2,4,21);wclrtoeol(win2);
            wmove(win2,6,26);wclrtoeol(win2);
            wmove(win2,10,3);wclrtoeol(win2);
            wmove(win2,12,3);wclrtoeol(win2);
            wmove(win2,14,0);wclrtoeol(win2);
            wmove(win2,15,0);wclrtoeol(win2);
            wmove(win2,16,0);wclrtoeol(win2);
            wmove(win2,17,0);wclrtoeol(win2);
            wmove(win2,18,0);wclrtoeol(win2);
            wmove(win2,19,0);wclrtoeol(win2);
            wmove(win2,20,0);wclrtoeol(win2);
            wmove(win2,21,0);wclrtoeol(win2);
}
ifstream fin;


int main()
{
    
    initscr();
    start_color();
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_BLUE,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    curs_set(0);
    // noecho();
    int yMax,xMax;
    getmaxyx(stdscr,yMax,xMax);
    //print the fancy text
    print_title();
    move(7,10);
    hline(ACS_HLINE, xMax-25);//horizontal line

    wattron(stdscr,COLOR_PAIR(2));
    mvprintw(10,10,"A Program To Calculate Minimun Distance Between Two Cities");
    wattroff(stdscr,COLOR_PAIR(2));
    wattron(stdscr,COLOR_PAIR(3));
    mvwprintw(stdscr,10,80,"F1:EXIT | F2:INSERT");
    wattroff(stdscr,COLOR_PAIR(3));
    //create window for displaying the cities
    WINDOW *win = newwin(25,20,12,10);
    WINDOW *win2 = newwin(25,60,12,80);
    wattron(win,COLOR_PAIR(4));
    mvwprintw(win,1,5,"CITIES");
    wattroff(win,COLOR_PAIR(4));
//displaying cities
    fin.open("cities.txt");
    int nV;
    fin>>nV;
    string Cities[nV];
    int x;
    for(int i=0;i<nV;i++)
     { fin>>x;
       fin>>Cities[x];
     }
    fin.close();

    for(int i=0;i<nV;i++)
    {
        mvwprintw(win,i+3,5,"%d",i);
        mvwprintw(win,i+3,7,Cities[i].c_str());
    }

    //displaying inputs to take
    wattron(win2,COLOR_PAIR(5));
    mvwprintw(win2,2,3,"Enter Respective Location Index");
    wattroff(win2,COLOR_PAIR(5));
    mvwprintw(win2,4,3,"Source Location : ");
    mvwprintw(win2,6,3,"Destination Location : ");
    int ch;
    int src=0,dest=9;
    wmove(win2,4,21);
    keypad(win2,true);
    refresh();
    wrefresh(win);

    while((ch = wgetch(win2)) != KEY_F(1))
    {
        switch (ch)
        {
        
        case KEY_F(2):
            
            clean(win2);

            curs_set(1);
            wmove(win2,4,21);
            wrefresh(win2);
            cin>>src;
            mvwprintw(win2,4,21,"%d",src);
            wrefresh(win2);
            // refresh();
            wmove(win2,6,26);
            wrefresh(win2);
            cin>>dest;
            curs_set(0);
            mvwprintw(win2,6,26,"%d",dest);
            wrefresh(win2);

            //call the shortest path function for given values
            if(!shortest_path(src,dest))
            {   
                wattron(win2,COLOR_PAIR(3));
                mvwprintw(win2,15,3,"Invalid Source Or Destination");
                mvwprintw(win2,16,3,"Please Check The List Displayed");
                wattroff(win2,COLOR_PAIR(3));
                wrefresh(win);
                wrefresh(win2);
                refresh();
                break;
            }

            //getting result
            fin.open("result");
            int nV;fin>>nV;
            int pSet[nV];
            for(int i=0;i<nV;i++)
                fin>>pSet[i];
            int distance; fin>>distance;
            fin.close();

            //displaying result
            
            mvwprintw(win2,10,3,"Shortest Distance is  : %d",distance);
            
            
            mvwprintw(win2,12,3,"Shortest Path is  : ");
            wattron(win2,COLOR_PAIR(1));

            
            wmove(win2,14,3);
            for(int i = 0;i<nV;i++)
            {
                if(pSet[i]!=-1)
                {   
                    wprintw(win2,Cities[pSet[i]].c_str());
                    if(pSet[i]!=dest)
                        wprintw(win2," -> ");   
                } 
            }
            wattroff(win2,COLOR_PAIR(1));
            wrefresh(win);
            wrefresh(win2);
            refresh();
            //clearing some stuff
        
           break;

        }


    }
    

    wrefresh(win2);
    // wgetch(win);
    endwin();
    return 0;
}

                                                                                                                                 