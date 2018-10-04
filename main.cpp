#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define s_c sizeof(char)
#define n_name 10
#define min_n 0
#define max_n 100
#define id_len 15

FILE* inf_itdc;
FILE* inf_hstr;
FILE* inf_prz;
FILE* inf_prz_1;
FILE* inf_prz_2;
FILE* inf_prz_3;
FILE* inf_user;
FILE* IDs;

int i = 0;
int j = 0;
int k = 0;
char line[6]="-----";
char start[2] = "{";
char over[2] = "}";
char id_sign[2] = "&";
char name_sign[2] = "(";

void Instructions();
int MainPage();
void clrscr();
void hitback();
void Blank(FILE* file);
void Lottery();
void Back_Stage();
void User_set();
void User_add();
void User_delete();
void User_info_c();
void Info_set();
void Lottery_set();
void History_set();
void Info();
void Info_User();
void Info_introduce();
void Info_prize();
void Info_history();
void About_Us();
int Delete_ID(char *ID);
int Existe_ID(char *ID);
void Single();
void Get_ID(char *str, int line, FILE *stream);
int Used_Line(int id, int m, int line_list[]);
void Record_Time(FILE *file);

int main()
{
    Instructions();
    MainPage();
    return 0;
}

void Instructions()
{
    clrscr();
    cout << line <<"欢迎来到抽奖系统" << line << endl;
    cout << "1.开始抽奖" << endl;
    cout << "2.后台管理" << endl;
    cout << "3.信息查看" << endl;
    cout << "4.退出" << endl;
}

int MainPage()
{
    int answer = 0;
    while(1){
        cin >> answer;
        switch(answer){
        case 1: Lottery(); break;
        case 2: Back_Stage(); break;
        case 3: Info(); break;
        case 4: exit(0); break;
        }
        Instructions();
    }
}

void Back_Stage()
{
    int answer = 0;
    while(!answer){
        clrscr();
        cout << line <<"欢迎来到后台" << line << endl;
        cout << "1.设置信息简介" << endl;
        cout << "2.设置奖项" << endl;
        cout << "3.删除抽奖历史信息" << endl;
        cout << "4.用户管理" << endl;
        cout << "5.返回" << endl;
        cin >> answer;
        switch(answer){
            case 1: Info_set(); break;
            case 2: Lottery_set(); break;
            case 3: History_set(); break;
            case 4: User_set(); break;
            case 5: return;
            default: answer = 0;
        }
        answer = 0;
    }
}

