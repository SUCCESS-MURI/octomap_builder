#include "octomap_builder/OctomapBuilder.h"

#include <std_srvs/Empty.h>

#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_ros/transforms.h>

#include <string.h>

OctomapBuilder::OctomapBuilder(ros::NodeHandle &nh, std::string octomap_topic) : nh(nh) {
    points_pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ>>(octomap_topic, 1);
}

void OctomapBuilder::clear_map() {

    ROS_INFO_STREAM("[OctomapBuilder] wait service /clear_octomap...");
    ros::service::waitForService("/clear_octomap");
    ROS_INFO_STREAM("[OctomapBuilder] ... done");
    ros::ServiceClient clear_octomap_srv = nh.serviceClient<std_srvs::Empty>("/clear_octomap");
    std_srvs::Empty srv;
    auto result = clear_octomap_srv.call(srv);
    ROS_INFO_STREAM("[OctomapBuilder] calling /clear_octomap...");
    ROS_INFO_STREAM("[OctomapBuilder] " << std::boolalpha << result);
}

void OctomapBuilder::restore_map() {
    for (auto cloud : points_built_on)
        publish(cloud);
}

void OctomapBuilder::process_and_publish(std::string topic) {
    auto points = ros::topic::waitForMessage<pcl::PointCloud<pcl::PointXYZ>>(topic, nh);
    ROS_INFO_STREAM("[OctomapBuilder] raw: " << points->size() << " points");

    pcl::PointCloud<pcl::PointXYZ>::Ptr no_outlier(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud(points);
    sor.setMeanK(50);
    sor.setStddevMulThresh(1.0);
    sor.filter(*no_outlier);
    ROS_INFO_STREAM("[OctomapBuilder] after cleaned: " << no_outlier->size() << " points");

    publish(no_outlier);
    points_built_on.emplace_back(no_outlier);
}

void OctomapBuilder::publish(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &points) {
    points_pub.publish(points);
    ros::spinOnce();
}