/*
*                    ____
*   ___ __ _ _ __   / ___| __ _ _ __ ___   ___ 
*  / __/ _` | '__| | |  _ / _` | '_ ` _ \ / _ \
* | (_| (_| | |    | |_| | (_| | | | | | |  __/
*  \___\__,_|_|     \____|\__,_|_| |_| |_|\___|
*
*   @author Tian
*/

#include"Game.h"

void Load_Game();
void Save_Game();
void Exit_Game();
void Run_Npc();
void Run_User();


int main(){

/***********打印Logo并初始化***********/

    Init_Game();
    Welcome_Animation();
    Sleep(1000);
    Cargame_Animation();
    Sleep(1000);


/***********选项标记***********/
    char mode = Menu();

/***********开始游戏***********/
    switch (mode){
/***********开始新游戏***********/
        case '1':
            break;
/***********加载上次游戏***********/
        case '2':
            Load_Game();
            break;
/***********退出游戏***********/
        case '3':
        default:
            Exit_Game();
            return 0;
    }

    //开始游戏
    system("cls");
    Display();
    _beginthread(&Run_Npc,0,NULL);
    Run_User();
    while(Game_State);
    Goodbye_Animation();

}

//npc进程
void Run_Npc(){
    while(Game_State){
        Npc_Move();
        Sleep(800);
    }
}

void Run_User(){
    while(Game_State){
        switch (getch()){
            //保存游戏
            case 'p':
            case 'P':
                Game_State=0;
                printf("正在保存游戏");
                Save_Game();
                Sleep(100);
                printf(".");
                Sleep(100);
                printf(".");
                Sleep(100);
                printf(".");

            //退出游戏
            case 'q':
            case 'Q':
                system("cls");
                Game_State=0;
                break;

            //刷新游戏
            case 'r':
            case 'R':
                system("cls");
                Display();
                break;

            //保存游戏
            case 'a':
            case 'A':
                Car_Move(car[0],'a');
                break;
            //保存游戏
            case 's':
            case 'S':
                Car_Move(car[0],'s');
                break;
            //保存游戏
            case 'd':
            case 'D':
                Car_Move(car[0],'d');
                break;
            //保存游戏
            case 'w':
            case 'W':
                Car_Move(car[0],'w');
                break;

            default:
                break;
        }
        Display();
    }
    
}


//加载游戏资源
void Load_Game(){

    char data[7]={0};
    Read_Game(data);

    car[0]->mode=0;
    car[1]->mode=1;
    car[2]->mode=1;
    score = data[0]-'a';

    short Loop_i,Loop_j=1;
    for(Loop_i=0;Loop_i<3;Loop_i++){
        car[Loop_i]->x=data[Loop_j++]-'a';
        car[Loop_i]->y=data[Loop_j++]-'a';
    }
}

//保存游戏
void Save_Game(){
    char data[7]={0};
    data[0]=(score>0?score:0)+'a';
    short Loop_i,Loop_j=1;
    for(Loop_i=0;Loop_i<3;Loop_i++){
        data[Loop_j++]=car[Loop_i]->x+'a';
        data[Loop_j++]=car[Loop_i]->y+'a';
    }

    Write_Game(data);
}

//退出游戏
void Exit_Game(){
    Goodbye_Animation();
    system("pause");
    exit;
}