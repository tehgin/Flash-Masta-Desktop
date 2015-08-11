//
//  usbfwd.h
//  FlashMasta
//
//  Created by Dan on 8/3/15.
//  Copyright (c) 2015 7400 Circuits. All rights reserved.
//

#ifndef __USBFWD_H__
#define __USBFWD_H__


namespace usb
{

  class usb_device;
  class libusb_usb_device;

  class exception;
  class busy_exception;
  class disconnected_exception;
  class interrupted_exception;
  class not_found_exception;
  class timeout_exception;
  class unconfigured_exception;
  class uninitialized_exception;
  class unopen_exception;

};


#endif /* defined(__USBFWD_H__) */
