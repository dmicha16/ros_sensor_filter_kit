#include <vector>
#include "iostream"

#define ALPHA_WEIGHT 0.5

typedef unsigned int uint;

enum feature_method {SMA = 1, EMA = 2, KALMAN = 3};
enum imu_dof {X_DDOT = 0, Y_DDOT = 1, Z_DDOT = 2, PHI_DOT = 3, \
  THETA_DOT = 4, PSI_DOT = 5};

typedef struct WindowContainer {
  std::vector<float> window;
} WindowContainer;

class FilterKit
{
  public:
    FilterKit(uint sensor_num, const uint window_size);
    ~FilterKit();

    void window(float sensor_readings[], uint sensors[], uint method);
    std::vector<double> get_features();

  private:

    // Simple Moving Average (SMA)
    void sma_(std::vector<float> current_window);

    // Exponential moving average (EMA)
    void ema_(std::vector<float> current_window);
    float previous_ema_;

    uint window_size_;
    std::vector<WindowContainer> windows_holder_;
    std::vector<double> features_;
};