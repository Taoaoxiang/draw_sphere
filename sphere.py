#!/usr/bin/env python

import sys
sys.setrecursionlimit(1000000000)
import time
import math


# ! ref: https://en.wikipedia.org/wiki/Octant_(solid_geometry)
OCTANTS = [
    (1,1,+1), (-1,1,+1), (-1,-1,+1), (1,-1,+1),
    (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,-1)
]

def get_range(radius, resolution):
    resolution = round(resolution, 3)
    re = [0]
    num = int(radius / resolution)
    # print("num => %s" %str(num))
    for i in range(num):
        re.append(round((i+1) * resolution, 3))
        # re.append(-(i+1) * resolution)
    return re

def sum_sqaure(a, b, c):
    re = (a * a) + (b * b) + (c * c)
    return re

def loop_sphere(radius, resolution, debug = False):
    time_start = time.time()

    if radius <= 0:
        return []

    if resolution > radius:
        resolution = radius

    set_range = get_range(radius, resolution)
    # print("set_range => %s" %str(set_range))

    # limit_sq_max = radius + resolution* resolution
    # limit_sq_min = radius - resolution* resolution
    limit_sq_max = radius + resolution
    limit_sq_min = radius - resolution

    len_range = len(set_range)

    global RECURSION_SET
    RECURSION_SET = set()

    for (i_z, z) in enumerate(set_range):
        i_x = len_range - 1
        while i_x >= i_z:
            i_y = 0
            while i_x >= i_y:
                s = sum_sqaure(set_range[i_x], set_range[i_y], set_range[i_z])
                if s >= limit_sq_min and s <= limit_sq_max:
                    RECURSION_SET.add( (set_range[i_x], set_range[i_y], set_range[i_z]) )
                    RECURSION_SET.add( (set_range[i_y], set_range[i_x], set_range[i_z]) )
                    RECURSION_SET.add( (set_range[i_z], set_range[i_y], set_range[i_x]) )
                i_y += 1
            i_x -= 1
    tot_points = set()
    if not debug:
        for (s_x, s_y, s_z) in OCTANTS:
            for p in RECURSION_SET:
                tot_points.add((s_x * p[0], s_y * p[1], s_z * p[2]))
    else:
        tot_points = RECURSION_SET

    print(len(tot_points))     
    time_end = time.time()
    time_duration = time_end - time_start
    print("Duration (s) [function: loop_sphere]: %5.3f" %time_duration)
    
    return (tot_points)

def recursion_sphere(radius, resolution, debug = False):
    time_start = time.time()

    global RECURSION_SET
    RECURSION_SET = set()

    limit_sq_max = radius + resolution
    limit_sq_min = radius - resolution
    p0 = [radius, 0, 0]
    recursive_sphere(p0, radius, resolution, limit_sq_min, limit_sq_max)
    tot_points = set()
    if not debug:
        for (s_x, s_y, s_z) in OCTANTS:
            for p in RECURSION_SET:
                tot_points.add((s_x * p[0], s_y * p[1], s_z * p[2]))
    else:
        tot_points = RECURSION_SET
    print(len(tot_points)) 
    time_end = time.time()
    time_duration = time_end - time_start
    print("Duration (s) [function: recursion_sphere]: %5.3f" %time_duration)
    return (tot_points)

def recursive_sphere(p, r, resolution, limit_min, limit_max):
    if p[0] < 0 or p[1] < 0 or p[2] < 0 or p[0] > r or p[1] > r or p[2] > r:
        return

    s = sum_sqaure(p[0], p[1], p[2])    
    if s >= limit_min and s <= limit_max:
        RECURSION_SET.add(tuple(p))

    for i in range(3):
        p1 = list(p)
        p1[i] = round(p1[i] + resolution, 3)
        if s <= limit_max and tuple(p1) not in RECURSION_SET:
            recursive_sphere(p1, r, resolution, limit_min, limit_max)
        p2 = list(p)
        p2[i] = round(p2[i] - resolution, 3)
        if s >= limit_min and tuple(p2) not in RECURSION_SET:
            recursive_sphere(p2, r, resolution, limit_min, limit_max)
    
    return

