#ifndef __WIDGET_HPP
#define __WIDGET_HPP

#include "interactable.hpp"
#include "drawable.hpp"

class CWidget : public CInteractable, public CDrawable
{
    public:
        void setInteractableToWholeBitmap();
};

void CWidget::setInteractableToWholeBitmap()
{
    setInteractibleParams( 0, drawX - 1, 0, drawY - 1 );
}

#endif