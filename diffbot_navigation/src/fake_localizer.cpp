#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_broadcaster.h>
#include <iostream>

void OdomCallback(const nav_msgs::OdometryConstPtr& msg){
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    
    geometry_msgs::Point position = msg->pose.pose.position;
    transform.setOrigin(tf::Vector3(position.x, position.y, position.z));
    
    geometry_msgs::Quaternion orientation = msg->pose.pose.orientation;    
    transform.setRotation(tf::Quaternion(orientation.x, orientation.y, orientation.z, orientation.w));

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_footprint"));

}

int main(int argc, char** argv){
    ros::init(argc, argv, "diffbot_fake_localizer");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/gazebo/odom_gt", 10, &OdomCallback);

    ros::spin();
    return 0;
};