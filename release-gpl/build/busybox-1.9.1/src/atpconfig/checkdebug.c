/* vi: set sw=4 ts=4: */
/*
 *
 */

#include <getopt.h>	/* for struct option */
#include "libbb.h"
#include "atpcommon.h"
#include "atpconfig.h"
//#include "bhal.h"


typedef struct BhalIoctParms
{
    char *pcString;
    char *pcBuf;
    unsigned int   ulType;
    unsigned int   ulStrLen;
    unsigned int   ulOffset;  
    int   lResult; 
} BHAL_IOCTL_PARMS_ST;

int checkdebugIoctl(unsigned int  ulBhalioctl, unsigned int  ulType, char *pcString,
                        unsigned int  ulStrLen, unsigned int  ulOffset, char *pcBuf)
{
    int lRet = -1;
    int lIoctlRet = 0;
    int lBoardFd = 0;
    BHAL_IOCTL_PARMS_ST stIoctlParms;

    lBoardFd = open("/dev/bhal", O_RDWR);
    if (lBoardFd != -1)
    {
        stIoctlParms.pcString = pcString;
        stIoctlParms.ulStrLen = ulStrLen;
        stIoctlParms.ulOffset = ulOffset;
        stIoctlParms.ulType   = ulType;
        stIoctlParms.pcBuf    = pcBuf;

        lIoctlRet = ioctl(lBoardFd, ulBhalioctl, &stIoctlParms);

        if( lIoctlRet >= 0 )
        {
            lRet = stIoctlParms.lResult;
        }

        close(lBoardFd);
    }
    else
    {
        printf("Unable to open device /dev/bhal.\n");
    }

    return lRet;
}


int  SetConsole_Type(unsigned int uiMode)
{
    int lRet = 0;
    printf("==========SetConsole_Type======[%d]\n\n",uiMode);
#ifdef BHAL_IOCTL_SET_CONSOLE_TYPE     
    lRet = checkdebugIoctl(BHAL_IOCTL_SET_CONSOLE_TYPE, uiMode, 0, 0, 0, "");
#endif

    return lRet;
}


int checkdebug_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
int checkdebug_main(int argc, char **argv)
{
#ifdef SUPPORT_ATP_ATP_DEBUG_IAMGE
    printf("\n current version is debug set console open\n");
    SetConsole_Type(1);
    return 0;
#else
    printf("\n current version is release\n");
    return 1;
#endif
}

