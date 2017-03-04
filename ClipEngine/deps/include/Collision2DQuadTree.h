#ifndef COLLISION2DQUADTREE_H_INCLUDED
#define COLLISION2DQUADTREE_H_INCLUDED

#include "World2D.h"

namespace Collision2D
{
    struct QuadTree
    {
        unsigned _currentLevel = 0;
        unsigned _maxObject;
        unsigned _maxLevel;
        Rect _rect;
        QuadTree *_parent = nullptr;
        QuadTree *_node[4] = {nullptr};

        std::vector<Entity*> _vecEntity;

        std::vector<Entity*> _vecIndex; // Contain all index of entity in the Quad

        QuadTree(Rect rect, QuadTree *parent = nullptr, unsigned maxObject = 8, unsigned maxLevel = 5)
        {
            _rect = rect;
            _parent = parent;
            _maxObject = maxObject;
            _maxLevel = maxLevel;

            if (_parent == nullptr)
                _currentLevel = 0;
            else
            {
                _currentLevel = _parent->_currentLevel + 1;
                _maxObject = _parent->_maxObject;
                _maxLevel = _parent->_maxLevel;
            }
        }
        ~QuadTree()
        {
            clearNode();
        }
        bool haveChild()
        {
            return (_node[0] != nullptr);
        }
        bool isLastBranch()
        {
            bool isLastBranch = true;
            for (int i = 0; i < 4; ++i)
            {
                if (_node[i] != nullptr)
                {
                    if (_node[i]->haveChild())
                        isLastBranch = false;
                }
            }
            if (isLastBranch)
                mlog("- is Last Branch -");
            return isLastBranch;
        }
        void split()
        {
            if (_currentLevel < _maxLevel)
            {
                VAR x = _rect._x;
                VAR y = _rect._y;
                VAR w = _rect._w;
                VAR h = _rect._h;
                VAR cW = w / 2;
                VAR cH = h / 2;

                _node[NW] = new QuadTree(Rect{x,y,cW,cH}, this);
                _node[NE] = new QuadTree(Rect{x+cW,y,cW,cH}, this);
                _node[SW] = new QuadTree(Rect{x,y+cH,cW,cH}, this);
                _node[SE] = new QuadTree(Rect{x+cW,y+cH,cW,cH}, this);
            }
        }
        void unSplit()
        {
            clearNode();
        }
        void clearNode()
        {
            if (!_vecIndex.empty())
            {
                for (auto & it : _vecIndex)
                {
                    if (it != nullptr)
                    {
                        delete it;
                        it = nullptr;

                    }
                }
                _vecIndex.clear();
                //log("- vecIndex cleared -");
            }

            //log("- Begin Clear Node -");
            if (haveChild())
            {
                //log("- Node have child -");
                for (int i = 0; i < 4; ++i)
                {
                    //if (_node[i] != nullptr)
                    //{

                        if (_node[i]->haveChild())
                            _node[i]->clearNode();

                        delete _node[i];
                        _node[i] = nullptr;

                        //printf("Delete Node %i \n", i);
                    //}
                }
            }



        }
        // Return wich node the object belongs to , -1 = Object belong Parent node
        int getQuadIndex(Rect &rect)
        {
            int index = -1;
            VAR cX = _rect._x + _rect._w / 2;
            VAR cY = _rect._y + _rect._h / 2;

            bool inN = (rect._y + rect._h < cY);
            bool inS = (rect._y > cY);
            bool inW = (rect._x + rect._w < cX);
            bool inE = (rect._x > cX);

            if (inN && inW) index = NW;
            if (inN && inE) index = NE;
            if (inS && inW) index = SW;
            if (inS && inE) index = SE;

            return index;
        }
        void insert(unsigned index, Rect rect)
        {
            if (haveChild()) // If have child transmit to child
            {
                int quadIndex = getQuadIndex(rect);
                if (quadIndex != -1)
                    _node[quadIndex]->insert(index, rect);

                return;
            }

            _vecIndex.push_back(new Entity{ index, rect });

            if (_vecIndex.size() > _maxObject && _currentLevel < _maxLevel)
            {
                //log("- need split -\n");
                if (!haveChild())
                    split();

                unsigned i = 0;
                while (i < _vecIndex.size())
                {
                    int quadIndex = getQuadIndex(_vecIndex[i]->_rect);
                    if (quadIndex != -1)
                    {
                        _node[quadIndex]->insert(_vecIndex[i]->_index, _vecIndex[i]->_rect);
                        delete _vecIndex[i]; // don't forget to delete Entity pointer !
                        _vecIndex.erase(_vecIndex.begin() + i);
                    }
                    else
                    {
                        ++i;
                    }
                }
            }
        }
        void findNear(std::vector<Entity*> &vecEntity, Rect &rect)
        {
            if (haveChild())
            {
                int quadIndex = getQuadIndex(rect);

                if (quadIndex != -1)
                {
                    _node[quadIndex]->findNear(vecEntity, rect);
                }
                else
                {
                    for (unsigned i = 0; i < 4; ++i)
                    {
                        _node[i]->findNear(vecEntity, rect);
                    }
                }
            }

            for (auto & it: _vecIndex)
                vecEntity.push_back(it);
        }


