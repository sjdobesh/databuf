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

### **usage**
#### Basic use cases. 
Making variables, setting, getting, and deleting them.
```c
databuf buf = create_databuf(); // make a buffer
new_var(&buf, "x", 1);          // make a new variable
set_var(&buf, "x", 2);          // set existing variable
int x; 
get_var(buf, "x", &x);          // get a value into a local variable
print_var(buf, "x");            // prints associated value
free_var(&buf, "x");            // free variable from the buffer
[or]
free_databuf(&buf);             // frees the entire databuffer
```
#### **type generic arguments**
`new_var()`, `free_var()`, `set_var()`, `get_var()`, and `print_var()` are all type generic. The value may be any type and the name can be either the user given string name or the id number returned from `new_var()`. With some constant inputs, you may need to cast in order for it to be the type you expect. For example, `'a'` is an int, `(char)'a'` is a char and `3.14` is a double, `3.14f` is a float.
```c
new_var(&buf, "x", 1);         // int
new_var(&buf, "y", 3.14f);     // float
new_var(&buf, "z", 6.28);      // double
new_var(&buf, "w", (char)'a'); // char
new_var(&buf, "s", "hi");      // char*
new_var(&buf, "p", (int*)&x);  // int*
int id = new_var(&buf, "a", 1);
int a;
get_var(buf, id, &a); // we can search by name or by unique id
```

### **functions**
Most functions are implemented with generic macros and accept multiple types.
`name` can by either an int for the ID or a char ptr for the name.
`value` can be an int, float, double, char, or any corresponding ptr types. 
`prim_ptr` can be any type of primative ptr, or a ptr to a ptr.
Note that in order to  force the compiler to recognize constants, you may need to cast and explicitly show type (eg. `(char)'a'`).

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
