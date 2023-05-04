#include "MainObject.h"
#include <iostream>

MainObject::MainObject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 128;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = 2;
    input_type.down = 0;
    input_type.up = 0;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    on_ground = false;
    map_x = 0;
    map_y = 0;
    come_back_time = 0;
    bulletbar = 0;
    coincollected = 0;
    heart = 3;
    playerspeed = PLAYER_SPEED;
}

MainObject::~MainObject()
{

}

bool MainObject::loadImg(std::string path, SDL_Renderer* screen, int num)
{
    bool ret = baseobject::loadImg(path, screen); //load ảnh chứa tất cả frame

    if(ret == true)
    {
        width_frame = rect_.w; //chia nhỏ kích thước thành 1 frame
        height_frame = rect_.h;
    }
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;
    return rect;
}

void MainObject::set_clips()
{
    if(width_frame > 0 && height_frame > 0) //gán chỉ số khung frame trong mảng
    {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;
    }
}

void MainObject::Show(SDL_Renderer* des)
{

    frame = 0;
    if(come_back_time == 0)
    {
        rect_.x = x_pos - map_x; //vị trí x, y để show ảnh và không làm nhân vật teleport khi map chạy
        rect_.y = y_pos - map_y; //kiểu như map_x, map_y là vị trí bắt đầu của map khi map chạy -> kéo nhân vật đúng màn hình


        SDL_Rect current_clip = frame_clip[frame]; //thông số vị trí để cắt ảnh
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame}; //thông số bức ảnh - kiểu z :)))
        SDL_RenderCopy(des, p_object_, &current_clip, &renderQuad);
    }
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen) //nhận lệnh từ keyboard
{

    if(events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
            input_type.jump = 1;
            break;

        case SDLK_x:                      // xử lý đạn
            BulletObject* p_bullet = new BulletObject(); //tạo ra đạn (giống mua đạn)
            if(bulletbar > 0)  //kiểm tra thanh đạn
            {
                if(status == WALK_LEFT) p_bullet->set_bullet_type(BulletObject::ROCKET_BULLET_LEFT);
                else if(status == WALK_RIGHT) p_bullet->set_bullet_type(BulletObject::ROCKET_BULLET_RIGHT);
                bulletbar--;
            }
            else
            {
                p_bullet->set_bullet_type(BulletObject::NORM_BULLET);
            }
            p_bullet->loadImgBullet(screen);

            //chinh huong dan
            p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
            p_bullet->SetRect(this->rect_.x + width_frame - 20, rect_.y + height_frame*0.3); //khởi tạo vị trí đạn


            p_bullet->set_x_val(20); //set tốc độ viên đạn
            p_bullet->set_is_move(true);

            p_bullet_list.push_back(p_bullet); //nạp 1 viên

            break;
        }
    }
    //else if(events.type == SDL_KEYUP)
    //{
      //  switch (events.key.keysym.sym)
        //{
        //case SDLK_RIGHT:
            //status = IDLE_RIGHT;
            //input_type.idle = 1;
          //  input_type.right = 0;
            //break;
        //case SDLK_LEFT:
            //status = IDLE_LEFT;
            //input_type.idle = 1;
          //  input_type.left = 0;
            //break;
        //}
    //}
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for(int i = 0; i < p_bullet_list.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des); //hiển thị ảnh đạn
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin() + i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

bool MainObject::MovePlayer(Map& map_data)
{
    bool check = 0;
    if(come_back_time == 0)
    {
        x_val = playerspeed;
        y_val += GRAVITY_SPEED;

        if(y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }

        if(input_type.jump == 1)
        {
                y_val = - PLAYER_JUMP_VALUE; //nhảy ngay lập tức
                //on_ground = false;
            input_type.jump = 0;
        }
        check = CheckMapLimits(map_data);
        CenterEntityOnMap(map_data);
    }
    if(come_back_time > 0)
    {
        come_back_time--;
        if(come_back_time == 0)
        {
            if(x_pos > 256)
            {
                x_pos -= 256; //4 tiles

            }
            else x_pos = 0;
            y_pos = 128;
            x_val = 0;
            y_val = 0;
        }
    }
    //std::cout << check << std::endl;
    return check;
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH/4);  //khi map di chuyển nhân vật luôn ở giữa
    if(map_data.start_x < 0)
    {
        map_data.start_x = 0;  //map không bị di quá mép trái
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;  //map không bị di quá mép phải
    }

    map_data.start_y = y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

