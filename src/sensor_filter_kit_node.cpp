#include "sensor_filter_kit/sensor_filter_kit_lib.h"
#include "imu_interface/gy_88_lib.h"
#include "imu_interface/Gy88Data.h"
#include "ros/ros.h"
#include "iostream"

struct imu_data
{
  float accel_x, accel_y, accel_z;
  float gyro_x, gyro_y, gyro_z;      // Yaw angular acceleration [degrees/s^2]
  unsigned long long timestamp;      // Unix timestamp [ms]
};

imu_data imu_data;

void imu_data_callback(const imu_interface::Gy88Data::ConstPtr& imu_msg)
{
  imu_data.accel_x = imu_msg->accel_x;
  imu_data.accel_y = imu_msg->accel_y;
  imu_data.accel_z = imu_msg->accel_z;
  
  imu_data.gyro_x = imu_msg->gyro_x;
  imu_data.gyro_y = imu_msg->gyro_y;
  imu_data.gyro_z = imu_msg->gyro_z;
}

int main(int argc, char **argv)
{
  const uint window_size = 100;
  const uint SENSOR_NUMBER = 6;
  uint sensors[SENSOR_NUMBER] = {ACCEL_X, ACCEL_Y, ACCEL_Z, GYRO_X, GYRO_Y, GYRO_Z};
  float sensor_readings[SENSOR_NUMBER];
  
  FilterKit filter_kit(SENSOR_NUMBER, window_size);
  
  ROS_INFO("Successfully constructed FilterKit class..");
  
  ros::init(argc, argv, "sensor_filter_kit_node");
  ros::NodeHandle n;
  
  ros::Subscriber imu_sub = n.subscribe("gy88_data", 1000, imu_data_callback);
  ros::Rate loop_rate(10);
  
  std::vector<double> features;
  std::cout << std::fixed;
  std::cout << std::setprecision(4);
  int counter = 0;
  
  while(ros::ok())
  {
    ros::spinOnce();
    sensor_readings[0] = imu_data.accel_x;
    sensor_readings[1] = imu_data.accel_y;
    sensor_readings[2] = imu_data.accel_z;
    sensor_readings[3] = imu_data.gyro_x;
    sensor_readings[4] = imu_data.gyro_y;
    sensor_readings[5] = imu_data.gyro_z;
    
    filter_kit.window(sensor_readings, sensors, SMA);
  
    features = filter_kit.get_features();
    std::cout << counter << " -X_DDOT: - " << imu_data.accel_x << " - " << features.at(0) << \
                            " -Y_DDOT: - " << imu_data.accel_y << " - " << features.at(1) << \
                            " -Z_DDOT: - " << imu_data.accel_z << " - " << features.at(2) << std::endl;
  
    loop_rate.sleep();
    counter++;
  }
}