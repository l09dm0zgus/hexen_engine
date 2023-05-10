//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_ICOMPONENT_H
#define BATTLEBLAZE_ICOMPONENT_H
#include "../core/memory_pool/AllocatedObject.h"
namespace comp
{
    class IComponent : public core::mem::AllocatedObject
    {
    public:
        ~IComponent() = default;;
        virtual void start() = 0;
        virtual void update(float deltaTime) = 0;
    };
}


#endif //BATTLEBLAZE_ICOMPONENT_H
