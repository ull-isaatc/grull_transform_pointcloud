This package uses a nodelet to transform point clouds to a given frame.

#### Required arguments

- `input_topic`     :  Name of the input `sensor_msgs::PointCloud2` topic.
- `output_topic`    :  Name of the output `sensor_msgs::PointCloud2` topic.
- `target_frame`    :  Name of the desired frame for the transformation.
- `nodelet_manager` :  Name of the nodelet manager to host this nodelet.

#### Optional arguments (`false` by default)

- `publish_tf`      :  Publish a generic transformation.
- `launch_manager`  :  Launch a nodelet manager to host this nodelet.

#### Usage with `velodyne_height_map`

In your launch file:

1. Create a nodelet manager.

        <node pkg="nodelet" type="nodelet" name="EXAMPLE_MANAGER" args="manager"/>

2. Include the launch file of this package, providing the required arguments.
   The output topic must be `/velodyne_points`.

        <include file="$(find grull_transform_pointcloud)/launch/launch.launch">
          <arg name="input_topic"     value="name_of_PointCloud2_topic"/>
          <arg name="output_topic"    value="/velodyne_points"/>
          <arg name="target_frame"    value="frame_id_of_the_world"/>
          <arg name="nodelet_manager" value="EXAMPLE_MANAGER"/>
        </include>

3. Start a `velodyne_height_map` nodelet.

        <node pkg="nodelet" type="nodelet" name="heightmap_nodelet"
              args="load velodyne_height_map/HeightMapNodelet EXAMPLE_MANAGER">
          <param name="cell_size" value="0.1"/>
          <remap from="velodyne_obstacles" to="obstacles"/>
        </node>
