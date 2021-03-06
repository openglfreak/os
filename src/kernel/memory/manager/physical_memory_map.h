#ifndef _PHYSICAL_MEMORY_MAP
#define _PHYSICAL_MEMORY_MAP

#include "page_type.h"

#define PHYSICAL_MEMORY_MAP_SECTION_ENTRY_PAGE_TYPE(t) ((t)&0x0F)
#define PHYSICAL_MEMORY_MAP_SECTION_ENTRY_REFERENCE_COUNT(c) (((c)&0xFF)<<0x04)
#define PHYSICAL_MEMORY_MAP_SECTION_ENTRY_DATA(d) ((((uint32_t)(d))&0x0FFFFF)<<0x0C)
#define PHYSICAL_MEMORY_MAP_SECTION_ENTRY(data,refc,type) \
        (PHYSICAL_MEMORY_MAP_SECTION_ENTRY_DATA(data) |\
        PHYSICAL_MEMORY_MAP_SECTION_ENTRY_REFERENCE_COUNT(refc) |\
        PHYSICAL_MEMORY_MAP_SECTION_ENTRY_PAGE_TYPE(type))

#define PHYSICAL_MEMORY_MAP_ENTRY_REFERENCE_COUNT(r) (((r)&0x03FFFF)<<0x0E)
#define PHYSICAL_MEMORY_MAP_ENTRY_ADDRESS(d) (((uint32_t)(d))&0xFFFFF000)
#define PHYSICAL_MEMORY_MAP_ENTRY_REFERENCED_PAGES_COUNT(c) ((((c)-1)&0x03FF)<<0x04)
#define PHYSICAL_MEMORY_MAP_ENTRY_DIRECT 0x08
#define PHYSICAL_MEMORY_MAP_ENTRY_SECTION 0x00
#define PHYSICAL_MEMORY_MAP_ENTRY_PAGE_TYPE(t) ((t)&0x07)
#define PHYSICAL_MEMORY_MAP_ENTRY(ar,refpc,s,type) \
        (((s)?PHYSICAL_MEMORY_MAP_ENTRY_REFERENCE_COUNT((uint32_t)(ar)):PHYSICAL_MEMORY_MAP_ENTRY_ADDRESS(ar)) |\
        PHYSICAL_MEMORY_MAP_ENTRY_REFERENCED_PAGES_COUNT(refpc) |\
        ((s)?PHYSICAL_MEMORY_MAP_ENTRY_DIRECT:PHYSICAL_MEMORY_MAP_ENTRY_SECTION) |\
        PAGE_TYPE(type))

typedef uint32_t PHYSICAL_MEMORY_MAP_SECTION_ENTRY;
typedef uint32_t PHYSICAL_MEMORY_MAP_ENTRY;

typedef struct __attribute__((aligned(0x1000))) {
    PHYSICAL_MEMORY_MAP_SECTION_ENTRY entries[1024];
} PHYSICAL_MEMORY_MAP_SECTION;

typedef struct {
    PHYSICAL_MEMORY_MAP_ENTRY entries[1024];
} PHYSICAL_MEMORY_MAP;

#endif // _PHYSICAL_MEMORY_MAP
