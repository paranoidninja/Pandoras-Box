/*
 * ddk/ntdddisk.h
 *
 * Driver Development Kit -- Disk IOCTL interface.
 *
 * Written by Casper S. Hornstrup  <chorns@users.sourceforge.net>
 * Copyright (C) 2002-2004, 2015, 2016, MinGW.org Project.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _DDK_NTDDDISK_H
#pragma GCC system_header

/* This file supports partial inclusion by <winioctl.h>; defer definition
 * of its normal repeat inclusion guard macro...
 */
#ifndef __WINIOCTL_H_SOURCED__
/* ...until we've ascertained that this is NOT such partial inclusion.
 */
#define _DDK_NTDDDISK_H

/* In case of full inclusion, we must also include the full content of:
 */
#include "ntddk.h"
#endif

/* In either case, we always include <ddk/ntddstor.h>, either in full,
 * or under the same criterion of selectivity as for this file itself.
 */
#include "ntddstor.h"

#if ! (defined _DDK_NTDDDISK_H && defined _WINIOCTL_H)
/* The content of this section is common to both <ddk/ntdddisk.h> and
 * <winioctl.h>.  If both repeat inclusion guards are already defined,
 * then we've already seen it; there is no need to process it again.
 */
#define __IOCTL_DISK_(FN,M,A)			  CTL_CODE(IOCTL_DISK_BASE,(FN),(M),(A))

#define IOCTL_DISK_BASE 			  FILE_DEVICE_DISK
#define IOCTL_DISK_GET_DRIVE_GEOMETRY		__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0000)
#define IOCTL_DISK_GET_PARTITION_INFO		__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0001)
#define IOCTL_DISK_SET_PARTITION_INFO		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0002)
#define IOCTL_DISK_GET_DRIVE_LAYOUT		__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0003)
#define IOCTL_DISK_SET_DRIVE_LAYOUT		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0004)
#define IOCTL_DISK_VERIFY			__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0005)
#define IOCTL_DISK_FORMAT_TRACKS		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0006)
#define IOCTL_DISK_REASSIGN_BLOCKS		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0007)
#define IOCTL_DISK_PERFORMANCE			__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0008)
#define IOCTL_DISK_IS_WRITABLE			__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0009)
#define IOCTL_DISK_FORMAT_TRACKS_EX		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x000B)
#define IOCTL_DISK_GET_PARTITION_INFO_EX	__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0012)
#define IOCTL_DISK_SET_PARTITION_INFO_EX	__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0013)
#define IOCTL_DISK_GET_DRIVE_LAYOUT_EX		__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0014)
#define IOCTL_DISK_SET_DRIVE_LAYOUT_EX		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0015)
#define IOCTL_DISK_CREATE_DISK			__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0016)
#define IOCTL_DISK_GET_LENGTH_INFO		__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0017)
#define IOCTL_DISK_PERFORMANCE_OFF		__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0018)
#define IOCTL_DISK_GET_DRIVE_GEOMETRY_EX	__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0028)
#define IOCTL_DISK_UPDATE_DRIVE_SIZE		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0032)
#define IOCTL_DISK_GROW_PARTITION		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0034)
#define IOCTL_DISK_GET_CACHE_INFORMATION	__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0035)
#define IOCTL_DISK_SET_CACHE_INFORMATION	__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0036)
#define IOCTL_DISK_DELETE_DRIVE_LAYOUT		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0040)
#define IOCTL_DISK_CHECK_VERIFY 		__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0200)
#define IOCTL_DISK_RESERVE			__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0204)
#define IOCTL_DISK_FIND_NEW_DEVICES		__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0206)
#define IOCTL_DISK_GET_MEDIA_TYPES		__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0300)

