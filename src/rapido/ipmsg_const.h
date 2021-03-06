﻿#ifndef IPMSG_CONST_H
#define IPMSG_CONST_H

/*
Some define.
*/

#define R_IPMSG_COMMAND_SEPERATOR		':'

// flag position from received data


#define R_IPMSG_VERSION_POS				0
#define R_IPMSG_PACKET_NO_POS			1
#define R_IPMSG_LOG_NAME_POS			2
#define R_IPMSG_HOST_POS				3
#define R_IPMSG_FLAGS_POS				4
#define R_IPMSG_ADDITION_INFO_POS		5
#define R_IPMSG_EXTENDED_INFO_POS		6

#define R_IPMSG_FLAGS_POS				4
#define R_IPMSG_NORMAL_FIELD_COUNT		6
#define R_SEND_MSG_PROCESS_INTERVAL		200


#define R_COMMAND_SEPERATOR				':'
#define R_EXTEND_INFO_SEPERATOR			'\0'
#define R_FILE_NAME_ESCAPE				"\a\a"
#define R_FILE_NAME_BEFORE				"::"
#define R_FILE_NAME_AFTER				":"

//user status
#define R_USERSTATUS_ONLINE             0
#define R_USERSTATUS_OFFLINE            1
#define R_USERSTATUS_BUSY               2
#define R_USERSTATUS_LEAVE              3
#define R_USERSTATUS_CREAZING           4

#define R_IPMSG_SEND_RETRY				3		/// 发送消息包时的重试次数
#define R_IPMSG_SEND_INTERVAL			1000	/// 发送消息包时的间隔时间（毫秒，非精确值）


/*
	IP Messenger Communication Protocol version 1.2 define
	@(#)Copyright (C) H.Shirouzu 1996-2004   ipmsg.h	Ver2.05
	========================================================================
    Project  Name			: IP Messenger for Win32
    Module Name				: Main Header
    Create					: 1996-06-01(Sat)
    Update					: 2004-01-01(Thu)
    Copyright				: H.Shirouzu
    Reference				:
	========================================================================
*/

/*  macro  */
#define IPMSG_GET_MODE(command)     (command & 0x000000ffUL)
#define IPMSG_GET_OPT(command)      (command & 0xffffff00UL)


/*  header  */
//#define IPMSG_VERSION           "1_lbt2_52#128#14FEB5EEC5A3#0#0#0"
#define IPMSG_VERSION           "1"
#define IPMSG_DEFAULT_PORT      0x0979

/*  command  */
#define IPMSG_NOOPERATION		0x00000000UL

#define IPMSG_BR_ENTRY			0x00000001UL
#define IPMSG_BR_EXIT			0x00000002UL
#define IPMSG_ANSENTRY			0x00000003UL
#define IPMSG_BR_ABSENCE		0x00000004UL

#define IPMSG_BR_ISGETLIST		0x00000010UL
#define IPMSG_OKGETLIST			0x00000011UL
#define IPMSG_GETLIST			0x00000012UL
#define IPMSG_ANSLIST			0x00000013UL
#define IPMSG_BR_ISGETLIST2		0x00000018UL

#define IPMSG_SENDMSG			0x00000020UL
#define IPMSG_RECVMSG			0x00000021UL
#define IPMSG_READMSG			0x00000030UL
#define IPMSG_DELMSG			0x00000031UL
#define IPMSG_ANSREADMSG		0x00000032UL

#define IPMSG_GETINFO			0x00000040UL
#define IPMSG_SENDINFO			0x00000041UL

#define IPMSG_GETABSENCEINFO	0x00000050UL
#define IPMSG_SENDABSENCEINFO	0x00000051UL

#define IPMSG_GETFILEDATA		0x00000060UL
#define IPMSG_RELEASEFILES		0x00000061UL
#define IPMSG_GETDIRFILES		0x00000062UL

#define IPMSG_GETPUBKEY			0x00000072UL
#define IPMSG_ANSPUBKEY			0x00000073UL

/*
FeiQ extension:
*/

//#define IPMSG_FEIQ_REMOTE_????          	0x00000077UL	//
#define IPMSG_FEIQ_REMOTE_START_TYPING		0x00000079UL	// remote user start input something.
#define IPMSG_FEIQ_REMOTE_KEEP_TYPING		0x0000007AUL	// remote user keep typing.
//#define IPMSG_FEIQ_REMOTE_????    		0x000000C9UL	//


/*  option for all command  */
#define IPMSG_ABSENCEOPT		0x00000100UL
#define IPMSG_SERVEROPT			0x00000200UL
#define IPMSG_DIALUPOPT			0x00010000UL
#define IPMSG_FILEATTACHOPT		0x00200000UL
#define IPMSG_ENCRYPTOPT		0x00400000UL

