#include <ros/ros.h>
#include "octomap_builder/OctomapBuilder.h"
#include <string.h>

//Topic to get the pointcloud from the robot
const std::string FETCH_TOPIC = "/head_camera/depth_downsample/points";
//Topic specified in your moveit_octomap_sensor_params_file
const std::string OCTOMAP_TOPIC = "rh/points_for_moveit_octomap";

int main(int argc, char **argv) {
    ros::init(argc, argv, "octomap_test");
    ros::NodeHandle nh;

    OctomapBuilder octomap_builder(nh, OCTOMAP_TOPIC);
    octomap_builder.clear_map();

    octomap_builder.process_and_publish(FETCH_TOPIC);

    std::cout << "Press Enter to clear octomap";
    std::cin.ignore();

    octomap_builder.clear_map();

    std::cout << "Press Enter to restore octomap";
    std::cin.ignore();

    octomap_builder.restore_map();

    ros::Duration(1).sleep();

    return 0;
}
