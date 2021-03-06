#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#define s_c sizeof(char)    //一个字符的大小
#define n_name 15           //输入用户名的大小
#define max_n 100           //最大输入字符数
#define id_len 15           //id的最大长度
#define n_illegal 9         //非法字符数

FILE* inf_itdc;     //抽奖介绍文本
FILE* inf_hstr;     //历史抽奖记录文本
FILE* inf_prz;      //奖品记录文本
FILE* inf_user;     //用户文档指针
FILE* IDs;          //用户ID储存文本

int num = 0;            //用于输入的数字
char answer[2] = "0";       //用于转换数字的字符
char id_sign[2] = "@";         //信息起始符
char name_sign[2] = "&";      //信息起始符
char prz_n_s[2] = "[";        //信息起始符
char prz_n_e[2] = "]";         //信息终止符
char prz_name[2] = "(";    //信息起始符
char prz_m_s[2] = "{";      //信息起始符
char prz_m_e[2] = "}";      //信息起始符
char illegal_word[n_illegal] = "&({}[]\\/";     //禁止输入的非法字符
char path[10] = "user_inf/";    //信息储存路径
const char line[6]="=====";       //固定显示

void Instructions();        //用户指导
void MainPage();             //主界面
void Back_Stage();          //后台
void Lottery();             //抽奖
void Lottery_set();         //奖品设置
void Lottery_set_s();       //单组抽奖奖品
void Lottery_set_m();       //多组抽奖奖品
void Single();                  //单人抽奖
void Multi();                   //多组抽奖
void Info();                //信息查看
void Info_set();            //抽奖信息管理
void Info_User();           //用户信息查看
void Info_introduce();      //抽奖简介信息查看
void Info_prize();          //奖品信息查看
void Info_prz_s();          //单组抽奖奖品设置
void Info_prz_m();          //多组抽奖奖品设置
void Info_history();        //历史信息查看
void User_set();            //用户设置界面
void User_add();            //添加用户
void User_delete();         //删除用户
void User_info_c();         //更换用户信息
void History_set();         //历史信息管理
void About_Us();            //关于我们
void Record_Time(FILE *file);           //记录时间
void F_Add(char *f,char *b,char *t);        //添加路径
void Sroll(FILE *file);         //滚动显示
void Sroll_set();       //设置滚动
void Get_ID(char *str, int line, FILE *file);   //读取ID
void clrscr();              //清屏函数
void hitback();             //点击返回
void Blank(FILE* file);     //指定文本换行
int Delete_ID(char *ID);        //删除ID
int Existe_ID(char *ID);        //判断ID是否存在
int Illegal_word(char *line);   //判断输入是否合法
int Used_Line(int id, int m, int line_list[]);  //判断ID是否重复抽取
int Input(char *input, int len);        //输入函数(不含空格)
int Input_B(char* input, int len);      //输入函数(含空格)
int Input_N(char *input);           //输入函数(数字)

int main()
{
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

void MainPage()
{
    while(1){
        Instructions();
        num = Input_N(answer);
        switch(num){
            case 1: Lottery(); break;
            case 2: Back_Stage(); break;
            case 3: Info(); break;
            case 4: exit(0); break;
            default : num = 0; break;
        }
    }
}

void Back_Stage()
{
    while(1){
        clrscr();
        cout << line <<"欢迎来到后台" << line << endl;
        cout << "1.设置信息简介" << endl;
        cout << "2.设置奖项" << endl;
        cout << "3.删除抽奖历史信息" << endl;
        cout << "4.用户管理" << endl;
        cout << "5.滚动显示" << endl;
        cout << "6.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: Info_set(); break;
            case 2: Lottery_set(); break;
            case 3: History_set(); break;
            case 4: User_set(); break;
            case 5: Sroll_set(); break;
            case 6: return;
            default: num = 0; break;
        }
    }
}

