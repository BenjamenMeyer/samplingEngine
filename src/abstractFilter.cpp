#include <samplingEngineInternal/interfaces/abstractFilter.h>
#include <samplingEngine/error_codes.h>

#include <stdlib.h>
#include <string.h>

namespace samplingEngine {
    namespace interfaces {

    abstractFilter::abstractFilter()
        {
        }
    void abstractFilter::add_dependencies(abstractFilter* _filter)
        {
        dependencies.push_back(_filter);
        };

    void abstractFilter::reset_dependencies()
        {
        dependencies.clear();
        };

    }
}


