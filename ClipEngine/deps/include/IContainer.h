#ifndef ICONTAINER_H
#define ICONTAINER_H

#include <iostream>
#include <algorithm>
#include <vector>

struct ZIndex
{
    int _z = 0;
    int _index = 0;
};


template <class OBJECT>
class IContainer
{
    public:
        IContainer()
        {

        }
        virtual ~IContainer()
        {
            if (!_vecObject.empty())
            {
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                    {
                        delete it;
                        it = nullptr;
                    }
                }
                _vecObject.clear();
            }

            _vecFreeObject.clear();
        }

        void add(OBJECT *object)
        {
            if (object != nullptr)
            {
                //object->_parent = (OBJECT*)this;

                if (!_vecFreeObject.empty())
                {
                    unsigned freeChildIndex = _vecFreeObject.back();
                    _vecFreeObject.pop_back();

                    _vecObject[freeChildIndex] = object;
                    object->setId(freeChildIndex);

                }
                else
                {
                    unsigned id = _vecObject.size();
                    object->setId(id);
                    _vecObject.push_back(object);
                }
                //_vecObject.push_back(object);

            }
            //std::cout << "IContainer added : "<< object->_name << "\n";
        }
        void del(unsigned index)
        {
            //std::cout << "BEFORE object deleted = " << _vecObject[id]->_name << "\n";
            if (!_vecObject.empty())
                if (index >= 0 && index < _vecObject.size() && _vecObject[index] != nullptr)
                {
                    //log ("- " + _vecObject[id]->_name + " deleted !\n");
                    _vecObject[index]->_isPlay = false;
                    delete _vecObject[index];
                    _vecObject[index] = nullptr;
                    _vecFreeObject.push_back(index);
                }

            //std::cout << "AFTER object deleted = " << _vecObject[id] << "\n";
        }

        void del(const char *name)
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->name() == name)
                        {
                            del(it->id());
                            it = nullptr;
                        }
                }
        }

        void delAll()
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        del(it->id());
                }
        }

        OBJECT *first() const
        {
            return _vecObject.front();
        }

        OBJECT *last() const
        {
            return _vecObject.back();
        }

        int firstId() const
        {
            return _vecObject.front()->id();
        }

        int lastId() const
        {
            return _vecObject.back()->id();
        }

        int getId(int id) const
        {
            if (id >= 0 && id < _vecObject.size() && _vecObject[id] != nullptr)
                return _vecObject[id]->id();
            else
                return nullptr;
        }


        unsigned vecSize() const
        {
            return _vecObject.size();
        }

        unsigned vecSizeFree() const
        {
            return _vecFreeObject.size();
        }

        int numActiveObject() const
        {
            return vecSize() - vecSizeFree();
        }

        bool isFree(int id) const
        {
            if (index >= 0 && index < _vecObject.size())
                if (nullptr != _vecObject[index])
                    return false;

            return true;

        }



        int indexByName(std::string name) const
        {
            if (!_vecObject.empty())
                for (unsigned i = 0; i<_vecObject.size(); i++)
                {
                    if (_vecObject[i] != nullptr)
                        if (_vecObject[i]->name() == name)
                            return i;
                }
            return 0;
        }

        int idByName(std::string name) const
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->_name == name)
                            return it->id();
                }

            return -1;
        }
        // Get unique Object : return first Object*
        // Fast method
        OBJECT* index(unsigned index) const
        {
            if (index >= 0 && index < _vecObject.size())
                if (nullptr != _vecObject[index])
                    return _vecObject[index];

            return nullptr;
        }
        // Slow Method
        OBJECT *at(int id) const
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->_id == id)
                            return it;
                }
            //log("OBJECT not found !");
            return nullptr;
        }
        OBJECT *at(std::string name) const
        {
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->name() == name)
                            return it;
                }

            return nullptr;
        }

        // Get group Object : return vector of Object*
        std::vector<OBJECT*> groupAt(int type) const
        {
            std::vector<OBJECT*> vecObject;
            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->_type == type)
                            vecObject.push_back(it);
                }
            //log("OBJECT not found !");
            return vecObject;
        }
//        std::vector<OBJECT*> groupAt(int id) const
//        {
//            std::vector<OBJECT*> vecObject;
//            if (!_vecObject.empty())
//                for (auto & it: _vecObject)
//                {
//                    if (it != nullptr)
//                        if (it->_id == id)
//                            vecObject.push_back(it);
//                }
//            //log("OBJECT not found !");
//            return vecObject;
//        }
        std::vector<OBJECT*> groupAt(std::string name) const
        {
            std::vector<OBJECT*> vecObject;

            if (!_vecObject.empty())
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                        if (it->name() == name)
                            vecObject.push_back(it);
                }
            //log("OBJECT not found !");

            return vecObject;
        }

        void showAll()
        {
            std::cout << "-- vecObjet --\n";
            for (auto & it:_vecObject)
            {
                if (it != nullptr)
                    std::cout <<" name = "<< it->_name << "\n" ;
            }
        }



    protected:

        std::vector<OBJECT*> _vecObject;
        std::vector<int> _vecFreeObject;
        std::vector<ZIndex*> _vecZIndex;

        void sortZIndex(std::vector<OBJECT*> &vecEntity, std::vector<ZIndex*> &vecZIndex)
        {

            if (vecZIndex.size() < vecEntity.size())
            {
                //mlog("- Resize ZIndex !\n");
                for (unsigned index = vecZIndex.size(); index < vecEntity.size(); ++index)
                {
                    vecZIndex.push_back(new ZIndex());
                }
            }

            for (unsigned index = 0; index < vecZIndex.size(); ++index)
            {
                if (nullptr != vecZIndex[index])
                    vecZIndex[index]->_index = index;
                else
                    continue;

                if (nullptr != vecEntity[index])
                {
                    //if (nullptr != vecEntity[index]->get<Position>())
                    //    vecZIndex[index]->_z = vecEntity[index]->get<Position>()->_z;
                    vecZIndex[index]->_z = vecEntity[index]->_z;

                }
                else
                    vecZIndex[index]->_z = 0;
            }

            std::stable_sort(vecZIndex.begin(), vecZIndex.end(), []( const ZIndex *a, const ZIndex *b ) ->bool
            {
                return a->_z < b->_z;
            });
        }

        unsigned zIndex(unsigned index)
        {
            return _vecZIndex[index]->_index;
        }

    private:
};

#endif // ICONTAINER_H
