<launch>
 <include file="$(find turtlebot_bringup)/launch/3dsensor.launch">
 <arg name="rgb_processing" value="false" />
 <arg name="depth_registration" value="false" />
 <arg name="depth_processing" value="false" />
 </include>
 <!-- Map server -->
 <arg name="map_file" default="$(find turtlebot_navigation)/maps/willow-2010-02-
18-0.10.yaml"/>
 <node name="map_server" pkg="map_server" type="map_server" args="$(arg
map_file)" />
 <arg name="initial_pose_x" default="0.0"/> <!-- Use 17.0 for willow's map in
simulation -->
 <arg name="initial_pose_y" default="0.0"/> <!-- Use 17.0 for willow's map in
simulation -->
 <arg name="initial_pose_a" default="0.0"/>
44
 <include file="$(find turtlebot_navigation)/launch/includes/_amcl.launch">
 <arg name="initial_pose_x" value="$(arg initial_pose_x)"/>
 <arg name="initial_pose_y" value="$(arg initial_pose_y)"/>
 <arg name="initial_pose_a" value="$(arg initial_pose_a)"/>
 </include>
 <include file="$(find turtlebot_navigation)/launch/includes/_move_base.launch"/>
</launch>
<launch>
 <node name="rviz" pkg="rviz" type="rviz" args="-d $(find
turtlebot_rviz_launchers)/rviz/navigation.rviz"/>

</launch>
