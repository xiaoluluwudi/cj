#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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
char line[6]="-----";

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
int Delete_ID(char *ID);
int Existe_ID(char *ID);


int main()
{
    Instructions();
    MainPage();
    return 0;
}

void Instructions()
{
    clrscr();
    cout << line <<"��ӭ�����齱ϵͳ" << line << endl;
    cout << "1.��ʼ�齱" << endl;
    cout << "2.��̨����" << endl;
    cout << "3.��Ϣ�鿴" << endl;
    cout << "4.�˳�" << endl;
}

int MainPage()
{
    int answer = 0;
    while(1){
        cin >> answer;
        switch(answer){
//        case 1: Lottery(); break;
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
        cout << line <<"��ӭ������̨" << line << endl;
        cout << "1.������Ϣ���" << endl;
        cout << "2.���ý���" << endl;
        cout << "3.�޸ĳ齱��ʷ��Ϣ" << endl;
        cout << "4.�û�����" << endl;
        cout << "5.����" << endl;
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
        cout << "���ļ�ʧ��" << endl;
        hitback();
        return;
    }
    char inf[max_n+1];
    cout << line << "������Ϣ���" << line << endl;
    cout << "�༭�齱��Ϣ��飺" << endl;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_itdc);
    fclose(inf_itdc);
}

void History_set()
{
    clrscr();
    if((inf_hstr = fopen("inf_hstr.txt","w+")) == NULL){
        cout << "��ȡ��Ϣʧ��" << endl;
        return;
    }
    int times = 0;  //�ܳ齱����
    int t_f = 0;    //һ�Ƚ��齱����
    int t_s = 0;    //���Ƚ��齱����
    int t_t = 0;    //���Ƚ��齱����

    cout << line << "�޸ĳ齱��ʷ��Ϣ" << line << endl;
    while(times<=0||times>=10000){
        cout << "�ܳ齱����(����0С��10000)��";
        cin >> times;
    }
    while(t_f<=0||t_f>times){
        cout << "һ�Ƚ�����(����0С��" << times+1 << "):";
        cin >> t_f;
    }
    while(t_s<=0||t_s>times){
        cout << "���Ƚ�����(����0С��" << times+1 << "):";
        cin >>t_s;
    }
    while(t_t<=0||t_s>times){
        cout << "���Ƚ�����(����0С��" << times+1 << "):";
        cin >> t_t;
    }
    char times_c[5];
    char t_f_c[5];
    char t_s_c[5];
    char t_t_c[5];
    itoa(times,times_c,10);
    itoa(t_f,t_f_c,10);
    itoa(t_s,t_s_c,10);
    itoa(t_t,t_t_c,10);
    fwrite(times_c,s_c,strlen(times_c),inf_hstr);
    Blank(inf_hstr);
    fwrite(t_f_c,s_c,strlen(t_f_c),inf_hstr);
    Blank(inf_hstr);
    fwrite(t_s_c,s_c,strlen(t_s_c),inf_hstr);
    Blank(inf_hstr);
    fwrite(t_t_c,s_c,strlen(t_t_c),inf_hstr);
    Blank(inf_hstr);
    fclose(inf_hstr);
}

void Lottery_set()
{
    clrscr();
    if((inf_itdc = fopen("inf_prz.txt","w")) == NULL){
        cout << "���ļ�ʧ��" << endl;
        return;
    }
    char name[n_name];
    char N[3];
    char inf[max_n+1];
    int num = 0;

    cout << line << "���ý���" << line << endl;
    for(i=1;i<4;i++){
        cout << "����" << i << "�Ƚ�" << endl;;
        cout << "���ƣ�" ;
        cin >> name;
        while(1){
            cout << "��Ʒ����(����" << min_n << "С��" << max_n << ")" << endl;
            cin >> num;
            if(num<=min_n||num >= max_n) cout << "���Ϸ������֣�����������" <<endl;
            else break;
        }
        itoa(num,N,10);
        fwrite(name,s_c,strlen(name),inf_itdc);
        fwrite("\n",s_c,1,inf_itdc);
        fwrite(N,s_c,strlen(N),inf_itdc);
        fwrite("\n",s_c,1,inf_itdc);
    }
    fclose(inf_itdc);
    if((inf_prz_1 = fopen("inf_prz_1.txt","w"))==NULL||(inf_prz_2 = fopen("inf_prz_2.txt","w"))==NULL||(inf_prz_3 = fopen("inf_prz_3.txt","w"))==NULL){
        cout << "�༭��Ʒ����ҳʧ�ܣ�" << endl;
        return;
    }
    for(i=0;i<max_n+1;i++)
        inf[i] = '\0';
    cout << "һ�Ƚ���Ϣ��" ;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_prz_1);
    for(i=0;i<max_n+1;i++)
        inf[i] = '\0';
    cout << "���Ƚ���Ϣ��" ;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_prz_2);
    for(i=0;i<max_n+1;i++)
        inf[i] = '\0';
    cout << "���Ƚ���Ϣ��" ;
    cin >> inf;
    fwrite(inf,s_c,strlen(inf),inf_prz_3);
    fclose(inf_prz_1);
    fclose(inf_prz_2);
    fclose(inf_prz_3);
}

