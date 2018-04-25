#ifndef LAR_H 
#define LAR_H

extern "C" {
  #include "lua.h"
  #include "lauxlib.h"
  #include "lualib.h"
}

#include "lunar.h"

class Lar{
	lua_Number m_num;
public:
  static const char className[];
  static Lunar<Lar>::RegType methods[];

  Lar(lua_State *L)      { m_num = luaL_checknumber(L, 1); }
  int readNum (lua_State *L) { lua_pushnumber(L, m_num); return 1; }
  ~Lar() { }
};

const char Lar::className[] = "Lar";

Lunar<Lar>::RegType Lar::methods[] = {
  LUNAR_DECLARE_METHOD(Lar, deposit),
  LUNAR_DECLARE_METHOD(Lar, readNum),
  {0,0}
};

#endif