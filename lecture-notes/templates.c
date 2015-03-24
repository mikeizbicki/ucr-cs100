#define MKSTRUCT(x,y) \
struct y \
{ \
    x *a; \
}

MKSTRUCT(char,C_char);
