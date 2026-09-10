#ifndef __SCRIPT_HPP___
#define __SCRIPT_HPP___


// #include <iostream>
class Actor;
class Script
{
public:
    Script(Actor* actor) : owner(actor)
    {

    }

    virtual ~Script() = default;

    virtual void Start() = 0;
    virtual void Update() = 0;

    virtual void RenderUpdate()const
    {

    };

protected:
    Actor *const owner;
};

#endif

