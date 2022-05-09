#!/usr/bin/env python

import sys
import time

def get_range(radius, resolution):
    re = [0]
    num = int(radius / resolution)
    # print("num => %s" %str(num))
    for i in range(num):
        re.append((i+1) * resolution)
        # re.append(-(i+1) * resolution)
    return re

def sum_sqaure(a, b, c):
    re = (a * a) + (b * b) + (c * c)
    return re

def loop_sphere(radius, resolution):
    time_start = time.time()
    re = []

    if radius <= 0:
        return re

    if resolution > radius:
        resolution = radius

    set_range = get_range(radius, resolution)
    # print("set_range => %s" %str(set_range))

    # limit_sq_max = radius + resolution* resolution
    # limit_sq_min = radius - resolution* resolution
    limit_sq_max = radius + resolution
    limit_sq_min = radius - resolution

    len_range = len(set_range)

    tot_points = set()
    for (i_z, z) in enumerate(set_range):
        i_x = len_range - 1
        while i_x >= i_z:
            i_y = 0
            while i_x >= i_y:
                s = sum_sqaure(set_range[i_x], set_range[i_y], set_range[i_z])
                if s >= limit_sq_min and s <= limit_sq_max:
                    for s_x in [-1, 1]:
                        for s_y in [-1, 1]:
                            for s_z in [-1, 1]:
                                p1 = (s_x * set_range[i_x], s_y * set_range[i_y], s_z * set_range[i_z], 'A')
                                p2 = (s_x * set_range[i_y], s_y * set_range[i_x], s_z * set_range[i_z], 'B')
                                p3 = (s_x * set_range[i_z], s_y * set_range[i_y], s_z * set_range[i_x], 'C')
                                for p in [p1, p2, p3]:
                                    tot_points.add(p)
                    # s_x = 1
                    # s_y = 1
                    # s_z = 1
                    # p1 = (s_x * set_range[i_x], s_y * set_range[i_y], s_z * set_range[i_z], 'A')
                    # p2 = (s_x * set_range[i_y], s_y * set_range[i_x], s_z * set_range[i_z], 'B')
                    # p3 = (s_x * set_range[i_z], s_y * set_range[i_y], s_z * set_range[i_x], 'C')

                    for p in [p1, p2, p3]:
                        tot_points.add(p)
                i_y += 1
            i_x -= 1
    print(len(tot_points))     
    time_end = time.time()
    time_duration = time_end - time_start
    print("Duration (s) [function: loop_sphere]: %5.3f" %time_duration)
    
    return (tot_points)

def write_to_pdb(tot_points, fname = "sphere_test_out.pdb"):
    with open(fname, 'w') as fo:
        fo.write('REMARK this is a sphere\n')
        for i, v in enumerate(tot_points):
            # ! ref: https://www.cgl.ucsf.edu/chimera/docs/UsersGuide/tutorials/pdbintro.html
            # ***  "00000 111111111222X2222233    3    4    5555566666666667"
            # ***  "12345-123456789012X3-78901----9----6----5678901234567890"
            line = "ATOM %s C    DUM %s%s    %8.3f%8.3f%8.3f  1.00  0.00  \n" % (f"{str(i+1) : >6}", v[3], f"{str((i+1)%10000) : >4}",v[0],v[1],v[2])
            fo.write(line)
        fo.write('TER')

def benchmark_test():
    # 0.092s
    loop_sphere(1, 0.01)

if __name__ == "__main__":
    time_start = time.time()
    tot_points = loop_sphere(1, 0.01)
    time_end = time.time()
    time_duration = time_end - time_start
    print("Runtime (s): %5.3f" %time_duration)
    write_to_pdb(tot_points, fname = "sphere_test_out.pdb")