void Info_set()
{
    clrscr();
    if((inf_itdc = fopen("sys_inf/inf_itdc.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        hitback();
        return;
    }
    char inf[max_n+1];
    cout << line << "设置信息简介" << line << endl;
    cout << "编辑抽奖信息简介：" << endl;
    if(Input_B(inf,max_n+1)==0) return;
    fwrite(inf,s_c,strlen(inf),inf_itdc);
    fclose(inf_itdc);
    cout << "设置成功！" << endl;
    hitback();
}

void History_set()
{
    clrscr();
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","r")) == NULL){
        cout << "暂无抽奖历史记录" << endl;
        hitback();
        return;
    }
    fclose(inf_hstr);
    cout << "清除抽奖历史信息？" << endl;
    cout << "1.确认" << endl << "2.返回" << endl;

    while(1){
        num = Input_N(answer);
        if(num == 1) {
            if((remove("sys_inf/inf_hstr.txt"))==0)
                cout << "删除成功！" <<endl;
            else cout << "删除失败！" << endl;
            hitback();
            return;
        }
        else if(num == 2) return;
        else num = 0;
    }
}

void Lottery_set()
{
      while(1){
        clrscr();
        cout << line <<"奖品设置" << line << endl;
        cout << "1.设置单组抽奖奖品" << endl;
        cout << "2.设置多组抽奖奖品" << endl;
        cout << "3.返回" << endl;

        num = Input_N(answer);
        switch(num){
            case 1: Lottery_set_s(); break;
            case 2: Lottery_set_m(); break;
            case 3: return;
            default: num = 0; break;
        }
    }
}

void Lottery_set_s()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        return;
    }
    char name[n_name];
    char N[3];
    char inf[max_n+1];
    int num_t = 0;
    int num_p = 0;
    int i = 0;

    cout << line << "设置单组抽奖奖项" << line << endl;

    while(num_t<=0||num_t>9){
        cout << "奖品种类数(1-9)：";
        num_t = Input_N(answer);
    }
    itoa(num_t,N,10);       //数字转字符
    fwrite(N,s_c,strlen(N),inf_prz);
    Blank(inf_prz);

    for(i=0;i<num_t;i++){
        cout << i+1 << "号奖品："<< endl;
        cout << "名称：" ;
        if(Input_B(name,n_name) == 0) return;
        num_p = 0;
        while(num_p <=0){
            cout << "数量：" ;
            num_p = Input_N(answer);
        }

        cout << "奖品详情：" ;
        if(Input_B(inf,max_n+1) == 0) return;
        itoa(num_p,N,10);
        fwrite(prz_n_s,s_c,1,inf_prz);
        fwrite(N,s_c,strlen(N),inf_prz);
        Blank(inf_prz);
        fwrite(prz_name,s_c,1,inf_prz);
        fwrite(name,s_c,strlen(name),inf_prz);
        Blank(inf_prz);
        fwrite(inf,s_c,strlen(inf),inf_prz);
        Blank(inf_prz);
        fwrite(prz_n_e,s_c,1,inf_prz);
    }
    fclose(inf_prz);
    cout << "设置成功！" << endl;
    hitback();
}

void Lottery_set_m()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz_m.txt","w")) == NULL){
        cout << "打开文件失败" << endl;
        return;
    }
    char name[n_name];
    char N[3];
    char inf[max_n+1];
    int num_n = 0;
    int num_t = 0;
    int num_p = 0;
    int i = 0;
    int j = 0;

    cout << line << "设置多组抽奖奖项" << line << endl;

    while(num_n<=0||num_n>=9){
        cout << "奖品组数：" ;
        num_n = Input_N(answer);
    }
    itoa(num_n,N,10);
    fwrite(N,s_c,strlen(N),inf_prz);

    for(i=0;i<num_n;i++){
        cout <<line<< "第" << i+1 <<"组奖品"<< endl;
        num_t = 0;
        while(num_t<=0||num_t>9){
            cout << "奖品种类数(1-9)：";
            num_t = Input_N(answer);
        }
        Blank(inf_prz);
        fwrite(prz_m_s,s_c,1,inf_prz);
        itoa(num_t,N,10);       //数字转字符
        fwrite(N,s_c,strlen(N),inf_prz);
        Blank(inf_prz);

        for(j=0;j<num_t;j++){
            cout << j+1 << "号奖品："<< endl;
            cout << "名称：" ;
            if(Input_B(name,n_name) == 0) return;
            num_p = 0;
            while(num_p <=0){
                cout << "数量：" ;
                num_p = Input_N(answer);
            }

            cout << "奖品详情：" ;
            if(Input_B(inf,max_n+1) == 0) return;
            itoa(num_p,N,10);
            fwrite(prz_n_s,s_c,1,inf_prz);
            fwrite(N,s_c,strlen(N),inf_prz);
            Blank(inf_prz);
            fwrite(prz_name,s_c,1,inf_prz);
            fwrite(name,s_c,strlen(name),inf_prz);
            Blank(inf_prz);
            fwrite(inf,s_c,strlen(inf),inf_prz);
            Blank(inf_prz);
            fwrite(prz_n_e,s_c,1,inf_prz);
        }
        fwrite(prz_m_e,s_c,1,inf_prz);
    }
    fclose(inf_prz);
    cout << "设置成功！" << endl;
    hitback();
}

