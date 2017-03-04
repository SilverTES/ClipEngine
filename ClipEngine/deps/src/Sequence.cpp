#include "Sequence.h"

Sequence::Sequence()
{

}

Sequence::~Sequence()
{

}

Sequence *Sequence::addFrame(Frame *frame)
{
    if (frame != nullptr)
        _vecFrame.push_back(frame);
    return this;
}

int Sequence::nbFrame() const
{
    return _vecFrame.size();
}

Frame* Sequence::frame(unsigned index) const
{
    if (index >= 0 && index < _vecFrame.size())
        return _vecFrame[index];
    else
        return nullptr;
}

void Sequence::render(unsigned index, int x, int y) const
{

}

void Sequence::render(Frame* frame, int x, int y) const
{

}
