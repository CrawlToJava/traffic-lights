#include "SemiSegmentDisplay.h"
#include <Arduino.h>

void SemiSegmentDisplay::displayNumber(int *nums, int num)
{
    PORTD = nums[num];
}