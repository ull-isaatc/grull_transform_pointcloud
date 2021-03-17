#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/transform_listener.h>

#include <pcl/pcl_base.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl_conversions/pcl_conversions.h>

#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>




#include <pluginlib/class_list_macros.h>

namespace grull_transform_pointcloud {
  class transform_pointcloud : public nodelet::Nodelet {
  private:
    ros::Publisher  pub;
    ros::Subscriber sub;
    std::string target_frame;
    tf::TransformListener listener;

    void callback(const sensor_msgs::PointCloud2::ConstPtr &msg) {
      sensor_msgs::PointCloud2::Ptr output = boost::make_shared<sensor_msgs::PointCloud2>();
      
      try {
          // listener.waitForTransform(target_frame, msg->header.frame_id, msg->header.stamp, ros::Duration(0.5));
          // listener.waitForTransform(target_frame, msg->header.frame_id, ros::Time(0), ros::Duration(10.0), ros::Duration(0.01))
          if (pcl_ros::transformPointCloud(target_frame, *msg, *output, listener)) {
              output->header.stamp = msg->header.stamp;//ros::Time::now();
              pub.publish(output);
          }
      } catch (const tf::TransformException & ex) {
          ROS_ERROR_STREAM(ex.what());
      }
    }

  public:
    virtual void onInit() override {

      ros::NodeHandle & n = getNodeHandle();
      ros::NodeHandle & pn = getPrivateNodeHandle();


      target_frame = pn.param<std::string>("target_frame", "");
      pub = n.advertise<sensor_msgs::PointCloud2>("output_topic", 1, true);
      sub = n.subscribe("input_topic", 1, &transform_pointcloud::callback, this);
    }
  };
}

PLUGINLIB_EXPORT_CLASS(grull_transform_pointcloud::transform_pointcloud, nodelet::Nodelet);