enum
{ PARTITION_ENTRY_UNUSED	= 0x00,
  PARTITION_FAT_12		= 0x01,
  PARTITION_XENIX_1		= 0x02,
  PARTITION_XENIX_2		= 0x03,
  PARTITION_FAT_16		= 0x04,
  PARTITION_EXTENDED		= 0x05,
  PARTITION_HUGE		= 0x06,
  PARTITION_IFS 		= 0x07,
  PARTITION_OS2BOOTMGR		= 0x0A,
  PARTITION_FAT32		= 0x0B,
  PARTITION_FAT32_XINT13	= 0x0C,
  PARTITION_XINT13		= 0x0E,
  PARTITION_XINT13_EXTENDED	= 0x0F,
  PARTITION_PREP		= 0x41,
  PARTITION_LDM 		= 0x42,
  PARTITION_UNIX		= 0x63,
  PARTITION_NTFT		= 0x80,
  VALID_NTFT			= 0xC0
};

#define IsRecognizedPartition( TYPE ) \
 (   (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_FAT_12))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_HUGE))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_IFS))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_FAT32))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_FAT32_XINT13))\
  || (((TYPE) & PARTITION_NTFT) && (((TYPE) & ~VALID_NTFT) == PARTITION_XINT13))\
  || ((TYPE) == PARTITION_FAT32) || ((TYPE) == PARTITION_FAT32_XINT13)\
  || ((TYPE) == PARTITION_FAT_12) || ((TYPE) == PARTITION_FAT_16)\
  || ((TYPE) == PARTITION_HUGE) || ((TYPE) == PARTITION_IFS)\
  || ((TYPE) == PARTITION_XINT13)\
 )
#define IsContainerPartition( TYPE ) \
 (((TYPE) == PARTITION_EXTENDED) || ((TYPE) == PARTITION_XINT13_EXTENDED))

typedef
enum _MEDIA_TYPE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff562216(v=vs.85).aspx */
{ Unknown			= 0x00,
  F5_1Pt2_512			= 0x01,
  F3_1Pt44_512			= 0x02,
  F3_2Pt88_512			= 0x03,
  F3_20Pt8_512			= 0x04,
  F3_720_512			= 0x05,
  F5_360_512			= 0x06,
  F5_320_512			= 0x07,
  F5_320_1024			= 0x08,
  F5_180_512			= 0x09,
  F5_160_512			= 0x0A,
  RemovableMedia		= 0x0B,
  FixedMedia			= 0x0C,
  F3_120M_512			= 0x0D,
  F3_640_512			= 0x0E,
  F5_640_512			= 0x0F,
  F5_720_512			= 0x10,
  F3_1Pt2_512			= 0x11,
  F3_1Pt23_1024 		= 0x12,
  F5_1Pt23_1024 		= 0x13,
  F3_128Mb_512			= 0x14,
  F3_230Mb_512			= 0x15,
  F8_256_128			= 0x16,
  F3_200Mb_512			= 0x17,
  F3_240M_512			= 0x18,
  F3_32M_512			= 0x19
} MEDIA_TYPE, *PMEDIA_TYPE;

typedef
enum _DETECTION_TYPE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552516%28v=vs.85%29.aspx */
{ DetectNone			= 0,
  DetectInt13			= 1,
  DetectExInt13			= 2
} DETECTION_TYPE;

typedef
struct _DISK_INT13_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552624(v=vs.85).aspx */
{ USHORT	DriveSelect;
  ULONG 	MaxCylinders;
  USHORT	SectorsPerTrack;
  USHORT	MaxHeads;
  USHORT	NumberDrives;
} DISK_INT13_INFO, *PDISK_INT13_INFO;

typedef
struct _DISK_EX_INT13_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552610(v=vs.85).aspx */
{ USHORT	ExBufferSize;
  USHORT	ExFlags;
  ULONG 	ExCylinders;
  ULONG 	ExHeads;
  ULONG 	ExSectorsPerTrack;
  ULONG64	ExSectorsPerDrive;
  USHORT	ExSectorSize;
  USHORT	ExReserved;
} DISK_EX_INT13_INFO, *PDISK_EX_INT13_INFO;

