# **Databuf**
Header only library implementing a dynamic data buffer.

### **quick start**
Place `databuf.h` in your project folder or include folder.
```c
#include "databuf.h"
```

### **structure**
A databuf is a collection of data structs, each wrapping a primative and containing relevant meta information.

```c
struct databuf {
  data* d;
  int n;
  int next_id;
};
```
```c
struct data{
  void* ptr;
  unsigned int type;
  unsigned int size;
  char* name;
  int id;
}; 
```

### **functions**
Most functions are implemented with generic macros and accept multiple types.
`name` can by either an int for the ID or a char ptr for the name.
`value` can be an int, float, double, char, or any corresponding ptr types. 
`prim_ptr` can be any type of primative ptr, or a ptr to a ptr.
Note that in order to 
force the compiler to recognize constants, you may need to cast and explicitly show type (eg. `(char)'a'`).

#### _creating and freeing a databuf_
Returns an empty databuf, with a null ptr and n = 0.
```c
databuf create_databuf();
```
Frees whatever remains in an allocated databuf.
```c
void free_databuf(databuf*)
```

#### _creating a new variable_
Returns the ID of the newly created data struct.
```c
int new_var(databuf*, name, value);
```

#### _setting an exisiting variable_
Returns an exit code, 0 if it found the variable and set the ptr, 1 if it did not.
```c
int set_var(databuf*, name, value);
```

#### _getting a variable_
Returns an exit code, 0 if it found the variable and set the ptr, 1 if it did not.
```c
int get_var(databuf, name, prim_ptr)
```

#### _freeing variables_
Returns an exit code, 0 if it found and removed the variable, 1 if it did not.
```c
free_var(databuf*, name);
```

#### _printing variables_
Print the value of a data struct.
```c
print_var(buf, name); 
```
Print an entire databufs values.
```c
print_databuf(buf);   
```
Print verbose, includes all information of each data struct in the buffer
```c
printv_databuf(buf);  
```

### **example usage**
```c
databuf buf = create_databuf();
new_var(&buf, "x", 1);
set_var(&buf, "x", 2);
new_var(&buf, "y", 3.14f);
new_var(&buf, "z", (char)'a');
new_var(&buf, "w", "hi");
int x;
get_var(buf, "x", &x);
free_var(&buf, "x");
print_databuf(buf);
free_databuf(&buf);
```
