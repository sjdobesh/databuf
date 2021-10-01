#ifndef _DATABUF_H_
#define _DATABUF_H_

#include <stdlib.h>

// ENUMS //---------------------------------------------------------------------

enum db_type {
  INT  = (1u << 0),
  FLT  = (1u << 1),
  DBL  = (1u << 2),
  CHR  = (1u << 3),
  INTP = (1u << 4),
  FLTP = (1u << 5),
  DBLP = (1u << 6),
  CHRP = (1u << 7),
  VOID = (1u << 8)
};

// STRUCTS //-------------------------------------------------------------------

typedef struct data {
  void* ptr;
  unsigned int type;
  unsigned int size;
  char* name;
  int id;
} data;

typedef struct databuf {
  data* d;
  int n;
  int next_id;
} databuf;

int get_next_id(databuf*);
int get_first_id(databuf);
int get_last_id(databuf);

void print_type(int type);
void print_databuf(databuf db);
void printv_databuf(databuf db);
void print_var_id(databuf db, int);
void print_var_name(databuf db, char*);
#define print_var(databuf, id) _Generic ((id), \
int: print_var_id, char*: print_var_name)(databuf, id)

databuf create_databuf();
void free_databuf(databuf*);

// ADD TO BUFFER
int add_data(databuf*, data);
data wrap_int (int*,     char*);
data wrap_flt (float*,   char*);
data wrap_dbl (double*,  char*);
data wrap_chr (char*,    char*);
data wrap_intp(int**,    char*);
data wrap_fltp(float**,  char*);
data wrap_dblp(double**, char*);
data wrap_chrp(char**,   char*);

#define wrap_data(data, name) _Generic ((data), \
char*:   wrap_chr, char**:   wrap_chrp,   \
int*:    wrap_int, int**:    wrap_intp,   \
float*:  wrap_flt, float**:  wrap_fltp,   \
double*: wrap_dbl, double**: wrap_dblp   \
)(data, name)

int new_int (databuf*, char*, int);
int new_flt (databuf*, char*, float);
int new_dbl (databuf*, char*, double);
int new_chr (databuf*, char*, char);
int new_intp(databuf*, char*, int*);
int new_fltp(databuf*, char*, float*);
int new_dblp(databuf*, char*, double*);
int new_chrp(databuf*, char*, char*);

#define new_var(db, name, x) _Generic ((x), \
char:   new_chr, char*:   new_chrp,\
int:    new_int, int*:    new_intp,\
float:  new_flt, float*:  new_fltp,\
double: new_dbl, double*: new_dblp\
)(db, name, x)

// GET FROM BUFFER
int get_data_id(databuf*, int, data*);
int get_data_name(databuf*, char*, data*);
#define get_data(databuf, id, data) _Generic ((id), \
int: get_data_id, char*: get_data_name)(databuf, id, data)

// int
int get_int_id   (databuf, int,   int*);
int get_int_name (databuf, char*, int*);
int get_intp_id  (databuf, int,   int**);
int get_intp_name(databuf, char*, int**);
// float
int get_flt_id   (databuf, int,   float*);
int get_flt_name (databuf, char*, float*);
int get_fltp_id  (databuf, int,   float**);
int get_fltp_name(databuf, char*, float**);
// double
int get_dbl_id   (databuf, int,   double*);
int get_dbl_name (databuf, char*, double*);
int get_dblp_id  (databuf, int,   double**);
int get_dblp_name(databuf, char*, double**);
// CHAR
int get_chr_id   (databuf, int,   char*);
int get_chr_name (databuf, char*, char*);
int get_chrp_id  (databuf, int,   char**);
int get_chrp_name(databuf, char*, char**);

#define get_var_id(var) _Generic ((var), \
char*:   get_chr_id, char**:   get_chrp_id,\
int*:    get_int_id, int**:    get_intp_id,\
float*:  get_flt_id, float**:  get_fltp_id,\
double*: get_dbl_id, double**: get_dblp_id\
)
#define get_var_name(var) _Generic ((var), \
char*:   get_chr_name, char**:   get_chrp_name,\
int*:    get_int_name, int**:    get_intp_name,\
float*:  get_flt_name, float**:  get_fltp_name,\
double*: get_dbl_name, double**: get_dblp_name\
)
#define get_var(databuf, id, var) _Generic ((id), \
int: get_var_id(var), char*: get_var_name(var))(databuf, id, var)

