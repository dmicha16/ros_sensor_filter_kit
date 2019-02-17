#include "sensor_filter_kit/sensor_filter_kit_lib.h"

FilterKit::FilterKit(uint sensors[], uint sensor_num, const uint window_size)
{
  window_size_ = window_size;

  WindowContainer window_filler;

  for(int i = 0; i < sensor_num; i++)
  {
    windows_holder_.push_back(window_filler);
  }
}

FilterKit::~FilterKit() {}

void FilterKit::window(int emg_readings[], uint sensors[], uint method)
{
  std::vector<int>::iterator window_it;
  features_.clear();
  for(int i = 0; i < windows_holder_.size(); i++)
  {
    window_it = windows_holder_[i].window.begin();
    windows_holder_[i].window.insert(window_it, emg_readings[sensors[i]]);
  }

  if (windows_holder_[0].window.size() == window_size_)
  {
    for(int i = 0; i < windows_holder_.size(); i++)
    {
      windows_holder_[i].window.pop_back();

      switch (method)
      {
        case INTEGRATE:
          integrate(windows_holder_[i].window);
          break;
        case SSC:
          break;
      }
    }
  }
}

void FilterKit::integrate(std::vector<int> current_window)
{
  int temp_window_value = 0;

  for(int i = 0; i < current_window.size(); i++)
  {
    temp_window_value += current_window[i];
  }

  features_.push_back(temp_window_value);
}

std::vector<double> FilterKit::get_features()
{
  // double* features_array = &features_[0];
  return features_;
}