bool MainObject::CheckMapLimits(Map& map_data)
{
    bool crashh = 0;
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
            int val3 = map_data.tile[y1][x1];
            int val4 = map_data.tile[y2][x1];
            if(val1 == STATE_COIN)
            {
                map_data.tile[y1][x2] = 0;
                InsertCoin();
            }
            if(val2 == STATE_COIN)
            {
                map_data.tile[y2][x2] = 0;
                InsertCoin();
            }
            if(val3 == STATE_COIN)
            {
                map_data.tile[y1][x1] = 0;
                InsertCoin();
            }
            if(val4 == STATE_COIN)
            {
                map_data.tile[y2][x1] = 0;
                InsertCoin();
            }
            if(val1 == STATE_ROCKET)
            {
                map_data.tile[y1][x2] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val2 == STATE_ROCKET)
            {
                map_data.tile[y2][x2] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val3 == STATE_ROCKET)
            {
                map_data.tile[y1][x1] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val4 == STATE_ROCKET)
            {
                map_data.tile[y2][x1] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val1 == STATE_HEART)
            {
                map_data.tile[y1][x2] = 0;
                IncreaseHeart();
            }
            if(val2 == STATE_HEART)
            {
                map_data.tile[y2][x2] = 0;
                IncreaseHeart();
            }
            if(val3 == STATE_HEART)
            {
                map_data.tile[y1][x1] = 0;
                IncreaseHeart();
            }
            if(val1 == STATE_HEART)
            {
                map_data.tile[y2][x1] = 0;
                IncreaseHeart();
            }
        }
    }//2 1
    if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE
       || map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
    {
            crashh = true; //check va cham
            //std::cout << crashh;
            come_back_time = 60;
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
            if(val1 == STATE_COIN)
            {
                map_data.tile[y2][x1] = 0;
                InsertCoin();
            }
            if(val2 == STATE_COIN)
            {
                map_data.tile[y2][x2] = 0;
                InsertCoin();
            }
            if(val1 == STATE_ROCKET)
            {
                map_data.tile[y2][x1] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val2 == STATE_ROCKET)
            {
                map_data.tile[y2][x2] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val1 == STATE_HEART)
            {
                map_data.tile[y2][x1] = 0;
                IncreaseHeart();
            }
            if(val2 == STATE_HEART)
            {
                map_data.tile[y2][x2] = 0;
                IncreaseHeart();
            }
            /*else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos = y2*TILE_SIZE;
                    y_pos = y_pos - height_frame;
                    y_val = 0;
                    on_ground = true;
                }
                else on_ground = false;
            }*/
        }
        else if(y_val < 0) //jumping/flying
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if(val1 == STATE_COIN)
            {
                map_data.tile[y1][x1] = 0;
                InsertCoin();
            }
            if(val2 == STATE_COIN)
            {
                map_data.tile[y1][x2] = 0;
                InsertCoin();
            }
            if(val1 == STATE_ROCKET)
            {
                map_data.tile[y1][x1] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val2 == STATE_ROCKET)
            {
                map_data.tile[y1][x2] = 0;
                InsertBullet(ROCKET_NUM);
            }
            if(val1 == STATE_HEART)
            {
                map_data.tile[y1][x1] = 0;
                IncreaseHeart();
            }
            if(val2 == STATE_HEART)
            {
                map_data.tile[y1][x2] = 0;
                IncreaseHeart();
            }
            /*else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos = (y1 + 1)*TILE_SIZE;
                    y_val = 0;
                    on_ground = true;
                }
                else on_ground = false;
            }*/
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
        crashh = true; //check va cham
        //come_back_time = 60;
    }
    //flappy bird
    //1 1 - 1 2
    if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE
       || map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
    {
            crashh = true; //check va cham
            //std::cout << crashh;
            come_back_time = 60;
    }
    //std::cout << crashh<<"-";
    //crashh = false;
    return crashh;
}


void MainObject::RemoveBullet(const int &idx)
{
    int sz = p_bullet_list.size();
    if(sz > 0 && idx < sz)
    {
        BulletObject* p_bullet = p_bullet_list.at(idx);
        p_bullet_list.erase(p_bullet_list.begin() + idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