void Info_set()
{
    clrscr();
    if((inf_itdc = fopen("inf_itdc.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        hitback();
        return;
    }
    char inf[max_n+1];
    cout << line << "设置信息简介" << line << endl;
    cout << "编辑抽奖信息简介：" << endl;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_itdc);
    fclose(inf_itdc);
}

void History_set()
{
    clrscr();
    if((inf_hstr = fopen("inf_hstr.txt","w+")) == NULL){
        cout << "暂无抽奖历史记录" << endl;
        hitback();
        return;
    }
    fclose(inf_hstr);
    cout << "清除抽奖历史信息？" << endl;
    cout << "1.确认" << endl << "2.返回" << endl;
    int answer = 0;
    while(answer == 0){
        cin>>answer;
        if(answer == 1) {
            remove("inf_hstr.txt");
            cout << "删除成功！" <<endl;
            hitback();
            return;
        }
        else if(answer==2) return;
        else answer = 0;
    }
}

void Lottery_set()
{
    clrscr();
    if((inf_prz = fopen("inf_prz.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        return;
    }
    char name[n_name];
    char N[3];
    char inf[max_n+1];
    int num_p = 0;
    int num = 0;

    cout << line << "设置奖项" << line << endl;

    while(num_p<=0||num_p>99){
        cout << "奖品种类数(1-99)：";
        cin >>num_p;
    }
    itoa(num_p,N,10);
    fwrite(N,s_c,strlen(N),inf_prz);
    Blank(inf_prz);

    for(i=0;i<num_p;i++){
        cout << i+1 << "号奖品："<< endl;
        cout << "名称：" ;
        cin >> name;
        num = 0;
        while(num <=0){
            cout << "数量：" ;
            cin >> num;
        }
        cout << "奖品详情：" ;
        cin >> inf;
        itoa(num,N,10);
        fwrite(start,s_c,1,inf_prz);
        fwrite(N,s_c,strlen(N),inf_prz);
        Blank(inf_prz);
        fwrite(name_sign,s_c,1,inf_prz);
        fwrite(name,s_c,strlen(name),inf_prz);
        Blank(inf_prz);
        fwrite(inf,s_c,strlen(inf),inf_prz);
        Blank(inf_prz);
        fwrite(over,s_c,1,inf_prz);
    }
    fclose(inf_prz);
    cout << "设置成功！" << endl;
    hitback();
}

void Info()
{
    int answer=0;
    while(!answer){
        clrscr();
        cout << line << "信息查看" << line << endl;
        cout << "1.抽奖简介" << endl;
        cout << "2.奖品信息" << endl;
        cout << "3.历史抽奖信息" << endl;
        cout << "4.用户信息" << endl;
        cout << "5.关于我们" << endl;
        cout << "6.返回" << endl;
        cin >> answer;
        switch(answer){
            case 1: Info_introduce(); break;
            case 2: Info_prize(); break;
            case 3: Info_history(); break;
            case 4: Info_User(); break;
            case 5: About_Us(); break;
            case 6: return;
            default: answer = 0;break;
        }
        answer = 0;
    }
}

void Info_introduce()
{
    clrscr();
    if((inf_itdc = fopen("inf_itdc.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        return;
    }
    char word = 'a';
    cout << line << "抽奖简介" << line <<endl;
    while(word!=EOF){
        word = fgetc(inf_itdc);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(inf_itdc);
}

void Info_prize()
{
    clrscr();
    if((inf_prz = fopen("inf_prz.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        hitback();
        return;
    }
    char word = fgetc(inf_prz);
    int num = word - '0';

    cout << line << "奖品信息" << line << endl;
    for(i=0;i<num;i++){
        while(word!=start[0]) word = fgetc(inf_prz);
        cout <<line<<"奖品"<<i+1<<endl;
        cout << "数量：" ;
        while(word!='\n') {
            word = fgetc(inf_prz);
            cout << word;
        }
        word = fgetc(inf_prz);
        cout << "名称: ";
        while((word = fgetc(inf_prz))!='\n')
            cout << word;
        word = 'a';
        cout << endl <<"奖品信息：";
        while(word!='\n') {
            word = fgetc(inf_prz);
            if(word==over[0]) break;
            cout << word;
        }
    }
    hitback();
    fclose(inf_prz);
}

void Info_history()
{
    clrscr();
    if((inf_hstr = fopen("inf_hstr.txt","r")) == NULL){
        cout << "暂无历史抽奖信息" << endl;
        hitback();
        return;
    }
    char word = 'a';
    while(word!=EOF){
        word = fgetc(inf_hstr);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(inf_hstr);
}

void Info_User()
{
    clrscr();
    char word = 'a';
    char ID[id_len];
    cout << line << "用户信息" << endl;
    cout << "输入想要查看的用户ID: ";
    cin >> ID;
    if((inf_user = fopen(ID,"r"))==NULL){
        cout << "不存在用户: " << ID << endl;
        hitback();
        return;
    }
    cout << "姓名：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "年龄：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "性别：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "简介：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(inf_user);
}

void About_Us()
{
    char word = 'a';
    clrscr();
    FILE *about ;
    if((about = fopen("about_us.txt","r"))==NULL){
        cout << "读取信息失败！" << endl;
        hitback();
        return;
    }
    cout << line << "关于我们" << line <<endl;
    while(word!=EOF){
        word = fgetc(about);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(about);
}

void clrscr()
{
    system("cls");
}

void hitback()
{
    system("pause");
}

void Blank(FILE* file)
{
    fwrite("\n",s_c,1,file);
}

void User_set()
{
    int answer = 0;
    while(1){
        clrscr();
        cout << line << "用户管理" << line << endl;
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.修改用户信息" << endl;
        cout << "4.返回" << endl;
        cin >> answer;
        if(answer == 1) User_add();
        else if(answer == 2) User_delete();
        else if(answer == 3) User_info_c();
        else if(answer == 4) return;
        else answer = 0;
    }
}

void User_add()
{
    char name[11];
    int age = 0;
    int sex = 0;
    char AGE[3];
    char ID[14];
    char info[101];
    clrscr();
    cout << line << "添加用户" << line << endl;
    cout << "登记用户信息：" << endl;
    cout << "ID(用户身份识别码): ";
    cin >> ID;
    if((inf_user = fopen(ID,"r"))!=NULL){
        cout << "用户已存在" << endl;
        hitback();
        fclose(inf_user);
        return;
    }

    cout << "姓名(10字节)：" ;
    cin >> name;
    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        cin >> age;
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        cin >> sex;
    }
    cout << "个人简介(100字节):" << endl;
    cin >> info;

    if((inf_user = fopen(ID,"w+"))==NULL){
        cout << "添加用户失败" << endl;
        hitback();
        return;
    }
    if((IDs = fopen("IDs.txt","a+")) == NULL){
        cout << "添加用户失败" << endl;
        hitback();
        return;
    }

    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fwrite(ID,s_c,strlen(ID),IDs);
    fwrite(id_sign,s_c,1,IDs);
    fwrite(name,s_c,strlen(name),IDs);
    fwrite("\n",s_c,1,IDs);

    cout << "添加用户：" << ID << "成功" << endl;
    hitback();
    fclose(IDs);
    fclose(inf_user);
}

void User_delete()
{
    clrscr();
    int answer = 0;
    char ID[14];
    cout << line << "删除用户" << line << endl;
    cout << "请输入要删除的用户的ID" << endl;
    cin >> ID;
    if((inf_user = fopen(ID,"r")) == NULL){
        cout << "不存在用户，请检查输入" << endl;
        hitback();
        return;
    }
    fclose(inf_user);
    clrscr();

    cout << "确定要删除ID：" << ID << endl;

    while(answer == 0){
        cout << "1.确认删除" <<endl<<"2.返回" << endl;
        cin>>answer;
        if(answer == 1) {
            if(Delete_ID(ID)==1)
                remove(ID);
        }
        else if(answer == 2) return;
        else answer = 0;
    }
}

int Delete_ID(char *ID)
{
    FILE *IDs_Backup;
    if((IDs=fopen("IDs.txt","r"))==NULL||(IDs_Backup=fopen("IDs_Backup.txt","w+"))==NULL){
        cout << "删除用户ID失败" << endl;
        hitback();
        return 0;
    }

    int len = strlen(ID);
    int out = 0;
    int recorder = 0;
    char line[id_len+n_name+1];
    char word = 'a';

    while(!out){
        recorder = 0;
        word = 'a';
        for(i=0;i<len;i++) line[i] = '\0';
        for(i=0;word!='\n';i++){
            word = fgetc(IDs);
            if(word == EOF) {
                out = 1; break;
            }
            line[i] = word;
        }
        for(j=0;j<len;j++){
            if(line[j]==ID[j]) recorder++;
        }
        if(recorder != len)
            fwrite(line,s_c,i,IDs_Backup);
        else{
            while(word!='\n')
                word = fgetc(IDs);
        }
    }
    cout << "删除成功！" << endl;
    hitback();

    fclose(IDs);
    fclose(IDs_Backup);
    remove("IDs.txt");
    rename("IDs_Backup.txt","IDs.txt");
    return 1;
}

void User_info_c()
{
    int age = 0;
    int sex = 0;
    char AGE[3];
    char ID[14];
    char info[101];
    clrscr();
    cout << line << "修改用户信息：" << line << endl;
    cout << "输入要修改的ID" << endl;
    cin >> ID;
    if((inf_user = fopen(ID,"r+")) == NULL){
        cout << "读取用户数据失败" << endl;
        hitback();
        return;
    }
    fclose(inf_user);

    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        cin >> age;
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        cin >> sex;
    }
    cout << "个人简介(100字节):" << endl;
    cin >> info;

    if((inf_user = fopen(ID,"w"))==NULL){
        cout << "写入用户数据失败" << endl;
        hitback();
        return;
    }
    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fclose(inf_user);
    return;
}

void Lottery()
{
    clrscr();
    cout << line <<"抽奖"<< line <<endl;
    cout << "1.单组抽奖" <<endl;
    cout << "2.多组抽奖" <<endl;
    cout << "3.返回" << endl;
    int answer = 0;
    while(answer==0){
        cin >> answer;
        switch(answer){
            case 1: Single(); break;
//            case 2: Multi();
            case 3: return;
            default : answer = 0;
        }
    }
}

void Single()
{
    clrscr();
    srand((int)time(NULL));
    if((inf_user = fopen("IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        hitback();
        return;
    }
    if((inf_prz = fopen("inf_prz.txt","r"))==NULL){
        cout << "读取奖品信息失败！" << endl;
        hitback();
        return;
    }
    if((inf_hstr = fopen("inf_hstr.txt","a"))==NULL){
        cout << "读取历史信息失败！" << endl;
        hitback();
        return;
    }
    char word = 'a';
    char ID[id_len];
    char NAME[n_name];
    int n_id = 0;       //用户总数
    while(word!=EOF){
        word = fgetc(inf_user);
        if(word == '\n') n_id++;
    }

    int id_rest = n_id;     //未中奖用户数
    char num_prz[2];        //奖品种类数
    for(i=0;i<2;i++) num_prz[i] = fgetc(inf_prz);
    int n_prz = atoi(num_prz);  //奖品种类数
    int n_p = 0;            //单个奖品数量
    int id_line=0;         //中奖用户的ID位置
    for(i=0;i<n_prz;i++){   //循环抽奖品总数次
        while(word != start[0]) word = fgetc(inf_prz);
        for(j=0;j<2;j++) num_prz[j] = fgetc(inf_prz);
        for(j=0;j<n_name;j++) NAME[j] = '\0';   //初始化奖品名称
        while(word != name_sign[0]) word = fgetc(inf_prz);
        for(j=0;(word = fgetc(inf_prz))!='\n';j++)
            NAME[j] = word;
//       cout <<"奖品名称：" << NAME << endl;
        n_p = atoi(num_prz);        //读取此种奖品数量
        int line_list[n_p];         //储存已中奖用户
        for(j=0;j<n_p;j++){         //循环抽此奖品数量次
            for(k=0;k<id_len;k++)   //初始化ID
                ID[k] = '\0';
            if(id_rest<=0){        //判断用户是否有剩余
                cout << "已无用户！" << endl;
                hitback();
                return;
            }
            while(1){               //随机ID
                id_line = rand()%n_id+1;
                if(!Used_Line(id_line,j,line_list)) break;
            }

            line_list[j] = id_line;             //储存中奖ID
            Get_ID(ID,id_line,inf_user);        //读取用户ID
            cout <<"恭喜ID：" <<ID << " 中奖：";
            cout << NAME << endl;
            id_rest--;              //剩余ID数-1
            Record_Time(inf_hstr);
            fwrite("中奖ID: ",s_c,8,inf_hstr);
            fwrite(ID,s_c,strlen(ID),inf_hstr);
            fwrite("\0|\0",s_c,3,inf_hstr);
            fwrite(" 奖品名称：",s_c,11,inf_hstr);
            fwrite(NAME,s_c,strlen(NAME),inf_hstr);
            Blank(inf_hstr);
        }
    }

    fclose(inf_user);
    fclose(inf_prz);
    fclose(inf_hstr);
    hitback();
}

void Get_ID(char *str, int line, FILE *stream)
{
    fseek(stream,0,SEEK_SET);
    char out = 'a';
    for(k=0;k<line;out = fgetc(stream)){
        if(out == '\n') k++;
    }
    for(k=0;out!='\n';k++){
        if(out!=id_sign[0]) str[k] = out;
        else return;
        out = fgetc(stream);
    }
}

int Used_Line(int id, int m, int line_list[])
{
    for(k=0;k<m;k++){
        if(id==line_list[k])
            return 1;
    }
    return 0;
}

void Record_Time(FILE *file)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    int year = 1900+p->tm_year;
    int mon = 1+p->tm_mon;
    int day = p->tm_mday;
    int hour = 8+p->tm_hour;
    int mini = p->tm_min;
    int sec = p->tm_sec;
    char time[5];
    fwrite("时间:",s_c,5,file);
    itoa(year,time,10);
    fwrite(time,s_c,strlen(time),file);
    fwrite("/",s_c,1,file);
    itoa(mon,time,10);
    fwrite(time,s_c,strlen(time),file);
    fwrite("/",s_c,1,file);
    itoa(day,time,10);
    fwrite(time,s_c,strlen(time),file);
    fwrite("\0",s_c,1,file);
    itoa(hour,time,10);
    fwrite(time,s_c,strlen(time),file);
    fwrite(":",s_c,1,file);
    itoa(mini,time,10);
    fwrite(time,s_c,strlen(time),file);
    fwrite(":",s_c,1,file);
    itoa(sec,time,10);
    fwrite(time,s_c,strlen(time),file);
    fwrite("\0|\0",s_c,3,file);
}
