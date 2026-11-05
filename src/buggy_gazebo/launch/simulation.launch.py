import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import ExecuteProcess


def generate_launch_description():

    gazebo_share = get_package_share_directory('buggy_gazebo')
    description_share = get_package_share_directory('buggy_description')

    world_file = os.path.join(
        gazebo_share,
        'worlds',
        'buggy_world.sdf'
    )

    model_path = os.path.join(
        description_share,
        'models'
    )

    existing_path = os.environ.get('GZ_SIM_RESOURCE_PATH', '')

    resource_path = model_path

    if existing_path:
        resource_path += os.pathsep + existing_path

    gazebo = ExecuteProcess(
        cmd=[
            'gz',
            'sim',
            '-r',
            world_file
        ],
        output='screen',
        additional_env={
            'GZ_SIM_RESOURCE_PATH': resource_path
        }
    )

    return LaunchDescription([
        gazebo
    ])
