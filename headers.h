#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include "prompt.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "echo.h"
#include "pinfo.h"
#include "fore.h"
#include "history.h"
#include "back.h"
#include "historyprint.h"
#include "redirection.h"
#include "fg.h"
#include "bg.h"
#include "env.h"
#include "jobs.h"
#include "kjob.h"
#include "overkill.h"

struct Node* ll;