/********************************************************************************
  Copyright             :  Huawei Technologies Co., Ltd
  File Name             :  Usbmntcmsapi.h
  Author                  :   
  Edition                  :  ATPV100R005
  Creat Date            :  2012-06-31
  Description           :  API of usbmount cms module

  Change Log:
    1. Date                : 2012-06-31
    2. Author             :  
    3. Modification     : Creat the file.

*********************************************************************************/

#ifndef __USBMNTCMSAPI_H__
#define __USBMNTCMSAPI_H__

#define     ATP_USB_MOUNT_UID       1103
#define     ATP_USB_MOUNT_UID_STR   "1103"
#define     ATP_USB_MOUNT_UID_NAME  "mnt"
#define     ATP_USB_MOUNT_GID       1103
#define     ATP_USB_MOUNT_GID_STR   "1103"
#define     ATP_USB_MOUNT_GID_NAME   "fs_mnt"
#define ATP_CBBID_USBMOUNTCMS_NAME "usbmountcms"
#define     ATP_USB_MOUNT_COMMAND_MAXLEN                        512
#define     ATP_USB_MOUNT_NTFS_USERMAPPING_FILE         "/var/NTFS_UserMapping"

#define     ATP_USB_MOUNT_NODE_POSITINO_MAXLEN                  15

#define    ATP_USB_MOUNT_TMPFS_MAGIC 0x01021994
#define    ATP_USB_MOUNT_ROMFS_MAGIC 0x7275
#define    ATP_USB_MOUNT_RAMFS_MAGIC 0x858458f6

enum ATP_USBMOUNTCMS_MSGTYPES_EN
{
    ATP_MSG_USBMOUNTCMS_START = ATP_MSG_CATEGORY_DEF(ATP_MODULE_USBMOUNTCMS), // = 0xAE00 = 44544
    ATP_MSG_USBMOUNTCMS_MOUNT_DISKSUBAREA_REFRESH,
    ATP_MSG_USBMOUNTCMS_MOUNT_SUBAREA_RESULT,
    ATP_MSG_USBMOUNTCMS_UMOUNT_SUBAREA_RESULT,
    ATP_MSG_USBMOUNTCMS_UNINSTALL,
    ATP_MSG_USBMOUNTCMS_UMOUNT_DISK,
    ATP_MSG_USBMOUNTCMS_GET_DISK_VOLUME,  // Get disk volume for OpenEE
} ;

typedef enum tagATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_EN
{
    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_START       = 0,
    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_NONE        = ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_START,        /* No mount operation. */
    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_TRY,
    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_SUCCESS,
    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_FAILED,

    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_END,
} ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_EN;

typedef enum tagATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_EN
{
    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_START       = 0,
    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_NONE        = ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_START,      /* No umount operation. */
    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_TRY,
    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_SUCCESS,
    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_FAILED,

    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_END,
} ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_EN;


typedef enum tagATP_USBMNTCMS_FILE_SYSTEM_EN
{
    ATP_USBMNTCMS_FILE_SYSTEM_START       = 0,
    ATP_USBMNTCMS_FILE_SYSTEM_UNKNOWN        = ATP_USBMNTCMS_FILE_SYSTEM_START,
    ATP_USBMNTCMS_FILE_SYSTEM_FAT,
    ATP_USBMNTCMS_FILE_SYSTEM_NTFS,
    ATP_USBMNTCMS_FILE_SYSTEM_HFS,
    ATP_USBMNTCMS_FILE_SYSTEM_HFSPLUS,
    ATP_USBMNTCMS_FILE_SYSTEM_EXFAT,
    ATP_USBMNTCMS_FILE_SYSTEM_EXT2,
    ATP_USBMNTCMS_FILE_SYSTEM_EXT3,
    ATP_USBMNTCMS_FILE_SYSTEM_EXT4,

    ATP_USBMNTCMS_FILE_SYSTEM_END,
} ATP_USBMNTCMS_FILE_SYSTEM_EN;



typedef struct tagATP_USBMNTCMS_MOUNT_RESULT_ST
{
    VOS_UINT32                                      ulMountPid;
    VOS_CHAR                                        acNodePosition[ATP_USB_MOUNT_NODE_POSITINO_MAXLEN+1];
    ATP_USBMNTCMS_SUBAREA_STATUS_MOUNTSTATE_EN      enMountState;
    ATP_USBMNTCMS_FILE_SYSTEM_EN                    enFileSystem;
} ATP_USBMNTCMS_MOUNT_RESULT_ST;


