/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2014 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */
#pragma once
#include <string>
#include <stdint.h>
#include <vector>
struct rgb_t
{
  uint8_t r,g,b;

  }  __attribute__((packed));

namespace libfreenect2
{

struct Frame
{
  int width,height,bytes_per_pixel;
  void * data; // for the algorithm
  void * pixeldata; // pixel origin
};


inline Frame prepareFrameRGB(int width, int height, unsigned char * p)
{
  Frame r;
  r.width = width;
  r.height = height;
  r.bytes_per_pixel = 3;
  r.data = p;
  r.pixeldata = p;
  return r;
}

inline Frame prepareFrameRGBA(int width, int height, unsigned char * p)
{
  Frame r;
  r.width = width;
  r.height = height;
  r.bytes_per_pixel = 4;
  r.data = p;
  r.pixeldata = p;
  return r;
}

inline Frame prepareFrame(int width, int height, float * p)
{
  Frame r;
  r.width = width;
  r.height = height;
  r.bytes_per_pixel = 4;
  r.data = p;
  r.pixeldata = p;
  return r;
}


inline Frame prepareFrame(int width, int height, unsigned short * p)
{
  Frame r;
  r.width = width;
  r.height = height;
  r.bytes_per_pixel = 2;
  r.data = p;
  r.pixeldata = p;
  return r;
}


// Allocates a buffer for the size of the color 
struct AllocFrameColor: public Frame
{
    AllocFrameColor(bool hdresolution = false, bool rgb = false, int bordertopbottom = 2)
    {
      width = hdresolution ? 1920: 512;
      height = (hdresolution? 1080:424)+bordertopbottom;
      bytes_per_pixel = rgb ? 3 : 4;
      xdata.resize(width*height*bytes_per_pixel);
      data = xdata.data();
      pixeldata = xdata.data() + bordertopbottom/2*width*bytes_per_pixel;
    }

    std::vector<uint8_t> xdata;
};

/// allocates a frame depth : e.g. undistored
struct AllocFrameDepth : public Frame
{
    // hddepth = true if FullHD othewise Depth resolution
    // intabordertopbottom = 2
    AllocFrameDepth(bool hdresolution = true, int bordertopbottom = 2)
    {
      width = hdresolution ? 1920 : 512;
      height = (hdresolution?1080:424)+bordertopbottom;
      bytes_per_pixel = 4; // sizeof(float)
      xdata.resize(width*height);
      data = xdata.data();
      pixeldata = xdata.data() + bordertopbottom/2*width;
    }
  
    std::vector<float> xdata;
};


class Freenect2Device
{
public:

  /** Parameters of the color camera. */
  struct ColorCameraParams
  {
    float fx, fy, cx, cy;

    float shift_d, shift_m;

    float mx_x3y0; // xxx
    float mx_x0y3; // yyy
    float mx_x2y1; // xxy
    float mx_x1y2; // yyx
    float mx_x2y0; // xx
    float mx_x0y2; // yy
    float mx_x1y1; // xy
    float mx_x1y0; // x
    float mx_x0y1; // y
    float mx_x0y0; // 1

    float my_x3y0; // xxx
    float my_x0y3; // yyy
    float my_x2y1; // xxy
    float my_x1y2; // yyx
    float my_x2y0; // xx
    float my_x0y2; // yy
    float my_x1y1; // xy
    float my_x1y0; // x
    float my_x0y1; // y
    float my_x0y0; // 1
  };

  /** IR camera parameters. */
  struct IrCameraParams
  {
    float fx, fy, cx, cy, k1, k2, k3, p1, p2;
  };


};

class Registration
{
public:
  Registration(const Freenect2Device::IrCameraParams& depth_p, const Freenect2Device::ColorCameraParams& rgb_p);

  // for correct allocation of bigdepth
  int getbigfiltermapsize() const;

  // undistort/register a single depth data point
  void apply(int dx, int dy, float dz, float& cx, float &cy) const;

  void getPointXYZRGB (const Frame* undistorted, const Frame* registered, int r, int c, float& x, float& y, float& z, float& rgb) const;

  using rgbt = rgb_t;

  /*
   * Case in which we have external RGBA color image mycolor and external Depth as floating point mydepth
  
   Frame rgb = prepareFrameRGBA(mycolor);
   Frame depth = prepareFrame(mydepth);
   AllocFrameDepth undistorted(false,0); // depth resolution, no border
   AllocFrameColor registered(false,true,0); // depth resolution, color RGB, no border
   apply4(&rgb,&depth,&undistorted,&registered);
   // Usable Output: Color=registered Depth=undistorted


   If you want instead FullHD output (depth registered over color)

   Frame rgb = prepareFrameRGBA(mycolor);
   Frame depth = prepareFrame(mydepth);
   AllocFrameDepth undistorted(false,0); // depth resolution, no border
   AllocFrameColor registered(false,true,0); // depth resolution, color RGB, no border
   AllocFrameDepth bigdepth(true,2);  
   apply4(&rgb,&depth,&undistorted,&registered,true,&bigdepth);

   // Usable Output: Color=rgb Depth=bigdepth (with offset use origin())
   */

  // undistort/register a whole image RGBA 
  bool apply4(const Frame* rgb, const Frame* depth, Frame* undistorted, Frame* registered, const bool enable_filter = true, Frame* bigdepth = 0) const;

  // undistort/register a whole image RGB
  bool apply3(const Frame* rgb, const Frame* depth, Frame* undistorted, Frame* registered, const bool enable_filter = true, Frame* bigdepth = 0) const;

  // undistort/register a whole image Gray
  bool apply1(const Frame* rgb, const Frame* depth, Frame* undistorted, Frame* registered, const bool enable_filter = true, Frame* bigdepth = 0) const;

  // undistort/register a whole image and automatically dispatch RGBA/RGB/Gray1
  bool apply(const Frame* rgb, const Frame* depth, Frame* undistorted, Frame* registered, const bool enable_filter = true, Frame* bigdepth = 0) const;

public:
  void distort(int mx, int my, float& dx, float& dy) const;
  void depth_to_color(float mx, float my, float& rx, float& ry) const;

  Freenect2Device::IrCameraParams depth;
  Freenect2Device::ColorCameraParams color;

  int distort_map[512 * 424];
  float depth_to_color_map_x[512 * 424];
  float depth_to_color_map_y[512 * 424];
  int depth_to_color_map_yi[512 * 424];
  mutable int mdepth_to_c_off [512 * 424]; // THIS make it NON PARALLEL

  const int filter_width_half;
  const int filter_height_half;
  const float filter_tolerance;
};

} /* namespace libfreenect2 */

