# success_octomap_builder
A package to create an octomap from a specified topic.

## Authors:
Zhao Han, UMass Lowell
Gregory LeMasurier, UMass Lowell

## How to use this package

You can use it as other ROS packages like `pcl_ros` but just need to build it by `catkin_make --pkg octomap_builder` or build the whole workspace.

Here is how you can use it like any other ROS packages.

```cmake
find_package(catkin REQUIRED COMPONENTS
  ...
  octomap_builder
)
```

Then you can `#include <octomap_builder/OctomapBuilder.h>`.

Pass in a nodehandle and the octomap topic that is specified in your `moveit_octomap_sensor_params_file`:
```
ros::NodeHandle nh;

OctomapBuilder octomap_builder(nh, "OCTOMAP_TOPIC");
```

To build an octomap:
```
octomap_builder.process_and_publish("POINTCLOUD TOPIC");
```

To clear the octomap:
```
octomap_builder.clear_map();
```

To restore a map that was created using `process_and_publish()`
```
octomap_builder.restore_map();
```

If you want to process your pointcloud before creating an octomap use:
NOTE: you can not restore an octomap created by calling publish directly.
```
octomap_builder.publish(points);
```
where points is your processed pointcloud of type: `pcl::PointCloud<pcl::PointXYZ>::ConstPtr`