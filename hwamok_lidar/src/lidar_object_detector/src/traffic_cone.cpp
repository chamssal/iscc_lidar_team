// 필요한 헤더 파일 포함
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/extract_clusters.h>
#include <visualization_msgs/MarkerArray.h>
#include <vector>

// Message
#include <lidar_object_detector/TrafficCone.h>
#include "header.h"
#include "dbscan.h"

#include <visualization_msgs/Marker.h>

using namespace std;

// 전역 변수 선언 및 초기화
int cluster_id = 0;
float center_x = 0.0, center_y = 0.0, center_z = 0.0;
pcl::PointXYZI minPoint, maxPoint;
pcl::PointCloud<pcl::PointXYZI> totalcloud_clustered;

//MSG
lidar_object_detector::TrafficCone TrafficConeMsg;

/*dbscan clustering 사용을 위한 변수*/
// int minPoints = 10;          //Core Point 기준 필요 인접점 최소 개수
// double epsilon = 0.3;        //Core Point 기준 주변 탐색 반경

//clustering 사이즈 설정해주어서 사이즈에 해당하는 clustring만 보여줌 - clustering 사이즈에 따라서 인식할 수 있는 물체가 달라짐
// min clustering과 maxclustering size를 이용하여 미션시 라바콘과 실제 차량의 차이를 구별 할 수 있지 않을까 생각됨.
// int minClusterSize = 100;     //Cluster 최소 사이즈
// int maxClusterSize = 10000;   //Cluster 최대 사이즈

//roi 값을 바꿔주면 관심 범위가 달라짐
// ex) xmin,ymin,zmin을 모두 0보다 크게 주면, 범위가 양수의 범위에만 bounding box가 쳐짐
// double xMinROI = 0;
// double xMaxROI = 5;
// double yMinROI = -5;
// double yMaxROI = 5;
// double zMinROI = -5;
// double zMaxROI = 5;

//ROI를 이용하여 걸러내진 못한 물체들을 BoundingBOX변수를 이용하여 한번 더 filtering 할 수 있음.
// double xMinBoundingBox = -3;
// double xMaxBoundingBox = 3;
// double yMinBoundingBox = -3;
// double yMaxBoundingBox = 3;
// double zMinBoundingBox = -3;
// double zMaxBoundingBox = 3; // BoundingBox 크기 범위 지정 변수

int minPoints;
double epsilon; 

int minClusterSize; 
int maxClusterSize; 

double xMinROI, xMaxROI, yMinROI, yMaxROI, zMinROI, zMaxROI; // ROI(PassThrough) 범위 지정 변수

double xMinBoundingBox, xMaxBoundingBox, yMinBoundingBox, yMaxBoundingBox, zMinBoundingBox, zMaxBoundingBox; // BoundingBox 크기 범위 지정 변수 

typedef pcl::PointXYZ PointT;

vector<float> obstacle;
vector< vector<float> > obstacle_vec;

ros::Publisher pubTrafficCone;

ros::Publisher roiPub;       //ROI Publisher
ros::Publisher clusterPub;   //Cluster Publisher
ros::Publisher boundingBoxPub; //Bounding Box Visualization Publisher

void dynamicParamCallback(lidar_object_detector::traffic_hyper_parameterConfig &config, int32_t level) {
  xMinROI = config.traffic_xMinROI;
  xMaxROI = config.traffic_xMaxROI;
  yMinROI = config.traffic_yMinROI;
  yMaxROI = config.traffic_yMaxROI;
  zMinROI = config.traffic_zMinROI;
  zMaxROI = config.traffic_zMaxROI;

  minPoints = config.traffic_minPoints;
  epsilon = config.traffic_epsilon;
  minClusterSize = config.traffic_minClusterSize;
  maxClusterSize = config.traffic_maxClusterSize;

  xMinBoundingBox = config.traffic_xMinBoundingBox;
  xMaxBoundingBox = config.traffic_xMaxBoundingBox;
  yMinBoundingBox = config.traffic_yMinBoundingBox;
  yMaxBoundingBox = config.traffic_yMaxBoundingBox;
  zMinBoundingBox = config.traffic_zMinBoundingBox;
  zMaxBoundingBox = config.traffic_zMaxBoundingBox;
}

