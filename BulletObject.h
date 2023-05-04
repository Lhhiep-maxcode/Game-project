#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "BaseObject.h"
#include "Commonfunc.h"

class BulletObject : public baseobject
{
    public:
        BulletObject();
        virtual ~BulletObject();

        enum BulletDir
        {
            DIR_RIGHT = 10,
            DIR_LEFT = 11,
        };

        enum BulletType
        {
            NORM_BULLET = 20,
            ROCKET_BULLET_LEFT = 21,
            ROCKET_BULLET_RIGHT = 22,
            BOSS_BULLET = 23,
            NORM_THREAT_BULLET_RIGHT = 24,
            NORM_THREAT_BULLET_LEFT = 25,
        };
        void set_x_val(const int &xVal) {x_val = xVal;}
        void set_y_val(const int &yVal) {y_val = yVal;}
        int get_x_val() const {return x_val;}
        int get_y_val() const {return y_val;}

        void set_is_move(const bool &isMove) {is_move = isMove;}
        bool get_is_move() const {return is_move;}

        void set_bullet_dir(const unsigned int &bulletDir) {bullet_dir = bulletDir;}
        unsigned int get_bullet_dir() const {return bullet_dir;}

        void set_bullet_type(const unsigned int &bulletType) {bullet_type = bulletType;}
        unsigned int get_bullet_type() const {return bullet_type;}

        void HandleMove(const int &x_border, const int &y_border);
        bool loadImgBullet(SDL_Renderer* des);

    private:
        int x_val;
        int y_val;
        bool is_move;
        unsigned int bullet_dir;
        unsigned int bullet_type;

};

#endif // BULLETOBJECT_H
