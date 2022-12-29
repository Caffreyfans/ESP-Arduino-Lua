#include "cc.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "lauxlib.h"
#include "lua.h"
#include "string.h"

int lwifi_setup(lua_State *L) {
  static bool setup = false;
  lua_pushstring(L, "wifi setup");
  if (setup == false) {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    setup = true;
  }

  return 1;
}

int lwifi_scan(lua_State *L) {
  wifi_ap_record_t *list;
  uint16_t count, i;
  u8_t table = 0;
  char auth[13];
  // Check if user wants scan's result as a table, or wants scan's result
  // on the console
  // if (lua_gettop(L) == 1) {
  //   luaL_checktype(L, 1, LUA_TBOOLEAN);
  //   if (lua_toboolean(L, 1)) {
  //     table = 1;
  //   }
  // }

  uint16_t number = 16;
  wifi_ap_record_t ap_info[16];
  uint16_t ap_count = 0;
  memset(ap_info, 0, sizeof(ap_info));

  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_start();
  esp_wifi_scan_start(NULL, true);
  esp_wifi_scan_get_ap_records(&number, ap_info);
  esp_wifi_scan_get_ap_num(&ap_count);

  for (int i = 0; i < ap_count; i++) {
    lua_createtable(L, 0, ap_count + 1);
    lua_pushstring(L, (char *)ap_info[i].ssid);
    lua_setfield(L, -2, "ssid");

    lua_pushinteger(L, ap_info[i].rssi);
    lua_setfield(L, -2, "rssi");
    printf("%s\n", ap_info[i].ssid);
  }
  return 1;
}