void Info()
{
    while(1){
        clrscr();
        cout << line << "信息查看" << line << endl;
        cout << "1.抽奖简介" << endl;
        cout << "2.奖品信息" << endl;
        cout << "3.历史抽奖信息" << endl;
        cout << "4.用户信息" << endl;
        cout << "5.关于我们" << endl;
        cout << "6.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: Info_introduce(); break;
            case 2: Info_prize(); break;
            case 3: Info_history(); break;
            case 4: Info_User(); break;
            case 5: About_Us(); break;
            case 6: return;
            default: num = 0;break;
        }
    }
}

void Info_introduce()
{
    clrscr();
    if((inf_itdc = fopen("sys_inf/inf_itdc.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        return;
    }
    char word = '0';
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
    while(1){
        clrscr();
        cout << line <<"奖品信息查看" << line << endl;
        cout << "1.查看单组抽奖奖品信息" << endl;
        cout << "2.查看多组抽奖奖品信息" << endl;
        cout << "3.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: Info_prz_s(); break;
            case 2: Info_prz_m(); break;
            case 3: return;
            default: num = 0; break;
        }
    }
}

void Info_prz_s()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        hitback();
        return;
    }
    char word = fgetc(inf_prz);
    int n_t = word - '0';
    int i = 0;

    cout << line << "奖品信息" << line << endl;
    for(i=0;i<n_t;i++){
        while(word!=prz_n_s[0]) word = fgetc(inf_prz);
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
        word = '0';
        cout << endl <<"奖品信息：";
        while(word!='\n') {
            word = fgetc(inf_prz);
            if(word==prz_n_e[0]) break;
            cout << word;
        }
    }
    hitback();
    fclose(inf_prz);
}

void Info_prz_m()
{
    clrscr();
    if((inf_prz = fopen("sys_inf/inf_prz_m.txt","r")) == NULL){
        cout << "读取信息失败" << endl;
        hitback();
        return;
    }
    char word = fgetc(inf_prz);
    int n_t = word - '0';
    int n_p = 0;
    int i = 0;
    int j = 0;

    cout << line << "奖品信息" << line << endl;
    cout << "奖品组数：" << n_t << endl;
    for(i=0;i<n_t;i++){
        cout << line << "第" << i+1 << "组奖品："<< endl;
        cout << "奖品种类数：" ;
        while(word!=prz_m_s[0]) word = fgetc(inf_prz);
        for(j=0;word!='\n';j++) {
            word = fgetc(inf_prz);
            answer[j] = word;
            cout << word;
        }
        n_p = atoi(answer);
        for(j=0;j<n_p;j++){
            while(word!=prz_n_s[0]) word = fgetc(inf_prz);
            cout <<"奖品"<<j+1<<endl;
            cout << "数量：" ;
            while(word!='\n') {
                word = fgetc(inf_prz);
                cout << word;
            }
            word = fgetc(inf_prz);
            cout << "名称: ";
            while((word = fgetc(inf_prz))!='\n')
                cout << word;
            word = '0';
            cout << endl <<"奖品信息：";
            while(word!='\n') {
                word = fgetc(inf_prz);
                if(word==prz_n_e[0]) break;
                cout << word;
            }
        }
    }
    hitback();
    fclose(inf_prz);
}

