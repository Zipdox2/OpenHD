#ifndef CAMERA_H
#define CAMERA_H

#include <array>
#include <chrono>
#include <vector>

#include "DPlatform.h"

#include "json.hpp"

#include "openhd-camera.hpp"
#include "openhd-discoverable.hpp"

/**
 * Discover all connected cameras and write them to json.
 */
class DCameras : public OHD::IDiscoverable {
 public:
  DCameras(PlatformType platform_type, BoardType board_type);

  virtual ~DCameras() = default;

  void discover() override;

  void write_manifest() override;

  [[nodiscard]] int count() const {
	return (int)m_cameras.size();
  }
 private:
  /*
   * These are for platform-specific camera access methods, most can also be accessed through v4l2
   * but there are sometimes downsides to doing that. For example on the Pi, v4l2 can have higher latency
   * than going through the broadcom API, and at preset bcm2835-v4l2 doesn't support all of the ISP controls.
   *
   */
  /**
   * This is used when the gpu firmware is in charge of the camera, we have to ask it. This should
   * be the only place in the entire system that uses vcgencmd for this purpose, anything else that
   * needs to know should read from the openhd system manifest instead.
   */
  void detect_raspberrypi_csi();
  /**
   * Something something stephen.
   */
  bool process_v4l2_node(const std::string &node, Camera &camera, CameraEndpoint &endpoint);
  /*
   * Detect all v4l2 cameras, that is cameras that show up as a v4l2 device (/dev/videoXX)
   */
  void detect_v4l2();
  /**
   * Something something stephen.
   */
  void probe_v4l2_device(const std::string &device_node);

  /**
   * TODO unimplemented.
   */
  void detect_ip();

  std::vector<Camera> m_cameras;
  std::vector<CameraEndpoint> m_camera_endpoints;

  int m_discover_index = 0;

  PlatformType m_platform_type;
  BoardType m_board_type;
};

#endif