#include "net.h"
#include "lua.h"
#include "net_wifi.h"
#include "lauxlib.h"


static int lwifi_test(lua_State *L) {
  lua_pushstring(L, "hello world");
  return 1;
}

static const luaL_Reg net_map[] = {
    {"setup", lwifi_setup},
    {"scan", lwifi_scan},
    {"test", lwifi_test},
    {NULL, NULL}
};

LUAMOD_API int(luaopen_net)(lua_State *L) {
  luaL_newlib(L, net_map);
  lua_setglobal(L, "net");
  return 1;
}