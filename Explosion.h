#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Commonfunc.h"
#include "BaseObject.h"


class Explosion : public baseobject
{
    public:
        Explosion();
        virtual ~Explosion();
        void set_clips();
        void set_frame(const int &fr) {frame = fr;}
        bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        int get_width_frame() const {return width_frame;}
        int get_height_frame() const {return height_frame;}

    private:
        int width_frame;
        int height_frame;

        unsigned int frame;
        SDL_Rect frame_clip[10];
};

#endif // EXPLOSION_H
