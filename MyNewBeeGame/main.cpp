#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
using namespace std;

#define Xcnt 10 ///�����˸���
#define LevelCnt 9  ///�ؿ���
#define ToTalLevelCnt 100  ///�����ؿ���
#define PI 100  ///��Ϸ�й�����ʹ�õĵ�������
#define Rw 100  ///����ܵ�������
#define WuQiCnt 100  ///��������  ˫��Ϊ�񶷼�װ��������Ϊħ��ʦװ��
#define YiFuCnt  100   ///�·�����  ˫��Ϊ�񶷼�װ��������Ϊħ��ʦװ��
#define XieZiCnt 100   ///Ь������
#define GuaiWCnt  10  ///��������
#define NaiJiu 100   ///װ���;ö�

/// <summary>
/// ����Ϊ����ȫ�ֱ���

///�������
long long int up0,down0,left0,right0,type0,match0;
int up1,down1,left1,right1,type1,match1;
///ǰ����ͼ������
int nextMapX,nextMapY;
///�ж����������ɾ���ʯͷ����
int he701[30]={12,13,22,23,301,310,311,321,330,331,212,221,223,232,511,521,531,532,533,722,912,913,922,923};///24
int shi901[20]={302,313,343,701,710,711,733,734,743,900,910,920,930};///13
///�ж��Ƿ��ɱ��ħ��
int bossFlag=0;
///�ж���Ϸ�Ƿ����
int gameFlag=0;
///�Ƿ�������
int IsMeet=0;
///�ж��Ƿ��ڶ�Ѩ
int IsOnDongxue=0;
///�ж��Ƿ���������
int IsOnShengzi=0;
///�ж��Ƿ��������
int IsOnYidian=0;
///�ж��Ƿ��ںڰ�
int IsDark[22][22]={0};
///Ŀǰ�ڵ�ѧϰ��֯
struct MySchool{
    int xuexiaoLevel=0;
    int wuguanLevel=0;
    int ID=0; ///���� 1ѧУ 2���
    int firrenwu=0;
    int secrenwu=0;
    int thirdrenwu=0;
}myschool;
///�󷨴��͵�Ŀ�ĵ�
int To=-1;
///�ɳ�����
int ChengZhangRenWu[Rw+5]={0};
///�����ܵ���ɱ���������ʱ����
struct CurrentGuaiWuData{
    int number=-1;///��������
    int Id;      ///��������
}currentguaiwudata;
int CurrentGuaiWuData=0;
///ȷ���¼�ʱ���룬��ʵ�ʺ���
char inputC;
///���Ѫ��
int maxHP=50;
///��ǰ��ͼ�й�������
int GuaiNow1=0;
int GuaiNow2=0;
///��װ����װ��
int Mywuqi=-1;
int Myyifu=-1;
int Myxiezi=-1;
///�������
int RenWu[Rw+5]={0};  ///0Ϊδ��ȡ  1Ϊ��ȡ  2Ϊ�����
///�����ʱ����
long long int DisOld; ///�ؿ�������
int markxOld; ///�ؿ���Ϸ���λ��
int markyOld;
///�ж��Ƿ��ں���
int waterFlag = 0;  ///Ϊ1 ʱ���ں���
///�ж��Ƿ���Ұ��
int wildFlag = 0;   ///Ϊ1 ʱ����Ұ��
///�ж��Ƿ�����Զ�ս��
int ZiDong = 0;
///�ж��Ƿ���ս��
int fightFlag = 0;
///�������
int PlayerItems[PI+5]={0};  ///11-20Ϊӵ�е�������21-30Ϊӵ�е�װ����31-40Ϊӵ�е�Ь��  50������ 66������ 99����
///����װ��
    ///����
    struct WuQi{
        string s="test";
        int Zhi;///��Ҫ������ֵ������ֵ
        int Hit;///�˺�ֵ
        int Nai=NaiJiu;///�;�
    }wuqi[WuQiCnt+5];
    ///װ��
    struct YiFu{
        string s="test";
        int Zhi;///��Ҫ������ֵ������ֵ
        int FangYu;///����ֵ  ��Ϊħ��ʦ�Ķ���ʱ������Ϊ���ӵ��ٶ�ֵ
        int Nai=NaiJiu;///�;�
    }yifu[YiFuCnt+5];
    struct XieZi{
        string s="test";
        int Speed; ///�ٶ�
    }xiezi[XieZiCnt+5];
///Ұ�����
struct GuaiWu{  ///˫������������Ұ�֣������Ƿ�������Ұ��
    string s="test";
    int Hp;
    int Hit;
    int Speed;
    int Fangyu;
    int HitData=0; ///��ɱ����

}guaiwu[GuaiWCnt+5];
///�ؿ�����
struct Guanqia{
    string s="test";
    int wild; ///�Ƿ�ΪҰ��
    int level; ///��������
}guanqia[ToTalLevelCnt+5];
///����λ��  �������λ��  �±�������λ�ã���ֵ��������ࣨ��ͼ�е���ֵ����
int guaiwuLocx[25];
int guaiwuLocy[25];
///�ؿ�   �±�ģ26=0ʱΪ���ڵ�ͼ
long long int MyMap[(26*ToTalLevelCnt)+5]={
    0,900,500,0/*����������Ϊ0*/,0,0/*�˴�Ϊ���͵�*/,900,0,700,700,0,900,0,700,700,0,900,400,0,0,300,0,600,600,600,200,
    1,0,0,0,1200,801/*�˴�Ϊ���͵�*/,1200,1200,0,1200,1200,0,1200,1200,0,0,0,0,1200,1200,0,0,0,0,1200,0,
    2,600,600,600,600,803,600,201,700,202,600,600,700,999,700,600,600,203,700,204,600,600,600,600,600,600,
    3,1402,700,900,1303,800+LevelCnt,700,700,600,900,0,1302,700,0,0,0,700,700,0,1301,1401,0,0,0,900,1403,
    4,1201,0,0,0,800+LevelCnt,0,0,1201,1201,1201,1201,0,0,0,0,0,0,0,1201,0,0,1201,0,0,0,
    5,0,0,600,600,1006,600,700,401,301,600,600,700,205,501,600,0,700,700,700,0,0,0,600,600,0,
    6,1202,1202,0,1202,809,0,1202,0,1202,0,1202,0,1202,0,1202,0,1202,0,1202,0,0,0,0,206,1202,
    7,402,900,600,600,1008,900,900,600,302,600,207,0,700,600,600,0,0,809,900,900,0,0,0,900,502,
    8,1203,1203,0,1203,809,0,1203,0,1203,0,1203,0,1203,0,1203,0,1203,0,1203,0,0,0,0,208,1203,
    9,900,503,0,0,1500,900,0,700,700,0,900,0,700,700,0,900,403,1100,0,303,0,600,600,600,209,
    10,1600,0,1700,0,1800,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1101,0,1900,
    11,1600,0,1700,0,1800,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1900,
    12,1600,0,1700,0,1800,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1900,
    13,1600,0,1700,0,1800,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1900,
    14,1600,0,1700,0,1800,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1900,
    15,1600,0,1700,0,1800,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1900,
    16,0,0,0,1205,803,0,1205,0,1205,0,0,1205,0,1205,0,0,1205,0,1205,0,0,1205,0,0,0,
    17,1206,0,1206,0,803,0,1206,0,1206,0,1206,0,1206,0,1206,1206,0,1206,0,1206,0,0,0,0,0,
    18,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    19,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    20,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    21,0,0,0,700,220700, 0,0,0,700,220601, 0,0,0,700,220602, 0,0,0,700,220603, 3200000008,3200000007,3200000006,3200000705,3200220704,
    22,21000700,700,0,0,0, 21000601,700,0,0,0, 21000602,700,0,0,0, 21000603,700,0,0,0, 21000704,2300000705,2300000006,2300000007,2300000008,
    23,2300,220000000005,220000000006,220000000007,220000000008, 32000003,0,0,0,0, 32000002,0,0,0,0, 32000001,0,0,0,0, 32000000,0,0,0,0,
    24,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    25,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    26,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    27,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    28,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    29,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    30,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,2100, 0,0,0,0,0, 0,0,2100,0,0,
    31,0,0,2100,0,0, 0,0,0,0,0, 0,0,0,0,2100, 0,0,0,0,0, 0,0,0,0,0,
    32,210000000008,210000000007,210000000006,210000000005,210000000904, 0,0,0,0,230003, 48002109,2100,0,0,230002, 0,0,2100,0,230001, 0,0,3400002110,0,230000,
    33,0,0,320000002110,0,0, 0,0,0,0,0, 2100,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
    34,0,0,320000002110,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    35,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    36,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    37,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    38,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    39,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    40,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    41,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    42,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    43,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0,
    44,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    45,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    46,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    47,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    48,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,322109, 0,0,0,0,0, 0,0,0,0,0,
    49,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    50,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    51,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    52,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    53,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    54,0,0,2101,0,0, 0,0,2101,0,0, 0,0,2101,2101,2101, 0,0,2101,0,0, 0,0,2101,0,0,
    55,0,0,2101,0,0, 0,0,2101,0,0, 2101,2101,2101,2101,2101, 0,0,0,0,0, 0,0,0,0,0,
    56,0,0,0,0,0, 0,0,0,0,0, 2101,2101,2101,2101,2101, 0,0,2101,0,0, 0,0,2101,0,0,
    57,0,0,2101,0,0, 0,0,2101,0,0, 2101,2101,2101,0,0, 0,0,2101,0,0, 0,0,2101,0,0
};
///�ؿ�������
int Items;   ///��λ����ǰ��λ��ʾ��𣬺���λ��ʾ���壻
/*
  1��    500-599������  ��ʾͬһ����˼
  2��    ��λ��2������λ����ͬ��ʾ��ͬ���ˣ�������ͬ�ĶԻ�
  3��
  4��
  5װ
  6��
  7��
  8��    ����λ��ʾ�����Դ��͵��Ĺؿ�
  9ʯ
  10Ұ
  11��
  12��  �ڵ�ͼ��������ʾ���������
  13ѧ
  14��
  15ħ   ///����BOSS
  16��
  17��
  18��
  19��
  20��
  21��    ///2100��ʾ���Ӿ�ͷ��2101��ʾ�������ϣ���һ��ֻ���ƶ���������
  22��   ///��Ѩ��֩���
  23��
  24��

  ʮ��λ�� ��  ///��Խ��ͼ  ǰ��λ���������ң���ʾ��Խ���ĵ�ͼ���м���λ��ʾ���壻����λ��ʾ��Ӧ���
*/
///չʾ��ͼ
long long int DisPlayMap[5][5];
///�ж��Ƿ���ʾ������   ����Ҫ����
int Tips[Xcnt] = { 0 };
///��ʶ���λ��
int markx=4;       ///x����λ��
int marky=0;       ///y����λ��
int markLevel=0;  ///���ڵڼ�����ͼ
/// </summary>


/// <summary>
/// ����Ϊ���к���
void InitMap(); ///�ڴ������ͼ  ��45��
void PrintMap(); ///��ӡ��ͼ      ��62��
void PlayerMove(); ///����߶�
bool MoveOrNot(); /// �ж��Ƿ��ܹ��н�
void Init(); ///��ʼ����Ϸ����Ʒ�����ߵ�
void ChangeMyData(int i);///�ı��Լ������ԣ�����װ��ʱ���� -1��ʾж������ -2��ʾж���·� -3��ʾж��Ь�� >=0��ʾ������Ӧװ��
void LoadFight();   ///����ս������
void LoadXuexiao(int i); ///����ѧУ�ڵ�ͼ
void LoadWuguan(int i);  ///��������ڵ�ͼ
void LoadCaiDan(); ///���زʵ�
int color(int c);///�ı���ɫ
void ChangeDark();///���ºڰ�
void ChangeLevel(int x);///�ı��ͼ
void GetYidianData();///����������
/// </summary>