/*  option for send command  */
#define IPMSG_SENDCHECKOPT		0x00000100UL
#define IPMSG_SECRETOPT			0x00000200UL
#define IPMSG_BROADCASTOPT		0x00000400UL
#define IPMSG_MULTICASTOPT		0x00000800UL
#define IPMSG_NOPOPUPOPT		0x00001000UL
#define IPMSG_AUTORETOPT		0x00002000UL
#define IPMSG_RETRYOPT			0x00004000UL
#define IPMSG_PASSWORDOPT		0x00008000UL
#define IPMSG_NOLOGOPT			0x00020000UL
#define IPMSG_NEWMUTIOPT		0x00040000UL
#define IPMSG_NOADDLISTOPT		0x00080000UL
#define IPMSG_READCHECKOPT		0x00100000UL
#define IPMSG_SECRETEXOPT		(IPMSG_READCHECKOPT|IPMSG_SECRETOPT)

/* encryption flags for encrypt command */
#define IPMSG_RSA_512			0x00000001UL
#define IPMSG_RSA_1024			0x00000002UL
#define IPMSG_RSA_2048			0x00000004UL
#define IPMSG_RC2_40			0x00001000UL
#define IPMSG_RC2_128			0x00004000UL
#define IPMSG_RC2_256			0x00008000UL
#define IPMSG_BLOWFISH_128		0x00020000UL
#define IPMSG_BLOWFISH_256		0x00040000UL
#define IPMSG_SIGN_MD5			0x10000000UL

/* compatibilty for Win beta version */
#define IPMSG_RC2_40OLD			0x00000010UL	// for beta1-4 only
#define IPMSG_RC2_128OLD		0x00000040UL	// for beta1-4 only
#define IPMSG_BLOWFISH_128OLD	0x00000400UL	// for beta1-4 only
#define IPMSG_RC2_40ALL			(IPMSG_RC2_40|IPMSG_RC2_40OLD)
#define IPMSG_RC2_128ALL		(IPMSG_RC2_128|IPMSG_RC2_128OLD)
#define IPMSG_BLOWFISH_128ALL	(IPMSG_BLOWFISH_128|IPMSG_BLOWFISH_128OLD)

/* file types for fileattach command */
#define IPMSG_FILE_REGULAR		0x00000001UL
#define IPMSG_FILE_DIR			0x00000002UL
#define IPMSG_FILE_RETPARENT	0x00000003UL	// return parent directory
#define IPMSG_FILE_SYMLINK		0x00000004UL
#define IPMSG_FILE_CDEV			0x00000005UL	// for UNIX
#define IPMSG_FILE_BDEV			0x00000006UL	// for UNIX
#define IPMSG_FILE_FIFO			0x00000007UL	// for UNIX
#define IPMSG_FILE_RESFORK		0x00000010UL	// for Mac

/* file attribute options for fileattach command */
#define IPMSG_FILE_RONLYOPT		0x00000100UL
#define IPMSG_FILE_HIDDENOPT	0x00001000UL
#define IPMSG_FILE_EXHIDDENOPT	0x00002000UL	// for MacOS X
#define IPMSG_FILE_ARCHIVEOPT	0x00004000UL
#define IPMSG_FILE_SYSTEMOPT	0x00008000UL

/* extend attribute types for fileattach command */
#define IPMSG_FILE_UID			0x00000001UL
#define IPMSG_FILE_USERNAME		0x00000002UL	// uid by string
#define IPMSG_FILE_GID			0x00000003UL
#define IPMSG_FILE_GROUPNAME	0x00000004UL	// gid by string
#define IPMSG_FILE_PERM			0x00000010UL	// for UNIX
#define IPMSG_FILE_MAJORNO		0x00000011UL	// for UNIX devfile
#define IPMSG_FILE_MINORNO		0x00000012UL	// for UNIX devfile
#define IPMSG_FILE_CTIME		0x00000013UL	// for UNIX
#define IPMSG_FILE_MTIME		0x00000014UL
#define IPMSG_FILE_ATIME		0x00000015UL
#define IPMSG_FILE_CREATETIME	0x00000016UL
#define IPMSG_FILE_CREATOR		0x00000020UL	// for Mac
#define IPMSG_FILE_FILETYPE		0x00000021UL	// for Mac
#define IPMSG_FILE_FINDERINFO	0x00000022UL	// for Mac
#define IPMSG_FILE_ACL			0x00000030UL
#define IPMSG_FILE_ALIASFNAME	0x00000040UL	// alias fname
#define IPMSG_FILE_UNICODEFNAME	0x00000041UL	// UNICODE fname

#define IPMSG_FILELIST_SEPARATOR	'\a'
#define IPMSG_HOSTLIST_SEPARATOR	'\a'
#define IPMSG_HOSTLIST_DUMMY		"\b"


#endif // IPMSG_CONST_H
