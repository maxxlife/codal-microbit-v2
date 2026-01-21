#ifndef LIGHT_LEVEL_DETECTOR_H
#define LIGHT_LEVEL_DETECTOR_H

#include "CodalConfig.h"
#include "CodalComponent.h"
#include "Event.h"
#include "MicroBitDisplay.h"

#define MICROBIT_ID_LIGHT_DETECTOR      9000 
#define MICROBIT_LIGHT_EVT_DARK         1
#define MICROBIT_LIGHT_EVT_LIGHT        2

// Thresholds
#define LIGHT_THRESHOLD_HIGH            150  
#define LIGHT_THRESHOLD_LOW             50   

namespace codal
{
    class LightLevelDetector : public CodalComponent
    {
        MicroBitDisplay &display;
        uint16_t        state; 

    public:
        LightLevelDetector(MicroBitDisplay &_display, uint16_t id = MICROBIT_ID_LIGHT_DETECTOR);
        
        // replacing periodicCallback with a dedicated polling thread
        void sense(); 
    };
}
#endif