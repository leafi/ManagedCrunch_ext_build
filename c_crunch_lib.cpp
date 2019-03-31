// Based on crunch/emscripten/crunch_lib.cpp
// just... without PLATFORM_NACL. and with a few bits
// similar to ManagedCrunch's crn.cpp.
// ...and combining all the basic funcs into one "crn_get_info" func.
// ...and supporting cubemaps, optimistically.

#include <stddef.h> // For NULL, size_t
#include <cstring> // for malloc etc

#include <cstdint> // "C++11" uintptr_t definition

#include "crn_decomp.h"

#ifndef EXPORT
#   if defined(__GNUC__)
#       define EXPORT extern "C" __attribute__ ((visibility("default")))
#   else
#       define EXPORT extern "C" __declspec(dllexport)
#   endif
#endif

EXPORT void crn_get_info(
    void* src,
    unsigned int src_size,
    unsigned int* out_faces,
    crn_format* out_format,
    unsigned int* out_levels,
    unsigned int* out_width,
    unsigned int* out_height
) {
    crnd::crn_texture_info tex_info;
    crnd::crnd_get_texture_info(static_cast<crn_uint8*>(src), src_size, &tex_info);
    *out_faces = tex_info.m_faces;
    *out_format = tex_info.m_format;
    *out_levels = tex_info.m_levels;
    *out_width = tex_info.m_width;
    *out_height = tex_info.m_height;
}

EXPORT unsigned int crn_get_uncompressed_size_per_face(void* src, unsigned int src_size, unsigned int level) {
    crnd::crn_texture_info tex_info;
    crnd::crnd_get_texture_info(static_cast<crn_uint8*>(src), src_size, &tex_info);
    const crn_uint32 width = tex_info.m_width >> level;
    const crn_uint32 height = tex_info.m_height >> level;
    const crn_uint32 blocks_x = (width + 3) >> 2;
    const crn_uint32 blocks_y = (height + 3) >> 2;
    const crn_uint32 row_pitch = blocks_x * crnd::crnd_get_bytes_per_dxt_block(tex_info.m_format);
    const crn_uint32 total_face_size = row_pitch * blocks_y;
    return total_face_size;
}

EXPORT void crn_decompress_only_face(
    void* src,
    unsigned int src_size,
    void* dst,
    unsigned int dst_size,
    unsigned int firstLevel,
    unsigned int levelCount
) {
    crnd::crn_texture_info tex_info;
    crnd::crnd_get_texture_info(static_cast<crn_uint8*>(src), src_size, &tex_info);

    crn_uint32 width = tex_info.m_width >> firstLevel;
    crn_uint32 height = tex_info.m_height >> firstLevel;
    crn_uint32 bytes_per_block = crnd::crnd_get_bytes_per_dxt_block(tex_info.m_format);

    void* pDecomp_images[1];
    pDecomp_images[0] = dst;

    crnd::crnd_unpack_context pContext =
        crnd::crnd_unpack_begin(static_cast<crn_uint8*>(src), src_size);
    
    for (int i = firstLevel; i < firstLevel + levelCount; ++i) {
        crn_uint32 blocks_x = (width + 3) >> 2;
        crn_uint32 blocks_y = (height + 3) >> 2;
        crn_uint32 row_pitch = blocks_x * bytes_per_block;
        crn_uint32 total_level_size = row_pitch * blocks_y;

        crnd::crnd_unpack_level(pContext, pDecomp_images, total_level_size, row_pitch, i);
        pDecomp_images[0] = (char*)pDecomp_images[0] + total_level_size;

        width = width >> 1;
        height = height >> 1;
    }

    crnd::crnd_unpack_end(pContext);
}

EXPORT void crn_decompress_six_faces(
    void* src,
    unsigned int src_size,
    void** six_dsts,
    unsigned int each_dst_size,
    unsigned int firstLevel,
    unsigned int levelCount
) {
    crnd::crn_texture_info tex_info;
    crnd::crnd_get_texture_info(static_cast<crn_uint8*>(src), src_size, &tex_info);

    crn_uint32 width = tex_info.m_width >> firstLevel;
    crn_uint32 height = tex_info.m_height >> firstLevel;
    crn_uint32 bytes_per_block = crnd::crnd_get_bytes_per_dxt_block(tex_info.m_format);

    void* pDecomp_images[6];
    pDecomp_images[0] = six_dsts[0];
    pDecomp_images[1] = six_dsts[1];
    pDecomp_images[2] = six_dsts[2];
    pDecomp_images[3] = six_dsts[3];
    pDecomp_images[4] = six_dsts[4];
    pDecomp_images[5] = six_dsts[5];

    crnd::crnd_unpack_context pContext =
        crnd::crnd_unpack_begin(static_cast<crn_uint8*>(src), src_size);

    for (int i = firstLevel; i < firstLevel + levelCount; ++i) {
        crn_uint32 blocks_x = (width + 3) >> 2;
        crn_uint32 blocks_y = (height + 3) >> 2;
        crn_uint32 row_pitch = blocks_x * bytes_per_block;
        crn_uint32 total_level_size = row_pitch * blocks_y;

        crnd::crnd_unpack_level(pContext, pDecomp_images, total_level_size, row_pitch, i);
        pDecomp_images[0] = (char*)pDecomp_images[0] + total_level_size;
        pDecomp_images[1] = (char*)pDecomp_images[1] + total_level_size;
        pDecomp_images[2] = (char*)pDecomp_images[2] + total_level_size;
        pDecomp_images[3] = (char*)pDecomp_images[3] + total_level_size;
        pDecomp_images[4] = (char*)pDecomp_images[4] + total_level_size;
        pDecomp_images[5] = (char*)pDecomp_images[5] + total_level_size;

        width = width >> 1;
        height = height >> 1;
    }

    crnd::crnd_unpack_end(pContext);
}

