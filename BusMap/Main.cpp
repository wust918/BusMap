#include "Menu.h"
extern BusMap g_sMap;
int main()
{
    InitializeGraph(g_sMap);
    LoginScreen();
    return 0;
}
