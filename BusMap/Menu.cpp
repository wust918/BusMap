#include "Menu.h"
extern BusMap g_sMap;
//Menu里的界面函数
void gotoxy(int x, int y) //坐标函数
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}
void HideCursor(int n) /*隐藏光标*/
{
    CONSOLE_CURSOR_INFO cursor_info={1,n};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void LoginScreen()//开机界面
{
    int i,j,k;
    HideCursor(0);
    for(i=0;i<=27;i++)
    {
        cout<<Login[i]<<endl;
        Sleep(100);
    }
    for (k=1;k<=2;k++)//动态加载
    {
        for (i = 31; i <= 66; i = i + 2)
        {
            for (j = i - 4; j <= i; j = j + 2)
            {
                if (j >= 31 && j <= 65)
                {
                    gotoxy(j,21);
                    cout<<"[]";
                }
                Sleep(100);
            }
            for (j = i - 4; j <= i; j = j + 2)
            {
                if (j >= 31 && j <= 65)
                {
                    gotoxy(j, 21);
                    cout<<"  ";
                }
            }
        }
    }
    system("cls");
    gotoxy(0,0);
    HideCursor(1);
    MainMenu();
}
void Shutdown()//关机界面
{
    system("cls");
    gotoxy(0,0);
    HideCursor(0);
    for(int i=0;i<=12;i++)
    {
        cout<<Shut[i]<<endl;
        Sleep(100);
    }
    for (int i=1;i<=4;i++)//动态加载
    {
        gotoxy(49,12);
        for(int j=1;j<=4;j++)
        {
            cout<<".";
            Sleep(300);
        }
        for(int k=4;k>=0;k--)
        {
            gotoxy(49+k,12);
            cout<<" ";
        }
    }
    system("cls");
    exit(-1);
}
void MainMenu()//主菜单
{
    while(1)
    {
        int num;
        cout<<" ===========================  欢迎使用公交管理系统!  ==========================="<<endl;
        cout<<"|                                                                               |"<<endl;
        cout<<"|                                0.关机                                         |"<<endl;
        cout<<"|                                                                               |"<<endl;
        cout<<"|                                1.管理员登录                                   |"<<endl;
        cout<<"|                                                                               |"<<endl;
        cout<<"|                                2.乘客登录                                     |"<<endl;
        cout<<"|                                                                               |"<<endl;
        cout<<" =============================================================================== "<<endl;
        do
        {
             cout<<"请输入要使用的功能(数字>>0/1/2>>):";
             cin>>num;
        }while(num>2||num<0);
        switch(num)
        {
            case 0:
                {
                    system("cls");
                    Shutdown();
                    break;
                }
            case 1:
                {
                    system("cls");
                    LoginScreeForAdministrator();
                    break;
                }
            case 2:
                {
                    system("cls");
                    MenuForCustomer();
                    break;
                }
        }
        system("cls");
    }
}
void LoginScreeForAdministrator()//管理员登录界面
{
    string Administrator,Password;
    string administrator,password;
    int count=0;
    ifstream i;
    i.open("ADandPA.txt",ios::in); //获取ADandPa.txt文件中保存的用户名、密码
    i>>Administrator;
    i>>Password;
    i.close();
    do
    {
        system("cls");
        cout<<"------------------------   你好！请登录  ------------------------"<<endl;
        cout<<endl;
        cout<<"               ------------------------------"<<endl;
        cout<<"       用户名:                                 "<<endl;
        cout<<"               ------------------------------"<<endl;
        cout<<"       密  码:                                 "<<endl;
        cout<<"               ------------------------------"<<endl;
        cout<<"                 (用户名、密码初始均为Admin)   "<<endl;
        cout<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        gotoxy(15,3);
        cin>>administrator;
        gotoxy(15,5);
        cin>>password;
        cout<<endl;
        ++count;
        if(count==5)
        {
            break;
        }
        gotoxy(0,11);
        if(administrator==Administrator&&password!=Password)
        {
            cout<<"       输入用户名正确,但密码错误！你还有"<<5-count<<"次机会"<<endl;
        }
        else if(administrator!=Administrator)
        {
            cout<<"       用户名错误！你还有"<<5-count<<"次机会"<<endl;
        }
        else
        {
            cout<<"       用户名、密码正确！"<<endl;
        }
        cout<<endl;
        system("pause");
    }while(administrator!=Administrator||password!=Password);
    if(count<5)
    {
        MenuForAdministrator();
    }
}
void MenuForAdministrator() //管理员菜单
{
        int num;
        system("cls");
        cout<<"------------------  管理员,你好！ ------------------"<<endl;
        cout<<endl;
        cout<<"       1.查看本市所有公交"<<endl;
        cout<<"       2.查看本市所有站点"<<endl;
        cout<<"       3.查询本市某公交具体线路"<<endl;
        cout<<"       4.查询本市某站点相关信息"<<endl;
        cout<<"       5.公交添加、删除、修改"<<endl;
        cout<<"       6.站点添加、删除、修改"<<endl;
        cout<<"       7.修改用户名和密码"<<endl;
        cout<<"       8.返回主菜单"<<endl;
        cout<<endl;
        cout<<"----------------------------------------------------"<<endl;
        do
        {
            cout<<"请输入你要使用的功能:";
            cin>>num;
        }while(num>8||num<1);
        system("cls");
        switch(num)
        {
        case 1:
            {
                OutPutAllBusName();
                system("pause");
                MenuForAdministrator();
                break;
            }
        case 2:
            {
                OutPutAllStationName();
                system("pause");
                MenuForAdministrator();
                break;
            }
        case 3:
            {
                OutPutBusRoute();
                system("pause");
                MenuForAdministrator();
                break;
            }
        case 4:
            {
                OutPutStationInf();
                system("pause");
                MenuForAdministrator();
                break;
            }
        case 5:
            {
                MenuForBus();
                MenuForAdministrator();
                break;
            }
        case 6:
            {
                MenuForStation();
                MenuForAdministrator();
                break;
            }
        case 7:
            {
                ChangeInfo();
                system("pause");
                MenuForAdministrator();
                break;
            }
        case 8:
            {
                MainMenu();
                break;
            }
        }
}
void OutPutAllBusName()//输出库中所有公交及其起点终点
{
    cout<<"本市共有"<<g_sMap.bus_num<<"辆公交,如下:"<<endl;
    for(int i=0;i<g_sMap.bus_num;i++)
    {
            cout<<g_sMap.buses[i].name<<"   起点:"<<g_sMap.stations[g_sMap.buses[i].Start].name<<"   终点:"<<g_sMap.stations[g_sMap.buses[i].End].name<<endl;
    }
    cout<<endl;
}
void OutPutAllStationName()//输出库中所有站点名称
{
    cout<<"本市共有"<<g_sMap.station_num<<"个站点,如下:"<<endl;
    for(int i=0;i<g_sMap.station_num;i++)
    {
            cout<<g_sMap.stations[i].name<<endl;
    }
    cout<<endl;
}
void MenuForBus()//操作公交界面
{
    system("cls");
    int num;
    cout<<"-----------------------"<<endl;
    cout<<endl;
    cout<<"  1.添加公交路线"<<endl;
    cout<<"  2.删除公交路线"<<endl;
    cout<<"  3.修改公交信息"<<endl;
    cout<<"  4.返回管理员菜单"<<endl;
    cout<<endl;
    cout<<"-----------------------"<<endl;
    do
    {
        cout<<"请输入要使用功能:";
        cin>>num;
    }while(num>4||num<1);
    system("cls");
    if(num!=4)
    {
        switch(num)
        {
            case 1:
                {
                    AddBus();
                    system("pause");
                    MenuForBus();
                    break;
                }
            case 2:
                {
                    DeleteBus();
                    system("pause");
                    MenuForBus();
                    break;
                }
            case 3:
                {
                    ChangeBusInfo();
                    system("pause");
                    MenuForBus();
                    break;
                }
        }
    }
}
void AddBus()//添加上行、下行公交(公交名，起点，终点)
{
    string upBus,downBus;
    string BusName;
    do
    {
        system("cls");
        cout<<"Tip:该功能向库中添加公交名,及其线路."<<endl;
        cout<<endl;
        OutPutAllBusName();
        cout<<endl;
        cout<<"新增公交名(数字):"<<endl;
        cout<<endl;
        cout<<"请依次输入上行公交所经站点(输入#结束):"<<endl;
        gotoxy(17,5+g_sMap.bus_num);
        cin>>BusName;
    }while(FindBus(BusName+"上行")!=-1);
    upBus=BusName+"上行";
    downBus=BusName+"下行";
    int nBusUp=GetBus(upBus);
    int nBusDown=GetBus(downBus);
    gotoxy(0,6+g_sMap.bus_num);
    vector<string> station;
    string temp;
    while(cin>>temp&&temp!="#")
    {
        station.push_back(temp);
    }
    int Distance[station.size()];
    for(int i=1;i<station.size();i++)
    {
        cout<<"请输入 "<<station[i-1]<<" 与 "<<station[i]<<" 两站点的距离:";
        cin>>Distance[i];
    }
    int index[station.size()];
    for(int i=0;i<station.size();i++)
    {
        if(FindStation(station[i])==-1)//新站点写入Stations.txt文件
        {
            index[i]=GetStation(station[i]);//创建空间
            ofstream out;
            out.open("Stations.txt",ios::app);
            out<<station[i]<<endl;
            out.close();
        }
        else
        {
            index[i]=FindStation(station[i]);
        }
    }
    //将新增公交加入Buses.txt文件
    ofstream out;
    out.open("Buses.txt",ios::app);
    out<<upBus<<endl;
    out<<index[0]<<endl;
    out<<index[station.size()-1]<<endl;
    out<<downBus<<endl;
    out<<index[station.size()-1]<<endl;
    out<<index[0]<<endl;
    out.close();
    //将路线写入Routes.txt文件
    ofstream outR;
    outR.open("Routes.txt",ios::app);
    for(int i=0;i<station.size()-1;i++)//上行
    {
        outR<<nBusUp<<"     "<<index[i]<<"     "<<index[i+1]<<"     "<<Distance[i+1]<<endl;
    }
    for(int i=station.size()-1;i>=1;i--)//下行
    {
        outR<<nBusDown<<"     "<<index[i]<<"     "<<index[i-1]<<"     "<<Distance[i]<<endl;
    }
    outR.close();
    station.clear();
    InitializeGraph(g_sMap);//根据文件再次初始化g_sMap;
}
void DeleteBus()//删除公交
{
    cout<<"Tip:此函数删除公交线路,**上行/**下行,一次删除两条,**上行/**下行为两条"<<endl;
    cout<<endl;
    OutPutAllBusName();
    cout<<endl;
    string BusName;
    do
    {
        cout<<"请输入要删除的公交名(**上行/**下行):";
        cin>>BusName;
    }while(FindBus(BusName)==-1);
    int index=FindBus(BusName);
    //修改Buses.txt文件
    string Temp;
    int t;
    if(index%2==0)//上行公交
    {
        Temp=g_sMap.buses[index+1].name;
        t=index+1;
    }
    else//下行公交
    {
        Temp=g_sMap.buses[index-1].name;
        t=index-1;
    }
    string B;
    int S,E;
    fstream Bfile("Buses.txt");
    ofstream Btempfile("temp.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        Bfile>>B>>S>>E;
        if(B!=BusName&&B!=Temp)
        {
            Btempfile<<B<<endl;
            Btempfile<<S<<endl;
            Btempfile<<E<<endl;
        }
    }
    Btempfile.close();
    Bfile.close();
    ofstream Boutfile("Buses.txt",ios::out|ios::trunc);
    fstream Binfile("temp.txt");
    for(int i=0;i<g_sMap.bus_num-2;i++)
    {
        Binfile>>B>>S>>E;
        Boutfile<<B<<endl;
        Boutfile<<S<<endl;
        Boutfile<<E<<endl;
    }
    Boutfile.close();
    Binfile.close();
    //修改Routes.txt文件
    int L,D;
    fstream Rfile("Routes.txt");
    ofstream Rtempfile("temp.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.route_num;i++)
    {
        Rfile>>L>>S>>E>>D;
        if(L!=index&&L!=t)
        {
            Rtempfile<<L<<"     "<<S<<"     "<<E<<"     "<<D<<endl;
        }
    }
    Rtempfile.close();
    Rfile.close();
    ofstream Routfile("Routes.txt",ios::out|ios::trunc);
    fstream Rinfile("temp.txt");
    while(!Rinfile.eof())
    {
        Rinfile>>L>>S>>E>>D;
        Routfile<<L<<"     "<<S<<"     "<<E<<"     "<<D<<endl;
    }
    Routfile.close();
    Rinfile.close();
    InitializeGraph(g_sMap);//根据文件再次初始化g_sMap;
}
void ChangeBusInfo()//修改公交信息界面
{
    int num;
    cout<<"Tip:该功能可以修改公交的名称和(起点、终点)--同时修改上行/下行."<<endl;
    cout<<endl;
    cout<<"-----------------------"<<endl;
    cout<<endl;
    cout<<"  1.修改公交名称"<<endl;
    cout<<"  2.修改站点信息"<<endl;
    cout<<endl;
    cout<<"-----------------------"<<endl;
    cout<<endl;
    do
    {
        cout<<"请输入要使用的功能:";
        cin>>num;
    }while(num>2||num<1);
    cout<<endl;
    switch(num)
    {

        case 1:
            {
                ChangeBusName();
                break;
            }
        case 2:
            {
                ChangeBusStartandEnd();
                break;
            }
    }
}
void ChangeBusName()//修改公交名称
{
    string BusName;
    string NewName;
    string te;
    string a;
    string b;
    do
    {
        system("cls");
        cout<<"Tip:输入公交线路数字即可"<<endl;
        cout<<endl;
        for(int i=0;i<g_sMap.bus_num;i++)
        {
        if(i==0)
        {
            cout<<"库中公交:"<<g_sMap.buses[i].name;
        }
        else
        {
            cout<<"  "<<g_sMap.buses[i].name;
        }
        }
        cout<<endl;
        cout<<endl;
        cout<<"请输入要修改的公交数字:"<<endl;
        cout<<endl;
        cout<<"请输入新的公交数字:"<<endl;
        gotoxy(23,4);
        cin>>BusName;
        gotoxy(19,6);
        cin>>NewName;
        a=BusName+"上行";
        b=NewName+"上行";
        te=BusName+"下行";
    }while(FindBus(a)==-1||FindBus(b)!=-1);
    cout<<endl;
    fstream in;
    ofstream outfile;
    in.open("Buses.txt");
    outfile.open("temp.txt",ios::out|ios::trunc);
    string B;
    int S,E;
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        in>>B>>S>>E;
        if(B!=a&&B!=te)
        {
            outfile<<B<<endl;
            outfile<<S<<endl;
            outfile<<E<<endl;
        }
        else
        {
            if(B==a)
            {
                outfile<<b<<endl;
                outfile<<S<<endl;
                outfile<<E<<endl;
            }
            else
            {
                outfile<<NewName+"下行"<<endl;
                outfile<<S<<endl;
                outfile<<E<<endl;
            }
        }
    }
    in.close();
    outfile.close();
    ofstream out;
    fstream infile;
    out.open("Buses.txt",ios::out|ios::trunc);
    infile.open("temp.txt");
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        infile>>B>>S>>E;
        out<<B<<endl;
        out<<S<<endl;
        out<<E<<endl;
    }
    infile.close();
    out.close();
    cout<<"  修改成功!"<<endl;
    cout<<endl;
    InitializeGraph(g_sMap);//根据文件再次初始化g_sMap;
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        if(i==0)
        {
            cout<<"修改后库中公交:"<<g_sMap.buses[i].name;
        }
        else
        {
            cout<<"  "<<g_sMap.buses[i].name;
        }
    }
    cout<<endl;
    cout<<endl;
}
void ChangeBusStartandEnd()//修改公交起点、终点
{
    string BusName;
    string Start,End;
    do
    {
        system("cls");
        cout<<"Tip:本功能是修改已有公交起始点,输入公交数字即可,输入起点、终点输入库中已有站点."<<endl;
        cout<<endl;
        OutPutAllBusName();
        cout<<endl;
        cout<<"请输入要修改起点、终点的公交名:";
        cin>>BusName;
        cout<<"请输入新起点:";
        cin>>Start;
        cout<<"请输入新终点:";
        cin>>End;
    }while(FindBus(BusName+"上行")==-1||FindStation(Start)==-1||FindStation(End)==-1);
    int nB=FindBus(BusName+"上行");
    int s=g_sMap.buses[nB].Start;
    int e=g_sMap.buses[nB].End;
    int nS=FindStation(Start);
    int nE=FindStation(End);
    int L,S,E,D;
    //修改Routes.txt文件
    fstream in;
    ofstream out;
    in.open("Routes.txt");
    out.open("temp.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.route_num;i++)
    {
        in>>L>>S>>E>>D;
        if(L!=nB||L!=(nB+1))
        {
            out<<L<<"     "<<S<<"     "<<E<<"     "<<D<<endl;
        }
        else
        {
            if(L==nB&&S==s)
            {
                out<<L<<"     "<<nS<<"     "<<E<<"     "<<D<<endl;
            }
            else if(L==nB&&E==e)
            {
                out<<L<<"     "<<S<<"     "<<nE<<"     "<<D<<endl;
            }
            else
            {
                out<<L<<"     "<<S<<"     "<<E<<"     "<<D<<endl;
            }
            if(L==(nB+1)&&S==e)
            {
                out<<L<<"     "<<nE<<"     "<<E<<"     "<<D<<endl;
            }
            else if(L==(nB+1)&&E==s)
            {
                out<<L<<"     "<<S<<"     "<<nS<<"     "<<D<<endl;
            }
            else
            {
                out<<L<<"     "<<S<<"     "<<E<<"     "<<D<<endl;
            }
        }
    }
    in.close();
    out.close();
    ofstream outr;
    fstream inr;
    inr.open("temp.txt");
    outr.open("Routes.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.route_num;i++)
    {
        inr>>L>>S>>E>>D;
        outr<<L<<"     "<<S<<"     "<<E<<"     "<<D<<endl;
    }
    inr.close();
    outr.close();
    //修改Buses.txt文件
    fstream ins;
    ofstream outfile;
    ins.open("Buses.txt");
    outfile.open("temp.txt",ios::out|ios::trunc);
    string B;
    string up=BusName+"上行";
    string down=BusName+"下行";
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        ins>>B>>S>>E;
        if(B!=up&&B!=down)
        {
            outfile<<B<<endl;
            outfile<<S<<endl;
            outfile<<E<<endl;
        }
        else
        {
            if(B==up)
            {
                outfile<<B<<endl;
                outfile<<nS<<endl;
                outfile<<nE<<endl;
            }
            else
            {
                outfile<<B<<endl;
                outfile<<nE<<endl;
                outfile<<nS<<endl;
            }
        }
    }
    ins.close();
    outfile.close();
    ofstream outt;
    fstream infile;
    outt.open("Buses.txt",ios::out|ios::trunc);
    infile.open("temp.txt");
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        infile>>B>>S>>E;
        outt<<B<<endl;
        outt<<S<<endl;
        outt<<E<<endl;
    }
    infile.close();
    outt.close();
    InitializeGraph(g_sMap);
    OutPutAllBusName();
    cout<<endl;
}
void MenuForStation()//操作站点界面
{
    int num;
    cout<<"-----------------------"<<endl;
    cout<<endl;
    cout<<"  1.添加站点"<<endl;
    cout<<"  2.删除站点"<<endl;
    cout<<"  3.修改站点信息"<<endl;
    cout<<"  4.返回管理员菜单"<<endl;
    cout<<endl;
    cout<<"-----------------------"<<endl;
    do
    {
        cout<<"请输入要使用功能:";
        cin>>num;
    }while(num>4||num<1);
    system("cls");
    if(num!=4)
    {
        switch(num)
        {
            case 1:
                {
                    AddStation();
                    system("pause");
                    MenuForStation();
                    break;
                }
            case 2:
                {
                    DeleteStation();
                    system("pause");
                    MenuForStation();
                    break;
                }
            case 3:
                {
                    ChangeStationInfo();
                    system("pause");
                    MenuForStation();
                    break;
                }
        }
    }
}
void AddStation()//添加站点
{
    cout<<"Tip:该功能是想Station数组中添加新站名."<<endl;
    cout<<endl;
    for(int i=0;i<g_sMap.station_num;i++)
    {
        if(i==0)
            cout<<"当前库中站点:"<<g_sMap.stations[i].name;
        else
            cout<<"  "<<g_sMap.stations[i].name;
    }
    cout<<endl;
    cout<<endl;
    string StationName;
    do
    {
        cout<<"请输入要添加的新的站名:";
        cin>>StationName;
    }while(FindStation(StationName)!=-1);
    int n=GetStation(StationName);
    ofstream out;
    out.open("Stations.txt",ios::app);
    out<<StationName<<endl;
    out.close();
    cout<<endl;
    cout<<"   添加成功!"<<endl;
    cout<<endl;
    for(int i=0;i<g_sMap.station_num;i++)
    {
        if(i==0)
            cout<<"当前库中站点:"<<g_sMap.stations[i].name;
        else
            cout<<"  "<<g_sMap.stations[i].name;
    }
    cout<<endl;
}
void DeleteStation()//删除站点
{
    cout<<"Tip:该功能是想Station数组中删除已有站名."<<endl;
    cout<<endl;
    for(int i=0;i<g_sMap.station_num;i++)
    {
        if(i==0)
            cout<<"当前库中站点:"<<g_sMap.stations[i].name;
        else
            cout<<"  "<<g_sMap.stations[i].name;
    }
    cout<<endl;
    cout<<endl;
    string StationName;
    do
    {
        cout<<"请输入要删除的已有站名:";
        cin>>StationName;
    }while(FindStation(StationName)==-1);
    string te;
    fstream in;
    ofstream out;
    in.open("Stations.txt");
    out.open("temp.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.station_num;i++)
    {
        in>>te;
        if(te!=StationName)
        {
            out<<te<<endl;
        }
    }
    in.close();
    out.close();
    fstream inr;
    inr.open("temp.txt");
    ofstream outr;
    outr.open("Stations.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.station_num-1;i++)
    {
        inr>>te;
        outr<<te<<endl;
    }
    inr.close();
    outr.close();
    cout<<endl;
    cout<<"   删除成功!"<<endl;
    cout<<endl;
    InitializeGraph(g_sMap);
    for(int i=0;i<g_sMap.station_num;i++)
    {
        if(i==0)
            cout<<"删除后库中站点:"<<g_sMap.stations[i].name;
        else
            cout<<"  "<<g_sMap.stations[i].name;
    }
    cout<<endl;
}
void ChangeStationInfo()//改变站点名称
{
    string StationName;
    string NewName;
    do
    {
        system("cls");
        cout<<"Tip:该功能是想Station数组中修改站名."<<endl;
        cout<<endl;
        for(int i=0;i<g_sMap.station_num;i++)
        {
            if(i==0)
                cout<<"当前库中站点:"<<g_sMap.stations[i].name;
            else
                cout<<"  "<<g_sMap.stations[i].name;
        }
        cout<<endl;
        cout<<endl;
        cout<<"请输入要修改的站名:"<<endl;;
        cout<<endl;
        cout<<"请输入新名:"<<endl;
        gotoxy(19,4);
        cin>>StationName;
        gotoxy(11,6);
        cin>>NewName;
    }while(FindStation(StationName)==-1||FindStation(NewName)!=-1);
    int index=FindStation(StationName);
    fstream in;
    ofstream out;
    in.open("Stations.txt");
    out.open("temp.txt",ios::out|ios::trunc);
    string te;
    for(int i=0;i<g_sMap.station_num;i++)
    {
        in>>te;
        if(te!=StationName)
        {
            out<<te<<endl;
        }
        else
        {
            out<<NewName<<endl;
        }
    }
    in.close();
    out.close();
    fstream inr;
    ofstream outr;
    inr.open("temp.txt");
    outr.open("Stations.txt",ios::out|ios::trunc);
    for(int i=0;i<g_sMap.station_num;i++)
    {
        inr>>te;
        outr<<te<<endl;
    }
    inr.close();
    outr.close();
    cout<<endl;
    cout<<"    修改成功!"<<endl;
    g_sMap.stations[index].name=NewName;
    cout<<endl;
    for(int i=0;i<g_sMap.station_num;i++)
    {
        if(i==0)
            cout<<"当前库中站点:"<<g_sMap.stations[i].name;
        else
            cout<<"  "<<g_sMap.stations[i].name;
    }
    cout<<endl;
}
void ChangeInfo()//管理员账户、密码更改函数
{
    string Administrator,Password;
    ifstream change;
    change.open("ADandPA.txt",ios::in);
    change>>Administrator;
    change>>Password;
    change.close();
    cout<<"Tip:该功能是修改管理员账号密码,修改后永久保存!"<<endl;
    cout<<endl;
    cout<<"当前用户名:"<<Administrator<<"   当前密码:"<<Password<<endl;
    ofstream out;
    out.open("ADandPA.txt",ios::trunc);
    cout<<endl;
    cout<<"请输入新的用户名:"<<endl;
    cout<<"请输入新的密码:"<<endl;
    gotoxy(17,4);
    cin>>Administrator;
    gotoxy(15,5);
    cin>>Password;
    out<<Administrator<<endl;
    out<<Password<<endl;
    out.close();
    cout<<endl;
    cout<<endl;
    cout<<"更改用户名、密码成功！"<<endl;
    cout<<endl;
}
void MenuForCustomer()
{
    system("cls");
    int num;
    cout<<"------------------  乘客,你好！ ------------------"<<endl;
    cout<<endl;
    cout<<"--------     欢迎使用本市公交管理系统     --------"<<endl;
    cout<<endl;
    cout<<"       1.查询本市所有公交"<<endl;
    cout<<"       2.查询本市所有站点"<<endl;
    cout<<"       3.查询本市某公交具体线路"<<endl;
    cout<<"       4.查询本市某站点相关信息"<<endl;
    cout<<"       5.查询本市两站点如何可达(最多换乘1次)"<<endl;
    cout<<"       6.返回主菜单"<<endl;
    cout<<endl;
    cout<<"--------------------------------------------------"<<endl;
    do
    {
        cout<<"请输入您要使用的功能(数字):";
        cin>>num;
    }while(num>5||num<1);
    system("cls");
    switch(num)
    {
        case 1:
            {
                OutPutAllBusName();
                system("pause");
                MenuForCustomer();
                break;
            }
        case 2:
            {
                OutPutAllStationName();
                system("pause");
                MenuForCustomer();
                break;
            }
        case 3:
            {
                OutPutBusRoute();
                system("pause");
                MenuForCustomer();
                break;
            }
        case 4:
            {
                OutPutStationInf();
                system("pause");
                MenuForCustomer();
                break;
            }
        case 5:
            {
                SearchRoute();
                system("pause");
                MenuForCustomer();
                break;
            }
        case 6:
            {
                MainMenu();
                break;
            }
    }
}
void OutPutBusRoute()
{
    string BusName;
    cout<<"当前库中的公交线路名:";
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        if(i==0)
            cout<<g_sMap.buses[0].name;
        else
            cout<<" "<<g_sMap.buses[i].name;
    }
    cout<<endl;
    do
    {
        cout<<"请输入要查询的公交线路(名字):";
        cin>>BusName;
    }while(FindBus(BusName)==-1);
    TraverseBusRoute(BusName);
}
void OutPutStationInf()   //输出该站点所经过公交线路
{
    string StationName;
    cout<<"当前库中的站点名:"<<endl;
    for(int i=0;i<g_sMap.station_num;i++)
    {
        cout<<g_sMap.stations[i].name<<endl;
    }
    cout<<endl;
    do
    {
        cout<<"请输入要查询的站点:";
        cin>>StationName;
    }while(FindStation(StationName)==-1);
    int nStation=FindStation(StationName);
    Route *temp=g_sMap.stations[nStation].routes;
    int count=0;
    while(temp!=NULL)
    {
        ++count;
        cout<<g_sMap.buses[temp->bus].name<<"    开往下一站:"<<g_sMap.stations[temp->station].name<<"    距离:"<<temp->distance<<"（米）    公交终点站:"<<g_sMap.stations[g_sMap.buses[temp->bus].End].name<<endl;
        temp=temp->next;
    }
    cout<<endl;
    int flag=-1;
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        if(g_sMap.buses[i].End==nStation)
        {
            flag=i;
            break;
        }
    }
    if(flag==-1)
        cout<<"该站点共有"<<count<<"条线路经过"<<endl;
    else
    {
        cout<<"该站点是"<<g_sMap.buses[flag].name<<"的终点站"<<endl;
        cout<<endl;
        cout<<"该站点共有"<<count+1<<"条线路进过"<<endl;
    }
}
void SearchRoute()//根据用户输入起点、终点判断是否有路径，若有则输出
{
    string stationStart,stationEnd;
    int stationS,stationE;
    do
    {
        system("cls");
        cout<<"当前库中的站点名:"<<endl;
        for(int i=0;i<g_sMap.station_num;i++)
        {
            cout<<g_sMap.stations[i].name<<endl;
        }
        cout<<endl;
        cout<<"请输入要查询的起点:"<<endl;
        cout<<"请输入要查询的终点:"<<endl;
        gotoxy(19,g_sMap.station_num+2);
        cin>>stationStart;
        gotoxy(19,g_sMap.station_num+3);
        cin>>stationEnd;
        stationS=FindStation(stationStart);
        stationE=FindStation(stationEnd);
        if(stationS==-1||stationE==-1)
        {
            cout<<"输入站点在库中不存在"<<endl;
        }
    }while(FindStation(stationStart)==-1||FindStation(stationEnd)==-1);
    if(stationS==stationE)
    {
            cout<<"输入起点、终点一致,无需查询."<<endl;
    }
    else
    {
        string Path[10];
        bool Has=QueryRoutes(stationStart,stationEnd,Path);
        if(Has)
        {
            for(int i=0;Path[i]!=stationEnd;i++)
            {
                if(i==0)
                   cout<<Path[i];
                else
                    cout<<"--->>"<<Path[i];
            }
            cout<<"--->>"<<stationEnd<<endl;
        }
        else
        {
            cout<<"未能找到从"<<stationStart<<"到"<<stationEnd<<"的路线."<<endl;
        }
    }
}

