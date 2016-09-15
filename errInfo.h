// errInfo.h
//   Error message.
// History:
// 2016/09/14  Hao Xu  First release

#ifndef ERRINFO_H
#define ERRINFO_H

#include <stdexcept>
#include <stdio.h>

#ifndef _USEERRORMESSAGECLASS_

#define throwout(message) {printf("ERROR: %s\n     in file %s at line %d\n", message,__FILE__,__LINE__); throw(1);}
#else
struct errorMessage {
	char *message;
	char *file;
	int line;
	errorMessage(char *m, char *f, int l) : message(m), file(f), line(l) {}
};
#define throwout(message) throw(errorMessage(message,__FILE__,__LINE__));
void catchError(errorMessage err) {
	printf("ERROR: %s\n     in file %s at line %d\n",
		err.message, err.file, err.line);
	exit(1);
}
#endif

#endif /* ERRINFO_H */
