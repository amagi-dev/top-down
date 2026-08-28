#ifndef ___COMPONENT_HPP___
#define ___COMPONENT_HPP___

class Actor;
class Component
{
public:

    Component(){    };

    virtual void Ready(){   };
    virtual void Start(){   };

    virtual void Update(){   };
    virtual void Render(){   };

    Actor* owner = nullptr;
};





/*############################################################
 * Default Component Types
############################################################ */

class Transform : public Component
{

};

#endif


