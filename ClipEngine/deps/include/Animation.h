#ifndef ANIMATION_H
#define ANIMATION_H

#include "SpriteFX.h"

enum
{
    ONCE = 0,
    LOOP,
    PINGPONG
};

class Animation
{
    public:
        Animation();
        virtual ~Animation();

        Animation* addSequence(Sequence* sequence);
        int nbSequence() const;

        Sequence* sequence(int id) const;

        int frameDelay(Sequence *sequence, unsigned index) const;

        void update();

        void render(unsigned index, int x, int y, unsigned frame = 0);
        void render(Sequence *sequence, int x, int y, unsigned frame = 0);

    protected:

    private:

        unsigned _currentFrame = 0;
        std::vector<Sequence*> _vecSequence;


};


#endif // ANIMATION_H
