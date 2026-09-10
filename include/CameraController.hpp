#ifndef ___CAMERA_CONTROLLER_HPP___
#define ___CAMERA_CONTROLLER_HPP___

#include "Script.hpp"

class Camera;
class Transform;
class CameraController : public Script
{
public:
    using Script::Script;
    virtual ~CameraController() = default;


    Camera* camera = nullptr;
    Transform* targetTransform = nullptr;
    Transform   *transform = nullptr;
    void Start() override;
    void Update() override;



private:

};

#endif
