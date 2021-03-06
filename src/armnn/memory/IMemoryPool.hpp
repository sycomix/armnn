//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//
#pragma once

#include "arm_compute/runtime/IMemoryPool.h"

namespace armnn
{

class IMemoryPool : public arm_compute::IMemoryPool
{
public:
    /// Allocates memory for the entire pool
    virtual void AllocatePool() = 0;

    /// Releases all memory associated with the pool
    virtual void ReleasePool() = 0;
};

} // namespace armnn