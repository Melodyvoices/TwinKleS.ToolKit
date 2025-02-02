#pragma once

#if defined M_compiler_msvc
#pragma warning(push)
#endif
#if defined M_compiler_clang
#pragma clang diagnostic push
#endif

#include "third/libpng/png.h"
#include "third/libpng/pngstruct.h"
#include "third/libpng/pnginfo.h"

#if defined M_compiler_msvc
#pragma warning(pop)
#endif
#if defined M_compiler_clang
#pragma clang diagnostic pop
#endif

namespace TwinStar::Core::Third::libpng {

	using size_t = ::size_t;

	using png_structp = ::png_structp;

	using png_bytep = ::png_bytep;

	using png_const_bytep = ::png_const_bytep;

	using png_const_charp = ::png_const_charp;

	using png_color_16p = ::png_color_16p;

	using png_uint_32 = ::png_uint_32;

	inline constexpr auto png_error = ::png_error;

	inline constexpr auto png_set_error_fn = ::png_set_error_fn;

	inline constexpr auto png_set_read_fn = ::png_set_read_fn;

	inline constexpr auto png_set_write_fn = ::png_set_write_fn;

	inline constexpr auto png_get_io_ptr = ::png_get_io_ptr;

	inline constexpr auto png_create_read_struct = ::png_create_read_struct;

	inline constexpr auto png_destroy_read_struct = ::png_destroy_read_struct;

	inline constexpr auto png_create_write_struct = ::png_create_write_struct;

	inline constexpr auto png_destroy_write_struct = ::png_destroy_write_struct;

	inline constexpr auto png_create_info_struct = ::png_create_info_struct;

	inline constexpr auto png_read_info = ::png_read_info;

	inline constexpr auto png_read_row = ::png_read_row;

	inline constexpr auto png_read_end = ::png_read_end;

	inline constexpr auto png_write_info = ::png_write_info;

	inline constexpr auto png_write_row = ::png_write_row;

	inline constexpr auto png_write_end = ::png_write_end;

	inline constexpr auto png_set_IHDR = ::png_set_IHDR;

	inline constexpr auto png_get_sRGB = ::png_get_sRGB;

	inline constexpr auto png_get_gAMA = ::png_get_gAMA;

	inline constexpr auto png_get_tRNS = ::png_get_tRNS;

	inline constexpr auto png_get_bKGD = ::png_get_bKGD;

	inline constexpr auto png_set_background = ::png_set_background;

	inline constexpr auto png_set_add_alpha = ::png_set_add_alpha;

	inline constexpr auto png_set_tRNS_to_alpha = ::png_set_tRNS_to_alpha;

	inline constexpr auto png_set_palette_to_rgb = ::png_set_palette_to_rgb;

	inline constexpr auto png_set_expand_gray_1_2_4_to_8 = ::png_set_expand_gray_1_2_4_to_8;

	inline constexpr auto png_set_gray_to_rgb = ::png_set_gray_to_rgb;

	inline constexpr auto png_set_scale_16 = ::png_set_scale_16;

	inline constexpr auto png_set_gamma = ::png_set_gamma;

	inline constexpr auto PNG_DEFAULT_sRGB_ = PNG_DEFAULT_sRGB;

	inline constexpr auto PNG_FILLER_AFTER_ = PNG_FILLER_AFTER;

	inline constexpr auto PNG_BACKGROUND_GAMMA_FILE_ = PNG_BACKGROUND_GAMMA_FILE;

	inline constexpr auto PNG_COLOR_TYPE_PALETTE_ = PNG_COLOR_TYPE_PALETTE;

	inline constexpr auto PNG_COLOR_TYPE_GRAY_ = PNG_COLOR_TYPE_GRAY;

	inline constexpr auto PNG_COLOR_TYPE_GRAY_ALPHA_ = PNG_COLOR_TYPE_GRAY_ALPHA;

	inline constexpr auto PNG_COLOR_TYPE_RGB_ = PNG_COLOR_TYPE_RGB;

	inline constexpr auto PNG_COLOR_TYPE_RGB_ALPHA_ = PNG_COLOR_TYPE_RGB_ALPHA;

	inline constexpr auto PNG_INTERLACE_NONE_ = PNG_INTERLACE_NONE;

	inline constexpr auto PNG_COMPRESSION_TYPE_DEFAULT_ = PNG_COMPRESSION_TYPE_DEFAULT;

	inline constexpr auto PNG_FILTER_TYPE_DEFAULT_ = PNG_FILTER_TYPE_DEFAULT;

	inline constexpr auto PNG_LIBPNG_VER_STRING_ = PNG_LIBPNG_VER_STRING;

}
