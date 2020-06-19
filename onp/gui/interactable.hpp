#ifndef __INTERACTABLE_HPP
#define __INTERACTABLE_HPP

class CInteractable
{
    private:
        float interX0;
        float interX1;
        float interY0;
        float interY1;

    public:
        CInteractable();
        void setInteractibleParams( float interX0, float interX1, float interY0, float interY1 );
        bool testIfWasInteractedWith( float x, float y );
};

CInteractable::CInteractable()
{
    interX0 = 0;
    interX1 = 0;
    interY0 = 0;
    interY1 = 0;
}

void CInteractable::setInteractibleParams( float interX0, float interX1, float interY0, float interY1 )
{
    this->interX0 = interX0;
    this->interX1 = interX1;
    this->interY0 = interY0;
    this->interY1 = interY1;
}

bool CInteractable::testIfWasInteractedWith( float x, float y )
{
    return (x >= interX0) && (x <=interX1) & (y >= interY0) && (y <= interY1);
}

#endif