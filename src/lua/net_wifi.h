#ifndef NET_WIFI_H_
#define NET_WIFI_H_
#include "lauxlib.h"
#include "lua.h"
int lwifi_scan(lua_State *L);

int lwifi_setup(lua_State *L);
#endif  // NET_WIFI_H_