        void update(int mouseX, int mouseY, int mouseB)
        {
            //if ((mouseB & 1) && !haveChild())
            //{
            //	if (mouseX > _rect._x && mouseX < _rect._x + _rect._w &&
            //		mouseY > _rect._y && mouseY < _rect._y + _rect._h)
            //	{
            //		split();
            //	}
            //	mouseB = 0;
            //}

            //if ((mouseB & 2) && haveChild())
            //{
            //	if (mouseX > _rect._x && mouseX < _rect._x + _rect._w &&
            //		mouseY > _rect._y && mouseY < _rect._y + _rect._h)
            //	{
            //		bool nodeHaveChild = false;
            //		for (int i = 0; i < 4; ++i)
            //		{
            //			if (_node[i] != nullptr)
            //			{
            //				if (_node[i]->haveChild())
            //					nodeHaveChild = true;
            //
            //			}
            //		}

            //		if (!nodeHaveChild)
            //			unSplit();
            //	}
            //}

            //if (haveChild())
            //{
            //	for (int i = 0; i < 4; ++i)
            //	{
            //		if (_node[i] != nullptr)
            //		{
            //			_node[i]->update(mouseX, mouseY, mouseB);
            //		}
            //	}
            //}

        }

        void render(int mouseX, int mouseY, int mouseB)
        {

            if (mouseX > _rect._x && mouseX < _rect._x + _rect._w &&
                mouseY > _rect._y && mouseY < _rect._y + _rect._h &&
                !haveChild())
            {
                al_draw_filled_rectangle(
                    .5 + _rect._x, .5 + _rect._y,
                    .5 + _rect._x + _rect._w + 1, .5 + _rect._y + _rect._h + 1,
                    al_map_rgba(0, 155, 100, 50));


                //for (unsigned i = 0; i < _vecIndex.size(); ++i)
                //{
                //	al_draw_textf(font, al_map_rgb(25, 205, 255),
                //				  mouseX, mouseY + (i * 12), 0,
                //				  "vec[%i]=%i", i, _vecIndex[i]->_index
                //				  );
                //}

            }

            if (haveChild())
            {
                al_draw_line(
                    .5 + _rect._x + _rect._w / 2, .5 + _rect._y,
                    .5 + _rect._x + _rect._w / 2, .5 + _rect._y + _rect._h,
                    al_map_rgb(0, 155, 100), 0);

                al_draw_line(
                    .5 + _rect._x , .5 + _rect._y + _rect._h / 2 ,
                    .5 + _rect._x + _rect._w, .5 + _rect._y + _rect._h / 2,
                    al_map_rgb(0, 155, 100), 0);

                //for (unsigned i = 0; i < _vecIndex.size(); ++i)
                //{
                //	al_draw_textf(font, al_map_rgb(25, 205, 255),
                //				  _rect._x + 2, _rect._y + 12 + (i * 12)  , 0,
                //				  "vec[%i]=%i", i, _vecIndex[i]->_index
                //	);
                //}
            }

            if (haveChild())
                for (int i = 0; i < 4; ++i)
                {
                    if (_node[i] != nullptr)
                    {
                        _node[i]->render(mouseX, mouseY, mouseB);
                    }
                }

            if (!haveChild())
            {
                al_draw_filled_circle(
                    .5 + _rect._x + _rect._w/2, .5 + _rect._y + _rect._h/2, 1,
                    al_map_rgba(0, 155, 100, 255));

                //al_draw_textf(font, al_map_rgb(255, 200, 200),
                //			  _rect._x + 2, _rect._y + 2, 0,
                //			  //_rect._x + _rect._w / 2, _rect._y - 1 + _rect._h / 2, 1,
                //			  "%i:%i", _currentLevel, _vecIndex.size());
            }

        }
    };


}
#endif // COLLISION2DQUADTREE_H_INCLUDED
