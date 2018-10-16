#ifndef WIRINGPIWRAPPER_H
#define WIRINGPIWRAPPER_H

/**
 * Wrapper for wiringPi functions.
 * This is to prevent mistakes when develop.
 * it gives output for debuging, and can then compile
 * and run on the pi.
 */

class WiringPi
{
public:
    enum PinDir{
        eInput,
        eOutput
    };

    enum Value
    {
        eLow,
        eHigh
    };

    static void wiringPiSetup();
    static void pinMode(int aPin, PinDir aDir);
    static void digitalWrite(int aPin, Value aVal);

};




#endif // WIRINGPIWRAPPER_H
