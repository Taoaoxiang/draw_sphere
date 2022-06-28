# draw_sphere

Let's draw sphere in different ways!
- [x] Loop #1
    - [X] Python
    - [X] C++
- [x] Recursion #1
    - [X] Python
    - [ ] C++
- [ ] Others

***

## Loop #1

### Benchmark performance: 
* Python: 0.087s
* C++: 0.187s
### Total points: 
* Python: 125834
* C++: 126678

### Method: 

1. Iterate Z-axis [0, r], val: c
2. Iterate X-axis [r, c], val: a 
3. Iterate Y-axis [0, a], val: b
4. Draw a point (a, b, c) in the red area  
5. Draw a point (b, a, c) in the green area 
6. Draw a point (c, b, a) in the blue area
7. Iterate 8 octants (+,+,+) to (-,-,-)

### Representation (VMD):

![alt text](images/loop_model.jpg)

***

### Benchmark performance: 
* Python: 2.988s
* C++: 
### Total points: 
* Python: 125858
* C++: 

### Method:

1. Go over the first octant, find a qualified point (a, b, c)
2. Store the point (a, b, c)
3. Move the point, one direction at one time
    * (a +/- resolution, b, c)
    * (a, b +/- resolution, c)
    * (a, b, c +/- resolution)   
4. Iterate 8 octants (+,+,+) to (-,-,-)

> **_Note_**:  
> If the terminal complains about `Segmentation fault (core dumped)`, 
> modify `ulimit` in termial with the command below:
> `ulimit -s unlimited`

### Representation (VMD):

![alt text](images/recursion_model.jpg)

***