typedef
struct _DISK_DETECTION_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552601(v=vs.85).aspx */
{ ULONG 		      SizeOfDetectInfo;
  DETECTION_TYPE	      DetectionType;
  _ANONYMOUS_UNION union
  { _ANONYMOUS_STRUCT struct
    { DISK_INT13_INFO	      Int13;
      DISK_EX_INT13_INFO      ExInt13;
    } DUMMYSTRUCTNAME;
  } DUMMYUNIONNAME;
} DISK_DETECTION_INFO, *PDISK_DETECTION_INFO;

typedef
struct _DISK_GEOMETRY
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552613(v=vs.85).aspx */
{ LARGE_INTEGER 	Cylinders;
  MEDIA_TYPE		MediaType;
  ULONG 		TracksPerCylinder;
  ULONG 		SectorsPerTrack;
  ULONG 		BytesPerSector;
} DISK_GEOMETRY, *PDISK_GEOMETRY;

typedef
struct _DISK_GEOMETRY_EX
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552618(v=vs.85).aspx */
{ DISK_GEOMETRY 	Geometry;
  LARGE_INTEGER 	DiskSize;
  UCHAR 		Data[1];
} DISK_GEOMETRY_EX, *PDISK_GEOMETRY_EX;

/* Note: although declared as an array of only one byte, the Data area within
 * the DISK_GEOMETRY_EX structure represents a variable size region containing
 * a DISK_PARTITION_INFO structure followed by a DISK_DETECTION_INFO structure;
 * the above <ddk/ntdddisk.h> reference defines the following pair of macros,
 * for obtaining pointers to the embedded structures, given a pointer to the
 * containing DISK_GEOMETRY_EX structure itself; (the corresponding reference
 * for <winioctl.h> refers to these macros, without defining them).
 */
#if NTDDI_VERSION < NTDDI_WS03
 /* FIXME: given the above definition for DISK_GEOMETRY_EX, this pair of
  * macro definitions makes no sense at all...
  */
# define DiskGeometryGetPartition(Geometry) \
   ((PDISK_PARTITION_INFO)((Geometry) + 1))

# define DiskGeometryGetDetect(Geometry) \
   ((PDISK_DETECTION_INFO)(((PBYTE)DiskGeometryGetPartition(Geometry) + \
       DiskGeometryGetPartition(Geometry)->SizeOfPartitionInfo)))
#else
 /* ...whereas this pair would seem to be appropriate, regardless of the
  * underlying NTDDI_VERSION.
  */
# define DiskGeometryGetPartition(Geometry) \
   ((PDISK_PARTITION_INFO)((Geometry)->Data))

# define DiskGeometryGetDetect(Geometry) \
   ((PDISK_DETECTION_INFO)(((ULONG_PTR)DiskGeometryGetPartition(Geometry) + \
       DiskGeometryGetPartition(Geometry)->SizeOfPartitionInfo)))
#endif

typedef
struct _PARTITION_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563751(v=vs.85).aspx */
{ LARGE_INTEGER 	StartingOffset;
  LARGE_INTEGER 	PartitionLength;
  ULONG 		HiddenSectors;
  ULONG 		PartitionNumber;
  UCHAR 		PartitionType;
  BOOLEAN		BootIndicator;
  BOOLEAN		RecognizedPartition;
  BOOLEAN		RewritePartition;
} PARTITION_INFORMATION, *PPARTITION_INFORMATION;

typedef
struct _PARTITION_INFORMATION_GPT
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563763(v=vs.85).aspx */
{ GUID			PartitionType;
  GUID			PartitionId;
  ULONG64		Attributes;
  WCHAR 		Name[36];
} PARTITION_INFORMATION_GPT, *PPARTITION_INFORMATION_GPT;

typedef
struct _DISK_PARTITION_INFO
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552629(v=vs.85).aspx */
{ ULONG 		  SizeOfPartitionInfo;
  PARTITION_STYLE	  PartitionStyle;
  _ANONYMOUS_UNION union
  { struct
    { ULONG		    Signature;
      ULONG		    CheckSum;
    }			  Mbr;
    struct
    { GUID		    DiskId;
    }			  Gpt;
  } DUMMYUNIONNAME;
} DISK_PARTITION_INFO, *PDISK_PARTITION_INFO;

