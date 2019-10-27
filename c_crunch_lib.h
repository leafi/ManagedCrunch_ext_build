// Supported compressed pixel formats.
// Basically all the standard DX9 formats, with some swizzled DXT5 formats
// (most of them supported by ATI's Compressonator), along with some ATI/X360 GPU specific formats.
enum crn_format {
  cCRNFmtInvalid = -1,

  cCRNFmtDXT1 = 0,

  cCRNFmtFirstValid = cCRNFmtDXT1,

  // cCRNFmtDXT3 is not currently supported when writing to CRN - only DDS.
  cCRNFmtDXT3,

  cCRNFmtDXT5,

  // Various DXT5 derivatives
  cCRNFmtDXT5_CCxY,  // Luma-chroma
  cCRNFmtDXT5_xGxR,  // Swizzled 2-component
  cCRNFmtDXT5_xGBR,  // Swizzled 3-component
  cCRNFmtDXT5_AGBR,  // Swizzled 4-component

  // ATI 3DC and X360 DXN
  cCRNFmtDXN_XY,
  cCRNFmtDXN_YX,

  // DXT5 alpha blocks only
  cCRNFmtDXT5A,

  cCRNFmtETC1,
  cCRNFmtETC2,
  cCRNFmtETC2A,
  cCRNFmtETC1S,
  cCRNFmtETC2AS,

  cCRNFmtTotal,

  cCRNFmtForceDWORD = 0xFFFFFFFF
};


void crn_get_info(
    void* src,
    unsigned int src_size,
    unsigned int* out_faces,
    enum crn_format* out_format,
    unsigned int* out_levels,
    unsigned int* out_width,
    unsigned int* out_height
);

unsigned int crn_get_uncompressed_size_per_face(
    void* src,
    unsigned int src_size,
    unsigned int level
);

void crn_decompress_only_face(
    void* src,
    unsigned int src_size,
    void* dst,
    unsigned int dst_size,
    unsigned int firstLevel,
    unsigned int levelCount
);

void crn_decompress_six_faces(
    void* src,
    unsigned int src_size,
    void** six_dsts,
    unsigned int each_dst_size,
    unsigned int firstLevel,
    unsigned int levelCount
);

    
