//
// C++ Interface: diskio
//
// Description: Class to handle low-level disk I/O for GPT fdisk
//
//
// Author: Rod Smith <rodsmith@rodsbooks.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
// This program is copyright (c) 2009 by Roderick W. Smith. It is distributed
// under the terms of the GNU GPL version 2, as detailed in the COPYING file.

#ifndef __DISKIO_H
#define __DISKIO_H

#include <string>
#include <stdint.h>
#include <sys/types.h>
#ifdef _WIN32
#include <windows.h>
#include <winioctl.h>
#else
#include <sys/ioctl.h>
#endif

#ifdef __sun__
#include <sys/dkio.h>
#endif

#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__) || defined (__APPLE__)
#define fstat64 fstat
#define stat64 stat
#endif

#include "support.h"
//#include "parttypes.h"

/***************************************
 *                                     *
 * DiskIO class and related structures *
 *                                     *
 ***************************************/

class DiskIO {
   protected:
      std::string userFilename;
      std::string realFilename;
      std::string modelName;
      int isOpen;
      int openForWrite;
#ifdef _WIN32
      HANDLE fd;
#else
      int fd;
#endif
#ifdef ENABLE_HEAP_DISKIO
      const unsigned char* data;
      size_t size;
      off_t off;
#endif
   public:
      DiskIO(void);
      ~DiskIO(void);

      void MakeRealName(void);
#ifdef ENABLE_HEAP_DISKIO
      int OpenForRead(const unsigned char* data, size_t size);
#endif
      int OpenForRead(const std::string & filename);
      int OpenForRead(void);
      int OpenForWrite(const std::string & filename);
      int OpenForWrite(void);
      void Close();
      int Seek(uint64_t sector);
      int Read(void* buffer, int numBytes);
      int Write(void* buffer, int numBytes);
      int DiskSync(void); // resync disk caches to use new partitions
      int GetBlockSize(void);
      int GetPhysBlockSize(void);
      std::string GetModel(void) {return modelName;}
      uint32_t GetNumHeads(void);
      uint32_t GetNumSecsPerTrack(void);
      int IsOpen(void) {return isOpen;}
      int IsOpenForWrite(void) {return openForWrite;}
      std::string GetName(void) const {return realFilename;}

      uint64_t DiskSize(int* err);
}; // class DiskIO

#endif