typedef
struct _DISK_PERFORMANCE
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552633(v=vs.85).aspx */
{ LARGE_INTEGER 	BytesRead;
  LARGE_INTEGER 	BytesWritten;
  LARGE_INTEGER 	ReadTime;
  LARGE_INTEGER 	WriteTime;
  LARGE_INTEGER 	IdleTime;
  ULONG 		ReadCount;
  ULONG 		WriteCount;
  ULONG 		QueueDepth;
  ULONG 		SplitCount;
  LARGE_INTEGER 	QueryTime;
  ULONG 		StorageDeviceNumber;
  WCHAR 		StorageManagerName[8];
} DISK_PERFORMANCE, *PDISK_PERFORMANCE;

typedef
struct _PARTITION_INFORMATION_EX
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563754(v=vs.85).aspx */
{ PARTITION_STYLE		PartitionStyle;
  LARGE_INTEGER 		StartingOffset;
  LARGE_INTEGER 		PartitionLength;
  ULONG 			PartitionNumber;
  BOOLEAN			RewritePartition;
  _ANONYMOUS_UNION union
  { PARTITION_INFORMATION_MBR	Mbr;
    PARTITION_INFORMATION_GPT	Gpt;
  } DUMMYUNIONNAME;
} PARTITION_INFORMATION_EX, *PPARTITION_INFORMATION_EX;

typedef
struct _FORMAT_EX_PARAMETERS
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff553875(v=vs.85).aspx */
{ MEDIA_TYPE	MediaType;
  ULONG 	StartCylinderNumber;
  ULONG 	EndCylinderNumber;
  ULONG 	StartHeadNumber;
  ULONG 	EndHeadNumber;
  USHORT	FormatGapLength;
  USHORT	SectorsPerTrack;
  USHORT	SectorNumber[1];
} FORMAT_EX_PARAMETERS, *PFORMAT_EX_PARAMETERS;

typedef
struct _FORMAT_PARAMETERS
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff553878(v=vs.85).aspx */
{ MEDIA_TYPE	MediaType;
  ULONG 	StartCylinderNumber;
  ULONG 	EndCylinderNumber;
  ULONG 	StartHeadNumber;
  ULONG 	EndHeadNumber;
} FORMAT_PARAMETERS, *PFORMAT_PARAMETERS;

typedef
struct _GET_LENGTH_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff554986(v=vs.85).aspx */
{ LARGE_INTEGER 	Length;
} GET_LENGTH_INFORMATION, *PGET_LENGTH_INFORMATION;

typedef
struct _REASSIGN_BLOCKS
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff563962(v=vs.85).aspx */
{ USHORT  	Reserved;
  USHORT  	Count;
  ULONG 	BlockNumber[1];
} REASSIGN_BLOCKS, *PREASSIGN_BLOCKS;

typedef
struct _SET_PARTITION_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff566192(v=vs.85).aspx */
{ UCHAR 	PartitionType;
} SET_PARTITION_INFORMATION, *PSET_PARTITION_INFORMATION;

typedef
struct _VERIFY_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff568005(v=vs.85).aspx */
{ LARGE_INTEGER 	StartingOffset;
  ULONG 		Length;
} VERIFY_INFORMATION, *PVERIFY_INFORMATION;

typedef enum
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552583(v=vs.85).aspx */
{ EqualPriority 		= 0,
  KeepPrefetchedData		= 1,
  KeepReadData			= 2
} DISK_CACHE_RETENTION_PRIORITY;

