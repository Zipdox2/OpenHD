//
// Created by consti10 on 03.01.23.
//

#ifndef OPENHD_OPENHD_OHD_INTERFACE_INC_ETHERNET_LISTENER_H_
#define OPENHD_OPENHD_OHD_INTERFACE_INC_ETHERNET_LISTENER_H_

#include <atomic>
#include <memory>
#include <openhd-external-device.hpp>
#include <thread>

// Same pattern as usb_tether_listener.h
// See it for more info.
class EthernetListener{
 public:
  explicit EthernetListener(std::shared_ptr<openhd::ExternalDeviceManager> external_device_manager);
  ~EthernetListener();
 private:
  std::shared_ptr<spdlog::logger> m_console;
  std::shared_ptr<openhd::ExternalDeviceManager> m_external_device_manager;
  std::unique_ptr<std::thread> m_check_connection_thread;
  std::atomic<bool> m_check_connection_thread_stop =false;
  void loop_infinite();
  void connect_once();
};

#endif  // OPENHD_OPENHD_OHD_INTERFACE_INC_ETHERNET_LISTENER_H_
