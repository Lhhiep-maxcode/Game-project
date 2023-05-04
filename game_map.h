#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Commonfunc.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMat : public baseobject
{
    public:
        TileMat(){}
        virtual ~TileMat(){}

    protected:

    private:
};

class GameMap
{
public:
    GameMap(){}
    ~GameMap(){}
    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;} //để lấy map (vì đang ở dạng private)
    void SetMap(Map& map_data) {game_map = map_data;} //lấy dữ liệu map mới
    void RemoveTile(int y, int x);
private:
    Map game_map;
    TileMat tile_mat[MAX_TILES]; //mảng lưu cục đất

};

#endif // GAME_MAP_H