void Info_history()
{
    clrscr();
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","r")) == NULL){
        cout << "暂无历史抽奖信息" << endl;
        hitback();
        return;
    }
    char word = '0';
    int counter = 0;
    while(word!=EOF){
        word = fgetc(inf_hstr);
        if(word == '\n') counter++;
        cout << word;
        if(counter >=20){
            cout << endl <<"a键下一页,";
            cout <<"其他键返回"<<endl;
            cin>>word;
            if(word == 'a') {
                counter = 0;
                clrscr();
            } else  return;
        }
    }
    hitback();
    fclose(inf_hstr);
}

void Info_User()
{
    clrscr();
    char word = '0';
    char id[id_len];

    cout << line << "用户信息" << endl;
    cout << "输入想要查看的用户ID: ";
    if(Input(id,id_len) == 0) return;
    int len = strlen(id)+strlen(path);
    char *ID = new char[len+1];
    F_Add(path,id,ID);
    if((inf_user = fopen(ID,"r"))==NULL){
        cout << "不存在用户: " << id << endl;
        delete ID;
        hitback();
        return;
    }
    if((IDs = fopen("sys_inf/IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        delete ID;
        hitback();
        return;
    }
    cout << "姓名：" ;
    int i = 0;
    int j = 0;
    int out = 0;
    int recorder = 0;
    int l = strlen(id);
    char line[id_len];
    while(!out){
        recorder = 0;
        for(i=0;i<id_len;i++) line[i] = '\0';
        for(word='a';word!=id_sign[0];word=fgetc(IDs));
        for(i=0;(word = fgetc(IDs))!=name_sign[0];i++)
            line[i] = word;
        if(l == i){
            for(j=0;j<i;j++){
                if(line[j]==id[j]) recorder++;
            }
            if(recorder == i) {
                while((word = fgetc(IDs))!='\n') cout << word;
                out = 1;
            }
        }
        while((word=fgetc(IDs))!='\n'&&word!=EOF);
    }

    word = '0';
    cout << endl<<"年龄：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = '0';
    cout << "性别：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = '0';
    cout << "简介：";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    cout << endl;
    fclose(inf_user);
    delete ID;
    hitback();
}

void About_Us()
{
    char word = '0';
    clrscr();
    FILE *about ;
    if((about = fopen("sys_inf/about_us.txt","r"))==NULL){
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

void User_set()
{
    while(1){
        clrscr();
        cout << line << "用户管理" << line << endl;
        cout << "1.添加用户" << endl;
        cout << "2.删除用户" << endl;
        cout << "3.修改用户信息" << endl;
        cout << "4.返回" << endl;
        num = Input_N(answer);
        switch(num){
            case 1: User_add(); break;
            case 2: User_delete(); break;
            case 3: User_info_c(); break;
            case 4: return;
            default: num = 0;break;
        }
    }
}

void User_add()
{
    int age = 0;
    int sex = 0;
    char id[id_len];
    char AGE[3];
    char name[n_name];
    char info[max_n+1];
    clrscr();
    cout << line << "添加用户" << line << endl;
    cout << "登记用户信息：" << endl;
    cout << "ID(用户身份识别码): ";
    if(Input(id,id_len) == 0) return;
    int len = strlen(id)+strlen(path);
    char *ID = new char[len+1];
    F_Add(path,id,ID);
    if((inf_user = fopen(ID,"r"))!=NULL){
        cout << "用户已存在" << endl;
        delete ID;
        fclose(inf_user);
        hitback();
        return;
    }

    cout << "姓名(10字节)：" ;
    if(Input(name,n_name) == 0) return;

    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        age = Input_N(answer);
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        sex = Input_N(answer);
    }
    cout << ID <<endl;

    cout << "个人简介(100字节):" << endl;
    if(Input_B(info,max_n+1) == 0) return;

    if((inf_user = fopen(ID,"w+"))==NULL){
        cout << "创建用户信息失败" << endl;
        delete ID;
        hitback();
        return;
    }
    if((IDs = fopen("sys_inf/IDs.txt","a+")) == NULL){
        cout << "创建用户ID失败" << endl;
        remove(ID);
        delete ID;
        fclose(inf_user);
        hitback();
        return;
    }

    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if((sex-'0') == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);

    fwrite(id_sign,s_c,1,IDs);
    fwrite(id,s_c,strlen(id),IDs);
    fwrite(name_sign,s_c,1,IDs);
    fwrite(name,s_c,strlen(name),IDs);
    Blank(IDs);

    fclose(IDs);
    fclose(inf_user);
    cout << "添加用户：" << id << "成功" << endl;
    delete ID;
    hitback();
}

void User_delete()
{
    clrscr();
    char id[id_len];
    cout << line << "删除用户" << line << endl;
    cout << "请输入要删除的用户的ID" << endl;
    if(Input(id,id_len) == 0) return;
    int len = strlen(id)+strlen(path);
    char *ID = new char[len+1];
    F_Add(path,id,ID);
    if((inf_user = fopen(ID,"r")) == NULL){
        cout << "不存在ID:"<< id << endl;
        delete ID;
        hitback();
        return;
    }
    fclose(inf_user);
    clrscr();

    cout << "确定要删除ID：" << id <<"?"<< endl;

    while(1){
        cout << "1.确认删除" <<endl<<"2.返回" << endl;
        num = Input_N(answer);
        if(num == 1){
                if(Delete_ID(id)==1){
                    if((remove(ID))==0)
                        cout << "删除成功！" << endl;
                    else cout << "删除失败！" << endl;
                    delete ID;
                    hitback();
                    return;
                }else cout << "删除失败！" << endl;
        }else if(num == 2){
            delete ID;
            return;
        }
    }
    delete ID;
}

int Delete_ID(char *ID)
{
    FILE *IDs_Backup;
    if((IDs=fopen("sys_inf/IDs.txt","r"))==NULL){
        cout << "删除用户ID失败" << endl;
        hitback();
        return 0;
    }
    if((IDs_Backup=fopen("sys_inf/IDs_Backup.txt","w+"))==NULL){
        cout << "删除用户ID失败" << endl;
        fclose(IDs);
        hitback();
        return 0;
    }

    int i = 0;
    int j = 0;
    int len = strlen(ID);
    int s_l = id_len+n_name+2;
    int out = 0;
    int recorder = 0;
    char line[s_l];
    char word = '0';

    while(!out){
        recorder = 0;
        word = 'a';
        for(i=0;i<s_l;i++) line[i] = '\0';
        for(i=0;word!='\n';i++){
            word = fgetc(IDs);
            if(word == EOF) {
                out = 1; break;
            }
            line[i] = word;
        }
        if(out==1) break;
        //cout << line << "end" << endl;
        for(i=0;line[i]!=name_sign[0]&&line[i]!='\n';i++);
        //cout << i << ":" << len << endl;
        i--;
        if(i==len){
            for(j=0;j<len;j++){
                if(line[j+1]==ID[j]) recorder++;
            }
            if(recorder == len) continue;
        }
        fwrite(line,s_c,strlen(line),IDs_Backup);
//        while(word!='\n') word = fgetc(IDs);
    }
    /*
   while(!out){
        recorder = 0;
        word = '0';
        for(i=0;i<s_l;i++) line[i] = '\0';
        for(i=0;word!=id_sign[0];i++){
            word = fgetc(IDs);
            if(word == EOF) {
                out = 1; break;
            }
            line[i] = word;
        }
        if(out==1) break;
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
    */
    fclose(IDs);
    fclose(IDs_Backup);
    if((remove("sys_inf/IDs.txt"))!=0) {
            remove("sys_inf/IDs_Backup.txt");
            return 0;
    }
    rename("sys_inf/IDs_Backup.txt","sys_inf/IDs.txt");
    return 1;
}

void User_info_c()
{
    int age = 0;
    char sex = '0';
    char AGE[3];
    char id[id_len];
    char info[max_n+1];
    clrscr();
    cout << line << "修改用户信息：" << line << endl;
    cout << "输入要修改的ID" << endl;
    if(Input(id,id_len) == 0) return;
    int len = strlen(id)+strlen(path);
    char *ID = new char[len+1];
    F_Add(path,id,ID);

    if((inf_user = fopen(ID,"r")) == NULL){
        cout << "读取用户数据失败" << endl;
        delete ID;
        hitback();
        return;
    }
    fclose(inf_user);
    while(age<=0||age>99){
        cout << "年龄(1-99)：";
        age = Input_N(answer);
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "性别：1.男\t2.女" << endl;
        sex = Input_N(answer);
    }
    cout << "个人简介(100字节):" << endl;
    if(Input_B(info,max_n+1) == 0) return;

    if((inf_user = fopen(ID,"w"))==NULL){
        cout << "写入用户数据失败" << endl;
        hitback();
        return;
    }
    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if((sex-'0') == 1) fwrite("男",s_c,2,inf_user);
    else fwrite("女",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fclose(inf_user);
    delete ID;
    cout << "修改成功！" << endl;
    hitback();
    return;
}

void Lottery()
{
    while(1){
        clrscr();
        cout << line <<"抽奖"<< line <<endl;
        cout << "1.单组抽奖" <<endl;
        cout << "2.多组抽奖" <<endl;
        cout << "3.返回" << endl;

        num = Input_N(answer);
        switch(num){
            case 1: Single(); break;
            case 2: Multi(); break;
            case 3: return;
            default : num = 0; break;
        }
    }
}

void Single()
{
    if((IDs = fopen("sys_inf/IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        hitback();
        return;
    }
    if((inf_prz = fopen("sys_inf/inf_prz.txt","r"))==NULL){
        cout << "读取奖品信息失败！" << endl;
        fclose(inf_user);
        hitback();
        return;
    }
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","a"))==NULL){
        cout << "读取历史信息失败！" << endl;
        fclose(inf_user);
        fclose(inf_prz);
        hitback();
        return;
    }
    clrscr();
    srand((int)time(NULL));
    Sroll(IDs);
    char word = '0';
    char ID[id_len];
    char NAME[n_name];
    int i = 0;
    int j = 0;
    int k = 0;
    int n_id = 0;       //用户总数
    int id_rest;     //未中奖用户数
    char num_prz[2];        //奖品种类数
    for(i=0;i<2;i++) num_prz[i] = fgetc(inf_prz);
    int n_prz = atoi(num_prz);  //奖品种类数
    int n_p = 0;            //单个奖品数量
    int id_line=0;         //中奖用户的ID位置
    int counter = 0;
    int line_list[n_prz*99];         //储存已中奖用户

    while(word!=EOF){
        word = fgetc(IDs);
        if(word == id_sign[0]) n_id++;
    }
    id_rest = n_id;

    cout <<line << "抽奖结果：" << endl;
    for(i=0;i<n_prz;i++){   //循环抽奖品总数次
        while(word != prz_n_s[0]) word = fgetc(inf_prz);
        for(j=0;j<2;j++) num_prz[j] = fgetc(inf_prz);
        for(j=0;j<n_name;j++) NAME[j] = '\0';   //初始化奖品名称
        while(word != prz_name[0]) word = fgetc(inf_prz);
        for(j=0;(word = fgetc(inf_prz))!='\n';j++)
            NAME[j] = word;
        n_p = atoi(num_prz);    //读取此种奖品数量

        for(j=0;j<n_p;j++){         //循环抽此奖品数量次
            for(k=0;k<id_len;k++)   //初始化ID
                ID[k] = '\0';
            while(1){               //随机ID
                id_line = rand()%n_id;
                if(!Used_Line(id_line,counter,line_list)) break;
            }
            line_list[counter] = id_line;             //储存中奖ID
            Get_ID(ID,id_line,IDs);        //读取用户ID
            cout <<"恭喜ID：" <<ID<< " 中奖：";
            cout << NAME << endl;

            id_rest--;              //剩余ID数-1
            if(id_rest<=0){        //判断用户是否有剩余
                cout << "已无用户！" << endl;
                hitback();
                return;
            }

            Record_Time(inf_hstr);
            fwrite("中奖ID: ",s_c,8,inf_hstr);
            fwrite(ID,s_c,strlen(ID),inf_hstr);
            fwrite("\0|\0",s_c,3,inf_hstr);
            fwrite(" 奖品名称：",s_c,11,inf_hstr);
            fwrite(NAME,s_c,strlen(NAME),inf_hstr);
            Blank(inf_hstr);
            counter++;
        }
    }

    fclose(IDs);
    fclose(inf_prz);
    fclose(inf_hstr);
    hitback();
}

void Multi()
{
    if((IDs = fopen("sys_inf/IDs.txt","r"))==NULL){
        cout << "读取用户信息失败！" << endl;
        hitback();
        return;
    }
    if((inf_prz = fopen("sys_inf/inf_prz_m.txt","r"))==NULL){
        cout << "读取奖品信息失败！" << endl;
        fclose(inf_user);
        hitback();
        return;
    }
    if((inf_hstr = fopen("sys_inf/inf_hstr.txt","a"))==NULL){
        cout << "读取历史信息失败！" << endl;
        fclose(inf_user);
        fclose(inf_prz);
        hitback();
        return;
    }
    clrscr();
    srand((int)time(NULL));
    Sroll(IDs);
    char word = '0';
    char ID[id_len];
    char NAME[n_name];
    int i = 0;
    int j = 0;
    int k = 0;
    int c = 0;
    int n_id = 0;       //用户总数
    int id_rest;     //未中奖用户数
    char num_prz[2];        //奖品种类数
    for(i=0;i<2;i++) num_prz[i] = fgetc(inf_prz);
    int n_prz = atoi(num_prz);  //奖品种类数
    int n_p_t = 0;
    int n_p = 0;            //单个奖品数量
    int id_line=0;         //中奖用户的ID位置
    int counter = 0;
    int line_list[n_prz*99];         //储存已中奖用户

    while(word!=EOF){
        word = fgetc(IDs);
        if(word == id_sign[0]) n_id++;
    }
    id_rest = n_id;

    cout << line << "抽奖结果：" << endl;
    for(i=0;i<n_prz;i++){   //循环抽奖品总数次
        cout << "第" << i+1 << "组抽奖：" << endl;
        while(word!=prz_m_s[0]) word = fgetc(inf_prz);
        for(j=0;word!='\n';j++) {
            word = fgetc(inf_prz);
            answer[j] = word;
        }
        n_p_t = atoi(answer);
        for(j=0;j<n_p_t;j++){
            while(word != prz_n_s[0]) word = fgetc(inf_prz);
            for(k=0;k<2;k++) num_prz[k] = fgetc(inf_prz);
            for(k=0;k<n_name;k++) NAME[k] = '\0';   //初始化奖品名称
            while(word != prz_name[0]) word = fgetc(inf_prz);
            for(k=0;(word = fgetc(inf_prz))!='\n';k++)
                NAME[k] = word;
            n_p = atoi(num_prz);    //读取此种奖品数量
            for(k=0;k<n_p;k++){         //循环抽此奖品数量次
                for(c=0;c<id_len;c++)   //初始化ID
                    ID[c] = '\0';
                while(1){               //随机ID
                    id_line = rand()%n_id;
                    if(!Used_Line(id_line,counter,line_list)) break;
                }
                line_list[counter] = id_line;             //储存中奖ID
                Get_ID(ID,id_line,IDs);        //读取用户ID
                cout <<"恭喜ID：" <<ID<< " 中奖：";
                cout << NAME << endl;

                id_rest--;              //剩余ID数-1
                if(id_rest<=0){        //判断用户是否有剩余
                    cout << "已无用户！" << endl;
                    hitback();
                    return;
                }
                Record_Time(inf_hstr);
                fwrite("中奖ID: ",s_c,8,inf_hstr);
                fwrite(ID,s_c,strlen(ID),inf_hstr);
                fwrite("\0|\0",s_c,3,inf_hstr);
                fwrite(" 奖品名称：",s_c,11,inf_hstr);
                fwrite(NAME,s_c,strlen(NAME),inf_hstr);
                Blank(inf_hstr);
                counter++;
            }
        }
    }

    fclose(IDs);
    fclose(inf_prz);
    fclose(inf_hstr);
    hitback();

}

void Get_ID(char *str, int line, FILE *file)
{
    fseek(file,0,SEEK_SET);
    char out = '0';
    int k = 0;
    for(k=-1;k<line;out = fgetc(file)){
        if(out == id_sign[0]) k++;
    }
    for(k=0;out!=name_sign[0];k++){
        str[k] = out;
        out = fgetc(file);
    }
}

int Used_Line(int id, int m, int line_list[])
{
    int k = 0;
    for(k=0;k<m;k++){
        if(id==line_list[k])
            return 1;
    }
    return 0;
}

void F_Add(char *f,char *b,char *t)
{
    int i = 0;
    int j = 0;

    int len1 = strlen(f);
    int len2 = strlen(b);
    int len3 = strlen(t);
    for(i=0;i<len3;i++) t[i] = '\0';
    for(i=0;i<len1;i++) t[i] = f[i];
    for(j=0;j<len2;j++) t[j+i] = b[j];
}

void Sroll_set()
{
    clrscr();
    if((IDs=fopen("sys_inf/IDs.txt","r"))==NULL){
        cout << "打开文件失败！"<< endl;
        hitback();
        return;
    }
    cout << line << "滚动设置"<< line << endl;
    cout << "设置滚动次数(0-100)"<< endl;

    int num = -1;
    while(num<0||num>100)
            num = Input_N(answer);
    itoa(num,answer,10);
    FILE *IDs_Backup;
    if((IDs_Backup = fopen("sys_inf/IDs_Backup.txt","w"))==NULL){
        cout << "修改失败！"<< endl;
        fclose(IDs);
        hitback();
        return;
    }
    char word = 'a';
    while(word!='\n') word = fgetc(IDs);
    fwrite(answer,s_c,strlen(answer),IDs_Backup);
    Blank(IDs_Backup);
    while(answer[0]!=EOF){
        answer[0] = fgetc(IDs);
        fwrite(answer,s_c,1,IDs_Backup);
    }
    fclose(IDs);
    fclose(IDs_Backup);
    remove("sys_inf/IDs.txt");
    rename("sys_inf/IDs_Backup.txt","sys_inf/IDs.txt");
    cout << "修改成功！" << endl;
    hitback();
}

void Sroll(FILE *file)
{
    int i = 0;
    int j = 0;
    int id = 0;
    int n_id = 0;
    char word = 'a';
    char ID[id_len];
    for(i=0;i<n_name;i++){
        word = fgetc(file);
        if(word!=name_sign[0]) ID[i] = word;
        else break;
    }
    while(word!=EOF){
        word = fgetc(IDs);
        if(word == id_sign[0]) n_id++;
    }
    int times = atoi(ID);

    for(i=0;i<times;i++){
        clrscr();
        id = rand()%n_id;
        for(j=0;j<id_len;j++) ID[j] = '\0';
        Get_ID(ID,id,file);
        cout << line << line << line << endl;
        cout <<"正在抽奖：" << ID << endl;
        cout << line << line << line << endl;
    }
    fseek(file,0,SEEK_SET);
    clrscr();
}

void Record_Time(FILE *file)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    int year = p->tm_year - 100;
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

int Illegal_word(char word)
{
    int j = 0;
    for(j=0;j<n_illegal;j++){
        if(word == illegal_word[j]) {
                cout << "检测到非法字符：";
                cout << word << endl;
                return 1;
        }
    }
    return 0;
}

int Input(char* input, int len)
{
    int i = 0;
    int l = 0;
    int illegal = 0;
    while(1){
        illegal = 0;
        cin.sync();
        cin.getline(input,len,'\n');
        l = strlen(input);
        if(l == 0) return 0;
        if(l>id_len) illegal = 1;
        else for(i=0;i<l;i++){
            if(Illegal_word(input[i]) == 1) illegal = 1;
            if(input[i] == ' ') {
                    cout << "此处禁止输入空格符！" << endl;
                    illegal = 1;
            }
        }
        if(illegal == 1) cout << "请重新输入: ";
        else return 1;
    }
}

int Input_B(char* input, int len)
{
    int i = 0;
    int l = 0;
    int illegal = 0;
    while(1){
        illegal = 0;
        cin.sync();
        cin.getline(input,len,'\n');
        l = strlen(input);
        if(l == 0) return 0;
        else for(i=0;i<l;i++){
            if(input[i] == 27) return 0;
            if(Illegal_word(input[i]) == 1) illegal = 1;
        }
        if(illegal == 1) cout << "请重新输入: ";
        else return 1;
    }
    return 1;
}

int Input_N(char *input)
{
    num = 0;
    int i = 0;
    for(i=0;i<2;i++) input[i] = '\0';
    while(1){
        cin >> input;
        if(input[0]=='0') return 0;
        if((num=atoi(input))!=0) break;
    }
    return num;
}

void clrscr()
{
    system("cls");
}

void hitback()
{
    cout << endl;
    system("pause");
}

void Blank(FILE* file)
{
    fwrite("\n",s_c,1,file);
}
