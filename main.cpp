#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include "Commonfunc.h"
#include "baseobject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "TextNote.h"

using namespace std;

baseobject g_background;


TTF_Font* font_point = NULL;
TTF_Font* font_play = NULL;
TTF_Font* font_instruct = NULL;
TTF_Font* font_point_menu = NULL;


bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Gamevui", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL){
        success = false;
    }
    else{
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags)) success = false;
        }

        if(TTF_Init() == -1)
        {
            success = false;
        }
        font_point = TTF_OpenFont("font/dlxfont_.ttf", 18);
        font_play = TTF_OpenFont("font/dlxfont_.ttf", 18);
        font_instruct = TTF_OpenFont("font/dlxfont_.ttf", 18);
        font_point_menu = TTF_OpenFont("font/dlxfont_.ttf", 36);
        if(font_point == NULL || font_play == NULL || font_instruct == NULL || font_point_menu == NULL)
        {
            //std::cout << "hihi";
            success = false;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadImg("img/background2.png", g_screen);
    if(!ret) return false;
    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreatList() //tạo 1 list các đối tượng threat
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* moving_threats = new ThreatsObject[7];
    for(int i = 0; i < 7; i++)
    {
        ThreatsObject* p_threat = moving_threats + i;
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_left.png", g_screen, 8);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            //Khởi tạo giá trị gốc cho các threats
            if(i == 0)
            {
                p_threat->set_x_pos(1216);
                p_threat->set_y_pos(128);
            }
            else if(i == 1)
            {
                p_threat->set_x_pos(1728);
                p_threat->set_y_pos(64);
            }
            else if(i == 2)
            {
                p_threat->set_x_pos(2560);
                p_threat->set_y_pos(320);
            }
            else if(i == 3)
            {
                p_threat->set_x_pos(3392);
                p_threat->set_y_pos(64);
            }
            else if(i == 4)
            {
                p_threat->set_x_pos(3328);
                p_threat->set_y_pos(320);
            }
            else if(i == 5)
            {
                p_threat->set_x_pos(10304);
                p_threat->set_y_pos(64);
            }
            else if(i == 6)
            {
                p_threat->set_x_pos(9600);
                p_threat->set_y_pos(320);
            }
            p_threat->set_input_left(1); //gan status = left
            int pos1 = p_threat->get_x_pos() - 60; //giới hạn trái (animation_a)
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);


            list_threats.push_back(p_threat);
        }
    }
    ThreatsObject* threats_objects = new ThreatsObject[9]; //20 đối tượng threats
    for(int i = 0; i < 9; i++)
    {
        ThreatsObject* p_threat = threats_objects + i;
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img/threat_level.png", g_screen, 8);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            //Khởi tạo giá trị gốc cho các threats
            if(i == 0)
            {
                p_threat->set_x_pos(1728);
                p_threat->set_y_pos(320);
            }
            else if(i == 1)
            {
                p_threat->set_x_pos(2368);
                p_threat->set_y_pos(64);
            }
            else if(i == 2)
            {
                p_threat->set_x_pos(2944);
                p_threat->set_y_pos(192);
            }
            else if(i == 3)
            {
                p_threat->set_x_pos(7872);
                p_threat->set_y_pos(192);
            }
            else if(i == 4)
            {
                p_threat->set_x_pos(9536);
                p_threat->set_y_pos(64);
            }
            else if(i == 5)
            {
                p_threat->set_x_pos(10048);
                p_threat->set_y_pos(192);
            }
            else if(i == 6)
            {
                p_threat->set_x_pos(10304);
                p_threat->set_y_pos(320);
            }
            else if(i == 7)
            {
                p_threat->set_x_pos(10688);
                p_threat->set_y_pos(128);
            }
            else if(i == 8)
            {
                p_threat->set_x_pos(11008);
                p_threat->set_y_pos(256);
            }

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat);
        }
    }
    ThreatsObject* bossthreats = new ThreatsObject[5];
    for(int i = 0; i < 5; i++)
    {
        ThreatsObject* p_threat = bossthreats + i;
        if(p_threat != NULL)
        {
            if(i == 0)
            {
                p_threat->LoadImg("img/Ship2.png", g_screen, 1);
                p_threat->set_clips();
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->SetBossLives(3);
                p_threat->set_x_pos(14080);
                p_threat->set_y_pos(256);
                p_threat->SetBossSpeed(2);
                p_threat->SetThreatType(105);
            }
            else if(i == 1)
            {
                p_threat->LoadImg("img/Ship2.png", g_screen, 1);
                p_threat->set_clips();
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->SetBossLives(5);
                p_threat->set_x_pos(20352);
                p_threat->set_y_pos(256);
                p_threat->SetBossSpeed(2);
                p_threat->SetThreatType(105);
            }
            else if(i == 2)
            {
                p_threat->LoadImg("img/Ship3.png", g_screen, 1);
                p_threat->set_clips();
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->SetBossLives(10);
                p_threat->set_x_pos(21824);
                p_threat->set_y_pos(256);
                p_threat->SetBossSpeed(3);
                p_threat->SetThreatType(105);
            }
            else if(i == 3)
            {
                p_threat->LoadImg("img/Ship5.png", g_screen, 1);
                p_threat->set_clips();
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->SetBossLives(15);
                p_threat->set_x_pos(23296);
                p_threat->set_y_pos(256);
                p_threat->SetBossSpeed(4);
                p_threat->SetThreatType(105);
            }
            else if(i == 4)
            {
                p_threat->LoadImg("img/Ship6.png", g_screen, 1);
                p_threat->set_clips();
                p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
                p_threat->SetBossLives(35);
                p_threat->set_x_pos(24704);
                p_threat->set_y_pos(256);
                p_threat->SetBossSpeed(5);
                p_threat->SetThreatType(105);
            }

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}


int main(int argc, char* argv[])
{
    bool crash = false;
    ImpTimer fps_timer;


    if(!InitData()) return -1;
    if(!LoadBackground()) return -1;

    //point text
    TextObject point_game;
    point_game.SetColor(TextObject::WHITE_TEXT);

    //bullet text
    TextObject bullet;
    bullet.SetColor(TextObject::WHITE_TEXT);

    TextObject play;
    play.SetColor(TextObject::BLACK_TEXT);

    TextObject instruct;
    instruct.SetColor(TextObject::BLACK_TEXT);

    TextObject instruct_gameloop;
    instruct_gameloop.SetColor(TextObject::WHITE_TEXT);

    TextObject point_menu;
    point_menu.SetColor(TextObject::RED_TEXT);

    int point = 0;

    bool is_play = true;
    bool is_quit = true;
    bool is_instruct = false;


    while(is_play)
    {
        SDL_RenderClear(g_screen);

        g_background.loadImg("img/background3.png", g_screen);
        g_background.Render(g_screen, NULL);
        g_background.Free();

        std::string Points_menu_text = "Points: ";
        std::stringstream ss;
        ss << point;
        std::string strPoint = ss.str();
        Points_menu_text += strPoint;
        point_menu.SetText(Points_menu_text);
        point_menu.LoadFromRenderText(font_point_menu, g_screen);
        point_menu.RenderText(g_screen, 50, SCREEN_HEIGHT/2 + 70);
        point_menu.Free();

        std::string play_text = "Press [UP] button to play.";
        play.SetText(play_text);
        play.LoadFromRenderText(font_play, g_screen);
        play.RenderText(g_screen, 50, SCREEN_HEIGHT/2 + 150);
        play.Free();

        std::string instruct_text = "Press [C] button for instruction.";
        instruct.SetText(instruct_text);
        instruct.LoadFromRenderText(font_instruct, g_screen);
        instruct.RenderText(g_screen, 50, SCREEN_HEIGHT/2 + 200);
        instruct.Free();


        while(SDL_PollEvent(&g_event) != 0)
        {

            if(g_event.type == SDL_QUIT)
            {
                is_play = false;
            }
            if(g_event.type == SDL_KEYUP)
            {
                switch(g_event.key.keysym.sym)
                {
                case SDLK_UP:
                    is_quit = false;
                    point = 0;
                    g_background.loadImg("img/background2.png", g_screen);
                    g_background.Render(g_screen, NULL);

                case SDLK_c:
                    is_instruct = !is_instruct;
                }
            }
        }

        if(is_instruct)
        {
            SDL_Texture* new_texture = NULL;
            SDL_Surface* load_surface = IMG_Load("img/START.png");
            new_texture = SDL_CreateTextureFromSurface(g_screen, load_surface);
            SDL_FreeSurface(load_surface);
            SDL_Rect renderquad = {80, 20, 1119, 600};
            SDL_RenderCopy(g_screen, new_texture, NULL, &renderquad);
        }


        if(!is_quit)
        {
        GameMap game_map;
        game_map.LoadMap("map/map01.dat");
        game_map.LoadTiles(g_screen);

        MainObject p_player;
        p_player.loadImg("img/Ship4.png", g_screen, 8);
        p_player.set_clips();

        TextNote player_power;
        player_power.Init(g_screen);

        std::vector<ThreatsObject*> threats_list = MakeThreatList();

        Explosion p_explosion;
        p_explosion.LoadImg("img/explosion.png", g_screen);
        p_explosion.set_clips();

        RocketBullet rocket_bullet;
        rocket_bullet.Init(g_screen);
        rocket_bullet.SetPos(SCREEN_WIDTH/2 - 100, 15);

        int start_time = SDL_GetTicks64();
        int point_destroy = 0;
        int respond = 0;

        while(!is_quit)
        {
            crash = false;
            if(SDL_GetTicks64() - start_time >= 75000)
            {
                p_player.SetSpeed(6);
            }
//            else if(SDL_GetTicks64() - start_time >= 45000)
//            {
//                p_player.SetSpeed(6);
//            }

            int Heart1 = p_player.GetHeart();
            fps_timer.start();
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                    is_play = false;
                }
                if(g_event.type == SDL_KEYUP)
                {
                    switch(g_event.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        is_quit = true;
                        is_instruct = false;
                    }
                }
                p_player.HandleInputAction(g_event, g_screen);
            }
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
                                   RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);


            g_background.Render(g_screen, NULL);



            Map map_data = game_map.getMap();

            p_player.SetMapXY(map_data.start_x, map_data.start_y); //k làm nhân vật bị lỗi tele
            crash = p_player.MovePlayer(map_data);
//            if(crash && !respond) respond = 200;
//            else if(respond)
//            {
//                respond--;
//                crash = false;
//            }
            //std::cout << crash;
            if(respond) respond--;
            p_player.Show(g_screen);

            game_map.SetMap(map_data); //lấy dữ liệu map mới sau khi nhận lệnh từ keyboard
            game_map.DrawMap(g_screen);

            player_power.Show(g_screen);
            rocket_bullet.Show(g_screen);

            int frame_exp_width = p_explosion.get_width_frame();
            int frame_exp_height = p_explosion.get_height_frame();
            for(int i = 0; i < threats_list.size(); i++)
            {
                ThreatsObject* p_threat = threats_list.at(i);
                if(p_threat != NULL)
                {
                    p_threat->SetMapXY(map_data.start_x, map_data.start_y); //giống main (k làm quái di chuyển theo mãi)
                    p_threat->ImpMoveType(g_screen);
                    if(p_threat->GetThreatType() != ThreatsObject::BOSS)
                    {
                        p_threat->MovePlayer(map_data);
                    }
                    else
                    {
                        p_threat->BossChasing(p_player.get_y_pos());
                    }
                    p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                    if(p_threat->GetThreatType() != ThreatsObject::BOSS)
                    {
                        p_threat->Show(g_screen, 8); //8 la so frame
                    }
                    else
                    {
                        p_threat->Show(g_screen, 1);
                    }

                    SDL_Rect rect_player = p_player.GetRectFrame();
                    //người chạm quái/đạn quái
                    bool bCol1 = false;
                    std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                    for(int i = 0; i < tBullet_list.size(); i++)
                    {
                        BulletObject* pt_bullet = tBullet_list.at(i);
                        if(pt_bullet != NULL)
                        {
                                bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        }
                    }
                    SDL_Rect rect_threat = p_threat->GetRectFrame();

                    bool bCol2 = false;
                    bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                    if((bCol1 || bCol2|| crash) && (respond == 0))
                    {
                        //std::cout << crash;
                        //std::cout << 1;
                        respond = 200;
                        crash = false;
                        int width_exp_frame = p_explosion.get_width_frame();
                        int height_exp_frame = p_explosion.get_height_frame();
                        for(int r = 0; r < 10; r++)
                        {
                            int x_pos = (p_player.GetRect().x + p_player.get_width_frame()*0.5) - width_exp_frame*0.5;
                            int y_pos = (p_player.GetRect().y + p_player.get_width_frame()*0.5) - width_exp_frame*0.5;
                            p_explosion.set_frame(r);
                            p_explosion.SetRect(x_pos, y_pos);
                            p_explosion.Show(g_screen);
                            //SDL_Delay(10);
                            SDL_RenderPresent(g_screen);
                        }
                        p_player.DecreaseHeart();
                        if(p_player.GetHeart() > 0)
                        {
                            SDL_Delay(500);
                            p_player.set_come_back_time(60);
                            //float x_pos = (p_player.get_x_pos() - 256) < 0 ? 0 : (p_player.get_x_pos() - 256);
                            //float y_pos = (p_player.get_y_pos() - 256) < 0 ? 0 : (p_player.get_y_pos() - 256);
                            p_player.SetRect(0, 0);
                            //p_player.SetPos(x_pos, y_pos);
                            player_power.Decrease();
                            //player_power.Render(g_screen);

                        }
                    }
                }
            }

            if(p_player.GetHeart() <= 0)
            {
                if(MessageBox(NULL, "GAME OVER", "INFO", MB_OK | MB_ICONSTOP) == IDOK)
                {
                    is_quit = true;
                    is_instruct = false;
                }
            }
            p_player.HandleBullet(g_screen);

            std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
            for(int i = 0; i < bullet_arr.size(); ++i) //kiểm tra viên đạn thứ 1, 2, 3,.....
            {
                BulletObject* p_bullet = bullet_arr.at(i);
                if(p_bullet != NULL)
                {   //đạn chạm hộp
                    int x1 = 0; //vẽ từ x1 -> x2 (có thể thừa ra tí)
                    int x2 = 0;

                    int y1 = 0; //vẽ từ y1 -> y2 (có thể thừa ra tí)
                    int y2 = 0;

                    int map_x, map_y;

                    map_x = map_data.start_x/TILE_SIZE;  //tính cục đất thứ j để vẽ
                    x1 = (map_data.start_x % TILE_SIZE)*(-1); //tính điểm bắt đầu vẽ trên màn hình (pixel)
                    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

                    map_y = map_data.start_y/TILE_SIZE; //tính cục đất thứ i để vẽ
                    y1 = (map_data.start_y % TILE_SIZE)*(-1);
                    y2 = y1 + SCREEN_WIDTH + (y1 == 0 ? 0 : TILE_SIZE);

                    for(int z = y1; z < y2; z += TILE_SIZE)
                    {
                        map_x = map_data.start_x/TILE_SIZE;
                        for(int j = x1; j < x2; j += TILE_SIZE)
                        {
                            int val = map_data.tile[map_y][map_x];

                            if(val > 0 && val < 20 && val != 10 && val != 11 && val != 12)
                            {
                                SDL_Rect tile = {j, z, 64, 64};
                                SDL_Rect bRect = p_bullet->GetRect();
                                bool bCol = SDLCommonFunc::CheckCollision(bRect, tile);
                                if(bCol)
                                {
                                    //std::cout << point;
                                    for(int r = 0; r < 10; r++)
                                    {
                                        int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5; //để vụ nổ xảy ra đúng chỗ viên đạn chạm
                                        int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                        p_explosion.set_frame(r);
                                        p_explosion.SetRect(x_pos, y_pos);
                                        p_explosion.Show(g_screen);
                                        //SDL_Delay(20);
                                        SDL_RenderPresent(g_screen);
                                    }

                                    if(p_bullet->get_bullet_type() != BulletObject::ROCKET_BULLET_RIGHT) p_player.RemoveBullet(i);
                                    if(p_bullet->get_bullet_type() == BulletObject::ROCKET_BULLET_RIGHT)
                                    {
                                        game_map.RemoveTile(map_y, map_x);
                                        point_destroy += 1;
                                    }
                                    if(val == 7)
                                    {
                                        game_map.RemoveTile(map_y, map_x);
                                        point_destroy += 1;
                                    }
                                }
                            }
                            map_x++;
                        }
                        map_y++;
                    }
                    //đạn chạm quái
                    for(int j = 0; j < threats_list.size(); ++j) //kiểm tra con quái thứ 1, 2, 3,....
                    {
                        ThreatsObject* obj_threat = threats_list.at(j);
                        if(obj_threat != NULL)
                        {
                            SDL_Rect tRect;
                            tRect.x = obj_threat->GetRect().x;
                            tRect.y = obj_threat->GetRect().y;
                            tRect.w = obj_threat->get_width_frame(); //nếu nhân vât có chuỗi clip thì sao => lấy chiều ngang 1 frame cho chắc
                            tRect.h = obj_threat->get_height_frame();//_______________________________________________________

                            SDL_Rect bRect = p_bullet->GetRect();
                            //quái chạm đạn người
                            bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                            if(bCol)
                            {
                                if(p_bullet->get_bullet_type() == BulletObject::ROCKET_BULLET_RIGHT)
                                {
                                    int hearts = obj_threat->GetBossLives() - 5;
                                    obj_threat->SetBossLives(hearts);
                                }
                                else
                                {
                                    int hearts = obj_threat->GetBossLives() - 1;
                                    obj_threat->SetBossLives(hearts);
                                }

                                    for(int r = 0; r < 10; r++)
                                    {
                                        int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5; //để vụ nổ xảy ra đúng chỗ viên đạn chạm
                                        int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                        p_explosion.set_frame(r);
                                        p_explosion.SetRect(x_pos, y_pos);
                                        p_explosion.Show(g_screen);
                                        if(obj_threat->GetBossLives() < 1)
                                        {

                                            //SDL_Delay(5);
                                        }
                                        SDL_RenderPresent(g_screen);
                                    }

                                p_player.RemoveBullet(i);
                                if(obj_threat->GetBossLives() < 1)
                                {
                                    if(obj_threat->GetThreatType() == ThreatsObject::STATIC_THREAT) point_destroy += 2;
                                    else
                                    {
                                        if(obj_threat->GetBossSpeed() == 0) point_destroy += 5;
                                        else point_destroy += 10;
                                    }
                                    obj_threat->Free();
                                    threats_list.erase(threats_list.begin() + j);
                                }
                            }
                        }
                    }
                }
            }

            int Heart2 = p_player.GetHeart();
            if(Heart2 - Heart1 > 0)
            {
                cout << p_player.GetHeart() << endl;
                player_power.Increase();
                player_power.Show(g_screen);
            }

            //Show game points
            std::string Points_text = "Points: ";
            //point = (p_player.GetCoin() + point_destroy) > point ? (p_player.GetCoin() + point_destroy) : point; //point la coin
            point = p_player.GetCoin() + point_destroy;
            std::stringstream ss;
            ss << point;
            std::string strPoint = ss.str();
            Points_text += strPoint;
            point_game.SetText(Points_text);
            point_game.LoadFromRenderText(font_point, g_screen);
            point_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
            point_game.Free();

            int rocket = p_player.GetBulletBar();
            stringstream s;
            s << rocket;
            string rocketbull = s.str();
            bullet.SetText(rocketbull);
            bullet.LoadFromRenderText(font_point, g_screen);
            bullet.RenderText(g_screen, SCREEN_WIDTH/2, 15);
            bullet.Free();

            std::string instruct_exit = "Press [SPACE] button to exit.";
            instruct_gameloop.SetText(instruct_exit);
            instruct_gameloop.LoadFromRenderText(font_instruct, g_screen);
            instruct_gameloop.RenderText(g_screen, 750, 600);
            instruct_gameloop.Free();


            SDL_RenderPresent(g_screen);

            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000/FRAMES_PER_SECOND;
            if(real_imp_time < time_one_frame) //nếu quá nhanh
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time >= 0)
                    SDL_Delay(delay_time);
            }
        }

        for(int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if(p_threat)
            {
                p_threat->Free();
                p_threat = NULL;
            }
        }
        p_player.Free();
        player_power.Free();
        p_explosion.Free();
        rocket_bullet.Free();

        threats_list.clear();
        }

        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}
