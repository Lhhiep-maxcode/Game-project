#include "ThreatsObject.h"
#include "SDL.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

ThreatsObject::ThreatsObject()
{
    width_frame = 0;
    height_frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0.0;
    y_pos = 0.0;
    on_ground = false;
    come_back_time = 0;
    frame = 0;
    map_x = 0;
    map_y = 0;
    animation_a = 0;
    animation_b = 0;
    input_type.left = 0;
    type_move = STATIC_THREAT;
    status = WALK_NONEE;
    bosslives = 1;
    type_threat = NORM;
    speed = 0;
}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen, int num) //load anh thành dang texture
{
    bool ret = baseobject::loadImg(path, screen);
    if(ret)
    {
        width_frame = rect_.w/num;
        height_frame = rect_.h;
    }
    return ret;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;
    return rect;
}

void ThreatsObject::set_clips()
{
   if(width_frame > 0 && height_frame > 0) //cắt ảnh trong chuỗi ảnh
   {
       frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 2*width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame;
        frame_clip[2].h = height_frame;

        frame_clip[3].x = 3*width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].w = width_frame;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = 4*width_frame;
        frame_clip[4].y = 0;
        frame_clip[4].w = width_frame;
        frame_clip[4].h = height_frame;

        frame_clip[5].x = 5*width_frame;
        frame_clip[5].y = 0;
        frame_clip[5].w = width_frame;
        frame_clip[5].h = height_frame;

        frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;
   }
}

void ThreatsObject::Show(SDL_Renderer* des,const int num)
{
    if(come_back_time == 0)
    {
        rect_.x = x_pos - map_x; //x_pos tính theo map, map_x tính theo map => trừ đi để ra vị trí trong windows
        rect_.y = y_pos - map_y;
        frame++;
        if(frame >= num)
        {
            frame = 0;
        }
        SDL_Rect* currentClip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
    }
}

void ThreatsObject::MovePlayer(Map &gMap)
{
    if(come_back_time == 0)
    {
        x_val = 0;
        y_val += GRAVITY_SPEED;

        if(y_val >= 15) // 15 là MAX_FALL_SPEED
        {
            y_val = MAX_FALL_SPEED;
        }
        if(input_type.left == 1)
        {
            x_val -= THREAT_SPEED;
        }
        else if(input_type.right == 1)
        {
            x_val += THREAT_SPEED;
        }
        CheckMapLimits(gMap);

    }
    else if(come_back_time > 0)
    {
        come_back_time--;
        if(come_back_time == 0)
        { //khởi tạo ban đầu
            x_val = 0;
            y_val = 0;
            if(x_pos > 256)
            {
                x_pos -= 256; //lui vào 1 tí
                animation_a -= 256; //giới hạn trái phải cũng phải lùi vào 1 tí để threat vẫn di chuyển trong 1 khoảng
                animation_b -= 256;
            }
            else
            {
                x_pos = 0;
            }
            y_pos = 0;
            come_back_time = 0;
            input_type.left = 1;
        }
    }
}

void ThreatsObject::BossChasing(const float &Ypos)
{
    if(y_pos <= Ypos)
    {
        y_pos += speed;
    }
    else if(y_pos >= Ypos)
    {
        y_pos -= speed;
    }
}

void ThreatsObject::CheckMapLimits(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //check horizontal
    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val > 0) //moving right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if((val1 != BLANK_TILE && val1 != STATE_ROCKET)||(val2 != BLANK_TILE && val2 != STATE_ROCKET))
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1; //tìm điểm x1 mới
                x_val = 0;
            }

        }
        else if(x_val < 0) //moving left
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if((val1 != BLANK_TILE && val2 != STATE_ROCKET) || (val2 != BLANK_TILE && val2 != STATE_ROCKET))
            {
                x_pos = (x1+1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }

    //check vertical
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val > 0) //gravity falling
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if((val1 != BLANK_TILE && val1 != STATE_ROCKET)|| (val2 != BLANK_TILE && val2 != STATE_ROCKET))
            {
                y_pos = y2*TILE_SIZE;
                y_pos = y_pos - height_frame;
                y_val = 0;
                on_ground = true;
            }
            else on_ground = false;
        }
        else if(y_val < 0) //jumping/flying
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if((val1 != BLANK_TILE && val1 != STATE_ROCKET)|| (val2 != BLANK_TILE && val2 != STATE_ROCKET))
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
                on_ground = true;
            }
            else on_ground = false;
        }
    }

    x_pos += x_val;  //nghĩ cẩn thận :)
    y_pos += y_val;  // :)

    if(x_pos < 0) x_pos = 0;
    else if(x_pos + width_frame > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame - 1;
    }

    if(y_pos > map_data.max_y)
    {
        come_back_time = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move == STATIC_THREAT)
    {
        ;
    }
    else
    {
        if(on_ground == true)
        {
            if(x_pos > animation_b)
            {
                input_type.left = 1;
                input_type.right = 0;
                status = WALK_LEFTT;
                LoadImg("img/threat_left.png", screen, 8);
            }
            else if(x_pos < animation_a)
            {
                input_type.left = 0;
                input_type.right = 1;
                status = WALK_RIGHTT;
                LoadImg("img/threat_right.png", screen, 8);
            }
        }
        else
        {
            if(input_type.left == 1)
            {
                status = WALK_LEFTT;
                LoadImg("img/threat_left.png", screen, 8);
            }
        }
    }
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::BOSS_BULLET);
        bool ret = p_bullet->loadImgBullet(screen);
        if(ret)
        {
            p_bullet->loadImgBullet(screen);
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(x_pos + 10, y_pos + 5); //khởi tạo vị trí ban đầu của đạn cho thích hợp
            p_bullet->set_x_val(20); //set tốc độ đạn

            bullet_list.push_back(p_bullet);
        }
    }
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int &x_limit, const int &y_limit)
{
    for(int i = 0; i < bullet_list.size(); i++)
    {
        BulletObject* p_bullet = bullet_list.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move())
            {
                int bullet_distance = rect_.x + width_frame - p_bullet->GetRect().x;
                if(bullet_distance < SCREEN_WIDTH/2 && bullet_distance > 0)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);

                }
                else
                {
                    p_bullet->set_is_move(false);
                }

            }
            else
            {
                p_bullet->set_is_move(true);
                //lưu ý rect.x khác x_pos (x_pos là theo bản đồ, rect_x theo màn hình)
                p_bullet->SetRect(this->rect_.x + 10, this->rect_.y + 5); //tìm vị trí hiển thị ảnh đạn ban đầu
            }
        }
    }
}

void ThreatsObject::RemoveBullet(const int &idx)
{
    int sz = bullet_list.size();
    if(sz > 0 && idx < sz)
    {
        BulletObject* p_bullet = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin() + idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

