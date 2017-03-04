#ifndef SEQUENCE_H_INCLUDED
#define SEQUENCE_H_INCLUDED

#include <functional>
#include <vector>
#include "Frame.h"

class Sequence
{
    public:
        Sequence();
        virtual ~Sequence();

        Sequence* addFrame(Frame* frame);
        int nbFrame() const;

        Frame* frame(unsigned index) const;

        virtual void render(unsigned index, int x, int y) const;
        virtual void render(Frame* frame, int x, int y) const;

    protected:
        unsigned _nbFrame = 0;
        std::vector<Frame*> _vecFrame;

    private:

};


#endif // SEQUENCE_H_INCLUDED
