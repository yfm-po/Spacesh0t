#include "Spacesh0t.h"

int main(int argc, char *argv[])
{
    throwException(argc, "Give difficulty level as argument: 1, 2 or 3\n");
    srand(time(NULL));
    askForNameAndScoreBoard();

    printf("In this game you will have to fight kill as many enemy spaceships you can.\n");
    printf("Every level-up will spawn more and more enemies.\n");
    printf("You can respawn 5 times, so you have only 5 lives.\n");
    sleep(3);
    
    initscr();
    start_color();
    noecho();
    raw();
    cbreak();
    timeout(0);
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    
    init_pair(1,COLOR_BLACK, COLOR_BLACK);
    init_pair(2,COLOR_BLUE, COLOR_BLUE);
    init_pair(3,COLOR_RED, COLOR_YELLOW);
    init_pair(4,COLOR_RED, COLOR_CYAN);
    init_pair(5,COLOR_BLUE,COLOR_WHITE);
    init_pair(6,COLOR_RED,COLOR_GREEN);
    init_pair(7,COLOR_BLACK,COLOR_WHITE);
    init_pair(8,COLOR_RED,COLOR_RED);
    init_pair(9,COLOR_GREEN,COLOR_GREEN);    
    
    int level = 1;
    int argument = 0;
    char *a = argv[1];
    argument = atoi(a);
    int splitter;

    switch (argument)
    {
        case 1:
            splitter = 100;
            break;
        case 2:
            splitter = 75;
            break;
        case 3:
            splitter = 10;
            break;
        default:
            break;
    }
    
    int p;
    int h;
    int w;
    int key;
    int die;
    int kills = 0;
    int deaths = 0;
    int bullets[50][2];
    int enemies[50][3];
    FILE *highscore;
    p = 0;
    h = 10;
    w = 6;
    die = false;
    
    memset(bullets, 0, sizeof(bullets));
    memset(enemies, 0, sizeof(enemies));
    
    while (true)
    {
    
        if (deaths == 5)
        {
            mvprintw(LINES/2, COLS/2-5, "[ YOU HAVE LOST THE GAME ]");
            refresh();
            getchar();
            break;
              
        }

        usleep(10000);
        p++;
        
        key = getch(); 
        
        switch(key)
        {
            case 'w': case KEY_UP:
                if (h > 1)
                {
                    h--;
                }
                break;
                
            case 's': case KEY_DOWN:
                if (h < 25)
                {
                    h++;
                }
                break;
                
            case 'd': case KEY_RIGHT:
            {
                if (w < 600)
                {
                    w++;
                }
                break;
            }
            
            case 'a': case KEY_LEFT:
            {
                if (w > 1)
                {
                    w--;
                }
                break;
            }
                
            case ' ':
                for(int x = 0; x < count(bullets);x++)
                {
                    if(bullets[x][0] == 0)
                    {
                        bullets[x][0] = w;
                        bullets[x][1] = h;
                        break;
                    }
                }
                break;
                
            case 'q' : case 'Q' :
            { 
                mvprintw(LINES/2, COLS/2-5, "[ QUIT GAME ]");
                refresh();
                while (true)
                {
                    int key_press = getch();

                    if (key_press == 'q' || key_press == 'Q')
                    {
                        endwin();
                    }
                }
                break;
            }
    
            case 'p' : case 'P' :
            {
                mvprintw(LINES/2,COLS/2-5,"[ PAUSED ]");
                refresh();
                while (true)
                {
                    int key_press = getch();

                    if (key_press == 'p' || key_press == 'P')
                    {
                        break;
                    }
                }
                break;
            }
         }
        
        if((rand() % splitter) == 0)
        {
            for(int x = 0;x != count(enemies);x++)
            {
                if(enemies[x][0] == 0)
                {
                    enemies[x][0] = 180;
                    enemies[x][1] = 7;
                  
                    if (rand() % 2 == 0)
                    {
                        enemies[x][1] -= (rand() % 7);
                    }
                    else
                    {
                        enemies[x][1] += (rand() % 7);
                    }
                    break;
                }
            }
        }
        
        int n;
        for (int x = 0;x != 600; x++)
        {
            for (int y = 0;y != 300; y++)
            {
                y-=20;
                
                if (cos((float)(x+p)/30) > ((float)y / 5))
                {
                    n = 1; 
                }
                else
                {
                    n = 2;
                    if (x == 16 && (h-18 > y))
                    {
                        
                        die = true;
                        deaths++;
                        if (deaths == 5)
                        {
                             mvprintw(LINES/2, COLS/2, "[ YOU HAVE LOST THE GAME ]");
                             refresh();
                             getchar();
                             break;  
                        }
                        
                    }
                }
                y+=20;
                
                attron(COLOR_PAIR(n));
                mvprintw(y,x,"."); 
                attroff(COLOR_PAIR(n));
            }
        }
        
        
        
        for(int x = 0;x != count(bullets); x++)
        {
            if (bullets[x][0] != 0)
            {
                bullets[x][0] += 1;
                attron(COLOR_PAIR(6));
                mvprintw(bullets[x][1],bullets[x][0],">");
            }
            
            if(bullets[x][0] > 200)
            {
                bullets[x][0] = 0;
            }
            
        }
        
        
        for(int x = 0;x != count(enemies); x++)
        {
            if (enemies[x][0] && enemies[x][2] == 0)
            {
                enemies[x][0]--;
            }
            
            if (enemies[x][0] == 1)
            {
                enemies[x][0] = 0;    
            }
            
            if (enemies[x][2] != 0)
            {
                enemies[x][2]--;
                attron(COLOR_PAIR(3)); 
                
                if(enemies[x][2] == 0)
                {
                    enemies[x][0] = 0;
                }
            }
            else
            {
                
                attron(COLOR_PAIR(4));
                
                if(enemies[x][0] != 0 && enemies[x][0] < w && diff(h, enemies[x][1]) < 3)
                {
                    if (deaths == 5)
                    {
                        mvprintw(LINES/2, COLS/2-5, "[ YOU HAVE LOST THE GAME ]");
                        refresh();
                        getchar();
                        break;    
                    }
                    die = true;
                    deaths++;
                    if (deaths == 5)
                    {
                        mvprintw(LINES/2, COLS/2-5, "[ YOU HAVE LOST THE GAME ]");
                        refresh();
                        getchar();
                        break;
              
                    }
                        attron(COLOR_PAIR(3));
                        enemies[x][2] = 4;
                        break;
                    if (deaths == 5)
                    {
                        mvprintw(LINES/2, COLS/2-5, "[ YOU HAVE LOST THE GAME ]");
                        refresh();
                        getchar();
                        break;    
                    }
                }
                
                for (int y = 0;y != count(bullets);y++)
                {
                    if (bullets[y][0] != 0 && diff(enemies[x][0],bullets[y][0]) < 2 && diff(enemies[x][1],bullets[y][1]) < 2)
                    {
                        kills++;
                        if (splitter != 5)
                        {
                            splitter--;
                        }
                        if (kills % 2 == 0)
                        {
                            level++;
                        }
                        
                      
                        attron(COLOR_PAIR(3));
                        enemies[x][2] = 4;
                        break;
                    }
                }
            }
            
            if (enemies[x][0])
            {
                mvprintw(enemies[x][1]-1,enemies[x][0]+2,"/|\\");
	            mvprintw(enemies[x][1],enemies[x][0],"<O-==={");
	            mvprintw(enemies[x][1]+1,enemies[x][0]+2,"\\|/");
            }
        }
        
        
        
        attron(COLOR_PAIR(8));
        mvprintw(0,177," ##########  ");
        mvprintw(1,177,"#");
        attron(COLOR_PAIR(7));
        mvprintw(1,177," Kills: %d    ", kills);
        mvprintw(2,177," Level: %d    ", level);
        mvprintw(3,177," Deaths:%d/5  ", deaths);
        attron(COLOR_PAIR(9));
        mvprintw(4,177," ##########  ");
        
        
        if(!die)
        {
            attron(COLOR_PAIR(5));
            mvprintw(h-1,w,"|\\ |\\");
	        mvprintw(h,w-1,"}======-O)");
	        mvprintw(h+1,w,"|/ |/");
	        move(0,0);
	        refresh();
        }
        else if (die)
        {
            attron(COLOR_PAIR(3));
            mvprintw(h-1,w,"|\\ |\\");
	        mvprintw(h,w-1,"}======-O)");
	        mvprintw(h+1,w,"|/ |/");
	        move(0,0);
	        refresh();
            sleep(0.5);
            p=0;
            h=10;
            w = 6;
            die = false;
            memset(bullets, 0, sizeof(bullets));
            memset(enemies, 0, sizeof(enemies));
        }
    }
    
    refresh();
    endwin();
    highscore = fopen("./highscores.txt","a");
    fprintf(highscore, "Name: %s | Level: %d | Kills: %d\n", name, level, kills);
    fclose(highscore);
}

void throwException(int argc, char *msg)
{
    if (argc != 2)
    {
        printf((char*)msg);
        exit(EXIT_FAILURE);
    }
}

void askForNameAndScoreBoard()
{
    char name[20];
    printf("Enter your name: ");
    printf("\n");
    scanf("%s", name);
    printf("Welcome to spacesh0t, %s.\n",name);
    int u; 
    printf("Press 0 if you want to see the scoreboard, press 1 if you want to play: \n");
    scanf("%d", &u);
    
    if (u == 0)
    {
        FILE *f;
        char c;
        
        f = fopen("./highscores.txt","r");
        c = fgetc(f);
        while (c != EOF)
        {
            printf("%c",c);
            c = fgetc(f);
        }
        printf("\n");
        fclose(f);
        sleep(3);
    }
}