void Info()
{
    int answer=0;
    while(!answer){
        clrscr();
        cout << line << "��Ϣ�鿴" << line << endl;
        cout << "1.�齱���" << endl;
        cout << "2.��Ʒ��Ϣ" << endl;
        cout << "3.��ʷ�齱��Ϣ" << endl;
        cout << "4.�û���Ϣ" << endl;
        cout << "5.����" << endl;
        cin >> answer;
        switch(answer){
            case 1: Info_introduce(); break;
            case 2: Info_prize(); break;
            case 3: Info_history(); break;
            case 4: Info_User(); break;
            case 5: return;
            default: answer = 0;break;
        }
        answer = 0;
    }
}

void Info_introduce()
{
    clrscr();
    if((inf_itdc = fopen("inf_itdc.txt","r")) == NULL){
        cout << "��ȡ��Ϣʧ��" << endl;
        return;
    }
    char word = 'a';
    cout << line << "�齱���" << line <<endl;
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
        cout << "��ȡ��Ϣʧ��" << endl;
        return;
    }
    char word = 'a';

    cout << line << "��Ʒ��Ϣ" << line << endl;
    for(i=1;i<4;i++){
        cout << i << "�Ƚ�: ";
        while(1){
            word = fgetc(inf_prz);
            if(word == '\n') break;
            cout << word;
        }
        cout << " ����: ";
        while(1){
            word = fgetc(inf_prz);
            if(word == '\n') break;
            cout << word;
        }
        cout << endl;
    }
    if((inf_prz_1 = fopen("inf_prz_1.txt","r"))==NULL){
        cout << "��ȡ��Ʒ����ʧ��" << endl;
        return;
    }
    if((inf_prz_2 = fopen("inf_prz_2.txt","r"))==NULL){
        cout << "��ȡ��Ʒ����ʧ��" << endl;
        return;
    }
    if((inf_prz_3 = fopen("inf_prz_3.txt","r"))==NULL){
        cout << "��ȡ��Ʒ����ʧ��" << endl;
        return;
    }
    word = 'a';
    cout << "��Ʒ����:" << endl;
    cout << "һ�Ƚ���";
    while(word!=EOF){
        word = fgetc(inf_prz_1);
        cout << word;
    }
    word = 'a';
    cout << endl << "���Ƚ�: ";
    while(word!=EOF){
        word = fgetc(inf_prz_2);
        cout << word;
    }
    word = 'a';
    cout << endl << "���Ƚ�: ";
    while(word!=EOF){
        word = fgetc(inf_prz_3);
        cout << word;
    }
    cout<<endl;
    hitback();
    fclose(inf_prz);
}

void Info_history()
{
    clrscr();
    if((inf_hstr = fopen("inf_hstr.txt","r")) == NULL){
        cout << "��ȡ��Ϣʧ��" << endl;
        return;
    }

    char word = 'a';
    cout << line << "��ʷ�齱��Ϣ" << line << endl;
    cout << "�ܿ���������" ;
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl << "һ�Ƚ�����������";
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl << "���Ƚ�����������";
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl << "���Ƚ�����������" ;
    while((word = fgetc(inf_hstr))!='\n'&&word!=EOF)
        cout << word;
    cout << endl;
    hitback();
    fclose(inf_hstr);
}

