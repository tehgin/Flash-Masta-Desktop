//
//  ngp_linkmasta_device.h
//  FlashMasta
//
//  Created by Dan on 7/24/15.
//  Copyright (c) 2015 7400 Circuits. All rights reserved.
//

#ifndef __NGP_LINKMASTA_DEVICE_H__
#define __NGP_LINKMASTA_DEVICE_H__

#include "usb/usbfwd.h"
#include "linkmasta_device.h"
#include "cartridge/ngp_cartridge.h"

class ngp_linkmasta_device: public linkmasta_device
{
public:
  
  // Constructors, initializers, and destructors
  /*constructor*/  ngp_linkmasta_device(usb::usb_device* usb_device);
  /*destructor */  ~ngp_linkmasta_device();
  void             init();
  
  // Getters
  bool             is_open() const;
  timeout_t        timeout() const;
  version_t        firmware_version();
  
  // Setters
  void             set_timeout(timeout_t timeout);
  
  // Operations
  void             open();
  void             close();
  data_t           read_byte(chip_index chip, address_t address);
  void             write_byte(chip_index chip, address_t address, data_t data);
  
  bool             supports_read_bytes() const;
  bool             supports_program_bytes() const;
  bool             supports_erase_chip() const;
  bool             supports_erase_chip_block() const;
  bool             supports_read_manufacturer_id() const;
  bool             supports_read_device_id() const;
  bool             supports_read_block_protection() const;
  
  unsigned int     read_bytes(chip_index chip, address_t start_address, data_t* buffer, unsigned int num_bytes, task_controller* controller = nullptr);
  unsigned int     program_bytes(chip_index chip, address_t start_address, const data_t* buffer, unsigned int num_bytes, bool bypass_mode, task_controller* controller = nullptr);
  void             erase_chip(chip_index chip);
  void             erase_chip_block(chip_index chip, address_t block_address);
  unsigned int     read_manufacturer_id(chip_index chip);
  unsigned int     read_device_id(chip_index chip);
  bool             read_block_protection(chip_index chip, address_t block_address);
  
private:
  void             fetch_firmware_version();
  
  // Resources
  usb::usb_device* const m_usb_device;
  
  // Status flags
  bool             m_was_init;
  bool             m_is_open;
  bool             m_firmware_version_set;
  
  // Cached values
  unsigned int     m_firmware_major_version;
  unsigned int     m_firmware_minor_version;
};

#endif /* defined(__NGP_LINKMASTA_DEVICE_H__) */