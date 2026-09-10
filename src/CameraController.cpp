#include "CameraController.hpp"
#include "Actor.hpp"


void CameraController::Start()
{
    camera = owner->GetComponent<Camera>();
    transform = owner->GetComponent<Transform>();

}

void CameraController::Update()
{
    transform->position = targetTransform->position;
    camera->camera.target.x = transform->position.x;
    camera->camera.target.y = transform->position.y;
}


