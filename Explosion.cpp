#include "Explosion.h"


Explosion::Explosion()
{
    //ctor
    width_frame = 0;
    height_frame = 0;
    frame = 0;
}

Explosion::~Explosion()
{
    //dtor
}

bool Explosion::LoadImg(std::string path, SDL_Renderer* screen) //load anh thành dang texture
{
    bool ret = baseobject::loadImg(path, screen);
    if(ret)
    {
        width_frame = rect_.w/10;
        height_frame = rect_.h;
    }
    return ret;
}

void Explosion::set_clips()
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

        frame_clip[8].x = 8*width_frame;
        frame_clip[8].y = 0;
        frame_clip[8].w = width_frame;
        frame_clip[8].h = height_frame;

        frame_clip[9].x = 9*width_frame;
        frame_clip[9].y = 0;
        frame_clip[9].w = width_frame;
        frame_clip[9].h = height_frame;

   }
}

void Explosion::Show(SDL_Renderer* des)
{

        SDL_Rect* currentClip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
        if(currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;

        }
        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
}
