#include "LightLevelDetector.h"

using namespace codal;

// Helper function to bounce the fiber call to the class method
void LightLevelDetector_main(void *param)
{
    LightLevelDetector *detector = (LightLevelDetector *)param;
    detector->sense();
}

LightLevelDetector::LightLevelDetector(MicroBitDisplay &_display, uint16_t id) 
    : display(_display)
{
    this->id = id;
    this->state = 0; 
    
    // Create a background thread (Fiber) to poll the sensor safely
    create_fiber(LightLevelDetector_main, (void*)this);
}

void LightLevelDetector::sense()
{
    while(true)
    {
        int level = display.readLightLevel();

        // State: currently dark then it becomes light
        if ((state == 0 || state == MICROBIT_LIGHT_EVT_DARK) && level > LIGHT_THRESHOLD_HIGH)
        {
            state = MICROBIT_LIGHT_EVT_LIGHT;
            Event(this->id, MICROBIT_LIGHT_EVT_LIGHT);
        }
        // State: Currently Light -> Becomes Dark
        else if (state == MICROBIT_LIGHT_EVT_LIGHT && level < LIGHT_THRESHOLD_LOW)
        {
            state = MICROBIT_LIGHT_EVT_DARK;
            Event(this->id, MICROBIT_LIGHT_EVT_DARK);
        }

        // Sleep to save power and let the display update
        // 100ms is fast enough for a music box
        fiber_sleep(100);
    }
}