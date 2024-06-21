#pragma once

#ifdef ALMADEN_CAC_EXPORTS
#define ALMADEN_CAC_API __declspec(dllexport)
#else
#define ALMADEN_CAC_API __declspec(dllimport)
#endif

#include "cactypes.hpp"

namespace edgecac {
    
    ALMADEN_CAC_NODE ALMADEN_CAC_API verifyEdgeProcesses();

}
