#include "BusMap.h"
BusMap g_sMap;
int CountLines(const char *filename)
{
     ifstream ReadFile;
     int n=0;
     string temp;
     ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
     if(ReadFile.fail())//文件打开失败:返回0
     {
         return 0;
     }
     else//文件存在
     {
         while(getline(ReadFile,temp))
         {
                 n++;
         }
         ReadFile.close();
         return n;
     }
}
template<typename T>
T* realloc_p(T* a,int length)
{
    T* t;
    t=new T[length];
    memcpy(t,a,(length-1)*sizeof(T));
    delete[] a;
    return t;
}
void InitializeGraph(BusMap &g_sMap)//根据文件数据构造图
{
    int STATION_NUM=CountLines("Stations.txt");
    g_sMap.station_num=STATION_NUM;

    ifstream inStation;
    g_sMap.stations=new Station[STATION_NUM];
    inStation.open("Stations.txt",ios::in);
    if(!inStation.is_open())
    {
        cout<<"can't open Stations.txt!"<<endl;
        exit(-1);
    }
    else
    {
    for(int i=0;i<STATION_NUM;i++)
    {
        inStation>>g_sMap.stations[i].name;
        g_sMap.stations[i].routes=NULL;
    }
    }
    inStation.close();

    int BUS_NUM=CountLines("Buses.txt")/3;
    g_sMap.bus_num=BUS_NUM;
    ifstream inBus;
    g_sMap.buses=new Bus[BUS_NUM];
    inBus.open("Buses.txt",ios::in);
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        inBus>>g_sMap.buses[i].name>>g_sMap.buses[i].Start>>g_sMap.buses[i].End;
    }
    inBus.close();

    int ROUTE_NUM=CountLines("Routes.txt");
    g_sMap.route_num=ROUTE_NUM;
    ifstream inRoute;
    inRoute.open("Routes.txt",ios::in);
    int Line_num;//线路编号，公交数组的下标
    int Start;//起始点
    int End;//终止点
    int Distance;//两站距离
    for(int i=0;i<g_sMap.route_num;i++)
    {
        inRoute>>Line_num>>Start>>End>>Distance;
        AddRoute(Line_num,Start,End,Distance);
    }
}

int FindBus(string nbus)    //查找公交数组中公交名,返回公交编号
{
    for(int i=0;i<g_sMap.bus_num;i++)
    {
        if(g_sMap.buses[i].name==nbus)
            return i;
    }
    return -1;
}
int FindStation(string nstation)  //查找库中站名
{
    for(int i=0;i<g_sMap.station_num;i++)
    {
        if(g_sMap.stations[i].name==nstation)
        {
            return i;
        }
    }
    return -1;
}
int GetBus(string bus)  //得到公交序号,若该公交不存在则建立该公交
{
    int  nBus=FindBus(bus);
    if(nBus==-1)
    {
        g_sMap.buses=(Bus*)realloc_p(g_sMap.buses,g_sMap.bus_num+1);
        Bus* pBus = g_sMap.buses + g_sMap.bus_num;
		pBus->name = bus;
		pBus->Start = pBus->End = -1;
		nBus=g_sMap.bus_num;//数组从0开始，直接赋值，没有第g_sMap.bus_num号元素
        g_sMap.bus_num++;
    }
    return nBus;
}
int GetStation(string station)  //得到站名序号,若该站点不存在则建立该站点
{
    int  nStation=FindStation(station);
    if(nStation==-1)
    {
        g_sMap.stations=(Station*)realloc_p(g_sMap.stations,g_sMap.station_num+1);
        Station* pStation=g_sMap.stations+g_sMap.station_num;
        pStation->name=station;
        pStation->routes=NULL;
        nStation=g_sMap.station_num;//数组从0开始，直接赋值，没有第g_sMap.station_num号元素
        g_sMap.station_num++;
    }
    return nStation;
}

bool AddRoute(int Line_number, int nStart, int nEnd, int distance)//添加公交线路图的边
{
        Station *TempStation=&g_sMap.stations[nStart];
        Route *TempRoute=TempStation->routes;
        while(TempRoute!=NULL&&TempRoute->next!=NULL) //检查该开始站点是否存在这条线路
        {
            if(TempRoute->bus==Line_number)     //理论上公交经过站点只有一条线路,只需判断该站点是否存在该公交线路即可
            {
                return false;
            }
            TempRoute=TempRoute->next;
        }
        Route *temp=(Route*)malloc(sizeof(Route));
        temp->bus=Line_number;
        temp->station=nEnd;
        temp->distance=distance;
        temp->next=NULL;
        if(TempRoute==NULL)
        {
            TempStation->routes=temp;
        }
        else
        {
            TempRoute->next=temp;
        }
        return true;
}

void TraverseBusRoute(string bus)//按照公交名输出线路
{
    int nBus=FindBus(bus);
    int nStationStart=g_sMap.buses[nBus].Start;
    TraverseStationByBusRoute(nStationStart,nBus);
}

bool TraverseStationByBusRoute(int nStation,int nBus)//得到公交线路，并输出
{
    if(nStation==g_sMap.buses[nBus].Start)
    {
        cout<<g_sMap.stations[nStation].name;
    }
    else
    {
        cout<<"-->"<<g_sMap.stations[nStation].name;
        if(nStation==g_sMap.buses[nBus].End)
        {
            cout<<endl;
            return true;
        }
    }
    Route *temp=g_sMap.stations[nStation].routes;
    int tempStation;
    while(temp!=NULL||g_sMap.buses[nBus].End==nStation)
    {
        if(temp->bus==nBus)
        {
            tempStation=temp->station;
            break;
        }
        temp=temp->next;
    }
    if(nStation!=g_sMap.buses[nBus].End)
        TraverseStationByBusRoute(tempStation,nBus);
}
bool HasPath(int nStart, int nEnd, bool *visited,string *p,int index)//判断是否存在路径
{
	bool bHas=false;
	if (!visited[nStart])
	{
		visited[nStart] = true;
		p[index] = g_sMap.stations[nStart].name;
	}
	if (nStart == nEnd)
	{
		return true;
	}
	Route *route = g_sMap.stations[nStart].routes;
	while (route != NULL)
	{
		if (!visited[route->station])
		{
			bHas = HasPath(route->station, nEnd, visited, p, index + 1);
		}
		if (bHas == true)
			return true;
		route = route->next;
	}
	return false;
}
bool QueryRoutes(string pStart, string pEnd,string *p)//查询两个站点公交路线
{
	bool *visited = (bool*)malloc(sizeof(bool)*g_sMap.station_num);
	for (int i = 0; i < g_sMap.station_num;i++)
	{
		visited[i] = false;
	}
	int nStart = GetStation(pStart);
	int nEnd = GetStation(pEnd);
	return HasPath(nStart,nEnd,visited,p,0);
}
