#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
using namespace std;

#define Xcnt 10 ///神秘人个数
#define LevelCnt 9  ///关卡数
#define ToTalLevelCnt 100  ///真正关卡数
#define PI 100  ///游戏中供人物使用的道具数量
#define Rw 100  ///玩家总的任务数
#define WuQiCnt 100  ///武器种类  双数为格斗家装备，单数为魔法师装备
#define YiFuCnt  100   ///衣服种类  双数为格斗家装备，单数为魔法师装备
#define XieZiCnt 100   ///鞋子种类
#define GuaiWCnt  10  ///怪物种类
#define NaiJiu 100   ///装备耐久度

/// <summary>
/// 以下为所有全局变量

///异点数据
long long int up0,down0,left0,right0,type0,match0;
int up1,down1,left1,right1,type1,match1;
///前往地图的坐标
int nextMapX,nextMapY;
///判断在哪里生成剧情石头，河
int he701[30]={12,13,22,23,301,310,311,321,330,331,212,221,223,232,511,521,531,532,533,722,912,913,922,923};///24
int shi901[20]={302,313,343,701,710,711,733,734,743,900,910,920,930};///13
///判断是否击杀了魔王
int bossFlag=0;
///判断游戏是否结束
int gameFlag=0;
///是否遇到怪
int IsMeet=0;
///判断是否在洞穴
int IsOnDongxue=0;
///判断是否在绳子上
int IsOnShengzi=0;
///判断是否在异点上
int IsOnYidian=0;
///判断是否处在黑暗
int IsDark[22][22]={0};
///目前在的学习组织
struct MySchool{
    int xuexiaoLevel=0;
    int wuguanLevel=0;
    int ID=0; ///类型 1学校 2武馆
    int firrenwu=0;
    int secrenwu=0;
    int thirdrenwu=0;
}myschool;
///阵法传送的目的地
int To=-1;
///成长任务
int ChengZhangRenWu[Rw+5]={0};
///当接受到击杀怪物的任务时调用
struct CurrentGuaiWuData{
    int number=-1;///怪物数量
    int Id;      ///怪物种类
}currentguaiwudata;
int CurrentGuaiWuData=0;
///确认事件时输入，无实际含义
char inputC;
///最大血量
int maxHP=50;
///当前地图中怪物数量
int GuaiNow1=0;
int GuaiNow2=0;
///已装备的装备
int Mywuqi=-1;
int Myyifu=-1;
int Myxiezi=-1;
///玩家任务
int RenWu[Rw+5]={0};  ///0为未接取  1为接取  2为已完成
///保存旧时数据
long long int DisOld; ///关卡中物体
int markxOld; ///关卡游戏玩家位置
int markyOld;
///判断是否处于河中
int waterFlag = 0;  ///为1 时处于河中
///判断是否处于野外
int wildFlag = 0;   ///为1 时处于野外
///判断是否进行自动战斗
int ZiDong = 0;
///判断是否处于战斗
int fightFlag = 0;
///人物道具
int PlayerItems[PI+5]={0};  ///11-20为拥有的武器；21-30为拥有的装备；31-40为拥有的鞋子  50百妖谱 66土灵珠 99仙器
///人物装备
    ///武器
    struct WuQi{
        string s="test";
        int Zhi;///需要的武力值或智力值
        int Hit;///伤害值
        int Nai=NaiJiu;///耐久
    }wuqi[WuQiCnt+5];
    ///装备
    struct YiFu{
        string s="test";
        int Zhi;///需要的武力值或智力值
        int FangYu;///防御值  当为魔法师的斗篷时，此项为增加的速度值
        int Nai=NaiJiu;///耐久
    }yifu[YiFuCnt+5];
    struct XieZi{
        string s="test";
        int Speed; ///速度
    }xiezi[XieZiCnt+5];
