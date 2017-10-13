#ifndef CUBE_H
#define CUBE_H

#include <dol.h>
#include "global.h"

#define PORT_IN  1
#define PORT_OUT 2

typedef struct _local_states {
    int index;
    int len;
} Cube_State;

void cube_init(DOLProcess *);
int cube_fire(DOLProcess *);

#endif