// Point cloud callback 함수
void cloud_cb(const sensor_msgs::PointCloud2ConstPtr& inputcloud) {
    // ROS message를 PCL 포인트 클라우드로 변환
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*inputcloud, *cloud);

    TrafficConeMsg = lidar_object_detector::TrafficCone();

    // Visualizing에 필요한 Marker 선언
    visualization_msgs::Marker boundingBox;
    visualization_msgs::MarkerArray boundingBoxArray;

    // Region of Interest (ROI) 필터링
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyzf(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PassThrough<pcl::PointXYZ> xfilter;
    xfilter.setInputCloud(cloud);
    xfilter.setFilterFieldName("x");
    xfilter.setFilterLimits(xMinROI, xMaxROI);
    xfilter.setFilterLimitsNegative(false);
    xfilter.filter(*cloud_xyzf);

    pcl::PassThrough<pcl::PointXYZ> yfilter;
    yfilter.setInputCloud(cloud_xyzf);
    yfilter.setFilterFieldName("y");
    yfilter.setFilterLimits(yMinROI, yMaxROI);
    yfilter.setFilterLimitsNegative(false);
    yfilter.filter(*cloud_xyzf);

    pcl::PassThrough<pcl::PointXYZ> zfilter;
    zfilter.setInputCloud(cloud_xyzf);
    zfilter.setFilterFieldName("z");
    zfilter.setFilterLimits(zMinROI, zMaxROI);
    zfilter.setFilterLimitsNegative(false);
    zfilter.filter(*cloud_xyzf);

    // KD-Tree
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    if (cloud_xyzf->size() > 0) {
        tree->setInputCloud(cloud_xyzf);
    }

    // Segmentation
    vector<pcl::PointIndices> cluster_indices;
    DBSCANKdtreeCluster<pcl::PointXYZ> dc;
    dc.setCorePointMinPts(minPoints);
    dc.setClusterTolerance(epsilon);
    dc.setMinClusterSize(minClusterSize);
    dc.setMaxClusterSize(maxClusterSize);
    dc.setSearchMethod(tree);
    dc.setInputCloud(cloud_xyzf);
    dc.extract(cluster_indices);

    int cluster_id = 0; // 초기화!

    vector<float> left_x;
    vector<float> left_y;
    for (const auto& cluster_index : cluster_indices) {
        pcl::PointCloud<pcl::PointXYZI> eachcloud_clustered;
        float cluster_counts = static_cast<float>(cluster_indices.size());

        // 각 클러스터 내 각 포인트 접근
        for (const auto& point_index : cluster_index.indices) {
            pcl::PointXYZI point;
            point.x = cloud_xyzf->points[point_index].x;
            point.y = cloud_xyzf->points[point_index].y;
            point.z = cloud_xyzf->points[point_index].z;
            point.intensity = cluster_id % 100;
            eachcloud_clustered.push_back(point);
        }

        // 클러스터 바운딩 박스 생성
        boundingBox.header.frame_id = "velodyne";
        boundingBox.ns = "my_namespace";
        boundingBox.id = cluster_id;
        boundingBox.header.stamp = ros::Time::now();
        boundingBox.type = visualization_msgs::Marker::CUBE;
        boundingBox.action = visualization_msgs::Marker::ADD;

        pcl::PointXYZI minPoint, maxPoint;
        pcl::getMinMax3D(eachcloud_clustered, minPoint, maxPoint);

        TrafficConeMsg.lengthX[cluster_id] = abs(maxPoint.x - minPoint.x);   //직육면체 x 모서리 크기
        TrafficConeMsg.lengthY[cluster_id] = abs(maxPoint.y - minPoint.y);   //직육면체 y 모서리 크기
        TrafficConeMsg.lengthZ[cluster_id] = abs(maxPoint.z - minPoint.z);   //직육면체 z 모서리 크기 
        TrafficConeMsg.centerX[cluster_id] = (minPoint.x + maxPoint.x) / 2.0f;
        TrafficConeMsg.centerY[cluster_id] = (minPoint.y + maxPoint.y) / 2.0f;
        TrafficConeMsg.centerZ[cluster_id] = (minPoint.z + maxPoint.z) / 2.0f;

        center_x = TrafficConeMsg.centerX[cluster_id];
        center_y = TrafficConeMsg.centerY[cluster_id];
        center_z = TrafficConeMsg.centerZ[cluster_id];

        // 라이다 센서의 위치는 0,0,0이기 때문에 이를 바탕으로 거리정보를 구할 수 있음
        float distance = sqrt(center_x * center_x + center_y * center_y); //장애물 <-> 차량 거리

        // if ( (xMinBoundingBox < x_len && x_len < xMaxBoundingBox) && (yMinBoundingBox < y_len && y_len < yMaxBoundingBox) && (zMinBoundingBox < z_len && z_len < zMaxBoundingBox) ) {
        //     // vector<float> left_x;
        //     // vector<float> left_y;
        //     boundingBox.header.frame_id = "velodyne";
        //     boundingBox.header.stamp = ros::Time();
        //     boundingBox.ns = cluster_counts; //ns = namespace
        //     boundingBox.id = cluster_id; 
        //     boundingBox.type = visualization_msgs::Marker::CUBE; //직육면체로 표시
        //     boundingBox.action = visualization_msgs::Marker::ADD;
            
        //     // 각 좌표의 중심
        //     boundingBox.pose.position.x = center_x; 
        //     boundingBox.pose.position.y = center_y;
        //     boundingBox.pose.position.z = center_z;

        //     left_x.push_back(center_x);
        //     left_y.push_back(center_y);
 
        //     // cout << "LEFT" << '\n';
        //     // cout << "center x  : " << center_x << '\n';
        //     // cout << "center y  : " << center_y << '\n';
        //     // cout << "\n"; 
            
        //     boundingBox.pose.orientation.x = 0.0;
        //     boundingBox.pose.orientation.y = 0.0;
        //     boundingBox.pose.orientation.z = 0.0;
        //     boundingBox.pose.orientation.w = 1.0; // w 값이 1.0이면, 바운딩 박스의 회전이 없음을 의미. 
        //     //즉, bounding box가 원점에 대해 정렬되어 있어서 회전하지 않은 상태입니다. 이는 bounding box의 모든 면이 축에 평행하게 정렬되어 있을 때 발생할 수 있습니다.
            
        //     // 길이 
        //     boundingBox.scale.x = x_len;
        //     boundingBox.scale.y = y_len;
        //     boundingBox.scale.z = z_len;
            
        //     // bounding box 색깔 설정
        //     boundingBox.color.a = 0.5; //직육면체 투명도, a = alpha
        //     boundingBox.color.r = 0.0; //직육면체 색상 RGB값
        //     boundingBox.color.g = 1.0;
        //     boundingBox.color.b = 0.0;
            
        //     // boundingbox 지속 시간 및 boundingBoxArray에 boundingbox추가
        //     // boundingbox지속시간을 0.1로 준 이유는 cluster한개만 보이는 것은 필요없기 때문에 빠르게 사라지게 하기 위해서 시간을 짧게 설정
        //     // emplace_back은 push_back과 같속
        //     boundingBox.lifetime = ros::Duration(0.1); //box 지속시간
        //     boundingBoxArray.markers.emplace_back(boundingBox);
        // }
        cluster_id++; //intensity 증가

        // Convert to ROS data type
        pcl::PCLPointCloud2 cloud_p;
        pcl::toPCLPointCloud2(eachcloud_clustered, cloud_p);

        sensor_msgs::PointCloud2 cluster;
        pcl_conversions::fromPCL(cloud_p, cluster);
        cluster.header.frame_id = "velodyne";

        clusterPub.publish(cluster);
    }

    TrafficConeMsg.objectCounts = cluster_id;
    pubTrafficCone.publish(TrafficConeMsg);

    // cout << "x" << endl;
    // for(int i = 0; i < left_x.size(); i++){
    //     cout << "[" << i << "]" << left_x[i] << ' ';
    // }
    // cout << '\n';
    // cout << '\n';
    // cout << "y" << endl;
    // for(int i = 0; i < left_y.size(); i++){
    //     cout << "[" << i << "]" <<  left_y[i] << ' ';
    // }
    // cout << endl;
    // Publish ROI and bounding boxes
    pcl::PCLPointCloud2 cloud_cropbox;
    pcl::toPCLPointCloud2(*cloud_xyzf, cloud_cropbox);

    sensor_msgs::PointCloud2 ROI;
    pcl_conversions::fromPCL(cloud_cropbox, ROI);
    ROI.header.frame_id = "velodyne";

    roiPub.publish(ROI);
    boundingBoxPub.publish(boundingBoxArray);


}

int main(int argc, char **argv) {
    ros::init(argc, argv, "traffic_cone_detector");
    ros::NodeHandle nh;
    
    dynamic_reconfigure::Server<lidar_object_detector::traffic_hyper_parameterConfig> server;
    dynamic_reconfigure::Server<lidar_object_detector::traffic_hyper_parameterConfig>::CallbackType f;

    f = boost::bind(&dynamicParamCallback, _1, _2);
    server.setCallback(f);

    ros::Subscriber rawDataSub = nh.subscribe("/velodyne_points", 1, cloud_cb);

    pubTrafficCone = nh.advertise<lidar_object_detector::TrafficCone>("/traffic_cone", 1);
    roiPub = nh.advertise<sensor_msgs::PointCloud2>("/roi", 1);
    clusterPub = nh.advertise<sensor_msgs::PointCloud2>("/cluster", 1);
    boundingBoxPub = nh.advertise<visualization_msgs::MarkerArray>("/boundingBox", 1);

    ros::spin();
 
}