# Databuf
Header only library implementing a dynamic data buffer.

### _structure_
A databuffer is a collection of data structs, each wrapping a primative and containing relevant meta information.
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

### _example usage_
```c
databuf buf = create_databuf();
new_var(&buf, "x", 1);
print_var(buf, "x");
set_var(&buf, "x", 2);
print_var(buf, "x");
free_var(&buf, "x");
```

### _functions_
```c
new_var(bufptr, name, value);
set_var(bufptr, name, value);
free_var(bufptr, name, value);
print_var(buf, name);
print_databuf(buf);
printv_databuf(buf);
get_next_id(bufptr);
```
