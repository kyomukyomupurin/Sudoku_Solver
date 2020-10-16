#pragma once

#include <iostream>

class Timer {
 public:
  // (second)
  double get_elapsed_time() {
    return static_cast<double>(get_cycle() - start_) /
           static_cast<double>(clock_frequency_);
  }

  void start() { start_ = get_cycle(); }

 private:
  int64_t start_;
  static constexpr int64_t clock_frequency_ = 1800000000;

  int64_t get_cycle() {
    uint32_t low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return (static_cast<int64_t>(low)) | (static_cast<int64_t>(high) << 32);
  }
};