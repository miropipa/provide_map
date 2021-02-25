import open3d as o3d
import numpy as np
import copy 


print("Load a point cloud, print it, and render it")
pcd = o3d.io.read_point_cloud("/home/anjun/catkin_ws/src/provide_map/map/rotated_ARC_carpark_map.pcd")
pcd_rotated = copy.deepcopy(pcd)


matrix = np.arange(3).reshape(3, 1)
matrix = np.array([[0], [0], [np.pi*11/18]], dtype = np.float64)
rotation_matrix = o3d.geometry.get_rotation_matrix_from_axis_angle(matrix)
pcd_rotated = pcd_rotated.rotate(rotation_matrix)

o3d.io.write_point_cloud("/home/anjun/catkin_ws/src/provide_map/map/rotated_ARC_carpark_map2.pcd", pcd_rotated)

o3d.visualization.draw_geometries([pcd, pcd_rotated])



