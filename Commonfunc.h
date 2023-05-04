
#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
//static bool crash = false;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int RENDER_DRAW_COLOR = 255;
const int FRAMES_PER_SECOND = 45;

#define TILE_SIZE 64
#define BLANK_TILE 0
#define MAX_MAP_X 405
#define MAX_MAP_Y 10
#define ROCKET_NUM 5
#define STATE_ROCKET 11
#define STATE_COIN 10
#define STATE_HEART 12

typedef struct Input
{
    int left;
    int right;
    int up; //rơi từ trên xuống
    int down;
    int jump;
    int idle;
};

typedef struct Map
{
    int start_x; // vị trí đầu (pixel)
    int start_y; //___________________
    int max_x; //vị trí cuối (pixel)
    int max_y; //___________________
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect &object1, const SDL_Rect &object2);
}

#endif // COMMONFUNC_H

