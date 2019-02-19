// #include "sensor_filter_kit/sensor_filter_kit_lib.h"
// #include "imu_interface/gy_88_lib.h"
// #include "imu_interface/Gy88Data.h"
// #include "ros/ros.h"
// #include "iostream"


// uulong_t get_millis_since_epoch()
// {
//   uulong_t millis_since_epoch =
//     std::chrono::duration_cast<std::chrono::milliseconds>
//         (std::chrono::system_clock::now().time_since_epoch()).count();

//   return millis_since_epoch;
// }

// void record_data(uulong_t timestamp, ChipMPU6050 chip_mpu6050, ChipHMC5883L chip_hmc5883l)
// {
//   std::ofstream recording_file;
//   recording_file.open ("/home/ubuntu/catkin_ws/src/sensor_filter_kit/sliding_window_10min.csv", std::ios_base::app);
//   recording_file << timestamp << "," << chip_mpu6050.accel_x << "," << chip_mpu6050.accel_y << "," << chip_mpu6050.accel_z << "," << chip_mpu6050.gyro_x << "," << chip_mpu6050.gyro_y << "," << chip_mpu6050.gyro_z << ",\n";
//   recording_file.close();
// }

// struct imu_data
// {
//     // coordinates_2d acceleration;    // Liner acceleration [m/s^2]
//     float x, y;
//     float yaw_vel;                  // Yaw angular acceleration [degrees/s^2]
//     float bearing;                  // Magnetic heading [degrees]
//     unsigned long long timestamp;                // Unix timestamp [ms]
// };

// void imu_data_callback(const imu_interface::Gy88Data::ConstPtr& imu_msg)
// {
//     imu_data.x = imu_msg->accel_x;
//     imu_data.y = imu_msg->accel_y;
//     imu_data.yaw_vel = -imu_msg->gyro_z;
//     imu_data.bearing = imu_msg->compass_angle;
//     imu_data.timestamp = imu_msg->timestamp;
// }

// int main(int argc, char **argv)
// {

//   imu_data imu_data;

//   const uint window_size = 100;
//   const uint SENSOR_NUMBER =  1;
//   uint sensors[SENSOR_NUMBER] = {X_DDOT};
//   FilterKit filter_kit(SENSOR_NUMBER, window_size);

//   ROS_INFO("Successfully constructed FilterKit class..");

//   ros::init(argc, argv, "sensor_filter_kit_node");
//   ros::NodeHandle n;

//   ros::Subscriber imu_sub = n.subscribe("gy88_data", 1000, imu_data_callback);
//   ros::Rate loop_rate(5);

//   float sensor_readings[1];

//   std::vector<double> features;
//   std::cout.precision(3);
//   int counter = 0;

//   while(ros::ok())
//   {
//     ros::spinOnce();
//     sensor_readings[0] = imu_data.x;
    
//     filter_kit.window(sensor_readings, sensors, SMA);

//     features = filter_kit.get_features();
//     std::cout << counter << ": " << imu_data.x << "--" << features.front() << std::endl;

//     loop_rate.sleep();
//     counter++;
//   }
// }