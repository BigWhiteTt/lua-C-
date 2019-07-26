// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>

extern "C"
{
#include "lua.h"   
#include "lauxlib.h"  
#include "lualib.h"  
}

using namespace std;

int main()
{
	lua_State *L = luaL_newstate();
	if (L == NULL) {
		system("pause");
		return 0;
	}

	int bRet = luaL_loadfile(L, "C:\\Users\\wanteng\\Desktop\\LUATEST\\test.lua");
	if (bRet) {
		cout << "load file error" << endl;
		system("pause");
		return 0;
	}

	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet) {
		cout << "pcall error" << endl;
		system("pause");
		return 0;
	}

	lua_getglobal(L, "str");
	string str = lua_tostring(L, -1);
	cout << "str = " << str.c_str() << endl;

	lua_getglobal(L, "tbl");

	lua_pushstring(L, "aaaaaaaaaaaaaaa");
	lua_pushstring(L, "bbbbbbbbbbbbbbb");
	lua_setfield(L, -3, "name");

	lua_getfield(L, -2, "name");
	str = lua_tostring(L, -1);
	cout << "tbl:name = " << str.c_str() << endl;

	lua_getglobal(L, "sub");
	lua_getglobal(L, "add");
	lua_pushnumber(L, 10);
	lua_pushnumber(L, 20);
	int iRet = lua_pcall(L, 2, 1, 0);
	if (iRet) {
		const char *pErrorMsg = lua_tostring(L, -1);
		cout << pErrorMsg << endl;
		lua_close(L);
		system("pause");
		return 0;
	}
	if (lua_isnumber(L, -1)) {
		double fValue = lua_tonumber(L, -1);
		cout << "Result is " << fValue << endl;
	}
	lua_close(L);
	system("pause");
	return 0;
}

