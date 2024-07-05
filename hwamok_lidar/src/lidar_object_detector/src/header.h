#ifndef HEADER_H
#define HEADER_H

#include <iostream> 
#include <string>  
#include <vector>
#include <ctime>
#include <chrono>
#include <time.h>
#include <algorithm>
#include <cmath>

#include <ros/ros.h>

#include <sensor_msgs/PointCloud2.h>

#include <pcl/io/pcd_io.h>
#include <pcl/common/common.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/crop_box.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/common/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/progressive_morphological_filter.h>

#include <std_msgs/Bool.h>

#include <lidar_object_detector/Boundingbox.h>
// #include "lidar_object_detector/Waypoint.h"
// #include "lidar_object_detector/Delivery.h"
// #include "lidar_object_detector/DynamicVelocity.h"
//#include "lidar_object_detector/PurePursuit.h"

#include <dynamic_reconfigure/server.h>
#include <lidar_object_detector/traffic_hyper_parameterConfig.h>

// #include "lidar_object_detector/dy_hyper_parameterConfig.h"
// #include "lidar_object_detector/small_st_hyper_parameterConfig.h"
// #include "lidar_object_detector/large_st_hyper_parameterConfig.h"
// #include "lidar_object_detector/de_hyper_parameterConfig.h"
// #include "lidar_object_detector/pk_hyper_parameterConfig.h"
// #include "lidar_object_detector/uturn_hyper_parameterConfig.h"


//#include <race/drive_values.h>


#endif // HEADER_H