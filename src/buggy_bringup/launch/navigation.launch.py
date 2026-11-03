from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    waypoint_manager = Node(
        package="buggy_navigation",
        executable="waypoint_manager",
        name="waypoint_manager",
        output="screen",
        parameters=[
            "/home/anand/buggy_ws/src/buggy_navigation/config/waypoints.yaml"
        ],
    )

    return LaunchDescription([
        waypoint_manager
    ])
