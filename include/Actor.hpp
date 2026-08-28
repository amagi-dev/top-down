#ifndef ___ACTOTR_HPP___
#define ___ACTOTR_HPP___


class Actor
{
public:

    Actor(){    };

    virtual void Ready(){   };
    virtual void Start(){   };

    virtual void Update(){   };
    virtual void Render(){   };

};

#endif


