#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/filters/passthrough.h>
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PCLPointCloud2      PclP;
typedef pcl::PCLPointCloud2::Ptr PPtr;
typedef sensor_msgs::PointCloud2 PclM;

PPtr stage1(new PclP);
PclP stage2;
PclM stage3, output;
pcl::PassThrough<PclP> filter;
Eigen::Matrix4f transform;
ros::Publisher pub;

void filtercallback(const PclM::ConstPtr &msg) {
  pcl_conversions::toPCL(*msg, *stage1);
  filter.setInputCloud(stage1);
  filter.filter(stage2);                   
  pcl_conversions::fromPCL(stage2, stage3);
  pcl_ros::transformPointCloud(transform, stage3, output);
  pub.publish(output);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "grull_flatten_pointcloud");
  ros::NodeHandle n, pn("~");
  double low, high, height;
  pn.getParam("lowest_height",  low);
  pn.getParam("highest_height", high);
  pn.getParam("desired_height", height);
  filter.setFilterFieldName("y");
  filter.setFilterLimits(low, high);
  transform << 1.0, 0.0, 0.0, 0.0,
               0.0, 0.0, 0.0, -height,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0;
  pub = n.advertise<PclM>("output_topic", 1, true);
  ros::Subscriber sub = n.subscribe("input_topic", 1, filtercallback);
  ros::spin();
  return 0;
}
