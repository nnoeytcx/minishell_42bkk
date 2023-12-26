#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <stdint.h>
#include <sys/types.h>
#include <errno.h> //<<< to add errno
#include <string.h> // <<< add for strrerror << have to del later maybe
#include "./define_var.h"
#include "../libft/libft.h"
#include "./struct.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "./define_var.h"
#include "../libft/libft.h"
#include "./struct.h"
#include "../exe/exe.h"
#include "../parser/parser.h"
#include "../free/free.h"
#include "../env_handle/env.h"
#include "../builtin/builtin.h"

#endif
