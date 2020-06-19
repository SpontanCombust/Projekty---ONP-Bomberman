#ifndef __DRAWABLE_HPP
#define __DRAWABLE_HPP

#include <allegro5/allegro.h>

class CDrawable
{
    protected:
        float drawX;
        float drawY;
        float drawW;
        float drawH;
        int drawFlags;
        ALLEGRO_BITMAP *bmp;

    public:
        CDrawable();
        void setDrawableParams( float drawX, float drawY, float drawW, float drawH, int drawFlags );
        void drawBitmap();
        virtual void updateBitmap() = 0;
};

CDrawable::CDrawable()
{
    drawX = 0;
    drawY = 0;
    drawW = 0;
    drawH = 0;
    drawFlags = 0;
    bmp = NULL;
}

void CDrawable::setDrawableParams( float drawX, float drawY, float drawW, float drawH, int drawFlags )
{
    this->drawX     = drawX;
    this->drawY     = drawY;
    this->drawW     = drawW;
    this->drawH     = drawH;
    this->drawFlags = drawFlags;
    bmp = al_create_bitmap( drawW, drawH );
}

void CDrawable::drawBitmap()
{
    al_draw_bitmap( bmp, drawX, drawY, drawFlags );
}

#endif