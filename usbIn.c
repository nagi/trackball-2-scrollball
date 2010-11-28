#include "common.h"

static uchar idleRate;   /* repeat rate for keyboards, never used for mice */

/* This is called by the driver when the host makes a requiest for data. Linux only makes one requrest
 * of type rq->bRequest == USBRQ_HID_GET_REPORT when the device is first plugged in.*/
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t    *rq = (void *)data;
    /* The following requests are never used. But since they are required by
     * the specification, we implement them in this example.
     */
    DBG1(0x66,data,8);
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            /* we only have one report type, so don't look at wValue */
            usbMsgPtr = (void *)&reportBuffer;
            return sizeof(reportBuffer);
        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }else if(rq->bRequest == USBRQ_SET_CONFIGURATION){
            // No need to do anything - we only have one meaning for the date which will follow.
        }
    }else{
        /* no vendor specific requests implemented */
    }
    return USB_NO_MSG;   /* default for not implemented requests: return no data back to host */
}

uchar usbFunctionRead(uchar *data, uchar len)
{
    // No need to do anything - we only have one meaning for the date which will follow.
    return len;
}

uchar usbFunctionWrite(uchar *data, uchar len)
{
    setLights(*data);
    return 1; // Return OK to driver
}
