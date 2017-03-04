#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <map>
#include <algorithm>

#include "Animation.h"

struct Clip;

extern std::map<std::string, int> _mapComponentType; // extern for avoid multiple definition

inline int componentType (std::string componentName, bool createNewComponentType = false)
{
    // if Name of component don't exist then create a new component name
    // by increase +1 with the highest id of component !
    if (_mapComponentType.find(componentName) == _mapComponentType.end())
    {
        if (createNewComponentType)
        {
            int lastComponent = -1;

            if (!_mapComponentType.empty())
            {
                // Get the highest element values in the map !
                auto it = std::max_element(_mapComponentType.begin(), _mapComponentType.end(),
                                           [](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2)
                {
                    return p1.second < p2.second;
                });

                lastComponent = it->second;

            }

            _mapComponentType[componentName] = lastComponent+1;
        }
        else
        {
            return 0;
        }
    }
    return _mapComponentType[componentName];
}

struct Component
{
    int _type;
    Clip *_clip = nullptr;

    virtual Component *clone() const = 0;
    virtual ~Component() // Avoid warning when we want to delete Component !
    {

    }

    virtual void update() = 0;
    virtual void render() = 0;


};

template <class DERIVED>
struct ComponentHelper : public Component
{
    virtual Component *clone() const
    {
        return new DERIVED(static_cast<const DERIVED&>(*this));
    }
};


#endif // COMPONENT_H_INCLUDED
