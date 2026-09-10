#include "Actor.hpp"

#include "Script.hpp"

void Actor::Start()
{
    for(auto& c : components)
    {
        std::visit([](Component& cc) { cc.Start(); }, c);
    }

    for(auto& s : scripts)
    {
        s->Start();
    }
}

void Actor::Update()
{
    for(auto& c : components)
    {
        std::visit([](Component& cc) { cc.Update(); }, c);
    }

    for(auto& s : scripts)
    {
        s->Update();
    }
}

void Actor::Render()
{
    for(auto& c : components)
    {
        std::visit([](Component& cc) { cc.Render(); }, c);
    }

    for(auto& s : scripts)
    {
        s->RenderUpdate();
    }
}

