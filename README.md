# draw_sphere

Let's draw sphere in different ways!
- [x] Loop #1
- [ ] Recursion
- [ ] Others

***

## Loop #1

### Benchmark performance: 0.092s

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

## Recursion [TODO]

### Benchmark performance: ???

### Method: ???