typedef struct tagATP_USBMNTCMS_UMOUNT_RESULT_ST
{
    VOS_UINT32                                      ulUmountPid;
    VOS_CHAR                                        acNodePosition[ATP_USB_MOUNT_NODE_POSITINO_MAXLEN+1];
    ATP_USBMNTCMS_SUBAREA_STATUS_UMOUNTSTATE_EN     enUmountStatus;
} ATP_USBMNTCMS_UMOUNT_RESULT_ST;


typedef struct tagATP_USBMNTCMS_MONITOR_MOUNTINFO_ST
{
    VOS_INT32                                   lAllMountedDiskSubareaNum;
    VOS_INT32                                   lRecentlyMountDiskSubareaNum;
    VOS_INT32                                   lRecentlyUmountDiskSubareaNum;
    VOS_BOOL                                    bCurUsbLunchFlag;
    VOS_BOOL                                    bNewUsbEnableFlag;
} ATP_USBMNTCMS_MONITOR_MOUNTINFO_ST;



typedef struct tagATP_USBMNTCMS_MOUNT_CMD_ST
{
    ATP_USBMNTCMS_FILE_SYSTEM_EN                enFileSystem;
    const VOS_CHAR                              *pacCommand;
    const VOS_CHAR                              *pacPara1;
    const VOS_CHAR                              *pacPara2;
} ATP_USBMNTCMS_MOUNT_CMD_ST;



typedef enum tagATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_EN
{
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_START       = 0,
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_FTPD        = ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_START,
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_SAMBA,
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_TR140,
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_DMS,
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_XUNLEI,
    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_SERVICE,

    ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_END,
} ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_EN;


//!...........................................外部api接口start.................................................
#if defined(__cplusplus)
extern "C" {
#endif
VOS_UINT32 ATP_USBMount_Init(VOS_VOID);

/*!
  \brief 注册usbmount disksubarea refresh 回调函数
  \param[in]  pfProc: 回调函数
  \param[in]  enPriority: 优先级
  \param[in]  pvNotifyHook: 参数
  \return VOS_OK 表示命令执行成功，其它表示不成功
*/
VOS_UINT32 ATP_USBStorage_Mount_DiskSubarea_Refresh_NotifyRegisterEx( AtpNotifierProc pfProc, ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_EN enPriority, VOS_VOID *pvNotifyHook );
#define ATP_USBStorage_Mount_DiskSubarea_Refresh_NotifyRegister(pfProc, ulPriority, pvNotifyHook) ATP_USBStorage_Mount_DiskSubarea_Refresh_NotifyRegisterEx(FUNCTION_POINTER(pfProc), ulPriority, pvNotifyHook)

/*!
  \brief 注册usb uninstall  refresh 回调函数
  \param[in]  pfProc: 回调函数
  \param[in]  enPriority: 优先级
  \param[in]  pvNotifyHook: 参数
  \return VOS_OK 表示命令执行成功，其它表示不成功
*/
VOS_UINT32 ATP_USBStorage_Uninstall_Refresh_NotifyRegisterEx( AtpNotifierProc pfProc, ATP_USBSTORAGE_MOUNTREFRESH_NOTIFY_PRIORITY_EN enPriority, VOS_VOID *pvNotifyHook );
#define ATP_USBStorage_Uninstall_Refresh_NotifyRegister(pfProc, ulPriority, pvNotifyHook) ATP_USBStorage_Uninstall_Refresh_NotifyRegisterEx(FUNCTION_POINTER(pfProc), ulPriority, pvNotifyHook)
#ifdef SUPPORT_ATP_CHANNEL_WAN_GUIDE
VOS_VOID ATP_USBStorage_Monitor_Mount_Info_Set_Current_Lunch_Flag( VOS_BOOL bFlag );
VOS_VOID ATP_USBStorage_Monitor_Mount_Info_Refresh_Usb_Enable_Flag();
VOS_VOID ATP_USBStorage_Usb_Service_Refresh_Proc();
#endif


#if defined(__cplusplus)
}
#endif
//!...........................................外部api接口end.................................................

#endif
