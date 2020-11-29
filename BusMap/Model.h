#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
#include<string>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<conio.h>
#include<stdlib.h>
#include<cstring>
#include<vector>
#include<windows.h>
using namespace std;
typedef struct Bus
{
	string name;//公交名
	int Start;//起始站点
	int End;//终点站点
}Bus;
typedef struct Station
{
	string name;//站点名
	struct Route* routes;//邻接矩阵，该站点所经公交线路，及邻接点
}Station;
typedef struct Route
{
    int bus;//公交编号
    int station;//站点编号
	int distance;//两站点距离
	bool *visited;
	struct Route *next;//下一条边
}Route;
typedef struct BusMap
{
	Bus* buses;//公交线路数组,只包含所有公交名，以及公交线路起始站、终点站，不含公交具体线路
	Station* stations;//站点数组,包含所有站名，以及各站所经过的公交线路
	int station_num;//站点数
	int bus_num;//公交数
	int route_num;//边数
}BusMap;
#endif //MODEL_H_INCLUDE

