/*=====头文件引入=====*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<process.h>

/*=====玩家初始位置配置=====*/
#define USER_INIT_X 1
#define USER_INIT_Y 8

//汽车数据
typedef struct {
    //顶端
    char x,y;

    //0:玩家
    //1:Npc
    char mode;
}Carstruct,*Car;

//游戏得分
long score=-7;

//数据定义,0为用户,1-2为Npc
Car car[3];

//游戏地图
char Map[]="*******************************\n** O-=-O *|* O-=-O *|* O-=-O **\n** | | | *|* | | | *|* | | | **\n** O-=-O *|* O-=-O *|* O-|-O **\n** O-=-O *|* O-=-O *|* O-=-O **\n** | | | *|* | | | *|* | | | **\n** O-=-O *|* O-=-O *|* O-|-O **\n** O-=-O *|* O-=-O *|* O-=-O **\n** | | | *|* | | | *|* | | | **\n** O-=-O *|* O-=-O *|* O-|-O **\n** O-=-O *|* O-=-O *|* O-=-O **\n** | | | *|* | | | *|* | | | **\n** O-=-O *|* O-=-O *|* O-|-O **\n*******************************\0";

//游戏运行状态,运行:1
short Game_State = 0;


//CarGame动画
void Cargame_Animation();
//Welcome动画
void Welcome_Animation();
//Goodbye动画
void Goodbye_Animation();
//GameOver动画
void Gameover_Animation();
//光标位置设置
void gotoxy(short x, short y);
//初始化地图,置空
void Init_Map();
//初始化人物数据
void Init_Car();
//初始化游戏
void Init_Game();
//菜单
char Menu();
//游戏结束判定
void Game_Determine();
//打印界面
void Display();
/**
 * 汽车移动函数
 * @param Car 汽车结构体
 * @param short 方向运动;wasd
*/
void Car_Move(Car car,char m);
/**
 * Npc随机移动函数
*/
void Npc_Move();
/**
 * 读取游戏数据
 * @param char[] 数据返回位置
*/
void Read_Game(char data[7]);
/**
 * 保存游戏数据
 * @param char[] 将要保存的数据
*/
void Write_Game(char data[7]);