void InitMap()  ///ת���ؿ�ʱ��Ҫ���µ�ͼ����
{
    int kcnt=26;
    int k=kcnt*markLevel;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            DisPlayMap[i][j] = MyMap[++k];
        }
    }
    if(wildFlag)
    {
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if(DisPlayMap[i][j]/100==12)
                {
                    guaiwuLocx[GuaiNow1++]=i;
                    guaiwuLocy[GuaiNow2++]=j;
                }
            }
        }
    }
    DisOld=DisPlayMap[markx][marky];
    DisPlayMap[markx][marky]=100;
    markxOld=markx;
    markyOld=marky;
    if(IsOnDongxue) ChangeDark();
}
void PrintMap()
{
    ///color(2);
    cout<<endl;
    cout<<"����R����������"<<endl<<endl;
    cout<<"����Q���򿪵�ͼ"<<endl<<endl;
    cout<<"����E�������Ե�����"<<endl<<endl;
    cout<<"����T����װ����"<<endl<<endl;
    cout<<"����Z����ս����ʽ"<<endl<<endl;
    cout<<"************************************************************************************************"<<endl;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
            if (DisPlayMap[i][j] / 100 == 0||((DisPlayMap[i][j]/100)%100)==0)
            {
                ///cout << "��";
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else
                {
                    cout<<"��";
                }
            }
            if (DisPlayMap[i][j] / 100 == 1)
            {
                cout << "��";
            }
			if (DisPlayMap[i][j] / 100 == 2) cout << "��";
			if (DisPlayMap[i][j] / 100 == 3) cout << "��";
			if (DisPlayMap[i][j] / 100 == 4) cout << "��";
			if (DisPlayMap[i][j] / 100 == 5) cout << "װ";
			if (DisPlayMap[i][j] / 100 == 6||((DisPlayMap[i][j]/100)%100)==6)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout << "��";
            }
            if (DisPlayMap[i][j] / 100 == 7||((DisPlayMap[i][j]/100)%100)==7)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);;
                }
                else cout << "��";
            }
            if (DisPlayMap[i][j] / 100 == 8)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout << "��";
            }
			if (DisPlayMap[i][j] / 100 == 9||((DisPlayMap[i][j]/100)%100)==9)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout << "ʯ";
            }
			if (DisPlayMap[i][j] / 100 == 10) cout << "Ұ";
			if (DisPlayMap[i][j] / 100 == 11)
			{
				int flag = 0;      //�ж��Ƿ����������λ��
				for (int i = 0; i < Xcnt; ++i)
				{
					if (Tips[i] == 1)
					{
						///cout << "��";
						flag = 1;
					}
				}
				if (flag == 0)
				{
				    color(21);
					cout << "  ";
					color(7);
				}
				else
                {
                    cout << "��";
                }
			}
            if (DisPlayMap[i][j] / 100 == 12)
            {
                cout<<"��";
            }
			if(DisPlayMap[i][j]/100==13) cout<<"ѧ";
			if(DisPlayMap[i][j]/100==14) cout<<"��";
			if(DisPlayMap[i][j]/100==15) cout<<"ħ";
			if(DisPlayMap[i][j]/100==16) cout<<"��";
			if(DisPlayMap[i][j]/100==17) cout<<"��";
			if(DisPlayMap[i][j]/100==18) cout<<"��";
            if(DisPlayMap[i][j]/100==19)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);;
                }
                else cout<<"��";
            }
			if(DisPlayMap[i][j]/100==20) cout<<"��";
            if(DisPlayMap[i][j]/100==21||((DisPlayMap[i][j]/100)%100)==21)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout<<"��";
            }
            if(DisPlayMap[i][j]/100==22)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout<<"��";
            }
            if(DisPlayMap[i][j]/100==23)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout<<"��";
            }
            if(DisPlayMap[i][j]/100==24) cout<<"��";

		}
		cout << endl;
	}
	cout<<"************************************************************************************************"<<endl;
}
void PlayerMove()
{
    ///****
    ///system("cls");
    ///PrintMap();
    ///****
    char c;
    cout<<endl<<"�����롰w a  s d��"<<endl;
    ///cin>>c;
    c=getch();
    if(c=='w'||c=='W')
    {
        markxOld=markx;
        markyOld=marky;
        markx--;
        if(MoveOrNot())
        {
            DisPlayMap[markxOld][markyOld]=DisOld;
            DisOld=DisPlayMap[markx][marky];
            DisPlayMap[markx][marky]=100;
            ///DisPlayMap[markxOld][markyOld]=DisOld;
            if(IsOnDongxue) ChangeDark();
            system("cls");
            PrintMap();
        }
        else{
            markx=markxOld;
            marky=markyOld;
            system("cls");
            PrintMap();
        }
    }
    else if(c=='a'||c=='A')
    {
        markxOld=markx;
        markyOld=marky;
        marky--;
        if(MoveOrNot())
        {
            DisPlayMap[markxOld][markyOld]=DisOld;
            DisOld=DisPlayMap[markx][marky];
            DisPlayMap[markx][marky]=100;
            ///DisPlayMap[markxOld][markyOld]=DisOld;
            if(IsOnDongxue) ChangeDark();
            system("cls");
            PrintMap();
        }
        else{
            markx=markxOld;
            marky=markyOld;
            system("cls");
            PrintMap();
        }
    }
    else if(c=='s'||c=='S')
    {
        markxOld=markx;
        markyOld=marky;
        markx++;
        if(MoveOrNot())
        {
            DisPlayMap[markxOld][markyOld]=DisOld;
            DisOld=DisPlayMap[markx][marky];
            DisPlayMap[markx][marky]=100;
            ///DisPlayMap[markxOld][markyOld]=DisOld;
            if(IsOnDongxue) ChangeDark();
            system("cls");
            PrintMap();
        }
        else{
            markx=markxOld;
            marky=markyOld;
            system("cls");
            PrintMap();
        }
    }
    else if(c=='d'||c=='D')
    {
        markxOld=markx;
        markyOld=marky;
        marky++;
        if(MoveOrNot())
        {
            DisPlayMap[markxOld][markyOld]=DisOld;
            DisOld=DisPlayMap[markx][marky];
            DisPlayMap[markx][marky]=100;
            ///DisPlayMap[markxOld][markyOld]=DisOld;
            if(IsOnDongxue) ChangeDark();
            system("cls");
            PrintMap();
        }
        else{
            markx=markxOld;
            marky=markyOld;
            system("cls");
            PrintMap();
        }
    }
    else if(c=='Z'||c=='z')
    {
        system("cls");
        cout<<endl;
        cout<<"Ŀǰս��״̬��";
        if(ZiDong==0) cout<<"�����Զ�ս���� "<<endl<<endl;
        if(ZiDong==1) cout<<"�����������Զ�ս���� "<<endl<<endl;
        if(ZiDong==2) cout<<"�����������Զ�ս���� "<<endl<<endl;
        cout<<"���л�ս��״̬�� "<<endl<<endl;
        cout<<"0. ��ȡ���Զ�ս����"<<endl<<endl;
        cout<<"1. ��ʹ���������������Զ�ս���� "<<endl<<endl;
        cout<<"2. ��ʹ�÷������������Զ�ս���� "<<endl<<endl;
        cout<<"�������Ӧ���֣� "<<endl<<endl;
        char zid;
        cin>>zid;
        while(zid!='0'&&zid!='1'&&zid!='2')
        {
            cin>>zid;
        }
        ZiDong=zid-'0';
        system("cls");
        PrintMap();
    }
    else if(c=='E'||c=='e')
    {
        system("cls");
        cout<<endl;
        cout<<"����ɫѪ����"<<PlayerItems[10]<<endl<<endl;
        cout<<"����ɫ�﹥ֵ��"<<PlayerItems[5]<<endl<<endl;
        cout<<"����ɫ����ֵ��"<<PlayerItems[6]<<endl<<endl;
        cout<<"����ɫ����ֵ��"<<PlayerItems[7]<<endl<<endl;
        cout<<"����ɫ�ٶȡ�"<<PlayerItems[8]<<endl<<endl;
        cout<<"����ɫ����ֵ��"<<PlayerItems[3]<<endl<<endl;
        cout<<"����ɫ����ֵ��"<<PlayerItems[2]<<endl<<endl;
        cout<<"����ɫTipֵ��"<<PlayerItems[4]<<endl<<endl;
        cout<<"������������"<<PlayerItems[0]<<endl<<endl;
        cout<<"��ľ��������"<<PlayerItems[1]<<endl<<endl;
        cout<<"����Ǯ����"<<PlayerItems[9]<<endl<<endl;
        cout<<"�������һ�������˳���"<<endl<<endl;
        char c;
        cin>>c;
        system("cls");
        PrintMap();
    }
    else if(c=='T'||c=='t')
    {
        system("cls");
        cout<<endl;
        cout<<"��������"<<endl;
        if(Mywuqi>=0)
        {
            cout<<wuqi[PlayerItems[Mywuqi]].s;
            if(PlayerItems[Mywuqi]%2==0)
            {
                cout<<"���﹥��"<<wuqi[PlayerItems[Mywuqi]].Hit<<"��";
                cout<<"���;ã�"<<wuqi[PlayerItems[Mywuqi]].Nai<<"��";
            }
            else{
                cout<<"��������"<<wuqi[PlayerItems[Mywuqi]].Hit<<"��";
                cout<<"���;ã�"<<wuqi[PlayerItems[Mywuqi]].Nai<<"��";
            }
            cout<<"��1.������"<<endl<<endl;
            ///cout<<endl<<endl;
        }
        else {
            cout<<"���ޡ�"<<"��1.������"<<endl<<endl;
        }
        cout<<"����װ��"<<endl;
        if(Myyifu>=0)
        {
            cout<<yifu[PlayerItems[Myyifu]].s;
            if(PlayerItems[Myyifu]%2==0)
            {
                cout<<"��������"<<yifu[PlayerItems[Myyifu]].FangYu<<"��";
                cout<<"���;ã�"<<yifu[PlayerItems[Myyifu]].Nai<<"��";
            }
            else{
                cout<<"���ٶȣ�"<<yifu[PlayerItems[Myyifu]].FangYu<<"��";
                cout<<"���;ã�"<<yifu[PlayerItems[Myyifu]].Nai<<"��";
            }
            cout<<"��2.������"<<endl<<endl;
            ///cout<<endl<<endl;
        }
        else {
            cout<<"���ޡ�"<<"��2.������"<<endl<<endl;
        }
        cout<<"��Ь�ӡ�"<<endl;
        if(Myxiezi>=0)
        {
            cout<<xiezi[PlayerItems[Myxiezi]].s;
            cout<<"���ٶȣ�"<<xiezi[PlayerItems[Myxiezi]].Speed<<"��";
            cout<<"��3.������"<<endl<<endl;
            ///cout<<endl<<endl;
        }
        else {
            cout<<"���ޡ�"<<"��3.������"<<endl<<endl;
        }

        cout<<"��Ҫ����װ���������Ӧ���֣��������֡� 4 ���˳���"<<endl<<endl;
        char cc;
        cin>>cc;
        while(cc!='1'&&cc!='2'&&cc!='3'&&cc!='4')
        {
            cin>>cc;
        }
        if(cc=='1')
        {
            system("cls");
            cout<<endl;
            for(int i=11;i<21;++i)
            {
                if(PlayerItems[i]>-1)
                {
                    cout<<i-11<<".";
                    cout<<wuqi[PlayerItems[i]].s;
                    if(PlayerItems[i]%2==0)
                    {
                        cout<<"���﹥��"<<wuqi[PlayerItems[i]].Hit<<"��";
                        cout<<"���;ã�"<<wuqi[PlayerItems[i]].Nai<<"��";
                    }
                    else
                    {
                        cout<<"��������"<<wuqi[PlayerItems[i]].Hit<<"��";
                        cout<<"���;ã�"<<wuqi[PlayerItems[i]].Nai<<"��";
                    }
                    cout<<endl<<endl;
                }
            }
            cout<<"�������뻻װ��ǰ��Ӧ���֣���������������֣��������𲻱�Ҫ��BUG�������������������κ������˳���"<<endl<<endl;
            int huanwuqi;
            cin>>inputC;
            huanwuqi=(inputC-'0')+11;
            if(huanwuqi>10&&huanwuqi<21)
            {
                if(PlayerItems[huanwuqi]>-1)
                {
                    ChangeMyData(-1);
                    ///���ˣ�����װ����������װ�Ժ�����Ʒ����ʧ�Ĺ�����
                    Mywuqi=huanwuqi;
                    ChangeMyData(Mywuqi);
                }
            }
        }
        if(cc=='2')
        {
            system("cls");
            cout<<endl;
            for(int i=21;i<31;++i)
            {
                if(PlayerItems[i]>-1)
                {
                    cout<<i-21<<".";
                    cout<<yifu[PlayerItems[i]].s;
                    if(PlayerItems[i]%2==0)
                    {
                        cout<<"��������"<<yifu[PlayerItems[i]].FangYu<<"��";
                        cout<<"���;ã�"<<yifu[PlayerItems[i]].Nai<<"��";
                    }
                    else
                    {
                        cout<<"���ٶȣ�"<<yifu[PlayerItems[i]].FangYu<<"��";
                        cout<<"���;ã�"<<yifu[PlayerItems[i]].Nai<<"��";
                    }
                    cout<<endl<<endl;
                }
            }
            cout<<"�������뻻װ��ǰ��Ӧ���֣���������������֣��������𲻱�Ҫ��BUG�������������������κ������˳���"<<endl<<endl;
            int huanyifu;
            cin>>inputC;
            huanyifu=(inputC-'0')+21;
            if(huanyifu>20&&huanyifu<31)
            {
                if(PlayerItems[huanyifu]>-1)
                {
                    ChangeMyData(-2);
                    Myyifu=huanyifu;
                    ChangeMyData(Myyifu);
                }
            }
        }
        if(cc=='3')
        {
            system("cls");
            cout<<endl;
            for(int i=31;i<41;++i)
            {
                if(PlayerItems[i]>-1)
                {
                    cout<<i-31<<".";
                    cout<<xiezi[PlayerItems[i]].s;
                    cout<<"���ٶȣ�"<<xiezi[PlayerItems[i]].Speed<<"��";
                    cout<<endl<<endl;
                }
            }
            cout<<"�������뻻װ��ǰ��Ӧ���֣���������������֣��������𲻱�Ҫ��BUG�������������������κ������˳���"<<endl<<endl;
            int huanxiezi;
            cin>>inputC;
            huanxiezi=(inputC-'0')+31;
            if(huanxiezi>30&&huanxiezi<41)
            {
                if(PlayerItems[huanxiezi]>-1)
                {
                    ChangeMyData(-3);
                    Myxiezi=huanxiezi;
                    ChangeMyData(Myxiezi);
                }
            }
        }
        if(cc=='4')
        {
            if(0)
            {
                cout<<"Ф��������"<<endl;
            }
        }
        system("cls");
        PrintMap();
    }
    else if(c=='R'||c=='r')
    {
        system("cls");
        cout<<endl;
        cout<<"��1.�������񡿡�2.�ɳ����񡿡�3.�˳���"<<endl<<endl;
        cout<<"��ѡ���Ӧ���֣� "<<endl<<endl;
        cin>>inputC;
        while(inputC!='1'&&inputC!='2'&&inputC!='3')
        {
            cin>>inputC;
        }
        if(inputC=='1')
        {
            for(int i=0; i<Rw; ++i)
            {
                if(RenWu[i]==1)
                {
                    ///����������ʱ������������Ӧ��������********************��Ҫ********************************

                    if(i==0)
                        cout<<"�������ִ��ʯͷȫ�����飬ע�ⲻҪ��������Ŷ�����������͵����½�����Ϸ�ˡ�"<<endl<<endl;
                    if(i==1)
                        cout<<"�������ִ���������ϰ�̸����ע�ⲻҪ��������Ŷ�����������͵����½�����Ϸ�ˡ�"<<endl<<endl;
                    if(i==2)
                        cout<<"�������ִ�ķ�װ���ϰ�̸����ע�ⲻҪ��������Ŷ�����������͵����½�����Ϸ�ˡ�"<<endl<<endl;
                    if(i==3)
                    {
                        cout<<"��ȥ����������ִ��ջ�ϰ�� 10 ֻҰ������"<<endl<<endl<<"��Ŀǰ��ɱ�ˣ�";
                        if(guaiwu[0].HitData-currentguaiwudata.number>10)
                            cout<<"10"<<endl<<endl;
                        else
                            cout<<guaiwu[0].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==4)
                        cout<<"����ʮ���µĲ�����תת��˵�������������ջ񣡡�"<<endl<<endl;
                    if(i==5)
                        cout<<"��������ң��ʯͷ�������������顿"<<endl<<endl;
                    if(i==6)
                    {
                        cout<<"��ȥ�����ְ����ѧ��׽ 4 ֻ��������"<<endl<<endl<<"��Ŀǰ׽���ˣ�";
                        if(guaiwu[2].HitData-currentguaiwudata.number>4)
                            cout<<"4"<<endl<<endl;
                        else
                            cout<<guaiwu[2].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==7)
                        cout<<"������ز�ҵ������������֡�"<<endl<<endl;
                    if(i==8)
                    {
                        cout<<"��ȥ�����°��Ӣ���׽ 4 ֻĪɣ������"<<endl<<endl<<"��Ŀǰ׽���ˣ�";
                        if(guaiwu[3].HitData-currentguaiwudata.number>4)
                            cout<<"4"<<endl<<endl;
                        else
                            cout<<guaiwu[3].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==9)
                        cout<<"���������ɶ��ں�������������������"<<endl<<endl;

                    ///����������ʱ������������Ӧ��������********************��Ҫ********************************
                }
            }
            cout<<"�������һ�������˳���"<<endl<<endl;
            char c;
            cin>>c;
        }
        if(inputC=='2')
        {
            for(int i=0; i<Rw; ++i)
            {
                if(ChengZhangRenWu[i]==1)
                {
                    ///����������ʱ������������Ӧ��������********************��Ҫ(�����ģ�********************************

                    if(i==0)
                    {
                        if(IsMeet==0)
                        {
                            cout<<"��ȥѧ����תһȦ��С�Ĳ�Ҫ���������ż������������"<<endl<<endl;
                        }
                        else cout<<"�����Ѿ��������ˣ�ȥ����ѧУ�ҵ�����·�ˣ�������ȡ����ɣ���"<<endl<<endl;
                    }
                    if(i==1)
                    {
                        cout<<"��ȥѧ�������� 10 ����ż����"<<endl<<endl<<"��Ŀǰ�����ˣ�";
                        if(guaiwu[1].HitData-currentguaiwudata.number>10)
                            cout<<"10"<<endl<<endl;
                        else
                            cout<<guaiwu[1].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==2)
                    {
                        if(IsMeet==0)
                            cout<<"��ȥ��Ƶ�תһȦ��С�Ĳ�Ҫ���������������������"<<endl<<endl;
                        else cout<<"�����Ѿ��������ˣ�ȥ����ѧУ���󻤷���������ȡ����ɣ���"<<endl<<endl;
                    }

                    if(i==3)
                    {
                        cout<<"��ȥ�ķ��ش�� 10 ֻ�����֣���"<<endl<<endl<<"��Ŀǰ�����ˣ�";
                        if(guaiwu[6].HitData-currentguaiwudata.number>10)
                            cout<<"10"<<endl<<endl;
                        else
                            cout<<guaiwu[6].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==4)
                        cout<<"����ʮ���µĲ�����תת��˵�������������ջ񣡡�"<<endl<<endl;

                    ///����������ʱ������������Ӧ��������********************��Ҫ********************************
                }
            }
            cout<<"�������һ�������˳���"<<endl<<endl;
            char c;
            cin>>c;
        }
        system("cls");
        PrintMap();
    }
    else if(c=='q'||c=='Q')
    {
        system("cls");
        cout<<endl;
        ///�����µ�ͼʱ������������***********************************��Ҫ****************************************

        if(markLevel==0)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ������ִ塿 "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"�������꡿    ���ϰ� "<<endl<<endl;
            cout<<"����װ�꡿    ���ϰ�"<<endl<<endl;
            cout<<"����  ջ��    ���ϰ�"<<endl<<endl;
            cout<<"��Ф  �    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���������    Ұ�� "<<endl<<endl;
        }
        if(markLevel==1)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ���������� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"��Ұ����    Ұ������"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==2)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ���ʮ���¡� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"����  ƽ��    NPC"<<endl<<endl;
            cout<<"����ƺ졿    NPC"<<endl<<endl;
            cout<<"�����ĺ���    NPC"<<endl<<endl;
            cout<<"��С  ����    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==3)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ��������� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"������ѧУ��    �ɳ�"<<endl<<endl;
            cout<<"���м�ѧУ��    �ɳ�"<<endl<<endl;
            cout<<"���߼�ѧУ��    �ɳ�"<<endl<<endl;
            cout<<"��������ݡ�    �ɳ�"<<endl<<endl;
            cout<<"���м���ݡ�    �ɳ�"<<endl<<endl;
            cout<<"���߼���ݡ�    �ɳ�"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==4)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ���ѧ������ "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"����ż��    Ұ������"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==5)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ�����Դ�� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"�������꡿    ���ϰ� "<<endl<<endl;
            cout<<"����װ�꡿    ���ϰ�"<<endl<<endl;
            cout<<"����  ջ��    ���ϰ�"<<endl<<endl;
            cout<<"������ң��    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�������֡�    Ұ�� "<<endl<<endl;
        }
        if(markLevel==6)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ��������֡� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"��������    Ұ������"<<endl<<endl;
            cout<<"������ѧ�ҡ�    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==7)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ������� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"�������꡿    ���ϰ� "<<endl<<endl;
            cout<<"����װ�꡿    ���ϰ�"<<endl<<endl;
            cout<<"����  ջ��    ���ϰ�"<<endl<<endl;
            cout<<"����  ز��    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�������¡�    Ұ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==8)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ��������¡� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"��Īɣ����    Ұ������"<<endl<<endl;
            cout<<"����Ӣ��ҡ�    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==9)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ���ħ���� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"�������꡿    ���ϰ� "<<endl<<endl;
            cout<<"����װ�꡿    ţ�ϰ�"<<endl<<endl;
            cout<<"����  ջ��    ���ϰ�"<<endl<<endl;
            cout<<"�������ɶ���    NPC"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"��ͨ��ĵط�"<<endl<<endl;
        }
        if(markLevel==10)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ�������ѧУ�� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"������ѧУ�󻤷���    ��ȡ�������� "<<endl<<endl;
            cout<<"������ѧУ��ϯ��    ��ȡ�߼�����"<<endl<<endl;
            cout<<"������ѧУ�һ�����    ��ȡ�м�����"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���󷨡�"<<endl<<endl;
        }
        if(markLevel==11)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ����м�ѧУ�� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"���м�ѧУ�󻤷���    ��ȡ�������� "<<endl<<endl;
            cout<<"���м�ѧУ��ϯ��    ��ȡ�߼�����"<<endl<<endl;
            cout<<"���м�ѧУ�һ�����    ��ȡ�м�����"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���󷨡�"<<endl<<endl;
        }
        if(markLevel==12)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ����߼�ѧУ�� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"���߼�ѧУ�󻤷���    ��ȡ�������� "<<endl<<endl;
            cout<<"���߼�ѧУ��ϯ��    ��ȡ�߼�����"<<endl<<endl;
            cout<<"���߼�ѧУ�һ�����    ��ȡ�м�����"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���󷨡�"<<endl<<endl;
        }
        if(markLevel==13)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ���������ݡ� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"����������󻤷���    ��ȡ�������� "<<endl<<endl;
            cout<<"�����������ϯ��    ��ȡ�߼�����"<<endl<<endl;
            cout<<"����������һ�����    ��ȡ�м�����"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���󷨡�"<<endl<<endl;
        }
        if(markLevel==14)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ����м���ݡ� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"���м�����󻤷���    ��ȡ�������� "<<endl<<endl;
            cout<<"���м������ϯ��    ��ȡ�߼�����"<<endl<<endl;
            cout<<"���м�����һ�����    ��ȡ�м�����"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���󷨡�"<<endl<<endl;
        }
        if(markLevel==15)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ����߼���ݡ� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"���߼�����󻤷���    ��ȡ�������� "<<endl<<endl;
            cout<<"���߼������ϯ��    ��ȡ�߼�����"<<endl<<endl;
            cout<<"���߼�����һ�����    ��ȡ�м�����"<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"���󷨡�"<<endl<<endl;
        }
        if(markLevel==16)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ�����Ƶء� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"����    Ұ����� "<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel==17)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ����ķ��ء� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"�������֡�    Ұ����� "<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"�����͵㡿"<<endl<<endl;
        }
        if(markLevel>=18&&markLevel<=66)
        {
            cout<<"�㵱ǰ���ڵĵط��ǣ�����Ѩ��"<<markLevel<<"�� "<<endl<<endl;
            cout<<"�����У� "<<endl<<endl;
            cout<<"��δ֪�� "<<endl<<endl;
            cout<<"����ͨ�� "<<endl<<endl;
            cout<<"��δ֪��"<<endl<<endl;
        }

        ///�����µ�ͼʱ������������***********************************��Ҫ****************************************
        cout<<"�������һ�������˳���"<<endl<<endl;
        char c;
        cin>>c;
        system("cls");
        PrintMap();
    }


}
bool MoveOrNot()
{
    if((markx>4||markx<0||marky>4||marky<0)&&IsOnYidian==0) return false;
    if(IsOnYidian==1&&(markx>4||markx<0||marky>4||marky<0))
    {
        if(markx<0) ///������
        {
            for(int i=1; i<=25; ++i) ///�ҵ�Ҫǰ����ͼ��ƥ����������
            {
                if(MyMap[26*up1+i]%100==match0&&MyMap[26*up1+i]/100>99)
                {
                    type0=(MyMap[26*up1+i]/100)%100;

                    nextMapY=(i-1)%5;
                    nextMapX=((i-1)-nextMapY)/5;

                    break;
                }
            }
            if(up1==0) return false;
            else
            {
                if(type0==0||type0==6||type0==21)
                {
                    ChangeLevel(0);
                    return false;
                }
                else if(type0==7)
                {
                    if(PlayerItems[1]==0)
                        return false;
                    else
                    {
                        ChangeLevel(0);
                        return false;
                    }
                }
                else
                {
                    if(PlayerItems[0]==0)
                        return false;
                    else
                    {
                        ///MyMap[26*up1+i]=(up1*10000000000+down1*100000000+left1*1000000+right1*10000+match1);
                        ChangeLevel(0);
                        return false;
                    }
                }
            }
        }
        else if(markx>4) ///������
        {
            for(int i=1; i<=25; ++i) ///�ҵ�Ҫǰ����ͼ��ƥ����������
            {
                if(MyMap[26*down1+i]%100==match0&&MyMap[26*down1+i]/100>99)
                {
                    type0=(MyMap[26*down1+i]/100)%100;

                    nextMapY=(i-1)%5;
                    nextMapX=((i-1)-nextMapY)/5;

                    break;
                }
            }
            if(down1==0) return false;
            else
            {
                if(type0==0||type0==6||type0==21)
                {
                    ChangeLevel(1);
                    return false;
                }
                else if(type0==7)
                {
                    if(PlayerItems[1]==0)
                        return false;
                    else
                    {
                        ChangeLevel(1);
                        return false;
                    }
                }
                else
                {
                    if(PlayerItems[0]==0)
                        return false;
                    else
                    {
                        ChangeLevel(1);
                        return false;
                    }
                }
            }
        }
        else if(marky>4) ///������
        {
            for(int i=1; i<=25; ++i) ///�ҵ�Ҫǰ����ͼ��ƥ����������
            {
                if(MyMap[26*right1+i]%100==match0&&MyMap[26*right1+i]/100>99)
                {
                    type0=(MyMap[26*right1+i]/100)%100;

                    nextMapY=(i-1)%5;
                    nextMapX=((i-1)-nextMapY)/5;

                    break;
                }
            }
            if(right1==0) return false;
            else
            {
                if(type0==0||type0==6||type0==21)
                {
                    ChangeLevel(3);
                    return false;
                }
                else if(type0==7)
                {
                    if(PlayerItems[1]==0)
                        return false;
                    else
                    {
                        ChangeLevel(3);
                        return false;
                    }
                }
                else
                {
                    if(PlayerItems[0]==0)
                        return false;
                    else
                    {
                        ChangeLevel(3);
                        return false;
                    }
                }
            }
        }
        else  ///������
        {
            for(int i=1; i<=25; ++i) ///�ҵ�Ҫǰ����ͼ��ƥ����������
            {
                if(MyMap[26*left1+i]%100==match0&&MyMap[26*left1+i]/100>99)
                {
                    type0=(MyMap[26*left1+i]/100)%100;

                    nextMapY=(i-1)%5;
                    nextMapX=((i-1)-nextMapY)/5;

                    break;
                }
            }
            if(left1==0) return false;
            else
            {
                if(type0==0||type0==6||type0==21)
                {
                    ChangeLevel(2);
                    return false;
                }
                else if(type0==7)
                {
                    if(PlayerItems[1]==0)
                        return false;
                    else
                    {
                        ChangeLevel(2);
                        return false;
                    }
                }
                else
                {
                    if(PlayerItems[0]==0)
                        return false;
                    else
                    {
                        ChangeLevel(2);
                        return false;
                    }
                }
            }
        }
    }
    ///�����յ�
    if(DisPlayMap[markx][marky]/100==0)
    {
        IsOnYidian=0;
        if(IsOnShengzi) return false;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        return true;
    }
    ///�������
    else if(DisPlayMap[markx][marky]/100>99)
    {
        GetYidianData();
        if(IsOnShengzi&&type1!=21) return false;
        if(type1==0||type1==6)
        {
            if(PlayerItems[1]>0&&waterFlag==1)
            {
                PlayerItems[1]--;
                waterFlag=0;
            }
            IsOnYidian=1;
            return true;
        }
        else if(type1==7)
        {
            if(PlayerItems[1]==0)
                return false;
            else
            {
                IsOnYidian=1;
                waterFlag=1;
                return true;
            }
        }
        else if(type1==9)
        {
            if(PlayerItems[0]==0)
                return false;
            else
            {
                IsOnYidian=1;

                if(PlayerItems[1]>0&&waterFlag==1)
                {
                    PlayerItems[1]--;
                    waterFlag=0;
                }
                PlayerItems[0]--;
                type0=0;type1=0;
                DisPlayMap[markx][marky]=up0*10000000000+down0*100000000+left0*1000000+right0*10000+type0*100+match0;
                MyMap[26*markLevel+1+5*markx+marky]=up0*10000000000+down0*100000000+left0*1000000+right0*10000+type0*100+match0;
                return true;
            }
        }
        else
        {
            if(DisOld==2100||DisOld==2101)
            {
                if(PlayerItems[1]>0&&waterFlag==1)
                {
                    PlayerItems[1]--;
                    waterFlag=0;
                }
                IsOnYidian=1;
                IsOnShengzi=1;
                return true;
            }
            else return false;
        }
    }
    ///�����Լ�����Ȼ������
    else if(DisPlayMap[markx][marky]/100==1)
    {
        cout<<"�����ߣ�Ф��";
        return false;
    }
    ///����NPC
    else if(DisPlayMap[markx][marky]/100==2)
    {
        if(IsOnShengzi) return false;
        ///����д0��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==0)
        {
            system("cls");
            cout<<endl;
            while (1)
            {
                cout<<"��Ф�"<<endl<<endl;
                cout<<"��ӭ�������ִ壬�װ�����ң��ҽ�Ф��"<<endl<<endl;
                cout<<"�������������Ϸ�е���·��"<<endl<<endl;
                cout<<"���ǲ����޷�ǰ���أ����������ֳɵ�ľ�������ṩ����"<<endl<<endl;
                cout<<"����ľ���Ϳ��Թ�����Ŷ"<<endl<<endl;
                cout<<"ľ����һ���Եģ�����Ӿͻ���ʧ�������û��ľ���Ļ�������ʱ�����ң������������ٴ��Ҷ�������ṩ��ѵ�ľ��"<<endl<<endl;
                ///cout<<"��ȥ�������װ���꿴���ɣ�Ҳ���ϰ���Ļ�����ṩ���ֵı�����װ���أ�"<<endl<<endl;
                cout<<"�������ڰ�ľ�����㣬ȥ�������ĸ��ȥ̽�հɣ�����"<<endl<<endl;
                cout<<"�һ���Զ����������Ŷ�������˾��������Ұɣ�����"<<endl<<endl;
                if(RenWu[0]==0)
                {
                    RenWu[0]=1;
                    cout<<"�������ȡ��"<<endl<<endl;
                    cout<<"������,��ֹ�㱻ʯͷ�ͺӿ��������ٸ���һЩ���Ӱɣ����ӿ��Ի���ʯͷŶ��"<<endl<<endl;
                    PlayerItems[0]=4;
                    cout<<"������ִ��ʯͷȫ�������Ժ��������Ұɣ���ʱ���һ�ָ�������̽�������������� ��"<<endl<<endl;
                    cout<<"������4�Ѵ��ӣ�����  "<<endl<<endl;
                }
                if(RenWu[0]==1&&DisPlayMap[0][0]==0&&DisPlayMap[1][0]==0&&DisPlayMap[2][0]==0&&DisPlayMap[3][0]==0)
                {
                    RenWu[0]=2;
                    cout<<"��ϲ������������ִ�ĵ�һ�����飡 "<<endl<<endl;
                    RenWu[1]=1;
                    cout<<"�������ȡ��"<<endl<<endl;
                    cout<<"���������ϰ��������ס�Ҹ��ڣ����Ҷ���ĺ����ѣ��������ҵĽ�����ȥ�������������һ�ѳ��ֵı��� ��"<<endl<<endl;
                    cout<<endl<<"������Ф��Ľ����ţ� "<<endl<<endl;
                }
                cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                char x;
                cin>>x;
                if(PlayerItems[1]==0) PlayerItems[1]++;
                break;
            }
        }
        ///����д����1��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==1)
        {
            system("cls");
            cout<<endl;
            cout<<"����ƽ��"<<endl<<endl;
            if(PlayerItems[4]%2==0)
            {
                cout<<"�㿴����ͼ�м��Ǹ�ʯͷ���� "<<endl<<endl;
                cout<<"��˵�����ӡ��һ���ǳ�ǿ��Ķ�ħ������"<<endl<<endl;
                cout<<"ҪС�Ĳ�Ҫ��������������  "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
            }
            else{
                cout<<"��֪�����ݡ��� "<<endl<<endl;
                cout<<"����һ��ֲ��������׷�ݵ��������� "<<endl<<endl;
                cout<<"�ȿȿȣ��е㳶Զ�ˣ� "<<endl<<endl;
                cout<<"˵˵��Ϸ��Ĳݰɣ����ɲ�������һ��װ��Ŷ�� "<<endl<<endl;
                cout<<"��Щ���������б����ģ�ʮ���µĲ�������б����� "<<endl<<endl;
                cout<<"ʲô��û�У� "<<endl<<endl;
                cout<<"������ϸ���ң�һ�����еģ� "<<endl<<endl;
                RenWu[4]=1;
                MyMap[53]=601;
                cout<<"���������һ������ȷ�� "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///����д����2��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==2)
        {
            system("cls");
            cout<<endl;
            cout<<"����ƺ졿"<<endl<<endl;
            cout<<"����������ϣ���Ҫ��������ֵ������ֵ����ֻ��ͨ��������ݺ�ѧУ�� "<<endl<<endl;
            cout<<"����������������������ֵ����ѧУѧϰ����������ֵ "<<endl<<endl;
            cout<<"��ݻ��ڵ�ͼ����ʾΪ���ݡ���ѧУ���ڵ�ͼ����ʾΪ��ѧ�� "<<endl<<endl;
            cout<<"������ֻ��һ��ѡ������һ�����룬ֻ�е����Ŀǰ����ݻ�ѧУ������ϲ��ܼ���������������ݻ�ѧУ����"<<endl<<endl;
            cout<<"���ܼ�����ͬ���ظ�����Ŷ���������Լ���ƫ��ѡ��� "<<endl<<endl;
            cout<<"�뵱�񶷼Ҿ�ѡ������������뵱ħ��ʦ��ȥѧУ�� "<<endl<<endl;
            cout<<"�붼ѡ��ȻҲ���ԣ� "<<endl<<endl;
            cout<<"���������һ������ȷ�� "<<endl<<endl;
            cin>>inputC;
        }
        ///����д����3��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==3)
        {
            system("cls");
            cout<<endl;
            cout<<"�����ĺ���"<<endl<<endl;
            cout<<"��֪���𣿵���Ĺ�����С�ڹ���ķ���ֵʱ���������������������ͻ��Ѫ "<<endl<<endl;
            cout<<"��������������֮ǰ��ս��ʱ������������ǲ�����Ϊ��BUG "<<endl<<endl;
            cout<<"�Ų����أ��������߹������ģ����� "<<endl<<endl;
            cout<<"�����һ���ϲ����ħ��ʦ "<<endl<<endl;
            cout<<"��ħ��������������û�������ˣ� "<<endl<<endl;
            cout<<"����Ҳ��һ�ֱ׶ˣ����Ƿ���̫�ͣ���Ѫ̫���ף���Ҫ�����ܿ�ջ "<<endl<<endl;
            cout<<"ѡ�񵱸񶷼��Ժ�����ֵ���ˣ����Դ�һ���߷������·���Ȼ��ȥ�������Ұ�� "<<endl<<endl;
            cout<<"����Ұ������һ�£���ͻ����Ѫ�����������������Ӵ���Ҳ����ȥ��ջ "<<endl<<endl;
            cout<<"����Ҫ�ǵ��÷�������Ұ�� "<<endl<<endl;
            cout<<"��Ȼһ�´���Ұ������û����Ѫ�ˣ� "<<endl<<endl;
            cout<<"���������һ������ȷ�� "<<endl<<endl;
            cin>>inputC;
        }
        ///����д����4��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==4)
        {
            system("cls");
            cout<<endl;
            cout<<"��С����"<<endl<<endl;
            if(PlayerItems[4]%22==6)
            {
                cout<<"��˵���������Ϸ����Ҳ��Ф������ִ���Ǹ�������һ�������� "<<endl<<endl;
                cout<<"��֪���ǲ�����ģ����� "<<endl<<endl;
                cout<<"�л��������һ���� "<<endl<<endl;
                cout<<"������һ����������ȷ�� "<<endl<<endl;
                cin>>inputC;
            }
            else{
                cout<<"����ʱ��û����ú���˵ʲô ������ "<<endl<<endl;
                cout<<"������һ����������ȷ�� "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///����д����5��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==5)
        {
            system("cls");
            cout<<endl;
            cout<<"������ң��"<<endl<<endl;
            ///����Ϊ���ԣ���ɾ��
               ///PlayerItems[4]=197;///-*-����ĵ�����Դ�ĶԻ�����˵զ����
               ///int shenmegui=PlayerItems[4]%13;
               ///cout<<"���������˾��鴥����ʯͷ��"<<shi901[shenmegui]<<endl;
               ///cin>>inputC;
            ///����Ϊ���ԣ���ɾ��
            if(PlayerItems[4]>150)
            {
                if(RenWu[5]==0)
                {
                    cout<<"��ð�����·�ˣ��ҵ������鱻ħ���⵽��ʯͷ���棬���Ҳ�֪������һ��ʯͷ "<<endl<<endl;
                    cout<<"����԰������ҿ��� "<<endl<<endl;
                    cout<<"1.���ð����������æ���� "<<endl<<endl;
                    cout<<"2.��û�գ������������ðɣ��� "<<endl<<endl;
                    cout<<"��������Ӧ����ѡ�� "<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        int a,b,c,d;
                        d=PlayerItems[4]%13;
                        a=shi901[d]/100;
                        b=(shi901[d]/10)%10;
                        c=shi901[d]%10;
                        MyMap[a*26+b*5+c+1]=901;
                        RenWu[5]=1;
                        if(PlayerItems[0]==0)
                            PlayerItems[0]++;
                        cout<<"��л�����ѣ���Ҫ���ӵĻ���������ʱ�����ң� "<<endl<<endl;
                        cout<<"����ÿ��ֻ�ܸ���һ�� "<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"лл���ѣ�����ٻ������ҵģ�"<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(RenWu[5]==1)
                {
                    if(PlayerItems[0]==0)
                    {
                        cout<<"��л��İ�æ����û�д����������ٸ���һ�Ѱ�"<<endl<<endl;
                        cout<<"�����ˡ����ӡ�"<<endl<<endl;
                        PlayerItems[0]++;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"��ȥ�������Ұ����ѣ��һ�Ҫȥ���������أ� "<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else
                {
                    PlayerItems[66]=0;
                    cout<<"лл��æ���ѣ� "<<endl<<endl;
                    cout<<"ʲô����Ҫ���ꣿ "<<endl<<endl;
                    cout<<"�ҵ�ʱ��û��Ӧ���㱨�꣡ "<<endl<<endl;
                    cout<<"���������д������ӳ��ۣ�50��һ�ѣ�����Ҫ�� "<<endl<<endl;
                    cout<<"1.����Ҫ��"<<endl<<endl;
                    cout<<"2.������Ҫ�� "<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        if(PlayerItems[9]>=50)
                        {
                            PlayerItems[9]-=50;
                            PlayerItems[0]++;
                            cout<<"�ɽ������� "<<endl<<endl;
                            cout<<"��ʧȥ�ˡ�50��Ǯ�� "<<endl<<endl;
                            cout<<"������һ�ѡ����ӡ� "<<endl<<endl;
                        }
                        else
                        {
                            cout<<"�����Ǯ�����������ѣ� "<<endl<<endl;
                        }
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"���Ժ���Ҫ��æ����Ҳ�������ģ� "<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
            }
            else
            {
                cout<<"�ҿ��Ǿ�����Ӣ�ۣ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ� "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///����д����6��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==6)
        {
            system("cls");
            cout<<endl;
            cout<<"������ѧ�ҡ�"<<endl<<endl;
            cout<<"6 @#%���� �� "<<endl<<endl;
            cout<<"49 @#%���� 3000 "<<endl<<endl;
            cout<<"7th @#%���� 1000 "<<endl<<endl;
            cout<<"38 @#%���� 595 "<<endl<<endl;
            cout<<"425->420 @#%���� 574 "<<endl<<endl;
            cout<<"1804 @#%���� 22 "<<endl<<endl;
            cout<<"����������ʲô����"<<endl<<endl;
            cout<<"1.�����Ǵ���ѧ�ң���"<<endl;
            cout<<"2.������ʲô��Ǯ�ķ������ұȽ�ȱǮ����"<<endl<<endl;
            cout<<"�������Ӧ����"<<endl<<endl;
            cin>>inputC;
            while(inputC!='1'&&inputC!='2')
            {
                cin>>inputC;
            }
            if(inputC=='1')
            {
                system("cls");
                cout<<endl;
                cout<<"������ѧ�ҡ�"<<endl<<endl;
                cout<<"ʲô�����������ҵ���ѧ������ "<<endl<<endl;
                for(int i=0;i<GuaiWCnt;++i)
                {
                    cout<<"��һ��������"<<guaiwu[i].s<<guaiwu[i].HitData<<"��"<<endl;
                }
                cout<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                ///cout<<" "<<endl<<endl;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"������ѧ�ҡ�"<<endl<<endl;
                cout<<"��������о�������������ܰ���׽4ֻ�������ҾͿ��Ը���20��Ǯ�ı��꣡ "<<endl<<endl;
                cout<<"1.����ȡ����2.����������3.���뿪�� "<<endl<<endl;
                cout<<"��������Ӧ���� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2'&&inputC!='3')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    if(currentguaiwudata.number>=0)
                    {
                        cout<<"��������������������ȥ��ɰɣ� "<<endl<<endl;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        currentguaiwudata.Id=1202;
                        currentguaiwudata.number=guaiwu[2].HitData;
                        cout<<"���ѽ������� "<<endl<<endl;
                        RenWu[6]=1;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(inputC=='2')
                {
                    system("cls");
                    cout<<endl;
                    cout<<"������ѧ�ҡ�"<<endl<<endl;
                    if(RenWu[6]==0)
                    {
                        cout<<"�㲢û�н����ҵ����񰡣�"<<endl<<endl;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        if(guaiwu[2].HitData-currentguaiwudata.number>=4)
                        {
                            currentguaiwudata.number=-1;
                            PlayerItems[9]+=20;
                            RenWu[6]=0;
                            cout<<"лл������Ҵ�æ��������ı��꣡ "<<endl<<endl;
                            cout<<"�����ˡ�20��Ǯ�� "<<endl<<endl;
                            cout<<"��������������ȷ�� "<<endl<<endl;
                            cin>>inputC;
                        }
                        else
                        {
                            cout<<"�㻹û������ҵ������أ� "<<endl<<endl;
                            cout<<"��������������ȷ�� "<<endl<<endl;
                            cin>>inputC;
                        }
                    }
                }
                else
                {
                    system("cls");
                    cout<<endl;
                    cout<<"������ѧ�ҡ�"<<endl<<endl;
                    cout<<"����Ҫ�������ң�"<<endl<<endl;
                    cout<<"��������������ȷ�� "<<endl<<endl;
                    cin>>inputC;
                }
            }
        }
        ///����д����7��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==7)
        {
            system("cls");
            cout<<endl;
            cout<<"����ز��"<<endl<<endl;
            if(RenWu[7]==0)
            {
                cout<<"�������������ɶ� "<<endl<<endl;
                cout<<"�ҵġ������ס��Ͳ�һ�ֽ����������������־������ "<<endl<<endl;
                cout<<"���Ҿ����Ҳ����������� "<<endl<<endl;
                cout<<"�װ��ģ�����԰�����������������ҵ������Դ����������� "<<endl<<endl;
                cout<<"�һ����һ�������׵ĸ�������������˸������ֵ����ϡ� "<<endl<<endl;
                cout<<"������ش��������ң� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                RenWu[7]=1;
            }
            else if(RenWu[7]==1)
            {
                cout<<"������ش��������������ң� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
            }
            else
            {
                cout<<"лл���װ��ģ�������Ҵ�æ�� "<<endl<<endl;
                cout<<"�Ȿ�������ס�����������ˣ��Ժ��������ʱ�鿴��������ϡ� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                PlayerItems[50]=1;
            }
        }
        ///����д����8��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==8)
        {
            system("cls");
            cout<<endl;
            cout<<"����Ӣ��ҡ�"<<endl<<endl;
            cout<<"My.... "<<endl<<endl;
            cout<<"Name..."<<endl<<endl;
            cout<<"Is....."<<endl<<endl;
            cout<<"Show..."<<endl<<endl;
            cout<<"Young.."<<endl<<endl;
            cout<<"����������ʲô����"<<endl<<endl;
            cout<<"1.�����Ǵ�Ӣ��ң���"<<endl;
            cout<<"2.������ʲô��Ǯ�ķ������ұȽ�ȱǮ����"<<endl<<endl;
            cout<<"�������Ӧ����"<<endl<<endl;
            cin>>inputC;
            while(inputC!='1'&&inputC!='2')
            {
                cin>>inputC;
            }
            if(inputC=='1')
            {
                system("cls");
                cout<<endl;
                cout<<"����Ӣ��ҡ�"<<endl<<endl;
                cout<<"ʲô�����������ҵ�Ӣ�������� "<<endl<<endl;
                for(int i=0;i<22;++i)
                {
                    cout<<"Hello World!!!"<<endl;
                }
                cout<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                ///cout<<" "<<endl<<endl;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"����Ӣ��ҡ�"<<endl<<endl;
                cout<<"��������о�Īɣ����������ܰ���׽4ֻ�������ҾͿ��Ը���50��Ǯ�ı��꣡ "<<endl<<endl;
                cout<<"1.����ȡ����2.����������3.���뿪�� "<<endl<<endl;
                cout<<"��������Ӧ���� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2'&&inputC!='3')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    if(currentguaiwudata.number>=0)
                    {
                        cout<<"��������������������ȥ��ɰɣ� "<<endl<<endl;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        currentguaiwudata.Id=1203;
                        currentguaiwudata.number=guaiwu[3].HitData;
                        cout<<"���ѽ������� "<<endl<<endl;
                        RenWu[8]=1;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(inputC=='2')
                {
                    system("cls");
                    cout<<endl;
                    cout<<"����Ӣ��ҡ�"<<endl<<endl;
                    if(RenWu[8]==0)
                    {
                        cout<<"�㲢û�н����ҵ����񰡣�"<<endl<<endl;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        if(guaiwu[3].HitData-currentguaiwudata.number>=4)
                        {
                            currentguaiwudata.number=-1;
                            PlayerItems[9]+=50;
                            RenWu[8]=0;
                            cout<<"лл������Ҵ�æ��������ı��꣡ "<<endl<<endl;
                            cout<<"�����ˡ�50��Ǯ�� "<<endl<<endl;
                            cout<<"��������������ȷ�� "<<endl<<endl;
                            cin>>inputC;
                        }
                        else
                        {
                            cout<<"�㻹û������ҵ������أ� "<<endl<<endl;
                            cout<<"��������������ȷ�� "<<endl<<endl;
                            cin>>inputC;
                        }
                    }
                }
                else
                {
                    system("cls");
                    cout<<endl;
                    cout<<"����Ӣ��ҡ�"<<endl<<endl;
                    cout<<"����Ҫ�������ң�"<<endl<<endl;
                    cout<<"��������������ȷ�� "<<endl<<endl;
                    cin>>inputC;
                }
            }
        }
        ///����д����9��NPC�ĶԻ�
        if(DisPlayMap[markx][marky]%100==9)
        {
            system("cls");
            cout<<endl;
            cout<<"�������ɶ���"<<endl<<endl;
            ///����Ϊ���ԣ���ɾ��
               ///PlayerItems[4]=178;
               ///cout<<"���������˾��鴥���ĺӣ�"<<he701[PlayerItems[4]%24]<<endl;
               ///cin>>inputC;
            ///����Ϊ���ԣ���ɾ��
            if(PlayerItems[4]>150)
            {
                if(RenWu[9]==0)
                {
                    cout<<"��ð�����·�ˣ��ҵ������ڹ���ʱ�����˺��� "<<endl<<endl;
                    cout<<"�ҵ�ʱ��ľ���Ͽ����˼Ǻ� "<<endl<<endl;
                    cout<<"�����ҵ��ﰶ�ߺ󣬸��ݿ̵ļǺ���ȥ�ң������Ѿ��Ҳ����� "<<endl<<endl;
                    cout<<"����԰������ҿ��� "<<endl<<endl;
                    cout<<"1.���ð����������æ���� "<<endl<<endl;
                    cout<<"2.��û�գ�����ô�����Ǳ��������ˣ��� "<<endl<<endl;
                    cout<<"��������Ӧ����ѡ�� "<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        int a,b,c,d;
                        d=PlayerItems[4]%24;
                        a=he701[d]/100;
                        b=(he701[d]/10)%10;
                        c=he701[d]%10;
                        MyMap[a*26+b*5+c+1]=701;
                        RenWu[9]=1;
                        if(a==9)
                        {
                            DisPlayMap[b][c]=701;
                        }
                        if(PlayerItems[1]==0)
                            PlayerItems[1]+=2;
                        cout<<"��л�����ѣ���Ҫľ���Ļ���������ʱ�����ң� "<<endl<<endl;
                        cout<<"����ÿ��ֻ�ܸ������� "<<endl<<endl;
                        cout<<"���������ҡ�ľ����"<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"лл���ѣ�����ٻ������ҵģ�"<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(RenWu[9]==1)
                {
                    if(PlayerItems[1]==0)
                    {
                        cout<<"��л��İ�æ����û��ľ���������ٸ������Ұ�"<<endl<<endl;
                        cout<<"���������ҡ�ľ����"<<endl<<endl;
                        PlayerItems[1]+=2;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"��ȥ�������Ұ����ѣ��һ�Ҫȥ�����أ� "<<endl<<endl;
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else
                {
                    PlayerItems[99]=0;
                    cout<<"лл��æ���ѣ� "<<endl<<endl;
                    cout<<"ʲô����Ҫ���ꣿ "<<endl<<endl;
                    cout<<"�ҵ�ʱ��û��Ӧ���㱨�꣡ "<<endl<<endl;
                    cout<<"���������д���ľ�����ۣ�50��һ�ң�����Ҫ�� "<<endl<<endl;
                    cout<<"1.����Ҫ��"<<endl<<endl;
                    cout<<"2.������Ҫ�� "<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        if(PlayerItems[9]>=50)
                        {
                            PlayerItems[9]-=50;
                            PlayerItems[1]++;
                            cout<<"�ɽ������� "<<endl<<endl;
                            cout<<"��ʧȥ�ˡ�50��Ǯ�� "<<endl<<endl;
                            cout<<"������һ�ҡ�ľ���� "<<endl<<endl;
                        }
                        else
                        {
                            cout<<"�����Ǯ�����������ѣ� "<<endl<<endl;
                        }
                        cout<<"�������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"���Ժ���Ҫ��æ����Ҳ�������ģ� "<<endl<<endl;
                        cout<<"��������������ȷ�� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
            }
            else
            {
                cout<<"�����ɶ�Ҳͦ�õģ���������ʵ��Ҳ����ɣ������ҵ������Ҳ����ˣ������� "<<endl<<endl;
                if(PlayerItems[1]==0)
                {
                    cout<<"����һ��ľ���ɣ���Ȼ��Ϳ����ˣ�"<<endl<<endl;
                    cout<<"������һ�ҡ�ľ����"<<endl<<endl;
                    PlayerItems[1]++;
                }
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///������ջ
    else if(DisPlayMap[markx][marky]/100==3)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"�����ϰ塿"<<endl<<endl;
        if(RenWu[3]==1)
        {
            ///DisPlayMap[0][3]=1001;
            if(guaiwu[0].HitData-currentguaiwudata.number>=10)
            {
                currentguaiwudata.number=-1;
                cout<<"��ѽ��лл�㰡С��ƣ����Ұ���Ҿ�������!!!���Ǹ���Ľ��� "<<endl<<endl;
                cout<<"������50��Ǯ������ "<<endl<<endl;
                PlayerItems[9]+=50;
                cout<<"��������ȫ����ȥ����ĵط�ȥ��һ���ˣ���Ҫ���������ִ壡������֮ǰ���������Ұ�ֵ�ʱ�� "<<endl<<endl;
                cout<<"��û�п�����һ�������͵㡿���� "<<endl<<endl;
                cout<<"������Ϳ��Դ��͵���ʮ���¡���ʮ������Χ�и��֡���ݡ��͡�ѧУ����������������ѧϰ���������ġ�����ֵ���͡�����ֵ�� "<<endl<<endl;
                cout<<"�ڵ���ʮ���º�Ҫ�ǵö����˽������������˽�������磡 "<<endl<<endl;
                cout<<"���ˣ����������Ϊ��ظ�һ��Ѫ���ɣ��Ժ�����㲻�������ˣ��Ժ���������Ϣ�Ҿ�Ҫ�շ���Ŷ����������Ф��������ϣ�����������������ˣ������ٺ٣� "<<endl<<endl;
                cout<<"���Ѫ���ָ�������ֵ������ "<<endl<<endl;
                PlayerItems[10]=maxHP;
                MyMap[31]=802;
                RenWu[3]=2;
                cout<<"��������������ȷ�ϣ����� "<<endl<<endl;
                cin>>inputC;
            }
            else
            {
                cout<<"��л��Ϊ��ȥ׽Ұ����������ɺ��һ���㱨��ģ����� "<<endl<<endl;
                cout<<"�������׽Ұ����ʱ�����ˣ����������ң��Ҷ���Ϊ������ṩ��Ϣ�ĵط��� "<<endl<<endl;
                cout<<"�����˳������Ϣ�� "<<endl<<endl;
                cout<<"���Ѫ���ָ�������ֵ������ "<<endl<<endl;
                PlayerItems[10]=maxHP;
                cout<<"��������������ȷ�ϣ����� "<<endl<<endl;
                cin>>inputC;
            }
        }
        else{
            cout<<"����Ҫ��Ϣ�� "<<endl<<endl;
            cout<<"1.����Ҫ�� 2.������Ҫ�� "<<endl<<endl;
            cout<<"�������Ӧ���� "<<endl<<endl;
            char xiuxi;
            cin>>xiuxi;
            while(xiuxi!='1'&&xiuxi!='2')
            {
                cout<<"��������ȷ���֣�"<<endl<<endl;
                cin>>xiuxi;
            }
            if(xiuxi=='1')
            {
                if(PlayerItems[9]>=20)
                {
                    PlayerItems[9]-=20;
                    cout<<"�����˳������Ϣ�� "<<endl<<endl;
                    cout<<"���Ѫ���ָ�������ֵ������ "<<endl<<endl;
                    PlayerItems[10]=maxHP;
                    cout<<"��������������ȷ�ϣ����� "<<endl<<endl;
                    cin>>inputC;
                }
                else{
                    if(DisPlayMap[markx][marky]==300)
                    {
                        PlayerItems[9]-=20;
                        cout<<"�����˳������Ϣ�� "<<endl<<endl;
                        cout<<"���Ѫ���ָ�������ֵ������ "<<endl<<endl;
                        PlayerItems[10]=maxHP;
                        cout<<"��������������ȷ�ϣ����� "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"��û�г���Ľ�Ǯ��"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ����� "<<endl<<endl;
                        cin>>inputC;
                    }
                }
            }
        }
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///����������
    else if(DisPlayMap[markx][marky]/100==4)
    {
        if(IsOnShengzi) return false;
        ///����0���������ϰ�   ���ϰ�
        system("cls");
        cout<<endl;
        cout<<"�����ϰ塿"<<endl<<endl;
        if(DisPlayMap[markx][marky]%100==0)
        {
            if(RenWu[1]==1)
            {
                cout<<"����Ф��������İ������� "<<endl<<endl;
                cout<<"Ф����������ô���飬ϲ����æ�����;������ҼҰ������������� "<<endl<<endl;
                cout<<"�㽫�����뵱�񶷼һ���ħ��ʦ�أ� "<<endl<<endl;
                cout<<"�񶷼��﹥��ɫ���������Ȥ���񶷼ң�����Ժ��෢չ������ֵ ������Щս��װ��Ҳ������ֵ��Ҫ��"<<endl<<endl;
                cout<<"ħ��ʦ������ɫ���������Ȥ��ħ��ʦ������Ժ��෢չ������ֵ������Щս��װ��Ҳ������ֵ��Ҫ��"<<endl<<endl;
                cout<<"�񶷼��﹥�ܸߣ�����������ֵ�ߵĵ��ˣ����Ե���Щ���� "<<endl<<endl;
                cout<<"ħ��ʦ�������ӵ��˵ķ�����ͬ����ħ��ʦ�ķ���Ҳ�ܵͣ���������������ó��ĵ����Ե���Щ����"<<endl<<endl;
                cout<<"������������һ�ѱ����أ� "<<endl<<endl;
                cout<<"�������Ӧ���֣� "<<endl<<endl;
                cout<<"1.  ���ֵĶ̽� ���񶷼ҷ���"<<endl<<endl;
                cout<<"2.  ���ֵ����� ��ħ��ʦ���� "<<endl<<endl;
                char x;
                cin>>x;
                while(x!='1'&&x!='2')
                {
                    cin>>x;
                }
                if(x=='1')
                {
                    PlayerItems[11]=0;
                    system("cls");
                    cout<<endl;
                    cout<<"�����ˣ������ֵĶ̽���"<<endl<<endl;
                    cout<<"�Ұ���װ���ϰɣ�����"<<endl<<endl;
                    Mywuqi=11;
                    ChangeMyData(Mywuqi);
                    cout<<"����װ�����µ�װ�������ֵĶ̽��� "<<endl<<endl;
                    cout<<"������Ժ������µ�װ�����Դ�װ�����Լ�װ���� "<<endl<<endl;
                }
                else if(x=='2')
                {
                    PlayerItems[11]=1;
                    cout<<"�����ˣ������ֵ����ȡ�"<<endl<<endl;
                    cout<<"�Ұ���װ���ϰɣ�����"<<endl<<endl;
                    Mywuqi=11;
                    ChangeMyData(Mywuqi);
                    cout<<"����װ�����µ�װ�������ֵ����ȡ� "<<endl<<endl;
                    cout<<"������Ժ������µ�װ�����Դ�װ�����Լ�װ���� "<<endl<<endl;
                }
                RenWu[1]=2;
                cout<<"�������ȡ��"<<endl<<endl;
                cout<<"�����ִ��װ���ϰ����������ӣ��������ҵĽ����ţ����������˽�һЩװ�������� ��"<<endl<<endl;
                RenWu[2]=1;
                cout<<"���������ϰ�Ľ����ţ����� "<<endl<<endl;
                cout<<"���������һ������ȷ�ϣ� "<<endl<<endl;
                char c;
                cin>>c;
            }
            else
            {
                while(1)
                {
                    cout<<"��ӭ�������ִ�������꣬����������ϰ壬��������ʲô��Ҫ����"<<endl<<endl;
                    cout<<"1.  ���̽��� ����ֵ��10 ��Ǯ����20"<<endl<<endl;
                    cout<<"2.   ����װ��"<<endl<<endl;
                    cout<<"3.   �뿪"<<endl<<endl;
                    int L0x;
                    char c;
                    cin>>c;
                    while(c!='1'&&c!='2'&&c!='3')
                    {
                        cin>>c;
                    }
                    if(c=='1')
                        L0x=1;
                    if(c=='2')
                        L0x=2;
                    if(c=='3')
                        L0x=3;
                    if(L0x==1)
                    {
                        int L0xFlag=0;
                        int L0xX;
                        for(int i=11; i<21; ++i)
                        {
                            if(PlayerItems[i]<0)
                            {
                                L0xFlag=1;
                                L0xX=i;
                                break;
                            }
                        }
                        system("cls");
                        if(L0xFlag)
                        {
                            if(PlayerItems[9]>=20)
                            {
                                PlayerItems[9]-=20;
                                PlayerItems[L0xX]=1;
                                wuqi[PlayerItems[L0xX]].Nai=NaiJiu;
                                system("cls");
                                cout<<endl;
                                cout<<"�����ˣ����̽���"<<endl<<endl;
                                cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                                char a2;
                                cin>>a2;
                                break;
                            }
                            else
                            {
                                system("cls");
                                cout<<endl;
                                cout<<"��Ľ�Ǯ�������޷�����"<<endl<<endl;
                                cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                                char a2;
                                cin>>a2;
                                break;
                            }
                        }
                        else
                        {
                            system("cls");
                            cout<<endl;
                            cout<<"���װ�����������޷�����"<<endl<<endl;
                            cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                            char a2;
                            cin>>a2;
                            break;
                        }
                    }
                    else if(L0x==2)
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"����������Ҫ���۵�װ��:(�˴����������һ������)"<<endl<<endl;
                        for(int i=11; i<21; ++i)
                        {
                            if(PlayerItems[i]>-1)
                            {
                               cout<<i-11<<"."<<wuqi[PlayerItems[i]].s<<endl;
                            }
                        }
                        int Chu;
                        cin>>inputC;
                        Chu=(inputC-'0')+11;
                        while(Chu>20||Chu<11)
                        {
                            cout<<endl<<"�������Ӧ����:(0-9)"<<endl<<endl;
                            cin>>inputC;
                            Chu=(inputC-'0')+11;
                        }
                        if(PlayerItems[Chu]<0)
                        {
                            system("cls");
                            cout<<endl;
                            cout<<"��û�д˵��ߣ�"<<endl<<endl;
                            cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                            char a2;
                            cin>>a2;
                            break;
                        }
                        else
                        {
                            if(Chu==Mywuqi)
                            {
                                ChangeMyData(-1);
                                Mywuqi=-1;
                            }
                            PlayerItems[Chu]=-1;
                            PlayerItems[9]++;
                            system("cls");
                            cout<<endl;
                            cout<<"������һ��Ǯ��"<<endl<<endl;
                            cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                            char a2;
                            cin>>a2;
                            break;
                        }
                    }
                    else
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"��ӭ�´�����������"<<endl<<endl;
                        cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                        char a2;
                        cin>>a2;
                        break;
                    }
                }
            }
        }
        ///����1���������ϰ�*************************************����������ʱ�����������Ӵ���**********��Ҫ************************

        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///����װ����
    else if(DisPlayMap[markx][marky]/100==5)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"�����ϰ塿"<<endl<<endl;
        ///����0�ŷ�װ���ϰ�***********************************���ӷ�װ��ʱ�����������Ӵ���**********��Ҫ************************
        if(RenWu[2]==1)
        {
            cout<<"��ӭ�㰡�����ˣ������и񶷼Һ�ħ��ʦ���ŵ��·�����ѡ����һ���أ� "<<endl<<endl;
            cout<<"�񶷼ҵ��·������ֵĲ��¡�������Ϊ���ṩ����ֵ "<<endl<<endl;
            cout<<"ħ��ʦ���·������ֵĶ��񡿣�����Ϊ���ṩ�ٶȣ�������ս�������ȳ��� "<<endl<<endl;
            cout<<"1. �����ֵĲ��¡� "<<endl<<endl;
            cout<<"2. �����ֵĶ��� "<<endl<<endl;
            cout<<"�������Ӧ���ֽ���ѡ�� "<<endl<<endl;
            char x;
            cin>>x;
            while(x!='1'&&x!='2')
            {
                cin>>x;
            }
            system("cls");
            if(x=='1')
            {
                PlayerItems[21]=0;
                Myyifu=21;
                ChangeMyData(21);
                system("cls");
                cout<<endl;
                cout<<"�����ˣ������ֵĲ��¡�"<<endl<<endl;
                cout<<"�������㴩�ϰɣ�"<<endl<<endl;
                cout<<"��װ���ˣ������ֵĲ��¡� "<<endl<<endl;
                cout<<"������һ��������ֽ���ȷ�ϣ� "<<endl<<endl;
                char cy;
                cin>>cy;
            }
            else{
                PlayerItems[21]=1;
                Myyifu=21;
                ChangeMyData(21);
                system("cls");
                cout<<endl;
                cout<<"�����ˣ������ֵĶ���"<<endl<<endl;
                cout<<"�������㴩�ϰɣ�"<<endl<<endl;
                char cy;
                cout<<"��װ���ˣ������ֵĶ��� "<<endl<<endl;
                cout<<"������һ��������ֽ���ȷ�ϣ� "<<endl<<endl;
                cin>>cy;
            }
            system("cls");
            cout<<endl;
            cout<<"��������˫Ь�Ӱɣ��Ժ��װ����򲻵�Ь��Ŷ����Ҫ�����Լ�����ȥ��ã� "<<endl<<endl;
            cout<<"�����ˣ������ֵĲ�Ь�� "<<endl<<endl;
            cout<<"�������㴩�ϰɣ� "<<endl<<endl;
            char ccy;
            Myxiezi=31;
            PlayerItems[31]=0;
            ChangeMyData(31);
            cout<<"��װ���ˣ������ֵĲ�Ь�� "<<endl<<endl;
            cout<<"������һ��������ֽ���ȷ�ϣ� "<<endl<<endl;
            cin>>ccy;
            RenWu[2]=2;
            RenWu[3]=1;
            DisPlayMap[0][4]=1001;
            MyMap[5]=1001;
            cout<<"����������װ����ȫ�ˡ�����ջ�ϰ塿������ϲ������������ġ�Ұ�����⣬�����ڿ���ȥ���ִ�����Ͻǵ�Ұ��ȥ��ЩҰ�����������"<<endl<<endl;
            cout<<"��һ������㽱���ģ�"<<endl<<endl;
            if(currentguaiwudata.number<0)
            {
                currentguaiwudata.Id=1200;
                currentguaiwudata.number=guaiwu[currentguaiwudata.Id%100].HitData;
            }
            cout<<"������һ��������ֽ���ȷ�ϣ� "<<endl<<endl;
            cin>>ccy;
        }
        else
        {
            while(1)
            {
                char L0xx;
                cout<<"��ӭ�������ִ�ķ�װ�꣬������Ĳ��ϰ壬��������ʲô��Ҫ����"<<endl<<endl;
                cout<<"1.  �����¡� ����ֵ��5 ��Ǯ����20"<<endl<<endl;
                cout<<"2.   ����װ��"<<endl<<endl;
                cout<<"3.   �뿪"<<endl<<endl;
                int L0x;
                char c;
                cin>>c;
                while(c!='1'&&c!='2'&&c!='3')
                {
                    cin>>c;
                }
                if(c=='1') L0x=1;
                if(c=='2') L0x=2;
                if(c=='3') L0x=3;
                if(L0x==1)
                {
                    int L0xFlag=0;
                    int L0xX;
                    for(int i=11; i<21; ++i)
                    {
                        if(PlayerItems[i]<0)
                        {
                            L0xFlag=1;
                            L0xX=i;
                            break;
                        }
                    }
                    system("cls");
                    if(L0xFlag)
                    {
                        if(PlayerItems[9]>=20)
                        {
                            PlayerItems[9]-=20;
                            PlayerItems[L0xX]=1;
                            yifu[PlayerItems[L0xX]].Nai=NaiJiu;
                            system("cls");
                            cout<<endl;
                            cout<<"�����ˣ������¡�"<<endl<<endl;
                            cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                            cin>>L0xx;
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout<<endl;
                            cout<<"��Ľ�Ǯ�������޷�����"<<endl<<endl;
                            cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                            cin>>L0xx;
                            break;
                        }
                    }
                    else
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"���װ�����������޷�����"<<endl<<endl;
                        cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                        cin>>L0xx;
                        break;
                    }
                }
                else if(L0x==2)
                {
                    system("cls");
                    cout<<endl;
                    cout<<"����������Ҫ���۵�װ��:(�˴����������һ������)"<<endl<<endl;
                    for(int i=21; i<31; ++i)
                    {
                        if(PlayerItems[i]>-1)
                        {
                            cout<<i-21<<"."<<yifu[PlayerItems[i]].s<<endl;
                        }
                    }
                    int Chu;
                    cin>>inputC;
                    Chu=(inputC-'0')+21;
                    while(Chu>30||Chu<21)
                    {
                        cout<<endl<<"�������Ӧ����:(0-9)"<<endl<<endl;
                        cin>>inputC;
                        Chu=(inputC-'0')+21;
                    }
                    if(PlayerItems[Chu]<0)
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"��û�д˵��ߣ�"<<endl<<endl;
                        cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                        cin>>L0xx;
                        break;
                    }
                    else
                    {
                        if(Chu==Myyifu)
                        {
                            ChangeMyData(-2);
                            Myyifu=-1;
                        }
                        PlayerItems[Chu]=-1;
                        PlayerItems[9]++;
                        system("cls");
                        cout<<endl;
                        cout<<"������һ��Ǯ��"<<endl<<endl;
                        cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                        cin>>L0xx;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    cout<<endl;
                    cout<<"��ӭ�´�����������"<<endl<<endl;
                    cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                    cin>>L0xx;
                    break;
                }
            }
        }
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///�����ݵ�
    else if(DisPlayMap[markx][marky]/100==6)
    {
        if(IsOnShengzi) return false;
        IsOnYidian=0;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        if(DisPlayMap[markx][marky]==600) return true;
        else if(DisPlayMap[markx][marky]==601)
        {
            system("cls");
            cout<<endl;
            cout<<"��ϲ�㷢��������ľ�ϲ�� "<<endl<<endl;
            cout<<"���������ֵ +50�� "<<endl<<endl;
            maxHP+=50;
            MyMap[53]=600;
            DisPlayMap[markx][marky]=600;
            RenWu[4]=2;
            cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
            cin>>inputC;
            return true;
        }
        ///�������ӵ��ݵ��������ص��ߵĴ���
        else return true;
    }
    ///������
    else if(DisPlayMap[markx][marky]/100==7)
    {
        if(IsOnShengzi) return false;
        if(PlayerItems[1]==0) return false;
        else
        {
            IsOnYidian=0;

            if(DisPlayMap[markx][marky]==701)
            {
                system("cls");
                cout<<endl;
                cout<<"�����ҵ��������ɶ��������� "<<endl<<endl;
                PlayerItems[99]=1;
                RenWu[9]=2;
                cout<<"���������һ������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            waterFlag=1;
            return true;
        }
    }
    ///����������
    else if(DisPlayMap[markx][marky]/100==8)
    {
        if(IsOnShengzi) return false;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        system("cls");
        cout<<"����������Ҫ���͵��ĵط�������Ŀǰ�����Դ��͵ĵط�Ϊ��"<<DisPlayMap[markx][marky]%100<<"��"<<endl<<endl;
        ///�������Ӵ��Ͷ�Ӧ�ĵ���
        for(int i=0;i<=DisPlayMap[markx][marky]%100;++i)
        {
            cout<<i<<"."<<guanqia[i].s<<endl;
            ///cout<<guanqia[i].wild<<endl;
        }
        cout<<endl;
        cout<<" ������������֣�������ֲ���Ҫ��BUG"<<endl<<endl;
        int x;
        cin>>inputC;
        x=inputC-'0';
        while(x<0||x>LevelCnt)
        {
            cin>>inputC;
            x=inputC-'0';
        }
        if(x<=DisPlayMap[markx][marky]%100)
        {
            if(wildFlag)
            {
                for(int i=0;i<GuaiNow1;++i)
                {
                    DisPlayMap[guaiwuLocx[i]][guaiwuLocy[i]]=guanqia[markLevel].level;
                }
                GuaiNow1=0;
                GuaiNow2=0;
            }
            if(guanqia[x].wild==1) wildFlag=1;
            if(guanqia[x].wild==0) wildFlag=0;
            markLevel=x;
            markx=4;
            marky=0;
            ///***����
            if(wildFlag) wildFlag=0;
            ///***����
            InitMap();
            ///system("cls");
            ///PrintMap();
            return false;
        }
        else {
            cout<<"�޷�����"<<endl<<endl;
            cout<<"��������������ȷ�ϣ�"<<endl<<endl;
            char c;
            cin>>c;
            return false;
        }
    }
    ///����ʯͷ
    else if(DisPlayMap[markx][marky]/100==9)
    {
        if(IsOnShengzi) return false;
        if(PlayerItems[0]==0) return false;
        else{
            IsOnYidian=0;
            if(DisPlayMap[markx][marky]==900)
            {
                if(PlayerItems[1]>0&&waterFlag==1)
                {
                    PlayerItems[1]--;
                    waterFlag=0;
                }
                PlayerItems[0]--;
                DisPlayMap[markx][marky]=0;
                MyMap[26*markLevel+1+5*markx+marky]=0;
                return true;
            }
            else if(DisPlayMap[markx][marky]==999)
            {
                system("cls");
                cout<<endl;
                if(bossFlag==0)
                {
                    gameFlag=1;
                    cout<<"ʯͷ����ħ���Ľ�磡 "<<endl<<endl;
                    cout<<"�㱻��練�ˣ����ز���"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    return false;
                }
                else
                {
                    PlayerItems[0]--;
                    cout<<"���ʯͷ̫��Ӳ�ˣ� "<<endl<<endl;
                    cout<<"��Ĵ��ӱ����飬��ʯͷ��������"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    return false;
                }
            }
            else if(DisPlayMap[markx][marky]==901)
            {
                system("cls");
                cout<<endl;
                if(PlayerItems[1]>0&&waterFlag==1)
                {
                    PlayerItems[1]--;
                    waterFlag=0;
                }
                PlayerItems[0]--;
                DisPlayMap[markx][marky]=0;
                MyMap[26*markLevel+1+5*markx+marky]=0;
                cout<<"���ҵ��ˡ������顿 "<<endl<<endl;
                PlayerItems[66]=1;
                RenWu[5]=2;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                return true;
            }
        }
    }
    ///����Ұ�⴫��
    else if(DisPlayMap[markx][marky]/100==10)
    {
        if(IsOnShengzi) return false;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        wildFlag=1;
        markLevel=DisPlayMap[markx][marky]%100;
        markx=4;
        marky=0;
        InitMap();
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///����������
    else if(DisPlayMap[markx][marky]/100==11)
    {
        if(IsOnShengzi) return false;

        int Dp=DisPlayMap[markx][marky]%100;
        if(Tips[Dp]!=1)
        {
            if(PlayerItems[1]>0&&waterFlag==1)
            {
                PlayerItems[1]--;
                waterFlag=0;
            }
            return true;
        }
        else{
            ///���»����������������˵Ĵ���
            system("cls");
            cout<<endl;
            cout<<"�������ˡ� "<<endl<<endl;
            if(Dp==0)
            {
                cout<<"��ã��е�ʱ��������Ҫ���Լ�������գ�Ȼ���������ע���� "<<endl<<endl;
                cout<<"����Ҫ���Լ���TIPֵ��գ���Ϊ0�� "<<endl<<endl;
                cout<<"��1.��Ҫ����2.����������ģ���Ҫ��Ϊ0�� "<<endl<<endl;
                cout<<"��ѡ��: "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    PlayerItems[4]=0;
                    Tips[Dp]=0;
                    cout<<"������Ը����Ե�ټ��� "<<endl<<endl;
                    cout<<"��ġ�TIP��ֵ��Ϊ��0 "<<endl<<endl;
                    cout<<"������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                }
                else
                {
                    cout<<"���ߣ� "<<endl<<endl;
                    cout<<"������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                }
            }
            else if(Dp==1)
            {
                cout<<"��ã�����������������Ҫ��Ѫ����Ը������Ѫ������һЩ�� "<<endl<<endl;
                cout<<"��1.ʮ�����⡿��2.�ҵ�Ѫ����󣬲Ų�Ҫ�ָ��㡿 "<<endl<<endl;
                cout<<"��ѡ��: "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    if(PlayerItems[10]>2)
                    {
                        PlayerItems[10]=2;
                        Tips[Dp]=2;
                        cout<<"лл�㣬��Ե�ټ��� "<<endl<<endl;
                        cout<<"��ġ�HP��ֵ��Ϊ��2 "<<endl<<endl;
                        cout<<"������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                    }
                    else{
                        cout<<"��ġ�HP��ֵҲ�����أ� "<<endl<<endl;
                        cout<<"������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else
                {
                    cout<<"���ߣ� "<<endl<<endl;
                    cout<<"������������ȷ��"<<endl<<endl;
                    Tips[Dp]=2;
                    cin>>inputC;
                }
            }

            ///���ϻ����������������˵Ĵ���

            ///�������䵱�����Ի��¼�ʱ�󶨳��֣������淢�ֲ�����Ҫ
            ///system("cls");
            ///PrintMap();
            return false;
            ///�������䵱�����Ի��¼�ʱ�󶨳��֣������淢�ֲ�����Ҫ
        }
    }
    ///��������
    else if(DisPlayMap[markx][marky]/100==12)
    {
        if(IsOnShengzi) return false;
        IsMeet=1;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        ///*************************�˴���������ս������(�����ӣ�
        fightFlag=1;
        LoadFight();
        DisPlayMap[markx][marky]=0;
        return true;
    }
    ///����ѧУ
    else if(DisPlayMap[markx][marky]/100==13)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        if(DisPlayMap[markx][marky]%100==1)
        {
            if(myschool.xuexiaoLevel>=1&&myschool.ID!=1)
            {
                cout<<"���Ѿ������������ѧУ��ѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.ID==0&&myschool.xuexiaoLevel==0)
            {
                cout<<"��������·�ˡ�"<<endl<<endl;
                cout<<"���Ǽ���ѧУ����·�ˣ������ͨ���ҵ�һ��������ܽ�������ѧУѧϰ "<<endl<<endl;
                cout<<"��ȷ�������ҵ������� "<<endl<<endl;
                cout<<"1.��ȷ���� "<<endl<<endl;
                cout<<"2.�������� "<<endl<<endl;
                cout<<"�������Ӧ����ѡ�� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    myschool.ID=1;
                    IsMeet=0;
                    ChengZhangRenWu[0]=1;
                    system("cls");
                    cout<<endl;
                    cout<<"��ѧ������������ѵ�������������ǵĵط������Ŀ����ǣ� "<<endl<<endl;
                    cout<<"��ȥѧ����תһȦ����Ҫ��Ұ��������������ͨ���˿��飡��"<<endl<<endl;
                    cout<<"�����ڰ��㴫�͵���ѧ��������"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    markLevel=4;
                    markx=4;
                    marky=0;
                    wildFlag=1;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
                else
                {
                    markLevel=3;
                    markx=4;
                    marky=0;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
            }
            else if(myschool.ID==1&&myschool.xuexiaoLevel==0)
            {
                if(IsMeet==1)
                {
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"�㻹û������ҵ�����"<<endl<<endl;
                    cout<<"1.���ұ�Ұ�������ˣ�����������ȡ����"<<endl<<endl;
                    cout<<"2.���Ҳ���������ѧУѧϰ�ˣ�����ȡ������"<<endl<<endl;
                    cout<<"��ѡ����Ӧ����"<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        IsMeet=0;
                        cout<<"�ã����ٽ��㴫�͵���ѧ��������ף��˳����"<<endl<<endl;
                        cout<<"��������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                        markLevel=4;
                        markx=4;
                        marky=0;
                        wildFlag=1;
                        InitMap();
                        ///system("cls");
                        ///PrintMap();
                        return false;
                    }
                    else
                    {
                        myschool.ID=0;
                        ChengZhangRenWu[0]=0;
                        system("cls");
                        cout<<endl;
                        cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                        cout<<"��������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                        markLevel=3;
                        markx=4;
                        marky=0;
                        InitMap();
                        ///system("cls");
                        ///PrintMap();
                        return false;
                    }
                }
                else
                {
                    myschool.xuexiaoLevel++;
                    ChengZhangRenWu[0]=2;
                    system("cls");
                    cout<<endl;
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"��ϲ�㣬������ҵ���������ʽ��Ϊ������ѧУ��һԱ��"<<endl<<endl;
                    cout<<"�����ڰ��㴫��ѧУ��ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    LoadXuexiao(10);
                    return false;
                }
            }
            else if(myschool.ID==1&&myschool.xuexiaoLevel==1)
            {
                LoadXuexiao(10);
                return false;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
        }
        else if(DisPlayMap[markx][marky]%100==2)
        {
            if(myschool.xuexiaoLevel==0)
            {
                cout<<"�������������������ѧУѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.xuexiaoLevel==1&&myschool.ID==1)
            {
                cout<<"�������������������ѧУѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.xuexiaoLevel>=2&&myschool.ID!=1)
            {
                cout<<"���Ѿ����������ѧУ��ѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.ID==0&&myschool.xuexiaoLevel==1)
            {
                cout<<"���Ǽ���ѧУ����·��"<<endl<<endl;
                cout<<"��ȷ����������ѧУ������ "<<endl<<endl;
                cout<<"1.��ȷ���� "<<endl<<endl;
                cout<<"2.�������� "<<endl<<endl;
                cout<<"�������Ӧ����ѡ�� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    myschool.ID=1;
                    myschool.xuexiaoLevel++;
                    system("cls");
                    cout<<endl;
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"��ϲ�㣬����ʽ��Ϊ������ѧУ��һԱ��"<<endl<<endl;
                    cout<<"�����ڰ��㴫��ѧУ��ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    LoadXuexiao(11);
                    return false;
                }
                else
                {
                    markLevel=3;
                    markx=4;
                    marky=0;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
            }
            else if(myschool.ID==1&&myschool.xuexiaoLevel==2)
            {
                LoadXuexiao(11);
                return false;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
        }
        else if(DisPlayMap[markx][marky]%100==3)
        {
            if(myschool.xuexiaoLevel<2)
            {
                cout<<"�������������������ѧУѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.xuexiaoLevel==2&&myschool.ID==1)
            {
                cout<<"�������������������ѧУѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.xuexiaoLevel>=3&&myschool.ID!=1)
            {
                cout<<"���Ѿ����������ѧУ��ѧϰ������ "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.ID==0&&myschool.xuexiaoLevel==2)
            {
                cout<<"���Ǽ���ѧУ����·��"<<endl<<endl;
                cout<<"��ȷ����������ѧУ������ "<<endl<<endl;
                cout<<"1.��ȷ���� "<<endl<<endl;
                cout<<"2.�������� "<<endl<<endl;
                cout<<"�������Ӧ����ѡ�� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    myschool.ID=1;
                    myschool.xuexiaoLevel++;
                    system("cls");
                    cout<<endl;
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"��ϲ�㣬����ʽ��Ϊ������ѧУ��һԱ��"<<endl<<endl;
                    cout<<"�����ڰ��㴫��ѧУ��ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    LoadXuexiao(12);
                    return false;
                }
                else
                {
                    markLevel=3;
                    markx=4;
                    marky=0;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
            }
            else if(myschool.ID==1&&myschool.xuexiaoLevel==3)
            {
                LoadXuexiao(12);
                return false;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
        }
        else return false;
    }
    ///�������
    else if(DisPlayMap[markx][marky]/100==14)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        if(DisPlayMap[markx][marky]%100==1)
        {
            if(myschool.ID==0&&myschool.wuguanLevel==0)
            {
                cout<<"��������·�ˡ�"<<endl<<endl;
                cout<<"���Ǽ�����ݵ���·�ˣ������ͨ���ҵ�һ��������ܽ����������ѵ�� "<<endl<<endl;
                cout<<"��ȷ�������ҵ������� "<<endl<<endl;
                cout<<"1.��ȷ���� "<<endl<<endl;
                cout<<"2.�������� "<<endl<<endl;
                cout<<"�������Ӧ����ѡ�� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    if(currentguaiwudata.number<0)
                    {
                        currentguaiwudata.Id=1201;
                        currentguaiwudata.number=guaiwu[1].HitData;
                        myschool.ID=2;
                        ChengZhangRenWu[1]=1;
                        cout<<"��ѧ������������ѵ�������������ǵĵط������Ŀ����ǣ� "<<endl<<endl;
                        cout<<"��ȥѧ����תһȦ������10����ż��������ͨ���˿��飡��"<<endl<<endl;
                        cout<<"�����ڰ��㴫�͵���ѧ��������"<<endl<<endl;
                        cout<<"��������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                        markLevel=4;
                        markx=4;
                        marky=0;
                        wildFlag=1;
                        InitMap();
                        ///system("cls");
                        ///PrintMap();
                        return false;
                    }
                    else
                    {
                        cout<<"�㻹�л�ɱҰ�ֵ�����û����ɣ����������ɺ��������ң� "<<endl<<endl;
                        cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                        cout<<"��������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                        markLevel=3;
                        markx=4;
                        marky=0;
                        InitMap();
                        ///system("cls");
                        ///PrintMap();
                        return false;
                    }
                }
                else
                {
                    markLevel=3;
                    markx=4;
                    marky=0;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
            }
            else if(myschool.ID==2&&myschool.wuguanLevel==0)
            {
                if(guaiwu[1].HitData-currentguaiwudata.number<10)
                {
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"�㻹û������ҵ�����"<<endl<<endl;
                    cout<<"1.��������ȥ��ɣ���"<<endl<<endl;
                    cout<<"2.���Ҳ�����������ѵ���ˣ�����ȡ������"<<endl<<endl;
                    cout<<"��ѡ����Ӧ����"<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"�ã����ٽ��㴫�͵���ѧ��������ף��˳����"<<endl<<endl;
                        cout<<"��������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                        markLevel=4;
                        markx=4;
                        marky=0;
                        wildFlag=1;
                        InitMap();
                        ///system("cls");
                        ///PrintMap();
                        return false;
                    }
                    else
                    {
                        myschool.ID=0;
                        ChengZhangRenWu[0]=0;
                        system("cls");
                        cout<<endl;
                        cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                        cout<<"��������������ȷ��"<<endl<<endl;
                        cin>>inputC;
                        markLevel=3;
                        markx=4;
                        marky=0;
                        InitMap();
                        ///system("cls");
                        ///PrintMap();
                        return false;
                    }
                }
                else
                {
                    myschool.wuguanLevel++;
                    ChengZhangRenWu[1]=2;
                    system("cls");
                    cout<<endl;
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"��ϲ�㣬������ҵ���������ʽ��Ϊ�������ݵ�һԱ��"<<endl<<endl;
                    currentguaiwudata.number=-1;
                    cout<<"�����ڰ��㴫�͵������ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    LoadWuguan(13);
                    return false;
                }
            }
            else if(myschool.ID==2&&myschool.wuguanLevel==1)
            {
                LoadWuguan(13);
                return false;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
        }
        else if(DisPlayMap[markx][marky]%100==2)
        {
            if(myschool.wuguanLevel==0)
            {
                cout<<"�������������������������������� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.wuguanLevel==1&&myschool.ID==2)
            {
                cout<<"�������������������������������� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.wuguanLevel>=2&&myschool.ID!=2)
            {
                cout<<"���Ѿ������������ݵ����������� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.ID==0&&myschool.wuguanLevel==1)
            {
                cout<<"��������·�ˡ�"<<endl<<endl;
                cout<<"���Ǽ�����ݵ���·��"<<endl<<endl;
                cout<<"��ȷ������������������� "<<endl<<endl;
                cout<<"1.��ȷ���� "<<endl<<endl;
                cout<<"2.�������� "<<endl<<endl;
                cout<<"�������Ӧ����ѡ�� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    myschool.ID=2;
                    myschool.wuguanLevel++;
                    system("cls");
                    cout<<endl;
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"��ϲ�㣬����ʽ��Ϊ��������ݵ�һԱ��"<<endl<<endl;
                    cout<<"�����ڰ��㴫�������ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    LoadWuguan(14);
                    return false;
                }
                else
                {
                    markLevel=3;
                    markx=4;
                    marky=0;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
            }
            else if(myschool.ID==2&&myschool.wuguanLevel==2)
            {
                LoadWuguan(14);
                return false;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
        }
        else if(DisPlayMap[markx][marky]%100==3)
        {
            if(myschool.wuguanLevel<2)
            {
                cout<<"�������������������������������� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.wuguanLevel==2&&myschool.ID==2)
            {
                cout<<"�������������������������������� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.wuguanLevel>=3&&myschool.ID!=2)
            {
                cout<<"�������������������������������� "<<endl<<endl;
                cout<<"��������������ȷ�� "<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
            if(myschool.ID==0&&myschool.wuguanLevel==2)
            {
                cout<<"��������·�ˡ�"<<endl<<endl;
                cout<<"���Ǽ�����ݵ���·��"<<endl<<endl;
                cout<<"��ȷ������������������� "<<endl<<endl;
                cout<<"1.��ȷ���� "<<endl<<endl;
                cout<<"2.�������� "<<endl<<endl;
                cout<<"�������Ӧ����ѡ�� "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    myschool.ID=2;
                    myschool.wuguanLevel++;
                    system("cls");
                    cout<<endl;
                    cout<<"��������·�ˡ�"<<endl<<endl;
                    cout<<"��ϲ�㣬����ʽ��Ϊ��������ݵ�һԱ��"<<endl<<endl;
                    cout<<"�����ڰ��㴫�������ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ��"<<endl<<endl;
                    cin>>inputC;
                    LoadWuguan(15);
                    return false;
                }
                else
                {
                    markLevel=3;
                    markx=4;
                    marky=0;
                    InitMap();
                    ///system("cls");
                    ///PrintMap();
                    return false;
                }
            }
            else if(myschool.ID==2&&myschool.wuguanLevel==3)
            {
                LoadWuguan(15);
                return false;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"�㱻һ��ǿ��������ͳ������ "<<endl<<endl;
                cout<<"��������������ȷ��"<<endl<<endl;
                cin>>inputC;
                markLevel=3;
                markx=4;
                marky=0;
                InitMap();
                ///system("cls");
                ///PrintMap();
                return false;
            }
        }
        else return false;
    }
    ///����ħ��
    else if(DisPlayMap[markx][marky]/100==15)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"��ħ���� "<<endl<<endl;
        if(PlayerItems[2]<1&&PlayerItems[3]<1)
        {
            cout<<"�㻹�������ҵĶ��֣� "<<endl<<endl;
            DisPlayMap[markx][marky]=809;
            cout<<"��������������ȷ��"<<endl<<endl;
            cin>>inputC;
        }
        else
        {
            DisPlayMap[markx][marky]=2400;
        }
        return false;
    }
    ///�����󻤷�
    else if(DisPlayMap[markx][marky]/100==16)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(myschool.ID==1)
        {
            if(myschool.xuexiaoLevel==1)
            {
                cout<<"������ѧУ�󻤷��� "<<endl<<endl;
                if(ChengZhangRenWu[2]==0)
                {
                    cout<<"����һЩ�����ĥ��������Ի������ֵ�� "<<endl<<endl;
                    cout<<"����Ҫ���ܳ����������ս�� "<<endl<<endl;
                    cout<<"1.��ȷ����2.�������롿"<<endl<<endl;
                    cout<<"��ѡ�� "<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        IsMeet=0;
                        To=16;
                        ChengZhangRenWu[2]=1;
                        cout<<"��������ҵ�����"<<endl<<endl;
                        cout<<"�찴R���鿴�Լ��ĳɳ�������ʲô�ɣ����� "<<endl<<endl;
                        cout<<"���½��и��󷨿��Դ��㵽��ȥ�ĵط��� "<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(ChengZhangRenWu[2]==1)
                {
                    IsMeet=0;
                    cout<<"���Ѿ��������ҵ�����"<<endl<<endl;
                    cout<<"��ȥ��ɰɣ���ø�ǿ�� "<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    cin>>inputC;
                }
                else
                {
                    cout<<"���Ѿ�������ҵ�����"<<endl<<endl;
                    cout<<"ȥ��ɸ��߼�������ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    cin>>inputC;
                }
            }
            if(myschool.xuexiaoLevel==2)
            {
                cout<<"���м�ѧУ�󻤷��� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==3)
            {
                cout<<"���߼�ѧУ�󻤷��� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
        }
        else
        {
            if(myschool.wuguanLevel==1)
            {
                cout<<"����������󻤷��� "<<endl<<endl;
                if(ChengZhangRenWu[3]==0)
                {
                    cout<<"����һЩ�����ĥ��������Ի������ֵ�� "<<endl<<endl;
                    cout<<"����Ҫ���ܳ����������ս�� "<<endl<<endl;
                    cout<<"1.��ȷ����2.�������롿"<<endl<<endl;
                    cout<<"��ѡ�� "<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        if(currentguaiwudata.number==-1)
                        {
                            currentguaiwudata.Id=1206;
                            currentguaiwudata.number=guaiwu[6].HitData;
                            To=17;
                            ChengZhangRenWu[3]=1;
                            cout<<"��������ҵ�����"<<endl<<endl;
                            cout<<"�찴R���鿴�Լ��ĳɳ�������ʲô�ɣ����� "<<endl<<endl;
                            cout<<"���½��и��󷨿��Դ��㵽��ȥ�ĵط��� "<<endl<<endl;
                            cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                            cin>>inputC;
                        }
                        else
                        {
                            cout<<"������������û����ɣ��޷���ȡ���� "<<endl<<endl;
                            To=3;
                            cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                            cin>>inputC;
                        }
                    }
                }
                else if(ChengZhangRenWu[3]==1)
                {
                    cout<<"���Ѿ��������ҵ�����"<<endl<<endl;
                    cout<<"��ȥ��ɰɣ���ø�ǿ�� "<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    cin>>inputC;
                }
                else
                {
                    cout<<"���Ѿ�������ҵ�����"<<endl<<endl;
                    cout<<"ȥ��ɸ��߼�������ɣ�"<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    cin>>inputC;
                }
            }
            if(myschool.wuguanLevel==2)
            {
                cout<<"���м�����󻤷��� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==3)
            {
                cout<<"���߼�����󻤷��� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
        }
        return false;
    }
    ///����ѧУ/�����ϯ
    else if(DisPlayMap[markx][marky]/100==17)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(myschool.ID==1)
        {
            if(myschool.xuexiaoLevel==1)
            {
                cout<<"������ѧУ��ϯ�� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==2)
            {
                cout<<"���м�ѧУ��ϯ�� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==3)
            {
                cout<<"���߼�ѧУ��ϯ�� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
        }
        else
        {
            if(myschool.wuguanLevel==1)
            {
                cout<<"�����������ϯ�� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==2)
            {
                cout<<"���м������ϯ�� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==3)
            {
                cout<<"���߼������ϯ�� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
        }
        return false;
    }
    ///�����һ���
    else if(DisPlayMap[markx][marky]/100==18)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(myschool.ID==1)
        {
            if(myschool.xuexiaoLevel==1)
            {
                cout<<"������ѧУ�һ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==2)
            {
                cout<<"���м�ѧУ�һ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==3)
            {
                cout<<"���߼�ѧУ�һ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
        }
        else
        {
            if(myschool.wuguanLevel==1)
            {
                cout<<"����������һ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==2)
            {
                cout<<"���м�����һ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==3)
            {
                cout<<"���߼�����һ����� "<<endl<<endl;
                cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                cin>>inputC;
            }
        }
        return false;
    }
    ///������
    else if(DisPlayMap[markx][marky]/100==19)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(To==-1)
        {
            cout<<"���󷨡�"<<endl<<endl;
            cout<<"�㲢û����ȥ�ĵط��� "<<endl<<endl;
            cout<<"��������������ȷ��"<<endl<<endl;
            cin>>inputC;
            return false;
        }
        else
        {
            int x=To;
            if(guanqia[x].wild==1) wildFlag=1;
            if(guanqia[x].wild==0) wildFlag=0;
            markLevel=x;
            markx=4;
            marky=0;
            InitMap();
            ///system("cls");
            ///PrintMap();
            return false;
        }
    }
    ///�����ʵ�
    else if(DisPlayMap[markx][marky]/100==20)
    {
        if(IsOnShengzi) return false;
        IsOnYidian=0;
        LoadCaiDan();
        MyMap[26*10+13]=0;
        DisPlayMap[2][2]=0;
        return false;
    }
    ///��������
    else if(DisPlayMap[markx][marky]/100==21)
    {
        if(DisPlayMap[markx][marky]==2100)
        {
            if(PlayerItems[1]>0&&waterFlag==1)
            {
                PlayerItems[1]--;
                waterFlag=0;
            }
            IsOnShengzi=0;
            IsOnYidian=0;
            return true;
        }
        else
        {
            if(DisOld==2100)
            {
                IsOnShengzi=1;
                IsOnYidian=0;
                return true;
            }
            else
            {
                if(IsOnShengzi)
                {
                    IsOnYidian=0;
                    return true;
                }
                else return false;
            }
        }
    }
    ///����֩��BOSS
    else if(DisPlayMap[markx][marky]/100==22)
    {
        if(IsOnShengzi) return false;

        IsOnDongxue=0;

        markLevel=0;
        markx=4;
        marky=0;
        InitMap();
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///������ͷ
    else if(DisPlayMap[markx][marky]/100==23)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"ǰ��һ�ѿ��µĹ�ͷ "<<endl<<endl;
        cout<<"��������������ȷ��"<<endl<<endl;
        cin>>inputC;
        return false;
    }
    ///������Ѩ
    else  if(DisPlayMap[markx][marky]/100==24)
    {
        if(IsOnShengzi) return false;
        IsOnDongxue=1;
        markLevel=23; ///��Ѩ��ʼ�ؿ�Ϊ 23
        markx=4;
        marky=0;
        InitMap();
        return false;
    }

    return false;
}
void Init()
{
    ///�ڴ����ӹؿ�����**************************��Ҫ***********************************
    guanqia[0].level=-1;
    guanqia[0].s="�����ִ塿";
    guanqia[0].wild=0;
    guanqia[1].s="���������";
    guanqia[1].level=1200;
    guanqia[1].wild=1;
    guanqia[2].level=-1;
    guanqia[2].s="��ʮ���¡�";
    guanqia[2].wild=0;
    guanqia[3].level=-1;
    guanqia[3].s="��������";
    guanqia[3].wild=0;
    guanqia[4].level=1201;
    guanqia[4].s="��ѧ������";
    guanqia[4].wild=1;
    guanqia[5].level=-1;
    guanqia[5].s="����Դ��";
    guanqia[5].wild=0;
    guanqia[6].level=1202;
    guanqia[6].s="�������֡�";
    guanqia[6].wild=1;
    guanqia[7].level=-1;
    guanqia[7].s="������";
    guanqia[7].wild=0;
    guanqia[8].level=1203;
    guanqia[8].s="�������¡�";
    guanqia[8].wild=1;
    guanqia[9].level=-1;
    guanqia[9].s="��ħ����";
    guanqia[9].wild=0;
    guanqia[10].level=-1;
    guanqia[10].s="������ѧУ��";
    guanqia[10].wild=0;
    guanqia[11].level=-1;
    guanqia[11].s="���м�ѧУ��";
    guanqia[11].wild=0;
    guanqia[12].level=-1;
    guanqia[12].s="���߼�ѧУ��";
    guanqia[12].wild=0;
    guanqia[13].level=-1;
    guanqia[13].s="��������ݡ�";
    guanqia[13].wild=0;
    guanqia[14].level=-1;
    guanqia[14].s="���м���ݡ�";
    guanqia[14].wild=0;
    guanqia[15].level=-1;
    guanqia[15].s="���߼���ݡ�";
    guanqia[15].wild=0;
    guanqia[16].level=1205;
    guanqia[16].s="����Ƶء�";
    guanqia[16].wild=1;
    guanqia[17].level=1206;
    guanqia[17].s="���ķ��ء�";
    guanqia[17].wild=1;

    ///�ڴ����ӹ�������**************************��Ҫ***********************************
    ///˫��Ϊ���������Ĺ������Ϊ���������Ĺ���
    guaiwu[0].s="��Ұ����";  ///��������
    guaiwu[0].Hp=22;
    guaiwu[0].Hit=10;
    guaiwu[0].Fangyu=5;
    guaiwu[0].Speed=1;
    guaiwu[1].s="����ż��";  ///��������
    guaiwu[1].Hp=40;
    guaiwu[1].Hit=20;
    guaiwu[1].Fangyu=8;
    guaiwu[1].Speed=2;
    guaiwu[2].s="��������";   ///��
    guaiwu[2].Hp=60;
    guaiwu[2].Hit=30;
    guaiwu[2].Fangyu=16;
    guaiwu[2].Speed=3;
    guaiwu[3].s="��Īɣ����";  ///��������
    guaiwu[3].Hp=80;
    guaiwu[3].Hit=40;
    guaiwu[3].Fangyu=20;
    guaiwu[3].Speed=4;
    guaiwu[4].s="��������";   ///��
    guaiwu[4].Hp=100;
    guaiwu[4].Hit=60;
    guaiwu[4].Fangyu=25;
    guaiwu[4].Speed=5;
    guaiwu[5].s="����";  ///��
    guaiwu[5].Hp=1;
    guaiwu[5].Hit=1;
    guaiwu[5].Fangyu=999999;
    guaiwu[5].Speed=999999;
    guaiwu[6].s="�������֡�";  ///��
    guaiwu[6].Hp=50;
    guaiwu[6].Hit=40;
    guaiwu[6].Fangyu=50;
    guaiwu[6].Speed=999;

///PlayerItems[0]=0;  ///�������������������ҿ�ʯͷ
///PlayerItems[1]=0;  ///ľ��������������������
///PlayerItems[2]    ///�������ֵ
///playerItems[3]    ///�������ֵ
///playerItems[4]     Tipֵ���������������ˣ������������˶Ի��浵����ֻ�ã�ÿ��+1
    PlayerItems[5] = 1;///�﹥ֵ(����������Ϊ 1 ��
    PlayerItems[6] = 1; ///����ֵ
    PlayerItems[7] = 1; ///����ֵ
    PlayerItems[8] = 1; ///�ٶ�ֵ(����������Ϊ 1 ��
    PlayerItems[9] = 0; ///��Ǯ(��������Ϊ0)
    PlayerItems[10]=50;  ///HP
    for(int i=11; i<=40; ++i)
    {
        PlayerItems[i]=-1;
    }

    ///����Ϊ���Դ���**************��ɾ��
    /*PlayerItems[11]=0;
    PlayerItems[12]=1;
    PlayerItems[13]=2;
    PlayerItems[14]=3;
    PlayerItems[21]=0;
    PlayerItems[22]=1;
    PlayerItems[23]=2;
    PlayerItems[24]=3;
    PlayerItems[31]=0;
    PlayerItems[32]=1;
    PlayerItems[33]=2;
    PlayerItems[34]=3;
    PlayerItems[35]=4;
    PlayerItems[36]=5;
    PlayerItems[37]=6;*/
    ///����Ϊ���Դ���**************���������ע�ͻ�ɾ��

///�ڴ��޸�Ь������   Ь�Ӳ����������ܹ����ᳬ��ʮ˫Ь�ӣ� Ь��Ҳ�޷�����
    xiezi[0].s="�����ֵĲ�Ь��";
    xiezi[0].Speed=1;
    xiezi[1].s="����ѥ��";
    xiezi[1].Speed=2;
    xiezi[2].s="��ѩѥ��";
    xiezi[2].Speed=3;
    xiezi[3].s="����ѥ��";
    xiezi[3].Speed=4;
    xiezi[4].s="����ѥ��";
    xiezi[4].Speed=5;
    xiezi[5].s="����ѥ��";
    xiezi[5].Speed=6;
    xiezi[6].s="������ѥ��";
    xiezi[6].Speed=7;
    xiezi[7].s="��Ф��ѥ��";
    xiezi[7].Speed=8;

    ///xiezi[1].Speed=1;
///�ڴ��޸ĸ񶷼���������
    wuqi[0].s="�����ֵĶ̽���";
    wuqi[0].Zhi=0;
    wuqi[0].Hit=10;
    wuqi[0].Nai=-1; ///-1��ʾ���ÿ���
    wuqi[2].s="���̽���";
    wuqi[2].Zhi=0;
    wuqi[2].Hit=10;
    wuqi[2].Nai=20;

///�ڴ��޸ĸ񶷼�װ������
    yifu[0].s="�����ֵĲ��¡�";
    yifu[0].Zhi=0;
    yifu[0].FangYu=5;
    yifu[0].Nai=-1;
    yifu[2].s="�����¡�";
    yifu[2].Zhi=0;
    yifu[2].FangYu=5;
    yifu[2].Nai=20;

///�ڴ��޸�ħ��ʦ��������
    wuqi[1].Zhi=0;
    wuqi[1].s="�����ֵ����ȡ�";
    wuqi[1].Hit=5;
    wuqi[1].Nai=-1;
    wuqi[3].s="�����ȡ�";
    wuqi[3].Zhi=0;
    wuqi[3].Hit=5;
    wuqi[3].Nai=20;

///�ڴ��޸�ħ��ʦ��������
    yifu[1].Zhi=0;
    yifu[1].s="�����ֵĶ���";
    yifu[1].FangYu=1;
    yifu[1].Nai=-1;
    yifu[3].s="������";
    yifu[3].Zhi=0;
    yifu[3].FangYu=1;
    yifu[3].Nai=20;

}
void ChangeMyData(int i) ///11-20 ���� 21-30  �·� 31-40 Ь��
{
    ///-1��ʾж������ -2��ʾж���·� -3��ʾж��Ь�� >=0��ʾ������Ӧװ��
    if(i==-1)
    {
        if(Mywuqi>-1)
        {
            if(PlayerItems[Mywuqi]%2==0)
                PlayerItems[5]-=wuqi[PlayerItems[Mywuqi]].Hit;
            else
                PlayerItems[6]-=wuqi[PlayerItems[Mywuqi]].Hit;
        }
    }
    else if(i==-2)
    {
        if(Myyifu>-1)
        {
            if(PlayerItems[Myyifu]%2==0)
                PlayerItems[7]-=yifu[PlayerItems[Myyifu]].FangYu;
            else
                PlayerItems[8]-=yifu[PlayerItems[Myyifu]].FangYu;
        }
    }
    else if(i==-3)
    {
        if(Myxiezi>-1)
            PlayerItems[8]-=xiezi[PlayerItems[Myxiezi]].Speed;
    }
    else if(i>10&&i<21)
    {
        if(PlayerItems[i]%2==0) PlayerItems[5]+=wuqi[PlayerItems[i]].Hit;
        else PlayerItems[6]+=wuqi[PlayerItems[i]].Hit;
    }
    else if(i>20&&i<31)
    {
        if(PlayerItems[i]%2==0) PlayerItems[7]+=yifu[PlayerItems[i]].FangYu;
        else PlayerItems[8]+=yifu[PlayerItems[i]].FangYu;
    }
    else if(i>30&&i<41)
    {
        PlayerItems[8]+=xiezi[PlayerItems[i]].Speed;
    }
}
void LoadFight()
{
    if(Mywuqi>0)
    {
        if(wuqi[PlayerItems[Mywuqi]].Nai>0)
            wuqi[PlayerItems[Mywuqi]].Nai--;
    }
    if(Myyifu>0)
    {
        if(yifu[PlayerItems[Myyifu]].Nai>0)
            yifu[PlayerItems[Myyifu]].Nai--;
    }
    system("cls");
    int Ghp=guaiwu[DisPlayMap[markx][marky]%100].Hp;
    while(fightFlag)
    {
        int x;
        char xx;
        if(!ZiDong)
        {
            cout<<endl;
            cout<<"�������ˣ�"<<guaiwu[DisPlayMap[markx][marky]%100].s<<endl<<endl;
            cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"��Ѫ��:"<<Ghp<<"��"<<endl<<endl;
            cout<<"���ҡ�"<<"��Ѫ��:"<<PlayerItems[10]<< "��"<<endl<<endl;
        }
        if(PlayerItems[8]>guaiwu[DisPlayMap[markx][marky]%100].Speed)
        {
            if(ZiDong==0)
            {
                cout<<"��ѡ����Ĺ����� 1.�������� 2.����������"<<endl<<endl;
                cin>>xx;
                while(xx!='1'&&xx!='2')
                {
                    cin>>xx;
                }
                if(xx=='1')
                    x=1;
                if(xx=='2')
                    x=2;
            }
            if(ZiDong==1) x=1;
            if(ZiDong==2) x=2;
            if(x==1)
            {
                if(!ZiDong)
                {
                    cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"Ѫ��������:"<<PlayerItems[5]-guaiwu[(DisPlayMap[markx][marky]%100)].Fangyu<<endl<<endl;
                }
                Ghp-=(PlayerItems[5]-guaiwu[DisPlayMap[markx][marky]%100].Fangyu);
                if(Ghp<=0) {
                    system("cls");
                    cout<<endl<<"���ʤ�ˣ�������ϲ������"<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    char xsheng;
                    cin>>xsheng;
                    guaiwu[DisPlayMap[markx][marky]%100].HitData++ ;fightFlag=0;
                    if(PlayerItems[4]<maxHP) PlayerItems[4]++;
                    break;
                }
                if(Ghp&&(DisPlayMap[markx][marky]%2==0))
                {
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[(DisPlayMap[markx][marky]%100)].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=(guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]);
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                    if(PlayerItems[10]>maxHP) PlayerItems[10]=maxHP;

                }
                else{
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                }
            }
            else{
                if(!ZiDong)
                {
                    cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"Ѫ��������:"<<PlayerItems[6]<<endl<<endl;
                }
                Ghp-=PlayerItems[6];
                if(Ghp<=0)
                {
                    ///Ghp=0;
                    cout<<endl<<"���ʤ�ˣ�������ϲ������"<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    char xsheng;
                    cin>>xsheng;
                    guaiwu[DisPlayMap[markx][marky]%100].HitData++ ;
                    fightFlag=0;
                    if(PlayerItems[4]<maxHP) PlayerItems[4]++;
                    break;
                }
                if(DisPlayMap[markx][marky]%2==0)
                {
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7];
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                    if(PlayerItems[10]>maxHP)
                        PlayerItems[10]=maxHP;

                }
                else
                {
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                }
            }
        }
        else{
            if(!ZiDong)
            {
                cout<<"��ѡ����Ĺ����� 1.�������� 2.����������"<<endl<<endl;
                cin>>xx;
                while(xx!='1'&&xx!='2')
                {
                    cin>>xx;
                }
                if(xx=='1')
                    x=1;
                if(xx=='2')
                    x=2;
            }
            if(ZiDong==1) x=1;
            if(ZiDong==2) x=2;
            if(x==1)
            {
                if(Ghp&&(DisPlayMap[markx][marky]%2==0))
                {
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=(guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]);
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                    if(PlayerItems[10]>maxHP) PlayerItems[10]=maxHP;

                }
                else{
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                }
                if(!ZiDong)
                {
                    cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"Ѫ��������:"<<PlayerItems[5]-guaiwu[DisPlayMap[markx][marky]%100].Fangyu<<endl<<endl;
                }
                Ghp-=(PlayerItems[5]-guaiwu[DisPlayMap[markx][marky]%100].Fangyu);
                if(Ghp<=0)
                {
                    cout<<endl<<"���ʤ�ˣ�������ϲ������"<<endl<<endl;
                    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                    char xsheng;
                    cin>>xsheng;
                    guaiwu[DisPlayMap[markx][marky]%100].HitData++ ;
                    fightFlag=0;
                    if(PlayerItems[4]<maxHP) PlayerItems[4]++;
                    break;
                }
            }
            else{
                if(DisPlayMap[markx][marky]%2==0)
                {
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=(guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]);
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                    if(PlayerItems[10]>maxHP)
                        PlayerItems[10]=maxHP;

                }
                else
                {
                    if(!ZiDong)
                    {
                        cout<<"���㡿"<<"Ѫ��������:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"��ʧ�����ˣ��������ͣ�����"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        fightFlag=0;
                        if(PlayerItems[4]>0) PlayerItems[4]--;
                        PlayerItems[10]=1;
                        ///markLevel=0;
                        ///InitMap();
                        break;
                    }
                }
                if(PlayerItems[10])
                {
                    if(!ZiDong)
                    {
                        cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"Ѫ��������:"<<PlayerItems[6]<<endl<<endl;
                    }
                    Ghp-=PlayerItems[6];
                    if(Ghp<=0)
                    {
                        cout<<endl<<"���ʤ�ˣ�������ϲ������"<<endl<<endl;
                        cout<<"��������������ȷ�ϣ�"<<endl<<endl;
                        char xsheng;
                        cin>>xsheng;
                        guaiwu[DisPlayMap[markx][marky]%100].HitData++ ;
                        fightFlag=0;
                        if(PlayerItems[4]<maxHP) PlayerItems[4]++;
                        break;
                    }
                }
            }
        }
    }
}
void LoadXuexiao(int i)
{
    if(PlayerItems[4]>100&&Tips[1]==0) Tips[1]=1;
    if(PlayerItems[10]==2) MyMap[26*10+13]=2021;
    if(ChengZhangRenWu[2]==1)
    {
        if(IsMeet==0)
        {
            ChengZhangRenWu[2]=2;
            PlayerItems[3]++;
            To=-1;
            cout<<"����Ϸ����Ա�� "<<endl<<endl;
            cout<<"���Ѿ�����˳���ѧУ�ĳ�����������ֵ�õ��������� "<<endl<<endl;
            cout<<"������ֵ +1�� "<<endl<<endl;
            cout<<"��������������ȷ�ϣ�"<<endl<<endl;
            cin>>inputC;
        }
    }
    markLevel=i;
    markx=4;
    marky=0;
    InitMap();
    ///system("cls");
    ///PrintMap();
}
void LoadWuguan(int i)
{
    if(ChengZhangRenWu[3]==1)
    {
        if(guaiwu[6].HitData-currentguaiwudata.number>=10)
        {
            currentguaiwudata.number=-1;
            PlayerItems[2]++;
            To=-1;
            ChengZhangRenWu[3]=2;
            cout<<"����Ϸ����Ա�� "<<endl<<endl;
            cout<<"���Ѿ�����˳�����ݵĳ�����������ֵ�õ��������� "<<endl<<endl;
            cout<<"������ֵ +1�� "<<endl<<endl;
            cout<<"��������������ȷ�ϣ�"<<endl<<endl;
            cin>>inputC;
        }
    }
    markLevel=i;
    markx=4;
    marky=0;
    InitMap();
    ///system("cls");
    ///PrintMap();
}
void LoadCaiDan()
{
    system("cls");
    cout<<endl;
    cout<<"��δ����"<<endl<<endl;
    cout<<"��������������ȷ�ϣ�"<<endl<<endl;
    cin>>inputC;
}
int color(int c) 	//SetConsoleTextAttribute��API���ÿ���̨����������ɫ�ͱ���ɫ�ĺ���
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
    return 0;
}
void ChangeDark()
{
    if(IsOnDongxue)
    {
        for(int i=0;i<6;++i)
        {
            for(int j=0;j<6;++j)
            {
                IsDark[i][j]=1;
            }
        }
    }
    if(PlayerItems[66])
    {
        if(marky-1>=0&&marky-1<5)
            IsDark[markx][marky-1]=0;
        if(marky+1>=0&&marky+1<5)
            IsDark[markx][marky+1]=0;
        if(markx-1>=0&&markx-1<5)
        {
            IsDark[markx-1][marky]=0;
            if(marky-1>=0&&marky-1<5) IsDark[markx-1][marky-1]=0;
            if(marky+1>=0&&marky+1<5) IsDark[markx-1][marky+1]=0;
        }
        if(markx+1>=0&&markx+1<5)
        {
            IsDark[markx+1][marky]=0;
            if(marky-1>=0&&marky-1<5) IsDark[markx+1][marky-1]=0;
            if(marky+1>=0&&marky+1<5) IsDark[markx+1][marky+1]=0;
        }
    }
}
void ChangeLevel(int x)
{
    if(PlayerItems[1]>0&&waterFlag==1&&type0!=7)
    {
        PlayerItems[1]--;
        waterFlag=0;
    }
    if(x==0) markLevel=up1;
    if(x==1) markLevel=down1;
    if(x==2) markLevel=left1;
    if(x==3) markLevel=right1;
    markx=nextMapX;
    marky=nextMapY;
    DisPlayMap[markx][marky]=MyMap[26*markLevel+5*markx+marky+1];
    GetYidianData();

    if(type0==9)
    {
        MyMap[26*markLevel+5*markx+marky+1]=0;
        DisPlayMap[markx][marky]=0;
    }
    InitMap();
}
void GetYidianData()
{
    ///DisPlayMap[markx][marky]=MyMap[26*markLevel+5*markx+marky+1];
    match0=DisPlayMap[markx][marky]%100;
    type0=(DisPlayMap[markx][marky]/100)%100;
    right0=(DisPlayMap[markx][marky]/10000)%100;
    left0=(DisPlayMap[markx][marky]/1000000)%100;
    down0=(DisPlayMap[markx][marky]/100000000)%100;
    up0=(DisPlayMap[markx][marky]/10000000000)%100;
    match1=(int)match0;
    type1=(int)type0;
    right1=(int)right0;
    left1=(int)left0;
    down1=(int)down0;
    up1=(int)up0;
}
int main()
{
    ///*********���²�������ɾ��

    ///*********���ϲ�������ɾ��

    if(IsOnDongxue) ChangeDark();
    if(IsOnYidian) GetYidianData();
    Init();
	InitMap();
	DisOld=0;
	DisPlayMap[markx][marky]=100;
	PrintMap();
	while(1)
    {
        if(PlayerItems[4]>150)
        {
            Tips[0]=1;
        }
        PlayerMove();
        if(wuqi[PlayerItems[Mywuqi]].Nai==0)
        {
            cout<<"��װ�������������ˣ��뼰ʱ������ "<<endl<<endl;
            ChangeMyData(-1);
            PlayerItems[Mywuqi]=-1;
            Mywuqi=-1;
            cout<<"���������һ������ȷ�� "<<endl<<endl;
            cin>>inputC;
        }
        if(yifu[PlayerItems[Myyifu]].Nai==0)
        {
            cout<<"��װ�����·������ˣ��뼰ʱ������ "<<endl<<endl;
            ChangeMyData(-2);
            PlayerItems[Myyifu]=-1;
            Myyifu=-1;
            cout<<"���������һ������ȷ�� "<<endl<<endl;
            cin>>inputC;
        }
        if(gameFlag) break;
    }
    if(gameFlag==1)
    {
        cout<<"��ʤ���˱��ҳ��£������� "<<endl<<endl;
        cout<<"������������������������ "<<endl<<endl;
        cout<<"���������һ������ȷ�� "<<endl<<endl;
        cin>>inputC;
    }

    system("pause");
	return 0;
}