// UPDATE VARIABLES
int set_int_id   (databuf*, int,   int);
int set_int_name (databuf*, char*, int);
int set_intp_id  (databuf*, int,   int*);
int set_intp_name(databuf*, char*, int*);
// float
int set_flt_id   (databuf*, int,   float);
int set_flt_name (databuf*, char*, float);
int set_fltp_id  (databuf*, int,   float*);
int set_fltp_name(databuf*, char*, float*);
// double
int set_dbl_id   (databuf*, int,   double);
int set_dbl_name (databuf*, char*, double);
int set_dblp_id  (databuf*, int,   double*);
int set_dblp_name(databuf*, char*, double*);
// CHAR
int set_chr_id   (databuf*, int,   char);
int set_chr_name (databuf*, char*, char);
int set_chrp_id  (databuf*, int,   char*);
int set_chrp_name(databuf*, char*, char*);

#define set_var_id(var) _Generic ((var), \
char:   set_chr_id, char*:   set_chrp_id,\
int:    set_int_id, int*:    set_intp_id,\
float:  set_flt_id, float*:  set_fltp_id,\
double: set_dbl_id, double*: set_dblp_id\
)
#define set_var_name(var) _Generic ((var), \
char:   set_chr_name, char*:   set_chrp_name,\
int:    set_int_name, int*:    set_intp_name,\
float:  set_flt_name, float*:  set_fltp_name,\
double: set_dbl_name, double*: set_dblp_name\
)
#define set_var(databuf, id, var) _Generic ((id), \
int: set_var_id(var), char*: set_var_name(var))(databuf, id, var)

// FREE DATA
int free_var_id(databuf*, int);
int free_var_name(databuf*, char*);
#define free_var(databuf, id) _Generic ((id), \
int: free_var_id, char*: free_var_name)(databuf, id)


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// printing functions //--------------------------------------------------------
void print_type(int type) {
  switch (type) {
    case INT:
        printf("INT\n");
      break;
    case FLT:
        printf("FLT\n");
      break;
    case DBL:
        printf("DBL\n");
      break;
    case CHR:
        printf("CHR\n");
      break;
    case INTP:
        printf("INTP\n");
      break;
    case FLTP:
        printf("FLTP\n");
      break;
    case DBLP:
        printf("DBLP\n");
      break;
    case CHRP:
        printf("CHRP\n");
      break;
    default:
        printf("PTR\n");
      break;
  }
}
void print_var_id(databuf db, int id) {
  data d;
  if (!get_data(&db, id, &d)) {
    switch (d.type) {
      case INT:
        printf("%d\n", *(int*)d.ptr);
        break;
      case FLT:
        printf("%f\n", *(float*)d.ptr);
        break;
      case DBL:
        printf("%lf\n", *(double*)d.ptr);
        break;
      case CHR:
        printf("%c\n", *(char*)d.ptr);
        break;
      default:
        printf("%p\n", d.ptr);
        break;
    }
    return;
  }
}
void print_var_name(databuf db, char* name) {
  data d;
  if (!get_data(&db, name, &d)) {
    switch (d.type) {
      case INT:
        printf("%d\n", *(int*)d.ptr);
        break;
      case FLT:
        printf("%f\n", *(float*)d.ptr);
        break;
      case DBL:
        printf("%lf\n", *(double*)d.ptr);
        break;
      case CHR:
        printf("%c\n", *(char*)d.ptr);
        break;
      default:
        printf("%p\n", d.ptr);
        break;
    }
    return;
  }
}
// print an unsigned number as binary digits
void print_bin(unsigned n) {
  for (unsigned i = 1 << 31; i > 0; i = i/2) {
    n & i ? printf("1") : printf("0");
  }
  printf("\n");
}
// print the entire databuffer
void print_databuf(databuf db) {
  printf("\nDATABUF:\n");
  printf("n = %d\n", db.n);
  for (int i = 0; i < db.n; i++){
    printf("DATA %d\n", i);
    printf(" - val:  ");
    print_var(db, db.d[i].id);
    printf(" - name: %s\n", db.d[i].name);
    printf(" - id:   %d\n", db.d[i].id);
  }
}
// print verbose, extra info like ptr and size
void printv_databuf(databuf db) {
  printf("\nDATABUF:\n");
  printf("n = %d\n", db.n);
  for (int i = 0; i < db.n; i++){
    printf("DATA %d\n", i);
    printf(" - val:  ");
    print_var(db, db.d[i].id);
    printf(" - name: %s\n", db.d[i].name);
    printf(" - id:   %d\n", db.d[i].id);
    printf(" - type: "); print_type(db.d[i].type);
    printf(" - size: %u\n", db.d[i].size);
    printf(" - ptr:  %p\n", db.d[i].ptr);
  }
}