typedef
struct _DISK_CACHE_INFORMATION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552580(v=vs.85).aspx */
{ BOOLEAN				ParametersSavable;
  BOOLEAN				ReadCacheEnabled;
  BOOLEAN				WriteCacheEnabled;
  DISK_CACHE_RETENTION_PRIORITY 	ReadRetentionPriority;
  DISK_CACHE_RETENTION_PRIORITY 	WriteRetentionPriority;
  USHORT				DisablePrefetchTransferLength;
  BOOLEAN				PrefetchScalar;
  _ANONYMOUS_UNION union
  { struct
    { USHORT				  Minimum;
      USHORT				  Maximum;
      USHORT				  MaximumBlocks;
    }					ScalarPrefetch;
    struct
    { USHORT				  Minimum;
      USHORT				  Maximum;
    }					BlockPrefetch;
  } DUMMYUNIONNAME;
} DISK_CACHE_INFORMATION, *PDISK_CACHE_INFORMATION;

typedef
struct _DISK_GROW_PARTITION
/* https://msdn.microsoft.com/en-us/library/windows/hardware/ff552621(v=vs.85).aspx */
{ ULONG 		PartitionNumber;
  LARGE_INTEGER 	BytesToGrow;
} DISK_GROW_PARTITION, *PDISK_GROW_PARTITION;

/* End of _DDK_NTDDDISK_H and _WINIOCTL_H common declarations.
 */
#endif
#ifdef _DDK_NTDDDISK_H
/* Declarations specific to _DDK_NTDDDISK_H alone.
 */
_BEGIN_C_DECLS

#define DD_DISK_DEVICE_NAME			   "\\Device\\UNKNOWN"
#define DD_DISK_DEVICE_NAME_U			  L"\\Device\\UNKNOWN"

#define IOCTL_DISK_CONTROLLER_NUMBER		__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0011)
#define IOCTL_DISK_INTERNAL_SET_VERIFY		__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0100)
#define IOCTL_DISK_INTERNAL_CLEAR_VERIFY	__FILE_AM_BUFFERED(__IOCTL_DISK_,0x0101)

#define SMART_GET_VERSION			__FILE_RD_BUFFERED(__IOCTL_DISK_,0x0020)
#define SMART_RCV_DRIVE_DATA			__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0022)
#define SMART_SEND_DRIVE_COMMAND		__FILE_RW_BUFFERED(__IOCTL_DISK_,0x0021)

#define IsFTPartition( PartitionType ) \
 (((PartitionType) & PARTITION_NTFT) && IsRecognizedPartition(PartitionType))

DEFINE_GUID( WMI_DISK_GEOMETRY_GUID,
    0x25007f51L, 0x57c2, 0x11d1, 0xa5, 0x28, 0x0, 0xa0, 0xc9, 0x6, 0x29, 0x10
  );

typedef USHORT BAD_TRACK_NUMBER;
typedef USHORT *PBAD_TRACK_NUMBER;

typedef
struct _DISK_CONTROLLER_NUMBER
{ ULONG 		ControllerNumber;
  ULONG 		DiskNumber;
} DISK_CONTROLLER_NUMBER, *PDISK_CONTROLLER_NUMBER;

typedef SET_PARTITION_INFORMATION SET_PARTITION_INFORMATION_MBR;
typedef PARTITION_INFORMATION_GPT SET_PARTITION_INFORMATION_GPT;

typedef
struct _SET_PARTITION_INFORMATION_EX
{ PARTITION_STYLE			PartitionStyle;
  _ANONYMOUS_UNION union
  { SET_PARTITION_INFORMATION_MBR	Mbr;
    SET_PARTITION_INFORMATION_GPT	Gpt;
  } DUMMYUNIONNAME;
} SET_PARTITION_INFORMATION_EX, *PSET_PARTITION_INFORMATION_EX;

/* GETVERSIONINPARAMS.fCapabilities constants
 */
#define CAP_ATA_ID_CMD                    1
#define CAP_ATAPI_ID_CMD                  2
#define CAP_SMART_CMD                     4

