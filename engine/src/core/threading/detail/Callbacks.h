//
// Created by cx9ps3 on 20.07.2023.
//

#pragma once

namespace core::threading::detail
{
    using ThreadCreationCallback = void (*)(void *context, unsigned threadCount);

    using FiberCreationCallback = void (*)(void *context, unsigned fiberCount);

    using ThreadEventCallback = void (*)(void *context, unsigned threadIndex);

    using FiberAttachedCallback = void (*)(void *context, unsigned fiberIndex);

    using FiberDetachedCallback = void (*)(void *context, unsigned fiberIndex, bool isMidTask);

    struct EventCallbacks
    {
        void *Context = nullptr;

        ThreadCreationCallback onThreadsCreated = nullptr;
        FiberCreationCallback onFibersCreated = nullptr;

        ThreadEventCallback onWorkerThreadStarted = nullptr;
        ThreadEventCallback onWorkerThreadEnded = nullptr;

        FiberAttachedCallback onFiberAttached = nullptr;
        FiberDetachedCallback onFiberDetached = nullptr;
    };
}