// create a databuffer without junk values
databuf create_databuf() {
  databuf db = {NULL, 0};
  return db;
}

void free_databuf(databuf* buf) {
  for (int i = 0; i < buf->n; i++) {
    free(buf->d[i].ptr);
  }
  free(buf->d);
}

// wrap data implementations
// INT
data wrap_int(int* x, char* name){
  data d = {(void*)x, INT, sizeof(int), name};
  return d;
}
data wrap_intp(int** x, char* name) {
  data d = {(void*)x, INTP, sizeof(int*), name};
  return d;
}
// FLOAT
data wrap_flt(float* x, char* name) {
  data d = {(void*)x, FLT, sizeof(float), name};
  return d;
}
data wrap_fltp(float** x, char* name) {
  data d = {(void*)x, FLTP, sizeof(float*), name};
  return d;
}
// DOUBLE
data wrap_dbl(double* x, char* name){
  data d = {(void*)x, DBL, sizeof(double), name};
  return d;
}
data wrap_dblp(double** x, char* name) {
  data d = {(void*)x, DBLP, sizeof(double*), name};
  return d;
}
// CHAR
data wrap_chr(char* x, char* name) {
  data d = {(void*)x, CHR, sizeof(char), name};
  return d;
}
data wrap_chrp(char** x, char* name) {
  data d = {(void*)x, CHRP, sizeof(char*), name};
  return d;
}
// new_var() implementations
// INT
int new_int(databuf* buf, char* name, int x) {
  int* p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
int new_intp(databuf* buf, char* name, int* x) {
  int** p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
// FLOAT
int new_flt(databuf* buf, char* name, float x) {
  float* p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
int new_fltp(databuf* buf, char* name, float* x) {
  float** p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
// DOUBLE
int new_dbl(databuf* buf, char* name, double x) {
  double* p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
int new_dblp(databuf* buf, char* name, double* x) {
  double** p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
// CHAR
int new_chr(databuf* buf, char* name, char x) {
  char* p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}
int new_chrp(databuf* buf, char* name, char* x) {
  char** p = malloc(sizeof(x));
  *p = x;
  data d = wrap_data(p, name);
  return add_data(buf, d);
}

int get_next_id(databuf* buf) {
  int next = buf->next_id;
  buf->next_id++;
  return next;
}

int add_data(databuf* buf, data d) {
  d.id = get_next_id(buf);
  buf->d = realloc(buf->d, sizeof(data) * (buf->n+1));
  buf->d[buf->n] = d;
  buf->n++;
  return d.id;
}

int get_data_id(databuf* buf, int id, data* d) {
  for (int i = 0; i < buf->n; ++i) {
    if (buf->d[i].id == id) {
      *d = buf->d[i];
      return 0;
    }
  }
  return 1;
}

int get_data_name(databuf* buf, char* name, data* d) {
  for (int i = 0; i < buf->n; ++i) {
    if (!strcmp(buf->d[i].name, name)) {
      *d = buf->d[i];
      return 0;
    }
  }
  return 1;
}

// get_var() implimentations
// INT
int get_int_id(databuf buf, int id, int* var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(int*)d.ptr;
    return 0;
  }
  return 1;
}
int get_int_name(databuf buf, char* name, int* var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(int*)d.ptr;
    return 0;
  }
  return 1;
}
int get_intp_id(databuf buf, int id, int** var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(int**)d.ptr;
    return 0;
  }
  return 1;
}
int get_intp_name(databuf buf, char* name, int** var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(int**)d.ptr;
    return 0;
  }
  return 1;
}
// FLOAT
int get_flt_id(databuf buf, int id, float* var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(float*)d.ptr;
    return 0;
  }
  return 1;
}
int get_flt_name(databuf buf, char* name, float* var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(float*)d.ptr;
    return 0;
  }
  return 1;
}
int get_fltp_id(databuf buf, int id, float** var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(float**)d.ptr;
    return 0;
  }
  return 1;
}
int get_fltp_name(databuf buf, char* name, float** var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(float**)d.ptr;
    return 0;
  }
  return 1;
}
// DOUBLE
int get_dbl_id(databuf buf, int id, double* var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(double*)d.ptr;
    return 0;
  }
  return 1;
}
int get_dbl_name(databuf buf, char* name, double* var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(double*)d.ptr;
    return 0;
  }
  return 1;
}
int get_dblp_id(databuf buf, int id, double** var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(double**)d.ptr;
    return 0;
  }
  return 1;
}
int get_dblp_name(databuf buf, char* name, double** var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(double**)d.ptr;
    return 0;
  }
  return 1;
}
// CHAR
int get_chr_id(databuf buf, int id, char* var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(char*)d.ptr;
    return 0;
  }
  return 1;
}
int get_chr_name(databuf buf, char* name, char* var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(char*)d.ptr;
    return 0;
  }
  return 1;
}
int get_chrp_id(databuf buf, int id, char** var) {
  data d;
  if (!get_data(&buf, id, &d)) {
    *var = *(char**)d.ptr;
    return 0;
  }
  return 1;
}
int get_chrp_name(databuf buf, char* name, char** var) {
  data d;
  if (!get_data(&buf, name, &d)) {
    *var = *(char**)d.ptr;
    return 0;
  }
  return 1;
}

