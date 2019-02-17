#include <vector>
// #include <Arduino.h>

typedef unsigned int uint;

enum feature_method {INTEGRATE = 1, SSC = 2};
enum Sensors {sB1 = 0, sB2 = 1, sB3 = 2, sT1 = 3, sT2 = 4, sLT1 = 5, sLT2 = 6, sFree = 7};

typedef struct WindowContainer {
  std::vector<int> window;
} WindowContainer;

class FilterKit
{
  public:
    FilterKit(uint sensors[], uint sensor_num, const uint window_size);
    ~FilterKit();

    void window(int emg_readings[], uint sensors[], uint method);
    std::vector<double> get_features();

  private:
    void integrate(std::vector<int> current_window);

    std::vector<int> readings_window_;
    uint window_size_;
    std::vector<WindowContainer> windows_holder_;
    std::vector<double> features_;
};