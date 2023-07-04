#ifndef __LOG_H__
#define __LOG_H__

#ifdef DEBUG
#define LOG(fmt, ...) printf("DBG :%s:%3d: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define LOG(fmt, ...)
#endif

#endif
