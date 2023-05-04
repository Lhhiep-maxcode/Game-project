#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val = 0;
    y_val = 0;
    is_move = false;
    bullet_type = NORM_BULLET;

}

BulletObject::~BulletObject()
{
    //dtor
}

bool BulletObject::loadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if(bullet_type == NORM_BULLET)
    {
        ret = loadImg("img/Bullet.png", des);
    }
    else if(bullet_type == ROCKET_BULLET_RIGHT)
    {
        ret =loadImg("img/rocket.png", des);
    }
    else if(bullet_type == ROCKET_BULLET_LEFT)
    {
        ret = loadImg("img/rocket2.png", des);
    }
    else if(bullet_type == BOSS_BULLET)
    {
        ret = loadImg("img/spr_bullet_strip02.png", des);
    }
    else if(bullet_type == NORM_THREAT_BULLET_LEFT)
    {
        ret = loadImg("img/spr_bullet_strip1l.png", des);
    }
    else if(bullet_type == NORM_THREAT_BULLET_RIGHT)
    {
        ret = loadImg("img/spr_bullet_strip1.png", des);
    }
    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int &y_border) //hướng đạn
{
    if(bullet_dir == DIR_RIGHT)
    {
        rect_.x += x_val;
        if(rect_.x > x_border)
        {
            is_move = false;
        }
    }
    else if(bullet_dir == DIR_LEFT)
    {
        rect_.x -= x_val;
        if(rect_.x < 0)
        {
            is_move = false;
        }
    }

}
