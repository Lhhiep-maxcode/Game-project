#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "Explosion.h"

#define GRAVITY_SPEED 1
#define MAX_FALL_SPEED 15
#define PLAYER_SPEED 5
#define PLAYER_JUMP_VALUE 10

class MainObject : public baseobject
{
    public:
        MainObject();
        virtual ~MainObject();

        enum WalkType
        {
            IDLE_RIGHT = 0,
            IDLE_LEFT = 1,
            WALK_RIGHT = 2,
            WALK_LEFT = 3,
        };

        //xử lý lệnh và frame
        bool loadImg(std::string path, SDL_Renderer* screen, int num);
        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
        void set_clips();
        void set_come_back_time(int x) {come_back_time = x;}

        //xử lý di chuyển
        bool MovePlayer(Map& map_data);
        bool CheckMapLimits(Map& map_data);
        void SetMapXY(const int mapp_x, const int mapp_y) {map_x = mapp_x; map_y = mapp_y;} //giá trị x, y của map theo nhân vật
        void CenterEntityOnMap(Map& map_data);
        SDL_Rect GetRectFrame();
        int get_width_frame() const {return width_frame;} //cần khi check va chạm
        int get_height_frame() const {return height_frame;} //cần khi check va chạm

        void set_bullet_list(std::vector<BulletObject*> bullet_list) //nạp đạn
        {
            p_bullet_list = bullet_list;
        }
        std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list;}
        void HandleBullet(SDL_Renderer* des);
        void InsertBullet(const int rocketnum) {bulletbar = rocketnum;}
        int GetBulletBar() {return bulletbar;}
        void InsertCoin() {coincollected++;}
        int GetCoin() const {return coincollected;}
        void RemoveBullet(const int &idx);
        float get_x_pos() const {return x_pos;}
        float get_y_pos() const {return y_pos;}
        void SetPos(const float &x1, const float &x2) {x_pos = x1; y_pos = x2;}
        void IncreaseHeart() {heart++;}
        void DecreaseHeart() {heart--;}
        int GetHeart() const {return heart;}
        void SetSpeed(int speed) {playerspeed = speed;}
    private:
        std::vector<BulletObject*> p_bullet_list; //băng đạn
        float x_val; //giá trị theo trục x sau mỗi lần chạy
        float y_val;

        float x_pos; //vị trí nhân vật
        float y_pos;

        int width_frame;
        int height_frame;

        SDL_Rect frame_clip[12]; //mảng lưu frame - animation
        Input input_type; // up/down/left/right/jump
        int frame;
        int status;
        int bulletbar; //thanh đạn đặc biệt
        int coincollected;
        int heart;
        bool on_ground;

        int map_x;
        int map_y;
        int playerspeed;

        int come_back_time;
};

#endif // MAINOBJECT_H
