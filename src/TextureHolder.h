#pragma once
#ifndef TEXTUE_HOLDER_H
#define TEXTURE_HOLDER_H
#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;
class TextureHolder
{
private:
    //a map container from STL
    //that holds ralated pairs of string and texture
    map<string,Texture> m_Texture;
    static TextureHolder* m_s_Instance;

public:
    TextureHolder();
    static Texture& GetTexture(string const& filename);
};

#endif