def loop_sphere_geometry(radius, resolution, debug = False):
    time_start = time.time()

    if radius <= 0:
        return []

    if resolution > radius:
        resolution = radius

    set_range = get_range(radius, resolution)
    # print("set_range => %s" %str(set_range))

    # limit_sq_max = radius + resolution* resolution
    # limit_sq_min = radius - resolution* resolution
    limit_sq_max = radius + resolution
    limit_sq_min = radius - resolution

    len_range = len(set_range)

    global RECURSION_SET
    RECURSION_SET = set()

    for (i_z, z) in enumerate(set_range):
        i_x = len_range - 1
        while i_x >= i_z:
            
            y_list_index = []
            loop_up = True
            loop_down = True
            y_up = len_range
            y_down = -1
            diff = radius*radius - set_range[i_x]*set_range[i_x] - set_range[i_z]*set_range[i_z]
            # print("TEST => i_x: %s, i_z: %s, diff: %f " %(i_x, i_z, diff))

            try:
                diff_sqrt = math.sqrt(diff)
            except:
                diff_sqrt = 0

            index_y = min(range(len(set_range)), key=lambda i: abs(set_range[i]-diff_sqrt))
            s = sum_sqaure(set_range[i_x], set_range[index_y], set_range[i_z])
            if s >= limit_sq_min and s <= limit_sq_max:
                y_list_index.append(index_y)
            y_up = index_y + 1
            y_down = index_y -1
            
            while (y_up < len_range) and loop_up:
                s = sum_sqaure(set_range[i_x], set_range[y_up], set_range[i_z])
                if s >= limit_sq_min and s <= limit_sq_max:
                    y_list_index.append(y_up)
                else:
                    loop_up = False
                y_up += 1

            while (y_down >= 0) and loop_down:
                s = sum_sqaure(set_range[i_x], set_range[y_down], set_range[i_z])
                if s >= limit_sq_min and s <= limit_sq_max:
                    y_list_index.append(y_down)
                else:
                    loop_down = False
                y_down -= 1
            
            for i_y in y_list_index:
                RECURSION_SET.add( (set_range[i_x], set_range[i_y], set_range[i_z]) )
                # RECURSION_SET.add( (set_range[i_y], set_range[i_x], set_range[i_z]) )
                RECURSION_SET.add( (set_range[i_z], set_range[i_y], set_range[i_x]) )
            
            i_x -= 1

    tot_points = set()
    if not debug:
        for (s_x, s_y, s_z) in OCTANTS:
            for p in RECURSION_SET:
                tot_points.add((s_x * p[0], s_y * p[1], s_z * p[2]))
    else:
        tot_points = RECURSION_SET

    print(len(tot_points))     
    time_end = time.time()
    time_duration = time_end - time_start
    print("Duration (s) [function: loop_sphere_geometry]: %5.3f" %time_duration)
    
    return (tot_points)


def write_to_pdb(tot_points, fname = "sphere_test_out.pdb"):
    with open(fname, 'w') as fo:
        fo.write('REMARK this is a sphere\n')
        for i, v in enumerate(tot_points):
            if len(v) < 4:
                v3 = 'A'
            else:
                v3 = v[3]
            x = v[0]
            y = v[1]
            z = v[2]
  
            # ! ref: https://www.cgl.ucsf.edu/chimera/docs/UsersGuide/tutorials/pdbintro.html
            # ***  "00000 111111111222X2222233    3    4    5555566666666667"
            # ***  "12345-123456789012X3-78901----9----6----5678901234567890"
            line = "ATOM %s C    DUM %s%s    %8.3f%8.3f%8.3f  1.00  0.00  \n" % (f"{str(i+1) : >6}", v3, f"{str((i+1)%10000) : >4}",x,y,z)
            fo.write(line)
        fo.write('TER\n')

def benchmark_test():
    print("====Benchmark====")
    # Time(s): 0.087
    # Points: 125834
    tot_points = loop_sphere(1, 0.01)
    write_to_pdb(tot_points, fname = "benchmark_loop.pdb")

    # ! Note: set the stack for the environment
    # ! cmd: ulimit -s unlimited
    # Time(s): 2.988
    # Points: 125858
    tot_points= recursion_sphere(1, 0.01)
    write_to_pdb(tot_points, fname = "benchmark_recursion.pdb")

    # Time(s): 0.088
    # Points: 125858
    tot_points = loop_sphere_geometry(1, 0.01)
    write_to_pdb(tot_points, fname = "benchmark_loop_geometry.pdb")
    print("====Benchmark Finished====\n")

def debug_test():
    print("====Debug====")
    tot_points = loop_sphere(1, 0.01, True)
    write_to_pdb(tot_points, fname = "debug_loop.pdb")

    tot_points = recursion_sphere(1, 0.01, True)
    write_to_pdb(tot_points, fname = "debug_recursion.pdb")

    tot_points = loop_sphere_geometry(1, 0.01, True)
    write_to_pdb(tot_points, fname = "debug_loop_geometry.pdb")
    print("====Debug Finished====\n")

if __name__ == "__main__":
    time_start = time.time()
    debug_test()
    benchmark_test()
    time_end = time.time()
    time_duration = time_end - time_start
    print("Runtime (s): %5.3f" %time_duration)

