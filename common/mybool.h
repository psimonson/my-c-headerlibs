#ifndef _PRS_MYBOOL_H_
#define _PRS_MYBOOL_H_

typedef char bool;

#ifndef _WIN32
enum Boolean { FALSE, TRUE };
#endif

#define false 0
#define true 1

#endif
