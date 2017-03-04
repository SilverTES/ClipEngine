//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------

#include "FileData.h"

FileData::FileData()
{
    //ctor
}

FileData::~FileData()
{
    //dtor
}

nlohmann::json FileData::loadJsonFile(std::string const filename)
{
    std::string jdata("");

    std::ifstream jsonFile(filename);
    if (!jsonFile.is_open())
    {

        return mlog("JSON file not found ! \n");
    }
    else
    {
        std::string line("");
        while (!jsonFile.eof())
        {
            getline( jsonFile, line); // lecture d'une ligne de fichier
            jdata += line;
        }
    }
    jsonFile.close();
    mlog("Json File Loaded : "+filename+"\n");
    return nlohmann::json::parse(jdata);
}

void FileData::saveJsonFile(std::string const filename, nlohmann::json data)
{
    std::ofstream jsonFile(filename);
    if (jsonFile.is_open())
    {
        jsonFile << data.dump(4); // permet de cr�er les indentations �l�ments , sinon il serait align� sur une seule m�me ligne !
    }
    else
    {
        mlog("JSON file save impossible ! \n");
    }
    jsonFile.close();
    mlog("Json File Saved : "+filename+"\n");
}

// In Lua 5.0 reference manual is a table traversal example at page 29.
void FileData::PrintTable(lua_State *L)
{
    lua_pushnil(L);

    while(lua_next(L, -2) != 0)
    {
        if(lua_isstring(L, -1))
            //printf("%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
            std:: cout << lua_tostring(L, -2) << " = " << lua_tostring(L, -1) << "\n";
        else if(lua_isnumber(L, -1))
            //printf("%s = %d\n", lua_tostring(L, -2), lua_tonumber(L, -1));
            std:: cout << lua_tostring(L, -2) << " = " << lua_tostring(L, -1) << "\n";
        else if(lua_istable(L, -1))
        {
            PrintTable(L);
        }
        lua_pop(L, 1);
    }
}