typedef
struct _GETVERSIONINPARAMS
{ UCHAR 		bVersion;
  UCHAR 		bRevision;
  UCHAR 		bReserved;
  UCHAR 		bIDEDeviceMap;
  ULONG 		fCapabilities;
  ULONG 		dwReserved[4];
} GETVERSIONINPARAMS, *PGETVERSIONINPARAMS, *LPGETVERSIONINPARAMS;

/* IDEREGS.bCommandReg constants
 */
#define ATAPI_ID_CMD                      0xA1
#define ID_CMD                            0xEC
#define SMART_CMD                         0xB0

#define SMART_CYL_LOW                     0x4F
#define SMART_CYL_HI                      0xC2

typedef
struct _IDEREGS
{ UCHAR 		bFeaturesReg;
  UCHAR 		bSectorCountReg;
  UCHAR 		bSectorNumberReg;
  UCHAR 		bCylLowReg;
  UCHAR 		bCylHighReg;
  UCHAR 		bDriveHeadReg;
  UCHAR 		bCommandReg;
  UCHAR 		bReserved;
} IDEREGS, *PIDEREGS, *LPIDEREGS;

#include <pshpack1.h>
typedef
struct _SENDCMDINPARAMS
{ ULONG 		cBufferSize;
  IDEREGS		irDriveRegs;
  UCHAR 		bDriveNumber;
  UCHAR 		bReserved[3];
  ULONG 		dwReserved[4];
  UCHAR 		bBuffer[1];
} SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS;
#include <poppack.h>

/* DRIVERSTATUS.bDriverError constants
 */
#define SMART_NO_ERROR                    0
#define SMART_IDE_ERROR                   1
#define SMART_INVALID_FLAG                2
#define SMART_INVALID_COMMAND             3
#define SMART_INVALID_BUFFER              4
#define SMART_INVALID_DRIVE               5
#define SMART_INVALID_IOCTL               6
#define SMART_ERROR_NO_MEM                7
#define SMART_INVALID_REGISTER            8
#define SMART_NOT_SUPPORTED               9
#define SMART_NO_IDE_DEVICE               10

#define SMART_OFFLINE_ROUTINE_OFFLINE     0
#define SMART_SHORT_SELFTEST_OFFLINE      1
#define SMART_EXTENDED_SELFTEST_OFFLINE   2
#define SMART_ABORT_OFFLINE_SELFTEST      127
#define SMART_SHORT_SELFTEST_CAPTIVE      129
#define SMART_EXTENDED_SELFTEST_CAPTIVE   130

typedef
struct _DRIVERSTATUS
{ UCHAR 		bDriverError;
  UCHAR 		bIDEError;
  UCHAR 		bReserved[2];
  ULONG 		dwReserved[2];
} DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS;

#define READ_ATTRIBUTE_BUFFER_SIZE        512
#define IDENTIFY_BUFFER_SIZE              512
#define READ_THRESHOLD_BUFFER_SIZE        512
#define SMART_LOG_SECTOR_SIZE             512

#include <pshpack1.h>
typedef
struct _SENDCMDOUTPARAMS
{ ULONG 		cBufferSize;
  DRIVERSTATUS		DriverStatus;
  UCHAR 		bBuffer[1];
} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS;
#include <poppack.h>

#define READ_ATTRIBUTES                   0xD0
#define READ_THRESHOLDS                   0xD1
#define ENABLE_DISABLE_AUTOSAVE           0xD2
#define SAVE_ATTRIBUTE_VALUES             0xD3
#define EXECUTE_OFFLINE_DIAGS             0xD4
#define SMART_READ_LOG                    0xD5
#define SMART_WRITE_LOG                   0xd6
#define ENABLE_SMART                      0xD8
#define DISABLE_SMART                     0xD9
#define RETURN_SMART_STATUS               0xDA
#define ENABLE_DISABLE_AUTO_OFFLINE       0xDB

_END_C_DECLS

#endif	/* _DDK_NTDDDISK_H */
#endif	/* !_DDK_NTDDDISK_H: $RCSfile: ntdddisk.h,v $: end of file */
