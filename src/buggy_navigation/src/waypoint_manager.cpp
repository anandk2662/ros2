#include<rclcpp/rclcpp.hpp>
#include<nav_msgs/msg/path.hpp>
#include<geometry_msgs/msg/pose_stamped.hpp>
#include<vector>
#include <chrono>
#include <functional>
#include <utility>

class WayPointManager: public rclcpp::Node{
    public:
        WayPointManager():Node ("waypoint_manager"){
            path_publisher_ = this->create_publisher<nav_msgs::msg::Path>("/planning/path",10);
            this->declare_parameter("waypoints", std::vector<double>{});
            this->declare_parameter<double>(
                "origin_latitude",
                0.0
            );

            this->declare_parameter<double>(
                "origin_longitude",
                0.0
            );
            waypoints_ =
            this->get_parameter("waypoints").as_double_array();

            const double origin_latitude =
                this->get_parameter("origin_latitude").as_double();

            const double origin_longitude =
            this->get_parameter("origin_longitude").as_double();

            timer_ = this->create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&WayPointManager::publish_path,this)
            );

            RCLCPP_INFO(this->get_logger(),"waypoint manager started!");
        } 
    private:
            rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_publisher_;
            
            rclcpp::TimerBase::SharedPtr timer_;
            std::vector<double> waypoints_;

            void publish_path(){
                nav_msgs::msg::Path path;
                path.header.stamp = this->now();
                path.header.frame_id = "map";


                for (size_t i = 0; i + 1 < waypoints_.size(); i += 2)
                {
                    geometry_msgs::msg::PoseStamped pose;

                    pose.header.stamp = this->now();
                    pose.header.frame_id = "map";

                    pose.pose.position.x = waypoints_[i];
                    pose.pose.position.y = waypoints_[i + 1];
                    pose.pose.position.z = 0.0;

                    pose.pose.orientation.x = 0.0;
                    pose.pose.orientation.y = 0.0;
                    pose.pose.orientation.z = 0.0;
                    pose.pose.orientation.w = 1.0;

                    path.poses.push_back(pose);
                }

                path_publisher_->publish(path);

                RCLCPP_INFO(
                    this->get_logger(),
                    "Published path with %zu waypoints",
                    path.poses.size()
                );
            }
            
        };

int main(int argc , char* argv[]){
    rclcpp::init(argc,argv);

    auto node = std::make_shared<WayPointManager>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}