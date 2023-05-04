#ifndef THREATSOBJECT_H
#define THREATSOBJECT_H

#include "Commonfunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <iostream>

#define GRAVITY_SPEED 1;
#define MAX_FALL_SPEED 15;
#define THREAT_SPEED 3;

class ThreatsObject : public baseobject
{
    public:
        ThreatsObject();
        virtual ~ThreatsObject();

        enum TypeMove
        {
            STATIC_THREAT = 100,
            MOVE_IN_SPACE_THREAT = 101,
        };
        enum TypeThreat
        {
            BOSS = 105,
            NORM = 106,
        };
        enum ThreatsStatus
        {
            WALK_NONEE = 102,
            WALK_LEFTT = 103,
            WALK_RIGHTT = 104,
        };
        void set_x_val(const float &xVal) {x_val = xVal;}
        void set_y_val(const float &yVal) {y_val = yVal;}

        void set_x_pos(const float &xp) {x_pos = xp;} //dùng để dịch chuyển nhân vật
        void set_y_pos(const float &yp) {y_pos = yp;}
        float get_x_pos() const {return x_pos;}
        float get_y_pos() const {return y_pos;}
        void SetMapXY(const int &mp_x, const int &mp_y) {map_x = mp_x; map_y = mp_y;}

        void set_clips();
        bool LoadImg(std::string path, SDL_Renderer* screen, int num);
        void Show(SDL_Renderer* des,const int num);
        int get_width_frame() const {return width_frame;} //cần khi check va chạm
        int get_height_frame() const {return height_frame;} //cần khi check va chạm
        void MovePlayer(Map &gMap);
        void CheckMapLimits(Map &gMap);
        void BossChasing(const float &Ypos);

        void set_type_move(const int &typeMove) {type_move = typeMove;}
        void SetAnimationPos(const int &pos_a, const int &pos_b) {animation_a = pos_a; animation_b = pos_b;} //giới hạn trái phải cho threat di chuyển
        void set_input_left(const int &ipLeft) {input_type.left = ipLeft;} //khi đến giới hạn phải/trái thì đổi giá trị input_type.left
        void ImpMoveType(SDL_Renderer* screen);

        std::vector<BulletObject*> get_bullet_list() const {return bullet_list;}
        void set_bullet_list(const std::vector<BulletObject*> &bl_list) {bullet_list = bl_list;}
        void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);  //dùng để khởi tạo trạng thái của viên đạn
        void MakeBullet(SDL_Renderer* screen, const int &x_limit, const int &y_limit);
        void RemoveBullet(const int &idx);
        SDL_Rect GetRectFrame();
        void SetBossLives(const int &lives) {bosslives = lives;}
        int GetBossLives(){return bosslives;}
        void SetThreatType(const int &Type) {type_threat = Type;}
        int GetThreatType(){return type_threat;}
        void SetBossSpeed(const int &speedd) {speed = speedd;}
        int GetBossSpeed(){return speed;}

    private:
        int map_x;
        int map_y;
        float x_val;
        float y_val;
        float x_pos;
        float y_pos;
        bool on_ground;
        int come_back_time;
        SDL_Rect frame_clip[12];
        int width_frame;
        int height_frame;
        int frame;
        int bosslives;

        int type_move;
        int animation_a; //giới hạn đi chuyển của threats bên trái
        int animation_b; //___________________________________phải
        Input input_type;
        int type_threat;
        int speed;

        int status;

        std::vector<BulletObject*> bullet_list;
};

#endif // THREATSOBJECT_H
