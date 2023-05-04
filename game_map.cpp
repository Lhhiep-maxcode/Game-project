#include "game_map.h"
#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

void GameMap::LoadMap(char* name) // lưu map từ file vào mảng
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb"); //fp thành file
    if(fp == NULL) return;

    game_map.max_x = 0;
    game_map.max_y = 0;
    for(int i = 0; i < MAX_MAP_Y; i++){
        for(int j = 0; j < MAX_MAP_X; j++){
            fscanf(fp, "%d", &game_map.tile[i][j]); // lưu dần giá trị của file vào mảng game_map.tile

            int val = game_map.tile[i][j];
            if(val > 0)
            {
                if(j > game_map.max_x)
                {
                    game_map.max_x = j; //kéo dài map *update*
                }
                if(i > game_map.max_y)
                {
                    game_map.max_y = i;
                }
            }
        }
    }
    game_map.max_x = (game_map.max_x +1 )*TILE_SIZE; //tính độ dài theo pixel
    game_map.max_y = (game_map.max_y +1 )*TILE_SIZE;

    game_map.start_x = 0; //nơi bắt đầu
    game_map.start_y = 0;

    game_map.file_name = name;
    fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen) // load ảnh cục đất
{
    char file_img[30]; // tên file (giống string)
    FILE* fp = NULL;

    for(int i = 0; i < MAX_TILES; i++)
    {
        sprintf_s(file_img, "map/%d.png", i); //file_img chuyển thành tên file ảnh

        fopen_s(&fp, file_img, "rb"); // mở file ảnh
        if(fp == NULL) continue;
        fclose(fp);
        tile_mat[i].loadImg(file_img, screen); //tile_mat[i] = texture của ảnh (load sẵn lên)
    }
}

void GameMap::DrawMap(SDL_Renderer* screen) // vẽ map
{
    int x1 = 0; //vẽ từ x1 -> x2 (có thể thừa ra tí)
    int x2 = 0;

    int y1 = 0; //vẽ từ y1 -> y2 (có thể thừa ra tí)
    int y2 = 0;

    int map_x, map_y; //chỉ số của tile

    map_x = game_map.start_x/TILE_SIZE;  //tính cục đất thứ j để vẽ
    x1 = (game_map.start_x % TILE_SIZE)*(-1); //tính điểm bắt đầu vẽ trên màn hình (pixel)
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map.start_y/TILE_SIZE; //tính cục đất thứ i để vẽ
    y1 = (game_map.start_y % TILE_SIZE)*(-1);
    y2 = y1 + SCREEN_WIDTH + (y1 == 0 ? 0 : TILE_SIZE);

    for(int i = y1; i < y2; i+= TILE_SIZE)
    {
        map_x = game_map.start_x/TILE_SIZE; //khi hết một hàng
        for(int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map.tile[map_y][map_x];

            if(val > 0 && val < 20)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;//sang ô tiếp theo
        }
        map_y++;
    }
}
void GameMap::RemoveTile(int y, int x)
{
    game_map.tile[y][x] = 0;
}
