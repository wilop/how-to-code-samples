/*
* Copyright (c) 2015 - 2016 Intel Corporation.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GROVEKIT_HPP_
#define GROVEKIT_HPP_

#include "grove.hpp"
#include <jhd1313m1.hpp>
#include <grovemoisture.hpp>

// The hardware devices that the example is going to connect to
struct Devices
{
  upm::GroveLight* light;
  upm::Jhd1313m1* screen;
  upm::GroveMoisture* moisture;
  int moistureReading = 0;
  int lightReading = 0;
  bool turnedOn = false;
  bool turnedOff = false;

  Devices() {
  };

  // Initialization function
  void init() {
    // screen connected to the default I2C bus
    screen = new upm::Jhd1313m1(0, 0x3E, 0x62);

    // Light sensor attached to A0
    light = new upm::GroveLight(0);

    // moisture sensor attached to A1
    moisture = new upm::GroveMoisture(1);
  };

  // Cleanup on exit
  void cleanup() {
    delete screen;
    delete moisture;
    delete light;
  }

  // Reads the current value from the moisture sensor
  int readMoisture() {
    return moisture->value();
  }

  // Reads the current value from the light sensor
  int readLight() {
    return light->value();
  }

  // Is the light supposed to be turned on?
  bool turned_on() {
    return turnedOn;
  }

  // Is the light supposed to be turned off?
  bool turned_off() {
    return turnedOff;
  }

  // Turn on the light
  void turn_on() {
    if (turnedOn) return;
    turnedOn = true;
    turnedOff = false;
    message("on");
  }

  // Turn off the light
  void turn_off() {
    if (turnedOff) return;
    turnedOn = false;
    turnedOff = true;
    message("off");
  }

  // Display the current time on the LCD
  void display_time(struct tm* timeinfo) {
    char buffer[80];
    strftime(buffer, 80, "%I:%M:%S", timeinfo);
    std::string str(buffer);

    message(str, 0x00ff00);
  }

  // Display a message on the LCD
  void message(const std::string& input, const std::size_t color = 0x0000ff) {
    std::size_t red = (color & 0xff0000) >> 16;
    std::size_t green = (color & 0x00ff00) >> 8;
    std::size_t blue = (color & 0x0000ff);

    std::string text(input);
    text.resize(16, ' ');

    screen->setCursor(0, 0);
    screen->write(text);
    screen->setColor(red, green, blue);
  }
};

#endif /* GROVEKIT_HPP_ */
