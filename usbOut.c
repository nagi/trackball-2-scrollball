#include "common.h"

/* ----------------------------- USB interface ----------------------------- */
PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x05,                    // USAGE (Game Pad)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0x02, 0x00,              //     LOGICAL_MAXIMUM (2)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION

    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x06,                    //   USAGE_MAXIMUM (Button 6)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x07,                    //   REPORT_COUNT (2)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x81, 0x01,                    //   INPUT (Constant) - 2 bits are empty   

    0x95, 0x05,   // report count (5)
    0x75, 0x01,   // report size (1)                             Report five bits one time
    0x05, 0x08,   // usage page (page# for LEDs)                 Choose LED usage page
    0x19, 0x01,   // usage minimum (1)
    0x29, 0x05,   // usage maximum (5)                           Define five LEDs
    0x91, 0x02,   // output (data, variable, absolute) The defined bits above are an OUT transaction
    0x95, 0x01,   // report count (1)
    0x75, 0x03,   // report size (3)
    0x91, 0x01,   // output (constant)                           Three bit padding for the OUT transaction

    0xc0                           //   END_COLLECTION
        /*
           UsagePage(Generic Desktop),
           Usage(Game Pad),
           Collection(Application),
           Usage (Pointer),
           Collection (Physical),
           Usage (X),
           Usage (Y),
           Logical Minimum (-1), Logical Maximum (1),
           Report Count (2), Report Size (2),
           Input (Data, Variable, Absolute, No Null),
           End Collection(),
           Report Count (4),
           Report Size (1),
           Input (Constant, Variable, Absolute),          ; 4-bit pad
           Usage Page (Buttons),                          ; Buttons on the stick
           Usage Minimum (Button 1),
           Usage Maximum (Button 6),
           Logical Minimum (0), Logical Maximum (1),
           Report Count (6),
           Report Size (1),
           Input (Data, Variable, Absolute),
           Report Count (2),
           Input (Constant, Variable, Absolute)           ; 2-bit Pad
           End Collection()
           */
};

void usbInitialize()
{
    uchar   i;

    wdt_enable(WDTO_1S);
    /* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET!
     */
    /* RESET status: all port bits are inputs without pull-up.
     * That's the way we need D+ and D-. Therefore we don't need any
     * additional hardware initialization.
     */
    odDebugInit();
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;

    while(--i){             /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }

    usbDeviceConnect();
    sei();
    DBG1(0x10, 0, 0);       /* debug output: Init completed. */
}

