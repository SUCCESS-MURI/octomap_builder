#pragma once

#include <ros/ros.h>

#include <pcl_ros/point_cloud.h>

#include <tf/transform_listener.h>

#include <string.h>

// Used for moveit's obstacle avoidance.
//  To use it, need to change `point_cloud_topic` in the `moveit_octomap_sensor_params_file` in `move_group.launch`.
class OctomapBuilder {

public:
    OctomapBuilder(ros::NodeHandle &nh, std::string octomap_topic);

    void clear_map();

    void restore_map();

    void process_and_publish(std::string topic);

    //If you call this directly then the restore function will not work
    void publish(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &points);

private:
    ros::NodeHandle &nh;

    tf::TransformListener tf_listener;

    ros::Publisher points_pub;

    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> points_built_on;

};