int get_first_id(databuf buf) {
  if (buf.n > 0) {
    return buf.d[0].id;
  }
  return -1;
}
int get_last(databuf buf) {
  if (buf.n > 0) {
    return buf.d[buf.n-1].id;
  }
  return -1;
}


// SETTING
// set ints
int set_int_id(databuf* buf, int id, int var) {
  data d;
  if (!get_data(buf, id, &d)) {
    *(int*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_int_name(databuf* buf, char* name, int var) {
  data d;
  if (!get_data(buf, name, &d)) {
    *(int*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_intp_id(databuf* buf, int id, int* var) {
  data d;
  if (!get_data(buf, id, &d)) {
    *(int**)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_intp_name(databuf* buf, char* name, int* var){
  data d;
  if (!get_data(buf, name, &d)) {
    *(int**)d.ptr = var;
    return 0;
  }
  return 1;
}
// float
int set_flt_id (databuf* buf, int id, float var) {
  data d;
  if (!get_data(buf, id, &d)) {
    *(float*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_flt_name(databuf* buf, char* name, float var) {
  data d;
  if (!get_data(buf, name, &d)) {
    *(float*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_fltp_id(databuf* buf, int id, float* var)    {
  data d;
  if (!get_data(buf, id, &d)) {
    *(float**)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_fltp_name(databuf* buf, char* name, float* var){
  data d;
  if (!get_data(buf, name, &d)) {
    *(float**)d.ptr = var;
    return 0;
  }
  return 1;
}
// double
int set_dbl_id(databuf* buf, int id, double var)     {
  data d;
  if (!get_data(buf, id, &d)) {
    *(double*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_dbl_name(databuf* buf, char* name, double var) {
  data d;
  if (!get_data(buf, name, &d)) {
    *(double*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_dblp_id(databuf* buf, int id, double* var)    {
  data d;
  if (!get_data(buf, id, &d)) {
    *(double**)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_dblp_name(databuf* buf, char* name, double* var){
  data d;
  if (!get_data(buf, name, &d)) {
    *(double**)d.ptr = var;
    return 0;
  }
  return 1;
}
// CHAR
int set_chr_id(databuf* buf, int id, char var)     {
  data d;
  if (!get_data(buf, id, &d)) {
    *(char*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_chr_name(databuf* buf, char* name, char var) {
  data d;
  if (!get_data(buf, name, &d)) {
    *(char*)d.ptr = var;
    return 0;
  }
  return 1;
}
int set_chrp_id(databuf* buf, int id, char* var)    {
  data d;
  if (!get_data(buf, id, &d)) {
    *(char**)d.ptr = var;
    return 0;
  }
  return 1;
}

int set_chrp_name(databuf* buf, char* name, char* var){
  data d;
  if (!get_data(buf, name, &d)) {
    *(char**)d.ptr = var;
    return 0;
  }
  return 1;
}

int free_var_id(databuf* buf, int id) {
  int found = 0;
  for (int i = 0; i < buf->n; i++) {
    if (buf->d[i].id == id) {
      found = 1;
      free(buf->d[i].ptr);
    }
    if (found && i < buf->n-1) {
      buf->d[i] = buf->d[i+1];
    }
  }
  if (found) {
    buf->n--;
    buf->d = realloc(buf->d, sizeof(data) * buf->n);
    return 0;
  }
  return 1;
}

int free_var_name(databuf* buf, char* name) {
  int found = 0;
  for (int i = 0; i < buf->n; i++) {
    if (!strcmp(buf->d[i].name, name)) {
      found = 1;
      free(buf->d[i].ptr);
    }
    if (found && i < buf->n-1) {
      buf->d[i] = buf->d[i+1];
    }
  }
  if (found) {
    buf->n--;
    buf->d = realloc(buf->d, sizeof(data) * buf->n);
    return 0;
  }
  return 1;
}
#endif
