#ifndef BUSMAP_H_INCLUDED
#define BUSMAP_H_INCLUDED
#include "Model.h"
int CountLines(const char *filename);//获取对应txt文件行数
template<typename T>
T* realloc_p(T* a,int length);//重写realloc函数
void InitializeGraph(BusMap &g_sMap);//用于实现创建图,初始化公交地图数据

int FindBus(string bus);//查找库中公交名，存在返回其数组编号，不存在返回-1
int FindStation(string station);//查找库中站名，存在返回其数组编号，不存在返回-1

int GetBus(string bus);//得到公交序号,若该公交不存在则建立该公交
int GetStation(string station);//得到站名序号,若该站点不存在则建立该站点

bool AddRoute(int Line_number, int nStart, int nEnd, int distance);//添加路径

void TraverseBusRoute(string bus);//遍历指定公交线路
bool TraverseStationByBusRoute(int nStation,int nbus);//搜寻该站点的某条公交线路,找到终点返回true
bool HasPath(int nStart, int nEnd, bool *visited,string *p,int index);
bool QueryRoutes(string pStart, string pEnd,string *p);//查询两个站点公交路线
#endif // BUSMAP_H_INCLUDED
