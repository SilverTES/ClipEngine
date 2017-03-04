#include "Animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    if (!_vecSequence.empty())
    {
        for (auto & it: _vecSequence)
        {
            if (it != nullptr)
            {
                delete it;
                it = nullptr;
            }

        }
        _vecSequence.clear();
    }
    //dtor
}

Animation* Animation::addSequence(Sequence* sequence)
{
    if (sequence != nullptr)
        _vecSequence.push_back(sequence);
    return this;
}
int Animation::nbSequence() const
{
    return _vecSequence.size();
}


Sequence* Animation::sequence(int index) const
{
    return _vecSequence[index];
}

int Animation::frameDelay(Sequence* sequence, unsigned index) const
{
    if (sequence->frame(index) != nullptr)
        return sequence->frame(index)->_delay;
    else
        return 0;
}

void Animation::update()
{

}


void Animation::render(unsigned index, int x, int y, unsigned frame)
{
    _currentFrame = frame;

    if (_vecSequence[index] != nullptr)
        _vecSequence[index]->render(_currentFrame, x, y);
}

void Animation::render(Sequence* sequence, int x, int y, unsigned frame)
{
    _currentFrame = frame;

    if (sequence != nullptr)
        sequence->render(_currentFrame, x, y);
}
