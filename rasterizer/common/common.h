#ifndef __COMMON_H__
#define __COMMON_H__

#define SAFE_DELETE(p)			if (p) { delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p)	if (p) { delete [] p; p = NULL; }
#define SAFE_RELEASE(p)

#endif