void Info_User()
{
    clrscr();
    char word = 'a';
    char ID[id_len];
    cout << line << "�û���Ϣ" << endl;
    cout << "������Ҫ�鿴���û�ID: ";
    cin >> ID;
    if((inf_user = fopen(ID,"r"))==NULL){
        cout << "�������û�: " << ID << endl;
        hitback();
        return;
    }
    cout << "������";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "���䣺";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "�Ա�";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    word = 'a';
    cout << endl << "��飺";
    while(word!='\n'&&word!=EOF){
        word = fgetc(inf_user);
        cout << word;
    }
    cout << endl;
    hitback();
    fclose(inf_user);
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
        cout << line << "�û�����" << line << endl;
        cout << "1.����û�" << endl;
        cout << "2.ɾ���û�" << endl;
        cout << "3.�޸��û���Ϣ" << endl;
        cout << "4.����" << endl;
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
    cout << line << "����û�" << line << endl;
    cout << "�Ǽ��û���Ϣ��" << endl;
    cout << "ID(�û����ʶ����): ";
    cin >> ID;
    if((inf_user = fopen(ID,"r"))!=NULL){
        cout << "�û��Ѵ���" << endl;
        hitback();
        fclose(inf_user);
        return;
    }

    cout << "����(10�ֽ�)��" ;
    cin >> name;
    while(age<=0||age>99){
        cout << "����(1-99)��";
        cin >> age;
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "�Ա�1.��\t2.Ů" << endl;
        cin >> sex;
    }
    cout << "���˼��(100�ֽ�):" << endl;
    cin >> info;

    if((inf_user = fopen(ID,"w+"))==NULL){
        cout << "����û�ʧ��" << endl;
        hitback();
        return;
    }
    if((IDs = fopen("IDs.txt","a+")) == NULL){
        cout << "����û�ʧ��" << endl;
        hitback();
        return;
    }

    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("��",s_c,2,inf_user);
    else fwrite("Ů",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fwrite(ID,s_c,strlen(ID),IDs);
    fwrite("&",s_c,1,IDs);
    fwrite(name,s_c,strlen(name),IDs);
    fwrite("\n",s_c,1,IDs);

    fclose(IDs);
    fclose(inf_user);
}

void User_delete()
{
    clrscr();
    int answer = 0;
    char ID[14];
    cout << line << "ɾ���û�" << line << endl;
    cout << "������Ҫɾ�����û���ID" << endl;
    cin >> ID;
    if((inf_user = fopen(ID,"r")) == NULL){
        cout << "�������û�����������" << endl;
        hitback();
        return;
    }
    fclose(inf_user);
    clrscr();

    cout << "ȷ��Ҫɾ��ID��" << ID << endl;

    while(answer == 0){
        cout << "1.ȷ��ɾ��" <<endl<<"2.����" << endl;
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
        cout << "ɾ���û�IDʧ��" << endl;
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
    cout << "ɾ���ɹ���" << endl;
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
    cout << line << "�޸��û���Ϣ��" << line << endl;
    cout << "����Ҫ�޸ĵ�ID" << endl;
    cin >> ID;
    if((inf_user = fopen(ID,"r+")) == NULL){
        cout << "��ȡ�û�����ʧ��" << endl;
        hitback();
        return;
    }
    fclose(inf_user);

    while(age<=0||age>99){
        cout << "����(1-99)��";
        cin >> age;
    }
    itoa(age,AGE,10);
    while(sex!=1&&sex!=2){
        cout << "�Ա�1.��\t2.Ů" << endl;
        cin >> sex;
    }
    cout << "���˼��(100�ֽ�):" << endl;
    cin >> info;

    if((inf_user = fopen(ID,"w"))==NULL){
        cout << "д���û�����ʧ��" << endl;
        hitback();
        return;
    }
    fwrite(AGE,s_c,strlen(AGE),inf_user);
    Blank(inf_user);
    if(sex == 1) fwrite("��",s_c,2,inf_user);
    else fwrite("Ů",s_c,2,inf_user);
    Blank(inf_user);
    fwrite(info,s_c,strlen(info),inf_user);
    fclose(inf_user);
    return;
}

