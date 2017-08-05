#include <string.h>
#include <dlfcn.h>
#include "include/ebtables_u.h"
#include "atptypes.h"
#include "proclockutil.h"

FILE *(*gATP_UTIL_LockProc)(const char *psLockFile) = NULL;
void (*gATP_UTIL_RegUnLock)(FILE *pfLockFile) = NULL;
static void *ghandle = NULL;

static struct ebt_u_replace replace;
void ebt_early_init_once();

int main(int argc, char *argv[])
{
	ebt_silent = 0;
		struct iptc_handle *handle = NULL;
	
	FILE *pfLockFile = NULL;
	char *error = NULL;
	
	/*start: 用于查询组件版本号(iptables atpv),请产品不要修改或删除*/
        if ((argc == 2) && (NULL != argv[1]) && (0 == strcmp(argv[1],ATP_VERSION_CMD_KEY)))
        {
        	printf("\r\n ATPVERSION.\n");
                exit(0);
        }
        /*end */

    ghandle = dlopen("libgplutil.so", RTLD_LAZY);
    if(ghandle == NULL)
    {
        printf("libgplutil.so load failed\n");
        exit(-1);
    }
	
	gATP_UTIL_LockProc = dlsym((void *)(ghandle), "ATP_UTIL_LockProc");
    error = (char *)dlerror();
    if((NULL == gATP_UTIL_LockProc)||(NULL != error))
    {
	    printf("load ATP_UTIL_LockProc failed\n");
	    dlclose(ghandle);
	    exit(-1);
    }
	  
	gATP_UTIL_RegUnLock = dlsym((void *)(ghandle), "ATP_UTIL_RegUnLock");
    error = (char *)dlerror();
    if((NULL == gATP_UTIL_RegUnLock)||(NULL != error))
    {
        printf("load ATP_UTIL_RegUnLock failed\n");
        dlclose(ghandle);
        exit(-1);
    }

    pfLockFile = gATP_UTIL_LockProc(EBTABLES_LOCK_FILE);
    if (NULL == pfLockFile) {
        printf("iptables get lock failed\n");
        exit(-1);
    }

    gATP_UTIL_RegUnLock(pfLockFile);
	ebt_early_init_once();
	strcpy(replace.name, "filter");
	do_command(argc, argv, EXEC_STYLE_PRG, &replace);
	return 0;
}