///野外怪物
struct GuaiWu{  ///双数是物理攻击野怪；单数是法术攻击野怪
    string s="test";
    int Hp;
    int Hit;
    int Speed;
    int Fangyu;
    int HitData=0; ///击杀数量

}guaiwu[GuaiWCnt+5];
///关卡属性
struct Guanqia{
    string s="test";
    int wild; ///是否为野外
    int level; ///怪物属性
}guanqia[ToTalLevelCnt+5];
///怪物位置  储存怪物位置  下标用来存位置，数值存怪物种类（地图中的数值）；
int guaiwuLocx[25];
int guaiwuLocy[25];
///关卡   下标模26=0时为所在地图
long long int MyMap[(26*ToTalLevelCnt)+5]={
    0,900,500,0/*测试完毕请改为0*/,0,0/*此处为传送点*/,900,0,700,700,0,900,0,700,700,0,900,400,0,0,300,0,600,600,600,200,
    1,0,0,0,1200,801/*此处为传送点*/,1200,1200,0,1200,1200,0,1200,1200,0,0,0,0,1200,1200,0,0,0,0,1200,0,
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
///关卡中物体
int Items;   ///四位数，前两位表示类别，后两位表示具体；
/*
  1我    500-599都可以  表示同一个意思
  2人    百位是2，其他位数不同表示不同的人，触发不同的对话
  3客
  4武
  5装
  6草
  7河
  8传    后两位表示最大可以传送到的关卡
  9石
  10野
  11神
  12敌  在地图中隐性显示，不输出；
  13学
  14馆
  15魔   ///最终BOSS
  16左
  17主
  18右
  19阵
  20彩
  21绳    ///2100表示绳子尽头，2101表示在绳子上，下一步只能移动到绳子上
  22蛛   ///洞穴内蜘蛛怪
  23骨
  24洞

  十二位数 异  ///穿越地图  前八位（上下左右）表示穿越到的地图；中间两位表示物体；后两位表示对应异点
*/
///展示地图
long long int DisPlayMap[5][5];
///判断是否显示神秘人   按需要添加
int Tips[Xcnt] = { 0 };
///标识玩家位置
int markx=4;       ///x坐标位置
int marky=0;       ///y坐标位置
int markLevel=0;  ///处于第几个地图
/// </summary>


/// <summary>
/// 以下为所有函数
void InitMap(); ///在此输入地图  第45行
void PrintMap(); ///打印地图      第62行
void PlayerMove(); ///玩家走动
bool MoveOrNot(); /// 判断是否能够行进
void Init(); ///初始化游戏中物品，道具等
void ChangeMyData(int i);///改变自己的属性，更换装备时调用 -1表示卸下武器 -2表示卸下衣服 -3表示卸下鞋子 >=0表示穿上相应装备
void LoadFight();   ///加载战斗场景
void LoadXuexiao(int i); ///加载学校内地图
void LoadWuguan(int i);  ///加载武馆内地图
void LoadCaiDan(); ///加载彩蛋
int color(int c);///改变颜色
void ChangeDark();///更新黑暗
void ChangeLevel(int x);///改变地图
void GetYidianData();///获得异点数据
/// </summary>

void InitMap()  ///转化关卡时需要更新地图数据
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
    cout<<"输入R键打开任务栏"<<endl<<endl;
    cout<<"输入Q键打开地图"<<endl<<endl;
    cout<<"输入E键打开属性道具栏"<<endl<<endl;
    cout<<"输入T键打开装备栏"<<endl<<endl;
    cout<<"输入Z键打开战斗方式"<<endl<<endl;
    cout<<"************************************************************************************************"<<endl;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
            if (DisPlayMap[i][j] / 100 == 0||((DisPlayMap[i][j]/100)%100)==0)
            {
                ///cout << "口";
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else
                {
                    cout<<"口";
                }
            }
            if (DisPlayMap[i][j] / 100 == 1)
            {
                cout << "我";
            }
			if (DisPlayMap[i][j] / 100 == 2) cout << "人";
			if (DisPlayMap[i][j] / 100 == 3) cout << "客";
			if (DisPlayMap[i][j] / 100 == 4) cout << "武";
			if (DisPlayMap[i][j] / 100 == 5) cout << "装";
			if (DisPlayMap[i][j] / 100 == 6||((DisPlayMap[i][j]/100)%100)==6)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout << "草";
            }
            if (DisPlayMap[i][j] / 100 == 7||((DisPlayMap[i][j]/100)%100)==7)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);;
                }
                else cout << "河";
            }
            if (DisPlayMap[i][j] / 100 == 8)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout << "传";
            }
			if (DisPlayMap[i][j] / 100 == 9||((DisPlayMap[i][j]/100)%100)==9)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout << "石";
            }
			if (DisPlayMap[i][j] / 100 == 10) cout << "野";
			if (DisPlayMap[i][j] / 100 == 11)
			{
				int flag = 0;      //判断是否输出神秘人位置
				for (int i = 0; i < Xcnt; ++i)
				{
					if (Tips[i] == 1)
					{
						///cout << "神";
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
                    cout << "神";
                }
			}
            if (DisPlayMap[i][j] / 100 == 12)
            {
                cout<<"口";
            }
			if(DisPlayMap[i][j]/100==13) cout<<"学";
			if(DisPlayMap[i][j]/100==14) cout<<"馆";
			if(DisPlayMap[i][j]/100==15) cout<<"魔";
			if(DisPlayMap[i][j]/100==16) cout<<"左";
			if(DisPlayMap[i][j]/100==17) cout<<"主";
			if(DisPlayMap[i][j]/100==18) cout<<"右";
            if(DisPlayMap[i][j]/100==19)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);;
                }
                else cout<<"阵";
            }
			if(DisPlayMap[i][j]/100==20) cout<<"彩";
            if(DisPlayMap[i][j]/100==21||((DisPlayMap[i][j]/100)%100)==21)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout<<"绳";
            }
            if(DisPlayMap[i][j]/100==22)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout<<"蛛";
            }
            if(DisPlayMap[i][j]/100==23)
            {
                if(IsDark[i][j]==1&&IsOnDongxue==1)
                {
                    color(21);
                    cout<<"  ";
                    color(7);
                }
                else cout<<"骨";
            }
            if(DisPlayMap[i][j]/100==24) cout<<"洞";

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
    cout<<endl<<"请输入“w a  s d”"<<endl;
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
        cout<<"目前战斗状态：";
        if(ZiDong==0) cout<<"【非自动战斗】 "<<endl<<endl;
        if(ZiDong==1) cout<<"【物理攻击自动战斗】 "<<endl<<endl;
        if(ZiDong==2) cout<<"【法术攻击自动战斗】 "<<endl<<endl;
        cout<<"【切换战斗状态】 "<<endl<<endl;
        cout<<"0. 【取消自动战斗】"<<endl<<endl;
        cout<<"1. 【使用物理攻击进行自动战斗】 "<<endl<<endl;
        cout<<"2. 【使用法术攻击进行自动战斗】 "<<endl<<endl;
        cout<<"请输入对应数字： "<<endl<<endl;
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
        cout<<"【角色血量】"<<PlayerItems[10]<<endl<<endl;
        cout<<"【角色物攻值】"<<PlayerItems[5]<<endl<<endl;
        cout<<"【角色法攻值】"<<PlayerItems[6]<<endl<<endl;
        cout<<"【角色防御值】"<<PlayerItems[7]<<endl<<endl;
        cout<<"【角色速度】"<<PlayerItems[8]<<endl<<endl;
        cout<<"【角色智力值】"<<PlayerItems[3]<<endl<<endl;
        cout<<"【角色武力值】"<<PlayerItems[2]<<endl<<endl;
        cout<<"【角色Tip值】"<<PlayerItems[4]<<endl<<endl;
        cout<<"【锤子数量】"<<PlayerItems[0]<<endl<<endl;
        cout<<"【木筏数量】"<<PlayerItems[1]<<endl<<endl;
        cout<<"【金钱数】"<<PlayerItems[9]<<endl<<endl;
        cout<<"随便输入一个数字退出："<<endl<<endl;
        char c;
        cin>>c;
        system("cls");
        PrintMap();
    }
    else if(c=='T'||c=='t')
    {
        system("cls");
        cout<<endl;
        cout<<"【武器】"<<endl;
        if(Mywuqi>=0)
        {
            cout<<wuqi[PlayerItems[Mywuqi]].s;
            if(PlayerItems[Mywuqi]%2==0)
            {
                cout<<"【物攻："<<wuqi[PlayerItems[Mywuqi]].Hit<<"】";
                cout<<"【耐久："<<wuqi[PlayerItems[Mywuqi]].Nai<<"】";
            }
            else{
                cout<<"【法攻："<<wuqi[PlayerItems[Mywuqi]].Hit<<"】";
                cout<<"【耐久："<<wuqi[PlayerItems[Mywuqi]].Nai<<"】";
            }
            cout<<"【1.更换】"<<endl<<endl;
            ///cout<<endl<<endl;
        }
        else {
            cout<<"【无】"<<"【1.更换】"<<endl<<endl;
        }
        cout<<"【服装】"<<endl;
        if(Myyifu>=0)
        {
            cout<<yifu[PlayerItems[Myyifu]].s;
            if(PlayerItems[Myyifu]%2==0)
            {
                cout<<"【防御："<<yifu[PlayerItems[Myyifu]].FangYu<<"】";
                cout<<"【耐久："<<yifu[PlayerItems[Myyifu]].Nai<<"】";
            }
            else{
                cout<<"【速度："<<yifu[PlayerItems[Myyifu]].FangYu<<"】";
                cout<<"【耐久："<<yifu[PlayerItems[Myyifu]].Nai<<"】";
            }
            cout<<"【2.更换】"<<endl<<endl;
            ///cout<<endl<<endl;
        }
        else {
            cout<<"【无】"<<"【2.更换】"<<endl<<endl;
        }
        cout<<"【鞋子】"<<endl;
        if(Myxiezi>=0)
        {
            cout<<xiezi[PlayerItems[Myxiezi]].s;
            cout<<"【速度："<<xiezi[PlayerItems[Myxiezi]].Speed<<"】";
            cout<<"【3.更换】"<<endl<<endl;
            ///cout<<endl<<endl;
        }
        else {
            cout<<"【无】"<<"【3.更换】"<<endl<<endl;
        }

        cout<<"需要更换装备请输入对应数字，输入数字【 4 】退出："<<endl<<endl;
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
                        cout<<"【物攻："<<wuqi[PlayerItems[i]].Hit<<"】";
                        cout<<"【耐久："<<wuqi[PlayerItems[i]].Nai<<"】";
                    }
                    else
                    {
                        cout<<"【法攻："<<wuqi[PlayerItems[i]].Hit<<"】";
                        cout<<"【耐久："<<wuqi[PlayerItems[i]].Nai<<"】";
                    }
                    cout<<endl<<endl;
                }
            }
            cout<<"请输入想换装备前对应数字：（请务必输入数字，避免引起不必要的BUG，输入除上述数字外的任何数字退出）"<<endl<<endl;
            int huanwuqi;
            cin>>inputC;
            huanwuqi=(inputC-'0')+11;
            if(huanwuqi>10&&huanwuqi<21)
            {
                if(PlayerItems[huanwuqi]>-1)
                {
                    ChangeMyData(-1);
                    ///算了，不做装备上武器服装以后在物品栏消失的功能了
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
                        cout<<"【防御："<<yifu[PlayerItems[i]].FangYu<<"】";
                        cout<<"【耐久："<<yifu[PlayerItems[i]].Nai<<"】";
                    }
                    else
                    {
                        cout<<"【速度："<<yifu[PlayerItems[i]].FangYu<<"】";
                        cout<<"【耐久："<<yifu[PlayerItems[i]].Nai<<"】";
                    }
                    cout<<endl<<endl;
                }
            }
            cout<<"请输入想换装备前对应数字：（请务必输入数字，避免引起不必要的BUG，输入除上述数字外的任何数字退出）"<<endl<<endl;
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
                    cout<<"【速度："<<xiezi[PlayerItems[i]].Speed<<"】";
                    cout<<endl<<endl;
                }
            }
            cout<<"请输入想换装备前对应数字：（请务必输入数字，避免引起不必要的BUG，输入除上述数字外的任何数字退出）"<<endl<<endl;
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
                cout<<"肖杨制作！"<<endl;
            }
        }
        system("cls");
        PrintMap();
    }
    else if(c=='R'||c=='r')
    {
        system("cls");
        cout<<endl;
        cout<<"【1.剧情任务】【2.成长任务】【3.退出】"<<endl<<endl;
        cout<<"请选择对应数字： "<<endl<<endl;
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
                    ///当有新任务时在下面添加相应任务描述********************重要********************************

                    if(i==0)
                        cout<<"【将新手村的石头全部砸碎，注意不要被河困死哦！！！困死就得重新进行游戏了】"<<endl<<endl;
                    if(i==1)
                        cout<<"【找新手村的武器店老板谈话，注意不要被河困死哦！！！困死就得重新进行游戏了】"<<endl<<endl;
                    if(i==2)
                        cout<<"【找新手村的服装店老板谈话，注意不要被河困死哦！！！困死就得重新进行游戏了】"<<endl<<endl;
                    if(i==3)
                    {
                        cout<<"【去镇关西帮新手村客栈老板打 10 只野鸡！】"<<endl<<endl<<"你目前击杀了：";
                        if(guaiwu[0].HitData-currentguaiwudata.number>10)
                            cout<<"10"<<endl<<endl;
                        else
                            cout<<guaiwu[0].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==4)
                        cout<<"【在十里坡的草下面转转！说不定会有意外收获！】"<<endl<<endl;
                    if(i==5)
                        cout<<"【帮李逍遥在石头里面找找土灵珠】"<<endl<<endl;
                    if(i==6)
                    {
                        cout<<"【去紫竹林帮带数学家捉 4 只竹妖！】"<<endl<<endl<<"你目前捉到了：";
                        if(guaiwu[2].HitData-currentguaiwudata.number>4)
                            cout<<"4"<<endl<<endl;
                        else
                            cout<<guaiwu[2].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==7)
                        cout<<"【帮桃夭找到无名这种妖怪】"<<endl<<endl;
                    if(i==8)
                    {
                        cout<<"【去接天崖帮带英语家捉 4 只莫桑花！】"<<endl<<endl<<"你目前捉到了：";
                        if(guaiwu[3].HitData-currentguaiwudata.number>4)
                            cout<<"4"<<endl<<endl;
                        else
                            cout<<guaiwu[3].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==9)
                        cout<<"【帮刘半仙儿在河里找找找她的仙器】"<<endl<<endl;

                    ///当有新任务时在上面添加相应任务描述********************重要********************************
                }
            }
            cout<<"随便输入一个数字退出："<<endl<<endl;
            char c;
            cin>>c;
        }
        if(inputC=='2')
        {
            for(int i=0; i<Rw; ++i)
            {
                if(ChengZhangRenWu[i]==1)
                {
                    ///当有新任务时在下面添加相应任务描述********************重要(待更改）********************************

                    if(i==0)
                    {
                        if(IsMeet==0)
                        {
                            cout<<"【去学馆区转一圈，小心不要被那里的玩偶逮到！！！】"<<endl<<endl;
                        }
                        else cout<<"【你已经被逮到了，去初级学校找道场引路人，重新领取任务吧！】"<<endl<<endl;
                    }
                    if(i==1)
                    {
                        cout<<"【去学馆区击败 10 个玩偶！】"<<endl<<endl<<"你目前击败了：";
                        if(guaiwu[1].HitData-currentguaiwudata.number>10)
                            cout<<"10"<<endl<<endl;
                        else
                            cout<<guaiwu[1].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==2)
                    {
                        if(IsMeet==0)
                            cout<<"【去埋酒地转一圈，小心不要被那里的离愁逮到！！！】"<<endl<<endl;
                        else cout<<"【你已经被逮到了，去初级学校找左护法，重新领取任务吧！】"<<endl<<endl;
                    }

                    if(i==3)
                    {
                        cout<<"【去四方地打败 10 只方方怪！】"<<endl<<endl<<"你目前击败了：";
                        if(guaiwu[6].HitData-currentguaiwudata.number>10)
                            cout<<"10"<<endl<<endl;
                        else
                            cout<<guaiwu[6].HitData-currentguaiwudata.number<<endl<<endl;
                    }
                    if(i==4)
                        cout<<"【在十里坡的草下面转转！说不定会有意外收获！】"<<endl<<endl;

                    ///当有新任务时在上面添加相应任务描述********************重要********************************
                }
            }
            cout<<"随便输入一个数字退出："<<endl<<endl;
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
        ///当有新地图时请在下面添加***********************************重要****************************************

        if(markLevel==0)
        {
            cout<<"你当前所在的地方是：【新手村】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【武器店】    王老板 "<<endl<<endl;
            cout<<"【服装店】    卜老板"<<endl<<endl;
            cout<<"【客  栈】    孙老板"<<endl<<endl;
            cout<<"【肖  杨】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【镇关西】    野外 "<<endl<<endl;
        }
        if(markLevel==1)
        {
            cout<<"你当前所在的地方是：【镇关西】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【野鸡】    野外生物"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==2)
        {
            cout<<"你当前所在的地方是：【十里坡】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【杨  平】    NPC"<<endl<<endl;
            cout<<"【相酒红】    NPC"<<endl<<endl;
            cout<<"【杨文豪】    NPC"<<endl<<endl;
            cout<<"【小  六】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==3)
        {
            cout<<"你当前所在的地方是：【道场】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【初级学校】    成长"<<endl<<endl;
            cout<<"【中级学校】    成长"<<endl<<endl;
            cout<<"【高级学校】    成长"<<endl<<endl;
            cout<<"【初级武馆】    成长"<<endl<<endl;
            cout<<"【中级武馆】    成长"<<endl<<endl;
            cout<<"【高级武馆】    成长"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==4)
        {
            cout<<"你当前所在的地方是：【学馆区】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【玩偶】    野外生物"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==5)
        {
            cout<<"你当前所在的地方是：【桃源】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【武器店】    秦老板 "<<endl<<endl;
            cout<<"【服装店】    温老板"<<endl<<endl;
            cout<<"【客  栈】    宋老板"<<endl<<endl;
            cout<<"【李逍遥】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【紫竹林】    野外 "<<endl<<endl;
        }
        if(markLevel==6)
        {
            cout<<"你当前所在的地方是：【紫竹林】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【竹妖】    野外生物"<<endl<<endl;
            cout<<"【带数学家】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==7)
        {
            cout<<"你当前所在的地方是：【诡镇】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【武器店】    张老板 "<<endl<<endl;
            cout<<"【服装店】    悦老板"<<endl<<endl;
            cout<<"【客  栈】    郭老板"<<endl<<endl;
            cout<<"【桃  夭】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【接天崖】    野外 "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==8)
        {
            cout<<"你当前所在的地方是：【接天崖】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【莫桑花】    野外生物"<<endl<<endl;
            cout<<"【带英语家】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==9)
        {
            cout<<"你当前所在的地方是：【魔都】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【武器店】    相老板 "<<endl<<endl;
            cout<<"【服装店】    牛老板"<<endl<<endl;
            cout<<"【客  栈】    陈老板"<<endl<<endl;
            cout<<"【刘半仙儿】    NPC"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"无通向的地方"<<endl<<endl;
        }
        if(markLevel==10)
        {
            cout<<"你当前所在的地方是：【初级学校】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【初级学校左护法】    接取初级任务 "<<endl<<endl;
            cout<<"【初级学校主席】    接取高级任务"<<endl<<endl;
            cout<<"【初级学校右护法】    接取中极任务"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【阵法】"<<endl<<endl;
        }
        if(markLevel==11)
        {
            cout<<"你当前所在的地方是：【中级学校】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【中级学校左护法】    接取初级任务 "<<endl<<endl;
            cout<<"【中级学校主席】    接取高级任务"<<endl<<endl;
            cout<<"【中级学校右护法】    接取中极任务"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【阵法】"<<endl<<endl;
        }
        if(markLevel==12)
        {
            cout<<"你当前所在的地方是：【高级学校】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【高级学校左护法】    接取初级任务 "<<endl<<endl;
            cout<<"【高级学校主席】    接取高级任务"<<endl<<endl;
            cout<<"【高级学校右护法】    接取中极任务"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【阵法】"<<endl<<endl;
        }
        if(markLevel==13)
        {
            cout<<"你当前所在的地方是：【初级武馆】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【初级武馆左护法】    接取初级任务 "<<endl<<endl;
            cout<<"【初级武馆主席】    接取高级任务"<<endl<<endl;
            cout<<"【初级武馆右护法】    接取中极任务"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【阵法】"<<endl<<endl;
        }
        if(markLevel==14)
        {
            cout<<"你当前所在的地方是：【中级武馆】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【中级武馆左护法】    接取初级任务 "<<endl<<endl;
            cout<<"【中级武馆主席】    接取高级任务"<<endl<<endl;
            cout<<"【中级武馆右护法】    接取中极任务"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【阵法】"<<endl<<endl;
        }
        if(markLevel==15)
        {
            cout<<"你当前所在的地方是：【高级武馆】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【高级武馆左护法】    接取初级任务 "<<endl<<endl;
            cout<<"【高级武馆主席】    接取高级任务"<<endl<<endl;
            cout<<"【高级武馆右护法】    接取中极任务"<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【阵法】"<<endl<<endl;
        }
        if(markLevel==16)
        {
            cout<<"你当前所在的地方是：【埋酒地】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【离愁】    野外怪物 "<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel==17)
        {
            cout<<"你当前所在的地方是：【四方地】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【方方怪】    野外怪物 "<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【传送点】"<<endl<<endl;
        }
        if(markLevel>=18&&markLevel<=66)
        {
            cout<<"你当前所在的地方是：【洞穴："<<markLevel<<"】 "<<endl<<endl;
            cout<<"这里有： "<<endl<<endl;
            cout<<"【未知】 "<<endl<<endl;
            cout<<"这里通向： "<<endl<<endl;
            cout<<"【未知】"<<endl<<endl;
        }

        ///当有新地图时请在上面添加***********************************重要****************************************
        cout<<"随便输入一个数字退出："<<endl<<endl;
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
        if(markx<0) ///往上走
        {
            for(int i=1; i<=25; ++i) ///找到要前往地图相匹配的异点类型
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
        else if(markx>4) ///往下走
        {
            for(int i=1; i<=25; ++i) ///找到要前往地图相匹配的异点类型
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
        else if(marky>4) ///往右走
        {
            for(int i=1; i<=25; ++i) ///找到要前往地图相匹配的异点类型
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
        else  ///往左走
        {
            for(int i=1; i<=25; ++i) ///找到要前往地图相匹配的异点类型
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
    ///遇到空地
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
    ///遇到异点
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
    ///遇到自己，显然不可能
    else if(DisPlayMap[markx][marky]/100==1)
    {
        cout<<"制作者：肖杨";
        return false;
    }
    ///遇到NPC
    else if(DisPlayMap[markx][marky]/100==2)
    {
        if(IsOnShengzi) return false;
        ///下面写0号NPC的对话
        if(DisPlayMap[markx][marky]%100==0)
        {
            system("cls");
            cout<<endl;
            while (1)
            {
                cout<<"【肖杨】"<<endl<<endl;
                cout<<"欢迎来到新手村，亲爱的玩家，我叫肖杨"<<endl<<endl;
                cout<<"我是你在这个游戏中的引路人"<<endl<<endl;
                cout<<"你是不是无法前进呢？我这里有现成的木筏可以提供给你"<<endl<<endl;
                cout<<"有了木筏就可以过河了哦"<<endl<<endl;
                cout<<"木筏是一次性的，过完河就会消失，如果你没有木筏的话可以随时来找我，不论你来多少次我都会给你提供免费的木筏"<<endl<<endl;
                ///cout<<"请去武器店和装备店看看吧，也许老板好心会给你提供趁手的兵器和装备呢！"<<endl<<endl;
                cout<<"那我现在把木筏给你，去这个世界的更深处去探险吧！！！"<<endl<<endl;
                cout<<"我会永远在这等你归来哦，想我了就来看看我吧！！！"<<endl<<endl;
                if(RenWu[0]==0)
                {
                    RenWu[0]=1;
                    cout<<"【任务接取】"<<endl<<endl;
                    cout<<"【对了,防止你被石头和河卡死，我再给你一些锤子吧，锤子可以击碎石头哦！"<<endl<<endl;
                    PlayerItems[0]=4;
                    cout<<"请把新手村的石头全部砸完以后再来找我吧，到时候我会指引你如何探索这个神奇的世界 】"<<endl<<endl;
                    cout<<"你获得了4把锤子！！！  "<<endl<<endl;
                }
                if(RenWu[0]==1&&DisPlayMap[0][0]==0&&DisPlayMap[1][0]==0&&DisPlayMap[2][0]==0&&DisPlayMap[3][0]==0)
                {
                    RenWu[0]=2;
                    cout<<"恭喜你完成了在新手村的第一个测验！ "<<endl<<endl;
                    RenWu[1]=1;
                    cout<<"【任务接取】"<<endl<<endl;
                    cout<<"【武器店老板叫姓王，住我隔壁，是我多年的好朋友，你拿着我的介绍信去找他，他会给你一把趁手的兵器 】"<<endl<<endl;
                    cout<<endl<<"你获得了肖杨的介绍信！ "<<endl<<endl;
                }
                cout<<"请随便输入一个数字确认："<<endl<<endl;
                char x;
                cin>>x;
                if(PlayerItems[1]==0) PlayerItems[1]++;
                break;
            }
        }
        ///下面写遇到1号NPC的对话
        if(DisPlayMap[markx][marky]%100==1)
        {
            system("cls");
            cout<<endl;
            cout<<"【杨平】"<<endl<<endl;
            if(PlayerItems[4]%2==0)
            {
                cout<<"你看到地图中间那个石头了吗？ "<<endl<<endl;
                cout<<"据说里面封印这一个非常强大的恶魔！！！"<<endl<<endl;
                cout<<"要小心不要打破它啊！！！  "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
            }
            else{
                cout<<"你知道“草”吗？ "<<endl<<endl;
                cout<<"它是一种植物，最早可以追溯到。。。。 "<<endl<<endl;
                cout<<"咳咳咳！有点扯远了！ "<<endl<<endl;
                cout<<"说说游戏里的草吧，它可不仅仅是一种装饰哦！ "<<endl<<endl;
                cout<<"有些草下面是有宝贝的！十里坡的草下面就有宝贝！ "<<endl<<endl;
                cout<<"什么？没有？ "<<endl<<endl;
                cout<<"你再仔细找找！一定会有的！ "<<endl<<endl;
                RenWu[4]=1;
                MyMap[53]=601;
                cout<<"请随便输入一个数字确认 "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///下面写遇到2号NPC的对话
        if(DisPlayMap[markx][marky]%100==2)
        {
            system("cls");
            cout<<endl;
            cout<<"【相酒红】"<<endl<<endl;
            cout<<"在这个世界上，想要提升武力值和智力值，就只有通过加入武馆和学校！ "<<endl<<endl;
            cout<<"在武馆修炼会提升你的武力值，在学校学习会提升智力值 "<<endl<<endl;
            cout<<"武馆会在地图上显示为【馆】，学校会在地图上显示为【学】 "<<endl<<endl;
            cout<<"不过你只能一次选择其中一个加入，只有当你从目前的武馆或学校修炼完毕才能继续加入其他的武馆或学校修炼"<<endl<<endl;
            cout<<"不能加入相同的重复修炼哦！根据你自己的偏好选择吧 "<<endl<<endl;
            cout<<"想当格斗家就选择武馆修炼！想当魔法师就去学校！ "<<endl<<endl;
            cout<<"想都选择当然也可以！ "<<endl<<endl;
            cout<<"请随便输入一个数字确认 "<<endl<<endl;
            cin>>inputC;
        }
        ///下面写遇到3号NPC的对话
        if(DisPlayMap[markx][marky]%100==3)
        {
            system("cls");
            cout<<endl;
            cout<<"【杨文豪】"<<endl<<endl;
            cout<<"你知道吗？当你的攻击力小于怪物的防御值时，你用物理攻击怪物，怪物就会加血 "<<endl<<endl;
            cout<<"哈哈哈！！！你之前在战斗时看到这种情况是不是以为是BUG "<<endl<<endl;
            cout<<"才不是呢！这是作者故意做的！！！ "<<endl<<endl;
            cout<<"所以我还是喜欢当魔法师 "<<endl<<endl;
            cout<<"用魔法攻击怪物，怪物就没法防御了！ "<<endl<<endl;
            cout<<"不过也有一种弊端，就是防御太低！掉血太容易，需要经常跑客栈 "<<endl<<endl;
            cout<<"选择当格斗家以后武力值高了，可以穿一件高防御的衣服，然后去镇关西打野鸡 "<<endl<<endl;
            cout<<"这样野鸡打你一下，你就会会满血！！哈哈哈！！！从此再也不用去客栈 "<<endl<<endl;
            cout<<"不过要记得用法术攻击野鸡 "<<endl<<endl;
            cout<<"不然一下打死野鸡，就没法回血了！ "<<endl<<endl;
            cout<<"请输入随便一个数字确认 "<<endl<<endl;
            cin>>inputC;
        }
        ///下面写遇到4号NPC的对话
        if(DisPlayMap[markx][marky]%100==4)
        {
            system("cls");
            cout<<endl;
            cout<<"【小六】"<<endl<<endl;
            if(PlayerItems[4]%22==6)
            {
                cout<<"据说制作这个游戏的人也叫肖杨，和新手村的那个人名字一样！！！ "<<endl<<endl;
                cout<<"不知道是不是真的！！！ "<<endl<<endl;
                cout<<"有机会真想见一见他 "<<endl<<endl;
                cout<<"请输入一个随意数字确认 "<<endl<<endl;
                cin>>inputC;
            }
            else{
                cout<<"我暂时还没有想好和你说什么 。。。 "<<endl<<endl;
                cout<<"请输入一个随意数字确认 "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///下面写遇到5号NPC的对话
        if(DisPlayMap[markx][marky]%100==5)
        {
            system("cls");
            cout<<endl;
            cout<<"【李逍遥】"<<endl<<endl;
            ///以下为测试，需删除
               ///PlayerItems[4]=197;///-*-这里改的是桃源的对话，我说咋不变
               ///int shenmegui=PlayerItems[4]%13;
               ///cout<<"这里生成了剧情触发的石头："<<shi901[shenmegui]<<endl;
               ///cin>>inputC;
            ///以上为测试，需删除
            if(PlayerItems[4]>150)
            {
                if(RenWu[5]==0)
                {
                    cout<<"你好啊，过路人，我的土灵珠被魔王封到了石头里面，但我不知道是哪一块石头 "<<endl<<endl;
                    cout<<"你可以帮我找找看吗？ "<<endl<<endl;
                    cout<<"1.【好啊！很乐意帮忙！】 "<<endl<<endl;
                    cout<<"2.【没空，找你的灵儿妹妹吧！】 "<<endl<<endl;
                    cout<<"请输入相应数字选择： "<<endl<<endl;
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
                        cout<<"感谢你朋友！需要锤子的话，可以随时来找我！ "<<endl<<endl;
                        cout<<"但我每次只能给你一把 "<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"谢谢朋友，你会再回来找我的！"<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(RenWu[5]==1)
                {
                    if(PlayerItems[0]==0)
                    {
                        cout<<"感谢你的帮忙，你没有锤子了吗？我再给你一把吧"<<endl<<endl;
                        cout<<"你获得了【锤子】"<<endl<<endl;
                        PlayerItems[0]++;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"快去帮我找找吧朋友！我还要去拯救世界呢！ "<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else
                {
                    PlayerItems[66]=0;
                    cout<<"谢谢帮忙朋友！ "<<endl<<endl;
                    cout<<"什么？你要报酬？ "<<endl<<endl;
                    cout<<"我当时可没答应给你报酬！ "<<endl<<endl;
                    cout<<"不过我这有大量锤子出售！50文一把，你需要吗？ "<<endl<<endl;
                    cout<<"1.【需要】"<<endl<<endl;
                    cout<<"2.【不需要】 "<<endl<<endl;
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
                            cout<<"成交！！！ "<<endl<<endl;
                            cout<<"你失去了【50文钱】 "<<endl<<endl;
                            cout<<"你获得了一把【锤子】 "<<endl<<endl;
                        }
                        else
                        {
                            cout<<"你带的钱不够啊，朋友！ "<<endl<<endl;
                        }
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"你以后需要帮忙！我也会帮助你的！ "<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
            }
            else
            {
                cout<<"我可是救世大英雄！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认： "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///下面写遇到6号NPC的对话
        if(DisPlayMap[markx][marky]%100==6)
        {
            system("cls");
            cout<<endl;
            cout<<"【带数学家】"<<endl<<endl;
            cout<<"6 @#%…… 乙 "<<endl<<endl;
            cout<<"49 @#%…… 3000 "<<endl<<endl;
            cout<<"7th @#%…… 1000 "<<endl<<endl;
            cout<<"38 @#%…… 595 "<<endl<<endl;
            cout<<"425->420 @#%…… 574 "<<endl<<endl;
            cout<<"1804 @#%…… 22 "<<endl<<endl;
            cout<<"请问你找我什么事吗？"<<endl<<endl;
            cout<<"1.【你是大数学家？】"<<endl;
            cout<<"2.【你有什么挣钱的方法吗？我比较缺钱！】"<<endl<<endl;
            cout<<"请输入对应数字"<<endl<<endl;
            cin>>inputC;
            while(inputC!='1'&&inputC!='2')
            {
                cin>>inputC;
            }
            if(inputC=='1')
            {
                system("cls");
                cout<<endl;
                cout<<"【带数学家】"<<endl<<endl;
                cout<<"什么？你在质疑我的数学能力？ "<<endl<<endl;
                for(int i=0;i<GuaiWCnt;++i)
                {
                    cout<<"你一共击败了"<<guaiwu[i].s<<guaiwu[i].HitData<<"次"<<endl;
                }
                cout<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
                ///cout<<" "<<endl<<endl;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"【带数学家】"<<endl<<endl;
                cout<<"我最近在研究竹妖，如果你能帮我捉4只过来，我就可以给你20文钱的报酬！ "<<endl<<endl;
                cout<<"1.【接取任务】2.【交付任务】3.【离开】 "<<endl<<endl;
                cout<<"请输入相应数字 "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2'&&inputC!='3')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    if(currentguaiwudata.number>=0)
                    {
                        cout<<"你身上已有其他任务，先去完成吧！ "<<endl<<endl;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        currentguaiwudata.Id=1202;
                        currentguaiwudata.number=guaiwu[2].HitData;
                        cout<<"你已接受任务 "<<endl<<endl;
                        RenWu[6]=1;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(inputC=='2')
                {
                    system("cls");
                    cout<<endl;
                    cout<<"【带数学家】"<<endl<<endl;
                    if(RenWu[6]==0)
                    {
                        cout<<"你并没有接受我的任务啊！"<<endl<<endl;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        if(guaiwu[2].HitData-currentguaiwudata.number>=4)
                        {
                            currentguaiwudata.number=-1;
                            PlayerItems[9]+=20;
                            RenWu[6]=0;
                            cout<<"谢谢你帮了我大忙！这是你的报酬！ "<<endl<<endl;
                            cout<<"你获得了【20文钱】 "<<endl<<endl;
                            cout<<"请输入任意数字确认 "<<endl<<endl;
                            cin>>inputC;
                        }
                        else
                        {
                            cout<<"你还没有完成我的任务呢！ "<<endl<<endl;
                            cout<<"请输入任意数字确认 "<<endl<<endl;
                            cin>>inputC;
                        }
                    }
                }
                else
                {
                    system("cls");
                    cout<<endl;
                    cout<<"【带数学家】"<<endl<<endl;
                    cout<<"有需要再来找我！"<<endl<<endl;
                    cout<<"请输入任意数字确认 "<<endl<<endl;
                    cin>>inputC;
                }
            }
        }
        ///下面写遇到7号NPC的对话
        if(DisPlayMap[markx][marky]%100==7)
        {
            system("cls");
            cout<<endl;
            cout<<"【桃夭】"<<endl<<endl;
            if(RenWu[7]==0)
            {
                cout<<"啊啊啊！！！可恶！ "<<endl<<endl;
                cout<<"我的【百妖谱】就差一种叫做【无名】的妖怪就完成了 "<<endl<<endl;
                cout<<"但我就是找不到它在哪里 "<<endl<<endl;
                cout<<"亲爱的！你可以帮我找找吗？如果你能找到，可以带它来见我吗？ "<<endl<<endl;
                cout<<"我会给你一本百妖谱的副本，里面记载了各种妖怪的资料。 "<<endl<<endl;
                cout<<"求你务必带它来见我！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
                RenWu[7]=1;
            }
            else if(RenWu[7]==1)
            {
                cout<<"请你务必带【无名】来见我！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
            }
            else
            {
                cout<<"谢谢你亲爱的！你帮了我大忙！ "<<endl<<endl;
                cout<<"这本【百妖谱】副本是你的了，以后你可以随时查看上面的资料。 "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
                PlayerItems[50]=1;
            }
        }
        ///下面写遇到8号NPC的对话
        if(DisPlayMap[markx][marky]%100==8)
        {
            system("cls");
            cout<<endl;
            cout<<"【带英语家】"<<endl<<endl;
            cout<<"My.... "<<endl<<endl;
            cout<<"Name..."<<endl<<endl;
            cout<<"Is....."<<endl<<endl;
            cout<<"Show..."<<endl<<endl;
            cout<<"Young.."<<endl<<endl;
            cout<<"请问你找我什么事吗？"<<endl<<endl;
            cout<<"1.【你是大英语家？】"<<endl;
            cout<<"2.【你有什么挣钱的方法吗？我比较缺钱！】"<<endl<<endl;
            cout<<"请输入对应数字"<<endl<<endl;
            cin>>inputC;
            while(inputC!='1'&&inputC!='2')
            {
                cin>>inputC;
            }
            if(inputC=='1')
            {
                system("cls");
                cout<<endl;
                cout<<"【带英语家】"<<endl<<endl;
                cout<<"什么？你在质疑我的英语能力？ "<<endl<<endl;
                for(int i=0;i<22;++i)
                {
                    cout<<"Hello World!!!"<<endl;
                }
                cout<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
                ///cout<<" "<<endl<<endl;
            }
            else
            {
                system("cls");
                cout<<endl;
                cout<<"【带英语家】"<<endl<<endl;
                cout<<"我最近在研究莫桑花，如果你能帮我捉4只过来，我就可以给你50文钱的报酬！ "<<endl<<endl;
                cout<<"1.【接取任务】2.【交付任务】3.【离开】 "<<endl<<endl;
                cout<<"请输入相应数字 "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2'&&inputC!='3')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    if(currentguaiwudata.number>=0)
                    {
                        cout<<"你身上已有其他任务，先去完成吧！ "<<endl<<endl;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        currentguaiwudata.Id=1203;
                        currentguaiwudata.number=guaiwu[3].HitData;
                        cout<<"你已接受任务 "<<endl<<endl;
                        RenWu[8]=1;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(inputC=='2')
                {
                    system("cls");
                    cout<<endl;
                    cout<<"【带英语家】"<<endl<<endl;
                    if(RenWu[8]==0)
                    {
                        cout<<"你并没有接受我的任务啊！"<<endl<<endl;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        if(guaiwu[3].HitData-currentguaiwudata.number>=4)
                        {
                            currentguaiwudata.number=-1;
                            PlayerItems[9]+=50;
                            RenWu[8]=0;
                            cout<<"谢谢你帮了我大忙！这是你的报酬！ "<<endl<<endl;
                            cout<<"你获得了【50文钱】 "<<endl<<endl;
                            cout<<"请输入任意数字确认 "<<endl<<endl;
                            cin>>inputC;
                        }
                        else
                        {
                            cout<<"你还没有完成我的任务呢！ "<<endl<<endl;
                            cout<<"请输入任意数字确认 "<<endl<<endl;
                            cin>>inputC;
                        }
                    }
                }
                else
                {
                    system("cls");
                    cout<<endl;
                    cout<<"【带英语家】"<<endl<<endl;
                    cout<<"有需要再来找我！"<<endl<<endl;
                    cout<<"请输入任意数字确认 "<<endl<<endl;
                    cin>>inputC;
                }
            }
        }
        ///下面写遇到9号NPC的对话
        if(DisPlayMap[markx][marky]%100==9)
        {
            system("cls");
            cout<<endl;
            cout<<"【刘半仙儿】"<<endl<<endl;
            ///以下为测试，需删除
               ///PlayerItems[4]=178;
               ///cout<<"这里生成了剧情触发的河："<<he701[PlayerItems[4]%24]<<endl;
               ///cin>>inputC;
            ///以上为测试，需删除
            if(PlayerItems[4]>150)
            {
                if(RenWu[9]==0)
                {
                    cout<<"你好啊，过路人，我的仙器在过河时掉进了河里 "<<endl<<endl;
                    cout<<"我当时在木筏上刻上了记号 "<<endl<<endl;
                    cout<<"但当我到达岸边后，根据刻的记号再去找，发现已经找不到了 "<<endl<<endl;
                    cout<<"你可以帮我找找看吗？ "<<endl<<endl;
                    cout<<"1.【好啊！很乐意帮忙！】 "<<endl<<endl;
                    cout<<"2.【没空，你这么笨还是别用仙器了！】 "<<endl<<endl;
                    cout<<"请输入相应数字选择： "<<endl<<endl;
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
                        cout<<"感谢你朋友！需要木筏的话，可以随时来找我！ "<<endl<<endl;
                        cout<<"但我每次只能给你两艘 "<<endl<<endl;
                        cout<<"你获得了两艘【木筏】"<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"谢谢朋友，你会再回来找我的！"<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(RenWu[9]==1)
                {
                    if(PlayerItems[1]==0)
                    {
                        cout<<"感谢你的帮忙，你没有木筏了吗？我再给你两艘吧"<<endl<<endl;
                        cout<<"你获得了两艘【木筏】"<<endl<<endl;
                        PlayerItems[1]+=2;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"快去帮我找找吧朋友！我还要去修仙呢！ "<<endl<<endl;
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else
                {
                    PlayerItems[99]=0;
                    cout<<"谢谢帮忙朋友！ "<<endl<<endl;
                    cout<<"什么？你要报酬？ "<<endl<<endl;
                    cout<<"我当时可没答应给你报酬！ "<<endl<<endl;
                    cout<<"不过我这有大量木筏出售！50文一艘，你需要吗？ "<<endl<<endl;
                    cout<<"1.【需要】"<<endl<<endl;
                    cout<<"2.【不需要】 "<<endl<<endl;
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
                            cout<<"成交！！！ "<<endl<<endl;
                            cout<<"你失去了【50文钱】 "<<endl<<endl;
                            cout<<"你获得了一艘【木筏】 "<<endl<<endl;
                        }
                        else
                        {
                            cout<<"你带的钱不够啊，朋友！ "<<endl<<endl;
                        }
                        cout<<"请输入随机数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"你以后需要帮忙！我也会帮助你的！ "<<endl<<endl;
                        cout<<"请输入任意数字确认 "<<endl<<endl;
                        cin>>inputC;
                    }
                }
            }
            else
            {
                cout<<"当半仙儿也挺好的！！！（其实我也想成仙，不过我的仙器找不见了，哎！） "<<endl<<endl;
                if(PlayerItems[1]==0)
                {
                    cout<<"给你一艘木筏吧！不然你就卡关了！"<<endl<<endl;
                    cout<<"你获得了一艘【木筏】"<<endl<<endl;
                    PlayerItems[1]++;
                }
                cout<<"请输入任意数字确认 "<<endl<<endl;
                cin>>inputC;
            }
        }
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///遇到客栈
    else if(DisPlayMap[markx][marky]/100==3)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"【孙老板】"<<endl<<endl;
        if(RenWu[3]==1)
        {
            ///DisPlayMap[0][3]=1001;
            if(guaiwu[0].HitData-currentguaiwudata.number>=10)
            {
                currentguaiwudata.number=-1;
                cout<<"哎呀！谢谢你啊小伙计，你的野鸡我就收下了!!!这是给你的奖励 "<<endl<<endl;
                cout<<"你获得了50文钱！！！ "<<endl<<endl;
                PlayerItems[9]+=50;
                cout<<"你现在完全可以去更大的地方去闯一闯了，不要局限在新手村！！！你之前在镇关西打野怪的时候 "<<endl<<endl;
                cout<<"有没有看见过一个【传送点】啊！ "<<endl<<endl;
                cout<<"从那里就可以传送到【十里坡】，十里坡周围有各种【武馆】和【学校】！在那里历练和学习可以提高你的【武力值】和【智力值】 "<<endl<<endl;
                cout<<"在到达十里坡后要记得多与人交流啊！你会更了解这个世界！ "<<endl<<endl;
                cout<<"对了，让我在免费为你回复一次血量吧！以后你就算不上新人了，以后来我这休息我就要收费了哦！不过看在肖杨的面子上，你可以在我这里赊账！！！嘿嘿！ "<<endl<<endl;
                cout<<"你的血量恢复到了满值！！！ "<<endl<<endl;
                PlayerItems[10]=maxHP;
                MyMap[31]=802;
                RenWu[3]=2;
                cout<<"请输入任意数字确认！！！ "<<endl<<endl;
                cin>>inputC;
            }
            else
            {
                cout<<"感谢你为我去捉野鸡，事情完成后我会给你报酬的！！！ "<<endl<<endl;
                cout<<"如果你在捉野鸡的时候受伤，尽管来找我，我都会为你免费提供休息的地方！ "<<endl<<endl;
                cout<<"你获得了充足的休息！ "<<endl<<endl;
                cout<<"你的血量恢复到了满值！！！ "<<endl<<endl;
                PlayerItems[10]=maxHP;
                cout<<"请输入任意数字确认！！！ "<<endl<<endl;
                cin>>inputC;
            }
        }
        else{
            cout<<"你需要休息吗？ "<<endl<<endl;
            cout<<"1.【需要】 2.【不需要】 "<<endl<<endl;
            cout<<"请输入对应数字 "<<endl<<endl;
            char xiuxi;
            cin>>xiuxi;
            while(xiuxi!='1'&&xiuxi!='2')
            {
                cout<<"请输入正确数字！"<<endl<<endl;
                cin>>xiuxi;
            }
            if(xiuxi=='1')
            {
                if(PlayerItems[9]>=20)
                {
                    PlayerItems[9]-=20;
                    cout<<"你获得了充足的休息！ "<<endl<<endl;
                    cout<<"你的血量恢复到了满值！！！ "<<endl<<endl;
                    PlayerItems[10]=maxHP;
                    cout<<"请输入任意数字确认！！！ "<<endl<<endl;
                    cin>>inputC;
                }
                else{
                    if(DisPlayMap[markx][marky]==300)
                    {
                        PlayerItems[9]-=20;
                        cout<<"你获得了充足的休息！ "<<endl<<endl;
                        cout<<"你的血量恢复到了满值！！！ "<<endl<<endl;
                        PlayerItems[10]=maxHP;
                        cout<<"请输入任意数字确认！！！ "<<endl<<endl;
                        cin>>inputC;
                    }
                    else
                    {
                        cout<<"你没有充足的金钱！"<<endl<<endl;
                        cout<<"请输入任意数字确认！！！ "<<endl<<endl;
                        cin>>inputC;
                    }
                }
            }
        }
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///遇到武器店
    else if(DisPlayMap[markx][marky]/100==4)
    {
        if(IsOnShengzi) return false;
        ///遇到0号武器店老板   王老板
        system("cls");
        cout<<endl;
        cout<<"【王老板】"<<endl<<endl;
        if(DisPlayMap[markx][marky]%100==0)
        {
            if(RenWu[1]==1)
            {
                cout<<"你是肖杨介绍来的啊！！！ "<<endl<<endl;
                cout<<"肖杨他总是这么热情，喜欢帮忙，他就经常来我家帮我妻子做家务活！ "<<endl<<endl;
                cout<<"你将来是想当格斗家还是魔法师呢？ "<<endl<<endl;
                cout<<"格斗家物攻出色，如果有兴趣当格斗家，务必以后多多发展【武力值 】，有些战斗装备也有武力值的要求"<<endl<<endl;
                cout<<"魔法师法攻出色，如果有兴趣当魔法师，务必以后多多发展【智力值】，有些战斗装备也有智力值的要求"<<endl<<endl;
                cout<<"格斗家物攻很高，但遇到防御值高的敌人，会显得有些吃力 "<<endl<<endl;
                cout<<"魔法师法攻无视敌人的防御，同样的魔法师的防御也很低，在面对物理攻击擅长的敌人显得有些吃力"<<endl<<endl;
                cout<<"你想获得以下哪一把兵器呢？ "<<endl<<endl;
                cout<<"请输入对应数字： "<<endl<<endl;
                cout<<"1.  新手的短剑 【格斗家方向】"<<endl<<endl;
                cout<<"2.  新手的手杖 【魔法师方向】 "<<endl<<endl;
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
                    cout<<"你获得了：【新手的短剑】"<<endl<<endl;
                    cout<<"我帮你装备上吧！！！"<<endl<<endl;
                    Mywuqi=11;
                    ChangeMyData(Mywuqi);
                    cout<<"【你装备了新的装备：新手的短剑】 "<<endl<<endl;
                    cout<<"如果你以后获得了新的装备可以打开装备栏自己装备！ "<<endl<<endl;
                }
                else if(x=='2')
                {
                    PlayerItems[11]=1;
                    cout<<"你获得了：【新手的手杖】"<<endl<<endl;
                    cout<<"我帮你装备上吧！！！"<<endl<<endl;
                    Mywuqi=11;
                    ChangeMyData(Mywuqi);
                    cout<<"【你装备了新的装备：新手的手杖】 "<<endl<<endl;
                    cout<<"如果你以后获得了新的装备可以打开装备栏自己装备！ "<<endl<<endl;
                }
                RenWu[1]=2;
                cout<<"【任务接取】"<<endl<<endl;
                cout<<"【新手村服装店老板娘是我妻子，你拿着我的介绍信，可以找她了解一些装备的事情 】"<<endl<<endl;
                RenWu[2]=1;
                cout<<"你获得了王老板的介绍信！！！ "<<endl<<endl;
                cout<<"请随便输入一个数字确认： "<<endl<<endl;
                char c;
                cin>>c;
            }
            else
            {
                while(1)
                {
                    cout<<"欢迎来到新手村的武器店，我是这的王老板，请问你有什么需要的吗？"<<endl<<endl;
                    cout<<"1.  【短剑】 攻击值：10 金钱数：20"<<endl<<endl;
                    cout<<"2.   出售装备"<<endl<<endl;
                    cout<<"3.   离开"<<endl<<endl;
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
                                cout<<"你获得了：【短剑】"<<endl<<endl;
                                cout<<"请输入随便一个数字确认："<<endl<<endl;
                                char a2;
                                cin>>a2;
                                break;
                            }
                            else
                            {
                                system("cls");
                                cout<<endl;
                                cout<<"你的金钱不够，无法购买！"<<endl<<endl;
                                cout<<"请输入随便一个数字确认："<<endl<<endl;
                                char a2;
                                cin>>a2;
                                break;
                            }
                        }
                        else
                        {
                            system("cls");
                            cout<<endl;
                            cout<<"你的装备栏已满！无法购买！"<<endl<<endl;
                            cout<<"请输入随便一个数字确认："<<endl<<endl;
                            char a2;
                            cin>>a2;
                            break;
                        }
                    }
                    else if(L0x==2)
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"请输入你想要出售的装备:(此处请务必输入一个数字)"<<endl<<endl;
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
                            cout<<endl<<"请输入对应数字:(0-9)"<<endl<<endl;
                            cin>>inputC;
                            Chu=(inputC-'0')+11;
                        }
                        if(PlayerItems[Chu]<0)
                        {
                            system("cls");
                            cout<<endl;
                            cout<<"你没有此道具！"<<endl<<endl;
                            cout<<"请输入随便一个数字确认："<<endl<<endl;
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
                            cout<<"你获得了一文钱！"<<endl<<endl;
                            cout<<"请输入随便一个数字确认："<<endl<<endl;
                            char a2;
                            cin>>a2;
                            break;
                        }
                    }
                    else
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"欢迎下次再来！！！"<<endl<<endl;
                        cout<<"请输入随便一个数字确认："<<endl<<endl;
                        char a2;
                        cin>>a2;
                        break;
                    }
                }
            }
        }
        ///遇到1号武器店老板*************************************增加武器店时请在下面添加代码**********重要************************

        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///遇到装备店
    else if(DisPlayMap[markx][marky]/100==5)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"【卜老板】"<<endl<<endl;
        ///遇到0号服装店老板***********************************增加服装店时请在下面添加代码**********重要************************
        if(RenWu[2]==1)
        {
            cout<<"欢迎你啊，新人，我这有格斗家和魔法师入门的衣服你想选择哪一件呢？ "<<endl<<endl;
            cout<<"格斗家的衣服【新手的布衣】，可以为你提供防御值 "<<endl<<endl;
            cout<<"魔法师的衣服【新手的斗篷】，可以为你提供速度，让你在战斗中优先出手 "<<endl<<endl;
            cout<<"1. 【新手的布衣】 "<<endl<<endl;
            cout<<"2. 【新手的斗篷】 "<<endl<<endl;
            cout<<"请输入对应数字进行选择： "<<endl<<endl;
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
                cout<<"你获得了：【新手的布衣】"<<endl<<endl;
                cout<<"我来帮你穿上吧！"<<endl<<endl;
                cout<<"你装备了：【新手的布衣】 "<<endl<<endl;
                cout<<"请输入一个随便数字进行确认： "<<endl<<endl;
                char cy;
                cin>>cy;
            }
            else{
                PlayerItems[21]=1;
                Myyifu=21;
                ChangeMyData(21);
                system("cls");
                cout<<endl;
                cout<<"你获得了：【新手的斗篷】"<<endl<<endl;
                cout<<"我来帮你穿上吧！"<<endl<<endl;
                char cy;
                cout<<"你装备了：【新手的斗篷】 "<<endl<<endl;
                cout<<"请输入一个随便数字进行确认： "<<endl<<endl;
                cin>>cy;
            }
            system("cls");
            cout<<endl;
            cout<<"我再送你双鞋子吧！以后服装店可买不到鞋子哦！需要靠你自己运气去获得！ "<<endl<<endl;
            cout<<"你获得了：【新手的布鞋】 "<<endl<<endl;
            cout<<"我来帮你穿上吧！ "<<endl<<endl;
            char ccy;
            Myxiezi=31;
            PlayerItems[31]=0;
            ChangeMyData(31);
            cout<<"你装备了：【新手的布鞋】 "<<endl<<endl;
            cout<<"请输入一个随便数字进行确认： "<<endl<<endl;
            cin>>ccy;
            RenWu[2]=2;
            RenWu[3]=1;
            DisPlayMap[0][4]=1001;
            MyMap[5]=1001;
            cout<<"好了你现在装备齐全了。【客栈老板】孙先生喜欢【镇关西】的【野鸡】肉，你现在可以去新手村的右上角的野外去打些野鸡肉给他尝尝"<<endl<<endl;
            cout<<"他一定会给你奖励的！"<<endl<<endl;
            if(currentguaiwudata.number<0)
            {
                currentguaiwudata.Id=1200;
                currentguaiwudata.number=guaiwu[currentguaiwudata.Id%100].HitData;
            }
            cout<<"请输入一个随便数字进行确认： "<<endl<<endl;
            cin>>ccy;
        }
        else
        {
            while(1)
            {
                char L0xx;
                cout<<"欢迎来到新手村的服装店，我是这的卜老板，请问你有什么需要的吗？"<<endl<<endl;
                cout<<"1.  【布衣】 防御值：5 金钱数：20"<<endl<<endl;
                cout<<"2.   出售装备"<<endl<<endl;
                cout<<"3.   离开"<<endl<<endl;
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
                            cout<<"你获得了：【布衣】"<<endl<<endl;
                            cout<<"请输入随便一个数字确认："<<endl<<endl;
                            cin>>L0xx;
                            break;
                        }
                        else
                        {
                            system("cls");
                            cout<<endl;
                            cout<<"你的金钱不够，无法购买！"<<endl<<endl;
                            cout<<"请输入随便一个数字确认："<<endl<<endl;
                            cin>>L0xx;
                            break;
                        }
                    }
                    else
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"你的装备栏已满！无法购买！"<<endl<<endl;
                        cout<<"请输入随便一个数字确认："<<endl<<endl;
                        cin>>L0xx;
                        break;
                    }
                }
                else if(L0x==2)
                {
                    system("cls");
                    cout<<endl;
                    cout<<"请输入你想要出售的装备:(此处请务必输入一个数字)"<<endl<<endl;
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
                        cout<<endl<<"请输入对应数字:(0-9)"<<endl<<endl;
                        cin>>inputC;
                        Chu=(inputC-'0')+21;
                    }
                    if(PlayerItems[Chu]<0)
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"你没有此道具！"<<endl<<endl;
                        cout<<"请输入随便一个数字确认："<<endl<<endl;
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
                        cout<<"你获得了一文钱！"<<endl<<endl;
                        cout<<"请输入随便一个数字确认："<<endl<<endl;
                        cin>>L0xx;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    cout<<endl;
                    cout<<"欢迎下次再来！！！"<<endl<<endl;
                    cout<<"请输入随便一个数字确认："<<endl<<endl;
                    cin>>L0xx;
                    break;
                }
            }
        }
        ///system("cls");
        ///PrintMap();
        return false;
    }
    ///遇到草地
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
            cout<<"恭喜你发现了意外的惊喜！ "<<endl<<endl;
            cout<<"【最大生命值 +50】 "<<endl<<endl;
            maxHP+=50;
            MyMap[53]=600;
            DisPlayMap[markx][marky]=600;
            RenWu[4]=2;
            cout<<"请输入随便一个数字确认："<<endl<<endl;
            cin>>inputC;
            return true;
        }
        ///下面添加当草地中有隐藏道具的代码
        else return true;
    }
    ///遇到河
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
                cout<<"【你找到了刘半仙儿的仙器】 "<<endl<<endl;
                PlayerItems[99]=1;
                RenWu[9]=2;
                cout<<"请输入随便一个数字确认："<<endl<<endl;
                cin>>inputC;
            }
            waterFlag=1;
            return true;
        }
    }
    ///遇到传送门
    else if(DisPlayMap[markx][marky]/100==8)
    {
        if(IsOnShengzi) return false;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        system("cls");
        cout<<"请输入你想要传送到的地方：（你目前最多可以传送的地方为："<<DisPlayMap[markx][marky]%100<<"）"<<endl<<endl;
        ///下面添加传送对应的地名
        for(int i=0;i<=DisPlayMap[markx][marky]%100;++i)
        {
            cout<<i<<"."<<guanqia[i].s<<endl;
            ///cout<<guanqia[i].wild<<endl;
        }
        cout<<endl;
        cout<<" 请务必输入数字，避免出现不必要的BUG"<<endl<<endl;
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
            ///***不管
            if(wildFlag) wildFlag=0;
            ///***不管
            InitMap();
            ///system("cls");
            ///PrintMap();
            return false;
        }
        else {
            cout<<"无法传送"<<endl<<endl;
            cout<<"请输入任意数字确认："<<endl<<endl;
            char c;
            cin>>c;
            return false;
        }
    }
    ///遇到石头
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
                    cout<<"石头上有魔王的结界！ "<<endl<<endl;
                    cout<<"你被结界反伤！倒地不起！"<<endl<<endl;
                    cout<<"请输入任意数字确认"<<endl<<endl;
                    cin>>inputC;
                    return false;
                }
                else
                {
                    PlayerItems[0]--;
                    cout<<"这个石头太坚硬了！ "<<endl<<endl;
                    cout<<"你的锤子被震碎，但石头毫发无损！"<<endl<<endl;
                    cout<<"请输入任意数字确认"<<endl<<endl;
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
                cout<<"你找到了【土灵珠】 "<<endl<<endl;
                PlayerItems[66]=1;
                RenWu[5]=2;
                cout<<"请输入任意数字确认"<<endl<<endl;
                cin>>inputC;
                return true;
            }
        }
    }
    ///遇到野外传送
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
    ///遇到神秘人
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
            ///以下还需添加遇到神秘人的代码
            system("cls");
            cout<<endl;
            cout<<"【神秘人】 "<<endl<<endl;
            if(Dp==0)
            {
                cout<<"你好，有的时候我们需要将自己能力清空，然后才能重新注满！ "<<endl<<endl;
                cout<<"你需要将自己的TIP值清空，变为0吗？ "<<endl<<endl;
                cout<<"【1.需要】【2.我辛辛苦苦打的，不要变为0】 "<<endl<<endl;
                cout<<"请选择: "<<endl<<endl;
                cin>>inputC;
                while(inputC!='1'&&inputC!='2')
                {
                    cin>>inputC;
                }
                if(inputC=='1')
                {
                    PlayerItems[4]=0;
                    Tips[Dp]=0;
                    cout<<"如你所愿，有缘再见！ "<<endl<<endl;
                    cout<<"你的【TIP】值变为了0 "<<endl<<endl;
                    cout<<"输入任意数字确认"<<endl<<endl;
                    cin>>inputC;
                }
                else
                {
                    cout<<"慢走！ "<<endl<<endl;
                    cout<<"输入任意数字确认"<<endl<<endl;
                    cin>>inputC;
                }
            }
            else if(Dp==1)
            {
                cout<<"你好，我现在受了重伤需要输血，你愿意把你的血量分我一些吗？ "<<endl<<endl;
                cout<<"【1.十分乐意】【2.我的血很珍贵，才不要分给你】 "<<endl<<endl;
                cout<<"请选择: "<<endl<<endl;
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
                        cout<<"谢谢你，有缘再见！ "<<endl<<endl;
                        cout<<"你的【HP】值变为了2 "<<endl<<endl;
                        cout<<"输入任意数字确认"<<endl<<endl;
                        cin>>inputC;
                    }
                    else{
                        cout<<"你的【HP】值也不多呢！ "<<endl<<endl;
                        cout<<"输入任意数字确认"<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else
                {
                    cout<<"慢走！ "<<endl<<endl;
                    cout<<"输入任意数字确认"<<endl<<endl;
                    Tips[Dp]=2;
                    cin>>inputC;
                }
            }

            ///以上还需添加遇到神秘人的代码

            ///以下三句当遇到对话事件时绑定出现，，后面发现并不需要
            ///system("cls");
            ///PrintMap();
            return false;
            ///以上三句当遇到对话事件时绑定出现，，后面发现并不需要
        }
    }
    ///遇到敌人
    else if(DisPlayMap[markx][marky]/100==12)
    {
        if(IsOnShengzi) return false;
        IsMeet=1;
        if(PlayerItems[1]>0&&waterFlag==1)
        {
            PlayerItems[1]--;
            waterFlag=0;
        }
        ///*************************此处还需添加战斗代码(已添加）
        fightFlag=1;
        LoadFight();
        DisPlayMap[markx][marky]=0;
        return true;
    }
    ///遇到学校
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
                cout<<"你已经完成了在这所学校的学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"【道场引路人】"<<endl<<endl;
                cout<<"我是加入学校的引路人，你必须通过我的一个任务才能进入这所学校学习 "<<endl<<endl;
                cout<<"你确定接受我的任务吗？ "<<endl<<endl;
                cout<<"1.【确定】 "<<endl<<endl;
                cout<<"2.【放弃】 "<<endl<<endl;
                cout<<"请输入对应数字选择 "<<endl<<endl;
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
                    cout<<"【学馆区】是我们训练有望加入我们的地方，你的目标就是： "<<endl<<endl;
                    cout<<"【去学馆区转一圈，不要被野怪遇到，就算你通过了考验！】"<<endl<<endl;
                    cout<<"我现在把你传送到【学馆区】吧"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"你还没有完成我的任务！"<<endl<<endl;
                    cout<<"1.【我被野怪遇到了，我想重新领取任务】"<<endl<<endl;
                    cout<<"2.【我不想在你们学校学习了，我想取消任务】"<<endl<<endl;
                    cout<<"请选择相应数字"<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        IsMeet=0;
                        cout<<"好！我再将你传送到【学馆区】，祝你顺利！"<<endl<<endl;
                        cout<<"请输入随意数字确认"<<endl<<endl;
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
                        cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                        cout<<"请输入随意数字确认"<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"恭喜你，完成了我的任务！你正式成为了这所学校的一员！"<<endl<<endl;
                    cout<<"我现在把你传送学校里吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你的能力还不足以这所学校学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你的能力还不足以这所学校学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你已经完成了这所学校的学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"我是加入学校的引路人"<<endl<<endl;
                cout<<"你确定加入这所学校深造吗？ "<<endl<<endl;
                cout<<"1.【确定】 "<<endl<<endl;
                cout<<"2.【放弃】 "<<endl<<endl;
                cout<<"请输入对应数字选择 "<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"恭喜你，你正式成为了这所学校的一员！"<<endl<<endl;
                    cout<<"我现在把你传送学校里吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你的能力还不足以这所学校学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你的能力还不足以这所学校学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你已经完成了这所学校的学习！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"我是加入学校的引路人"<<endl<<endl;
                cout<<"你确定加入这所学校深造吗？ "<<endl<<endl;
                cout<<"1.【确定】 "<<endl<<endl;
                cout<<"2.【放弃】 "<<endl<<endl;
                cout<<"请输入对应数字选择 "<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"恭喜你，你正式成为了这所学校的一员！"<<endl<<endl;
                    cout<<"我现在把你传送学校里吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                cout<<"请输入随意数字确认"<<endl<<endl;
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
    ///遇到武馆
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
                cout<<"【道场引路人】"<<endl<<endl;
                cout<<"我是加入武馆的引路人，你必须通过我的一个任务才能进入这所武馆训练 "<<endl<<endl;
                cout<<"你确定接受我的任务吗？ "<<endl<<endl;
                cout<<"1.【确定】 "<<endl<<endl;
                cout<<"2.【放弃】 "<<endl<<endl;
                cout<<"请输入对应数字选择 "<<endl<<endl;
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
                        cout<<"【学馆区】是我们训练有望加入我们的地方，你的目标就是： "<<endl<<endl;
                        cout<<"【去学馆区转一圈，消灭10个玩偶，就算你通过了考验！】"<<endl<<endl;
                        cout<<"我现在把你传送到【学馆区】吧"<<endl<<endl;
                        cout<<"请输入随意数字确认"<<endl<<endl;
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
                        cout<<"你还有击杀野怪的任务没有完成，请把任务完成后再来找我！ "<<endl<<endl;
                        cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                        cout<<"请输入随意数字确认"<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"你还没有完成我的任务！"<<endl<<endl;
                    cout<<"1.【我马上去完成！】"<<endl<<endl;
                    cout<<"2.【我不想在这个武馆训练了，我想取消任务】"<<endl<<endl;
                    cout<<"请选择相应数字"<<endl<<endl;
                    cin>>inputC;
                    while(inputC!='1'&&inputC!='2')
                    {
                        cin>>inputC;
                    }
                    if(inputC=='1')
                    {
                        system("cls");
                        cout<<endl;
                        cout<<"好！我再将你传送到【学馆区】，祝你顺利！"<<endl<<endl;
                        cout<<"请输入随意数字确认"<<endl<<endl;
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
                        cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                        cout<<"请输入随意数字确认"<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"恭喜你，完成了我的任务！你正式成为了这间武馆的一员！"<<endl<<endl;
                    currentguaiwudata.number=-1;
                    cout<<"我现在把你传送到武馆里吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你的能力还不足以这所武馆修炼！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你的能力还不足以这所武馆修炼！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你已经完成了这所武馆的修炼！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"【道场引路人】"<<endl<<endl;
                cout<<"我是加入武馆的引路人"<<endl<<endl;
                cout<<"你确定加入这所武馆深造吗？ "<<endl<<endl;
                cout<<"1.【确定】 "<<endl<<endl;
                cout<<"2.【放弃】 "<<endl<<endl;
                cout<<"请输入对应数字选择 "<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"恭喜你，你正式成为了这所武馆的一员！"<<endl<<endl;
                    cout<<"我现在把你传送武馆里吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你的能力还不足以这所武馆修炼！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你的能力还不足以这所武馆修炼！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"你的能力还不足以这所武馆修炼！！！ "<<endl<<endl;
                cout<<"请输入任意数字确认 "<<endl<<endl;
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
                cout<<"【道场引路人】"<<endl<<endl;
                cout<<"我是加入武馆的引路人"<<endl<<endl;
                cout<<"你确定加入这所武馆深造吗？ "<<endl<<endl;
                cout<<"1.【确定】 "<<endl<<endl;
                cout<<"2.【放弃】 "<<endl<<endl;
                cout<<"请输入对应数字选择 "<<endl<<endl;
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
                    cout<<"【道场引路人】"<<endl<<endl;
                    cout<<"恭喜你，你正式成为了这所武馆的一员！"<<endl<<endl;
                    cout<<"我现在把你传送武馆里吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认"<<endl<<endl;
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
                cout<<"你被一股强大的气场送出了这里！ "<<endl<<endl;
                cout<<"请输入随意数字确认"<<endl<<endl;
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
    ///遇到魔王
    else if(DisPlayMap[markx][marky]/100==15)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"【魔王】 "<<endl<<endl;
        if(PlayerItems[2]<1&&PlayerItems[3]<1)
        {
            cout<<"你还不配做我的对手！ "<<endl<<endl;
            DisPlayMap[markx][marky]=809;
            cout<<"请输入随意数字确认"<<endl<<endl;
            cin>>inputC;
        }
        else
        {
            DisPlayMap[markx][marky]=2400;
        }
        return false;
    }
    ///遇到左护法
    else if(DisPlayMap[markx][marky]/100==16)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(myschool.ID==1)
        {
            if(myschool.xuexiaoLevel==1)
            {
                cout<<"【初级学校左护法】 "<<endl<<endl;
                if(ChengZhangRenWu[2]==0)
                {
                    cout<<"经过一些任务的磨练，你可以获得智力值！ "<<endl<<endl;
                    cout<<"你想要接受初级任务的挑战吗？ "<<endl<<endl;
                    cout<<"1.【确定】2.【再想想】"<<endl<<endl;
                    cout<<"请选择： "<<endl<<endl;
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
                        cout<<"你接受了我的任务"<<endl<<endl;
                        cout<<"快按R键查看自己的成长任务是什么吧！！！ "<<endl<<endl;
                        cout<<"右下角有个阵法可以带你到想去的地方！ "<<endl<<endl;
                        cout<<"请输入随意数字确认："<<endl<<endl;
                        cin>>inputC;
                    }
                }
                else if(ChengZhangRenWu[2]==1)
                {
                    IsMeet=0;
                    cout<<"你已经接受了我的任务"<<endl<<endl;
                    cout<<"快去完成吧！变得更强大！ "<<endl<<endl;
                    cout<<"请输入随意数字确认："<<endl<<endl;
                    cin>>inputC;
                }
                else
                {
                    cout<<"你已经完成了我的任务"<<endl<<endl;
                    cout<<"去完成更高级的任务吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认："<<endl<<endl;
                    cin>>inputC;
                }
            }
            if(myschool.xuexiaoLevel==2)
            {
                cout<<"【中级学校左护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==3)
            {
                cout<<"【高级学校左护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
        }
        else
        {
            if(myschool.wuguanLevel==1)
            {
                cout<<"【初级武馆左护法】 "<<endl<<endl;
                if(ChengZhangRenWu[3]==0)
                {
                    cout<<"经过一些任务的磨练，你可以获得智力值！ "<<endl<<endl;
                    cout<<"你想要接受初级任务的挑战吗？ "<<endl<<endl;
                    cout<<"1.【确定】2.【再想想】"<<endl<<endl;
                    cout<<"请选择： "<<endl<<endl;
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
                            cout<<"你接受了我的任务"<<endl<<endl;
                            cout<<"快按R键查看自己的成长任务是什么吧！！！ "<<endl<<endl;
                            cout<<"右下角有个阵法可以带你到想去的地方！ "<<endl<<endl;
                            cout<<"请输入随意数字确认："<<endl<<endl;
                            cin>>inputC;
                        }
                        else
                        {
                            cout<<"你有其他任务没有完成，无法接取任务！ "<<endl<<endl;
                            To=3;
                            cout<<"请输入随意数字确认："<<endl<<endl;
                            cin>>inputC;
                        }
                    }
                }
                else if(ChengZhangRenWu[3]==1)
                {
                    cout<<"你已经接受了我的任务"<<endl<<endl;
                    cout<<"快去完成吧！变得更强大！ "<<endl<<endl;
                    cout<<"请输入随意数字确认："<<endl<<endl;
                    cin>>inputC;
                }
                else
                {
                    cout<<"你已经完成了我的任务"<<endl<<endl;
                    cout<<"去完成更高级的任务吧！"<<endl<<endl;
                    cout<<"请输入随意数字确认："<<endl<<endl;
                    cin>>inputC;
                }
            }
            if(myschool.wuguanLevel==2)
            {
                cout<<"【中级武馆左护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==3)
            {
                cout<<"【高级武馆左护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
        }
        return false;
    }
    ///遇到学校/武馆主席
    else if(DisPlayMap[markx][marky]/100==17)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(myschool.ID==1)
        {
            if(myschool.xuexiaoLevel==1)
            {
                cout<<"【初级学校主席】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==2)
            {
                cout<<"【中级学校主席】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==3)
            {
                cout<<"【高级学校主席】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
        }
        else
        {
            if(myschool.wuguanLevel==1)
            {
                cout<<"【初级武馆主席】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==2)
            {
                cout<<"【中级武馆主席】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==3)
            {
                cout<<"【高级武馆主席】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
        }
        return false;
    }
    ///遇到右护法
    else if(DisPlayMap[markx][marky]/100==18)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(myschool.ID==1)
        {
            if(myschool.xuexiaoLevel==1)
            {
                cout<<"【初级学校右护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==2)
            {
                cout<<"【中级学校右护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.xuexiaoLevel==3)
            {
                cout<<"【高级学校右护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
        }
        else
        {
            if(myschool.wuguanLevel==1)
            {
                cout<<"【初级武馆右护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==2)
            {
                cout<<"【中级武馆右护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
            if(myschool.wuguanLevel==3)
            {
                cout<<"【高级武馆右护法】 "<<endl<<endl;
                cout<<"请输入随意数字确认："<<endl<<endl;
                cin>>inputC;
            }
        }
        return false;
    }
    ///遇到阵法
    else if(DisPlayMap[markx][marky]/100==19)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        if(To==-1)
        {
            cout<<"【阵法】"<<endl<<endl;
            cout<<"你并没有想去的地方！ "<<endl<<endl;
            cout<<"请输入随意数字确认"<<endl<<endl;
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
    ///遇到彩蛋
    else if(DisPlayMap[markx][marky]/100==20)
    {
        if(IsOnShengzi) return false;
        IsOnYidian=0;
        LoadCaiDan();
        MyMap[26*10+13]=0;
        DisPlayMap[2][2]=0;
        return false;
    }
    ///遇到绳子
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
    ///遇到蜘蛛BOSS
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
    ///遇到骨头
    else if(DisPlayMap[markx][marky]/100==23)
    {
        if(IsOnShengzi) return false;
        system("cls");
        cout<<endl;
        cout<<"前面一堆可怕的骨头 "<<endl<<endl;
        cout<<"请输入随意数字确认"<<endl<<endl;
        cin>>inputC;
        return false;
    }
    ///遇到洞穴
    else  if(DisPlayMap[markx][marky]/100==24)
    {
        if(IsOnShengzi) return false;
        IsOnDongxue=1;
        markLevel=23; ///洞穴起始关卡为 23
        markx=4;
        marky=0;
        InitMap();
        return false;
    }

    return false;
}
void Init()
{
    ///在此添加关卡属性**************************重要***********************************
    guanqia[0].level=-1;
    guanqia[0].s="【新手村】";
    guanqia[0].wild=0;
    guanqia[1].s="【镇关西】";
    guanqia[1].level=1200;
    guanqia[1].wild=1;
    guanqia[2].level=-1;
    guanqia[2].s="【十里坡】";
    guanqia[2].wild=0;
    guanqia[3].level=-1;
    guanqia[3].s="【道场】";
    guanqia[3].wild=0;
    guanqia[4].level=1201;
    guanqia[4].s="【学馆区】";
    guanqia[4].wild=1;
    guanqia[5].level=-1;
    guanqia[5].s="【桃源】";
    guanqia[5].wild=0;
    guanqia[6].level=1202;
    guanqia[6].s="【紫竹林】";
    guanqia[6].wild=1;
    guanqia[7].level=-1;
    guanqia[7].s="【诡镇】";
    guanqia[7].wild=0;
    guanqia[8].level=1203;
    guanqia[8].s="【接天崖】";
    guanqia[8].wild=1;
    guanqia[9].level=-1;
    guanqia[9].s="【魔都】";
    guanqia[9].wild=0;
    guanqia[10].level=-1;
    guanqia[10].s="【初级学校】";
    guanqia[10].wild=0;
    guanqia[11].level=-1;
    guanqia[11].s="【中级学校】";
    guanqia[11].wild=0;
    guanqia[12].level=-1;
    guanqia[12].s="【高级学校】";
    guanqia[12].wild=0;
    guanqia[13].level=-1;
    guanqia[13].s="【初级武馆】";
    guanqia[13].wild=0;
    guanqia[14].level=-1;
    guanqia[14].s="【中级武馆】";
    guanqia[14].wild=0;
    guanqia[15].level=-1;
    guanqia[15].s="【高级武馆】";
    guanqia[15].wild=0;
    guanqia[16].level=1205;
    guanqia[16].s="【埋酒地】";
    guanqia[16].wild=1;
    guanqia[17].level=1206;
    guanqia[17].s="【四方地】";
    guanqia[17].wild=1;

    ///在此添加怪物属性**************************重要***********************************
    ///双数为物理攻击的怪物，单数为法术攻击的怪物
    guaiwu[0].s="【野鸡】";  ///物理攻击
    guaiwu[0].Hp=22;
    guaiwu[0].Hit=10;
    guaiwu[0].Fangyu=5;
    guaiwu[0].Speed=1;
    guaiwu[1].s="【玩偶】";  ///法术攻击
    guaiwu[1].Hp=40;
    guaiwu[1].Hit=20;
    guaiwu[1].Fangyu=8;
    guaiwu[1].Speed=2;
    guaiwu[2].s="【竹妖】";   ///物
    guaiwu[2].Hp=60;
    guaiwu[2].Hit=30;
    guaiwu[2].Fangyu=16;
    guaiwu[2].Speed=3;
    guaiwu[3].s="【莫桑花】";  ///法术攻击
    guaiwu[3].Hp=80;
    guaiwu[3].Hit=40;
    guaiwu[3].Fangyu=20;
    guaiwu[3].Speed=4;
    guaiwu[4].s="【无名】";   ///物
    guaiwu[4].Hp=100;
    guaiwu[4].Hit=60;
    guaiwu[4].Fangyu=25;
    guaiwu[4].Speed=5;
    guaiwu[5].s="【离愁】";  ///法
    guaiwu[5].Hp=1;
    guaiwu[5].Hit=1;
    guaiwu[5].Fangyu=999999;
    guaiwu[5].Speed=999999;
    guaiwu[6].s="【方方怪】";  ///物
    guaiwu[6].Hp=50;
    guaiwu[6].Hit=40;
    guaiwu[6].Fangyu=50;
    guaiwu[6].Speed=999;

///PlayerItems[0]=0;  ///锤子数量，可以用来砸开石头
///PlayerItems[1]=0;  ///木筏数量，可以用来过河
///PlayerItems[2]    ///玩家武力值
///playerItems[3]    ///玩家智力值
///playerItems[4]     Tip值，用来触发神秘人，可以与神秘人对话存档，打怪获得，每次+1
    PlayerItems[5] = 1;///物攻值(测试完毕请改为 1 ）
    PlayerItems[6] = 1; ///法攻值
    PlayerItems[7] = 1; ///防御值
    PlayerItems[8] = 1; ///速度值(测试完毕请改为 1 ）
    PlayerItems[9] = 0; ///金钱(测试完后改为0)
    PlayerItems[10]=50;  ///HP
    for(int i=11; i<=40; ++i)
    {
        PlayerItems[i]=-1;
    }

    ///以下为测试代码**************请删除
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
    ///以上为测试代码**************测试完毕请注释或删除

///在此修改鞋子属性   鞋子不宜遇到，总共不会超过十双鞋子， 鞋子也无法出售
    xiezi[0].s="【新手的布鞋】";
    xiezi[0].Speed=1;
    xiezi[1].s="【短靴】";
    xiezi[1].Speed=2;
    xiezi[2].s="【雪靴】";
    xiezi[2].Speed=3;
    xiezi[3].s="【凉靴】";
    xiezi[3].Speed=4;
    xiezi[4].s="【长靴】";
    xiezi[4].Speed=5;
    xiezi[5].s="【棉靴】";
    xiezi[5].Speed=6;
    xiezi[6].s="【地球靴】";
    xiezi[6].Speed=7;
    xiezi[7].s="【肖杨靴】";
    xiezi[7].Speed=8;

    ///xiezi[1].Speed=1;
///在此修改格斗家武器属性
    wuqi[0].s="【新手的短剑】";
    wuqi[0].Zhi=0;
    wuqi[0].Hit=10;
    wuqi[0].Nai=-1; ///-1表示永久可用
    wuqi[2].s="【短剑】";
    wuqi[2].Zhi=0;
    wuqi[2].Hit=10;
    wuqi[2].Nai=20;

///在此修改格斗家装备属性
    yifu[0].s="【新手的布衣】";
    yifu[0].Zhi=0;
    yifu[0].FangYu=5;
    yifu[0].Nai=-1;
    yifu[2].s="【布衣】";
    yifu[2].Zhi=0;
    yifu[2].FangYu=5;
    yifu[2].Nai=20;

///在此修改魔法师手杖属性
    wuqi[1].Zhi=0;
    wuqi[1].s="【新手的手杖】";
    wuqi[1].Hit=5;
    wuqi[1].Nai=-1;
    wuqi[3].s="【手杖】";
    wuqi[3].Zhi=0;
    wuqi[3].Hit=5;
    wuqi[3].Nai=20;

///在此修改魔法师斗篷属性
    yifu[1].Zhi=0;
    yifu[1].s="【新手的斗篷】";
    yifu[1].FangYu=1;
    yifu[1].Nai=-1;
    yifu[3].s="【斗篷】";
    yifu[3].Zhi=0;
    yifu[3].FangYu=1;
    yifu[3].Nai=20;

}
void ChangeMyData(int i) ///11-20 武器 21-30  衣服 31-40 鞋子
{
    ///-1表示卸下武器 -2表示卸下衣服 -3表示卸下鞋子 >=0表示穿上相应装备
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
            cout<<"你遇到了："<<guaiwu[DisPlayMap[markx][marky]%100].s<<endl<<endl;
            cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"【血量:"<<Ghp<<"】"<<endl<<endl;
            cout<<"【我】"<<"【血量:"<<PlayerItems[10]<< "】"<<endl<<endl;
        }
        if(PlayerItems[8]>guaiwu[DisPlayMap[markx][marky]%100].Speed)
        {
            if(ZiDong==0)
            {
                cout<<"请选择你的攻击： 1.物理攻击 2.法术攻击。"<<endl<<endl;
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
                    cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"血量减少了:"<<PlayerItems[5]-guaiwu[(DisPlayMap[markx][marky]%100)].Fangyu<<endl<<endl;
                }
                Ghp-=(PlayerItems[5]-guaiwu[DisPlayMap[markx][marky]%100].Fangyu);
                if(Ghp<=0) {
                    system("cls");
                    cout<<endl<<"你获胜了！！！恭喜！！！"<<endl<<endl;
                    cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[(DisPlayMap[markx][marky]%100)].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=(guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]);
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                    cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"血量减少了:"<<PlayerItems[6]<<endl<<endl;
                }
                Ghp-=PlayerItems[6];
                if(Ghp<=0)
                {
                    ///Ghp=0;
                    cout<<endl<<"你获胜了！！！恭喜！！！"<<endl<<endl;
                    cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7];
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                cout<<"请选择你的攻击： 1.物理攻击 2.法术攻击。"<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=(guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]);
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                    cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"血量减少了:"<<PlayerItems[5]-guaiwu[DisPlayMap[markx][marky]%100].Fangyu<<endl<<endl;
                }
                Ghp-=(PlayerItems[5]-guaiwu[DisPlayMap[markx][marky]%100].Fangyu);
                if(Ghp<=0)
                {
                    cout<<endl<<"你获胜了！！！恭喜！！！"<<endl<<endl;
                    cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]<<endl<<endl;
                    }
                    PlayerItems[10]-=(guaiwu[DisPlayMap[markx][marky]%100].Hit-PlayerItems[7]);
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<"【你】"<<"血量减少了:"<<guaiwu[DisPlayMap[markx][marky]%100].Hit<<endl<<endl;
                    }
                    PlayerItems[10]-=guaiwu[DisPlayMap[markx][marky]%100].Hit;
                    if(PlayerItems[10]<=0)
                    {
                        cout<<endl<<"你失败了了！！！加油！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
                        cout<<guaiwu[DisPlayMap[markx][marky]%100].s<<"血量减少了:"<<PlayerItems[6]<<endl<<endl;
                    }
                    Ghp-=PlayerItems[6];
                    if(Ghp<=0)
                    {
                        cout<<endl<<"你获胜了！！！恭喜！！！"<<endl<<endl;
                        cout<<"请输入任意数字确认："<<endl<<endl;
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
            cout<<"【游戏管理员】 "<<endl<<endl;
            cout<<"你已经完成了初级学校的初级任务，智力值得到了提升！ "<<endl<<endl;
            cout<<"【智力值 +1】 "<<endl<<endl;
            cout<<"请输入任意数字确认："<<endl<<endl;
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
            cout<<"【游戏管理员】 "<<endl<<endl;
            cout<<"你已经完成了初级武馆的初级任务，武力值得到了提升！ "<<endl<<endl;
            cout<<"【武力值 +1】 "<<endl<<endl;
            cout<<"请输入任意数字确认："<<endl<<endl;
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
    cout<<"暂未开发"<<endl<<endl;
    cout<<"请输入任意数字确认："<<endl<<endl;
    cin>>inputC;
}
int color(int c) 	//SetConsoleTextAttribute是API设置控制台窗口字体颜色和背景色的函数
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
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
    ///*********以下测试用需删除

    ///*********以上测试用需删除

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
            cout<<"你装备的武器坏掉了！请及时更换！ "<<endl<<endl;
            ChangeMyData(-1);
            PlayerItems[Mywuqi]=-1;
            Mywuqi=-1;
            cout<<"请输入随便一个数字确认 "<<endl<<endl;
            cin>>inputC;
        }
        if(yifu[PlayerItems[Myyifu]].Nai==0)
        {
            cout<<"你装备的衣服坏掉了！请及时更换！ "<<endl<<endl;
            ChangeMyData(-2);
            PlayerItems[Myyifu]=-1;
            Myyifu=-1;
            cout<<"请输入随便一个数字确认 "<<endl<<endl;
            cin>>inputC;
        }
        if(gameFlag) break;
    }
    if(gameFlag==1)
    {
        cout<<"【胜败乃兵家常事！！！】 "<<endl<<endl;
        cout<<"【大侠请重新来过！！！】 "<<endl<<endl;
        cout<<"请输入随便一个数字确认 "<<endl<<endl;
        cin>>inputC;
    }

    system("pause");
	return 0;
}