void gotoxy(short x, short y){
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void Welcome_Animation(){
    char s[5][46]={
        {"                _                          "},
        {"  __      _____| | ___ ___  _ __ ___   ___ "},
        {"  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\"},
        {"   \\ V  V /  __/ | (_| (_) | | | | | |  __/"},
        {"    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|"}
    };

    int i,j,k;
    system("cls");
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    for(i=0;i<46;i++){
        gotoxy(0,1);
        for(j=0;j<5;j++){
            for(k=0;k<i;k++)
                printf("%c",s[j][k]);
            printf("\n");
        }
        Sleep(8);
    }
}

void Goodbye_Animation(){
    char s[6][46]={
        {"   ____                 _ _                "},
        {"  / ___| ___   ___   __| | |__  _   _  ___ "},
        {" | |  _ / _ \\ / _ \\ / _` | '_ \\| | | |/ _ \\"},
        {" | |_| | (_) | (_) | (_| | |_) | |_| |  __/"},
        {"  \\____|\\___/ \\___/ \\__,_|_.__/ \\__, |\\___|"},
        {"                                |___/      "}
    };

    int i,j,k;
    system("cls");
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    for(i=0;i<47;i++){
        gotoxy(0,1);
        for(j=0;j<6;j++){
            for(k=0;k<i;k++)
                printf("%c",s[j][k]);
            printf("\n");
        }
        Sleep(8);
    }
}

void Cargame_Animation(){
    char s[5][47]={
        {"                    ____                     "},
        {"   ___ __ _ _ __   / ___| __ _ _ __ ___   ___ "},
        {"  / __/ _` | '__| | |  _ / _` | '_ ` _ \\ / _ \\"},
        {" | (_| (_| | |    | |_| | (_| | | | | | |  __/"},
        {"  \\___\\__,_|_|     \\____|\\__,_|_| |_| |_|\\___|"}
    };

    int i,j,k;
    system("cls");
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    for(i=0;i<48;i++){
        gotoxy(0,1);
        for(j=0;j<5;j++){
            for(k=0;k<i;k++)
                printf("%c",s[j][k]);
            printf("\n");
        }
        Sleep(8);
    }
}

void Gameover_Animation(){
    char s[6][55]={
        {"   _____                         ____                 "},
        {"  / ____|                       / __ \\                "},
        {" | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ "},
        {" | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|"},
        {" | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   "},
        {"  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   "}
    };

    int i,j,k;
    system("cls");
    puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    for(i=0;i<56;i++){
        gotoxy(0,1);
        for(j=0;j<6;j++){
            for(k=0;k<i;k++)
                printf("%c",s[j][k]);
            printf("\n");
        }
        Sleep(8);
    }
}

void Init_Map(){
    short Loop_x,Loop_y;
    for(Loop_x=0;Loop_x<3;Loop_x++)
        for(Loop_y=0;Loop_y<12;Loop_y++){
            Map[Loop_x*10+Loop_y*32+35]=' ';
            Map[Loop_x*10+Loop_y*32+36]=' ';
            Map[Loop_x*10+Loop_y*32+37]=' ';
            Map[Loop_x*10+Loop_y*32+38]=' ';
            Map[Loop_x*10+Loop_y*32+39]=' ';
        }
}

void Init_Car(){

    short Loop_i;
    //初始化内存空间
    for(Loop_i=0;Loop_i<3;Loop_i++)
        car[Loop_i] = (Car)malloc(sizeof(Carstruct));

    //初始化值
    car[0]->mode=0;
    car[0]->x=USER_INIT_X;
    car[0]->y=USER_INIT_Y;
    for(Loop_i=1;Loop_i<3;Loop_i++){
        car[Loop_i]->mode=1;
        car[Loop_i]->x=0;
        car[Loop_i]->y=12;
    }
}

void Init_Game(){
    //初始化随机种子
    srand((unsigned)time(NULL));

    Init_Car();
    Init_Map();

    //允许游戏进入运行状态
    Game_State = 1;
}

char Menu(){
    system("cls");
    printf("\n");
    puts("*********************************");
    puts("*********************************");
    puts("**   欢迎来到躲避汽车小游戏    **");
    puts("**        ->开始新游戏         **");
    puts("**          继续旧游戏         **");
    puts("**          退出游戏           **");
    puts("*********************************");
    puts("*********************************");
    puts("  帮助:");
    puts("      w键向上移动");
    puts("      s键向下移动");
    puts("      空格键确认");

    char mode='1',temp;
    while(1){
        temp = getch();
        if((temp == 'w' || temp == 'W') && mode != '1')
            mode--;
        if((temp == 's' || temp == 'S') && mode != '3')
            mode++;
        if(temp == ' ')
            break;
        gotoxy(0,4);
        if(mode == '1')
            puts("**        ->开始新游戏         **");
        else
            puts("**          开始新游戏         **");
        if(mode == '2')
            puts("**        ->继续旧游戏         **");
        else
            puts("**          继续旧游戏         **");
        if(mode == '3')
            puts("**        ->退出游戏           **");
        else
            puts("**          退出游戏           **");
    }
    system("cls");
    return mode;
}

void Game_Determine(){
    if(
        //npc1碰撞
        (car[1]->x==car[0]->x &&
            car[0]->y <= car[1]->y+2 &&
            car[0]->y >= car[1]->y-2)||
        //npc2碰撞
        (car[2]->x==car[0]->x &&
            car[0]->y <= car[2]->y+2 &&
            car[0]->y >= car[2]->y-2))
    {
        Game_State = 0;
        Gameover_Animation();
    }
}

void Display(){

    Init_Map();

    //解析地图数据
    int Loop_i;
    for(Loop_i=0;Loop_i<3;Loop_i++){
        if(car[Loop_i]->y>=0 && car[Loop_i]->y<=11 &&
            car[Loop_i]->x>=0 && car[Loop_i]->x<3){
            Map[car[Loop_i]->x*10 + car[Loop_i]->y*32 +35]='O';
            Map[car[Loop_i]->x*10 + car[Loop_i]->y*32 +36]='-';
            Map[car[Loop_i]->x*10 + car[Loop_i]->y*32 +37]='=';
            Map[car[Loop_i]->x*10 + car[Loop_i]->y*32 +38]='-';
            Map[car[Loop_i]->x*10 + car[Loop_i]->y*32 +39]='O';
        }
        if(car[Loop_i]->y+1>=0 && car[Loop_i]->y+1<=11 &&
            car[Loop_i]->x>=0 && car[Loop_i]->x<3){
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+1)*32 +35]='|';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+1)*32 +36]=' ';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+1)*32 +37]='|';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+1)*32 +38]=' ';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+1)*32 +39]='|';
        }
        if(car[Loop_i]->y+2>=0 && car[Loop_i]->y+2<=11 &&
            car[Loop_i]->x>=0 && car[Loop_i]->x<3){
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+2)*32 +35]='O';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+2)*32 +36]='-';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+2)*32 +37]='=';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+2)*32 +38]='-';
            Map[car[Loop_i]->x*10 + (car[Loop_i]->y+2)*32 +39]='O';
        }
    }
    gotoxy(0,0);
    //打印地图
    printf(">>>当前得分:%3d\n",score>0?score:0);
    puts(Map);
}

void Car_Move(Car car,char m){

    switch (m){
        //上移
        case 'w':
            if(car->y!=0)
                car->y--;
            break;
        //下移
        case 's':
            if((car->mode==0 && car->y<9)||(car->mode==1 && car->y<12))
                car->y++;
            if(car->mode==1 && car->y==12)
                score++;
            break;
        //左移
        case 'a':
            if(car->x>0)
                car->x--;
            break;
        //右移
        case 'd':
            if(car->x<2)
                car->x++;
            break;
    
    default:
        break;
    }

    Game_Determine();

}

void Npc_Move(){
    if(car[1]->y == 12 && car[2]->y > 3){
        //随机重置npc1位置
        car[1]->x = rand()%3;
        car[1]->y = -3;
    }
    if(car[2]->y == 12 && car[1]->y > 3){
        //随机重置npc2位置
        car[2]->x = rand()%3;
        car[2]->y = -3;
    }
    //npc1,2下移
    Car_Move(car[1],'s');
    Car_Move(car[2],'s');
    Display();
}

void Read_Game(char data[7]){
    FILE *p = fopen("Cardata","a+");
    short Loop_i;
    for(Loop_i=0;Loop_i<7;Loop_i++)
            fscanf(p,"%c",&data[Loop_i]);
    fclose(p);
}

void Write_Game(char data[7]){
    FILE *p = fopen("Cardata","w");
    short Loop_i;
    for(Loop_i=0;Loop_i<7;Loop_i++)
            fprintf(p,"%c",data[Loop_i]);
    fclose(p);
}