#pragma once

#include "core/utility/utility.hpp"
#include "core/third/libpng.hpp"

namespace TwinStar::Core::Tool::Image::File::PNG {

	struct WriteCommon {

	protected:

		static auto png_error (
			Third::libpng::png_structp     png_ptr,
			Third::libpng::png_const_charp error_message
		) -> Void {
			throw UnnamedException{mss("libpng error : {}"_sf(error_message))};
			return;
		}

		static auto png_warning (
			Third::libpng::png_structp     png_ptr,
			Third::libpng::png_const_charp error_message
		) -> Void {
			M_log(mss("libpng warning : {}"_sf(error_message)));
			return;
		}

		// ----------------

		static auto png_read_data (
			Third::libpng::png_structp png_ptr,
			Third::libpng::png_bytep   data,
			Third::libpng::size_t      length
		) -> Void {
			auto & stream = *static_cast<IByteStreamView *>(Third::libpng::png_get_io_ptr(png_ptr));
			if (stream.reserve() < mbw<Size>(length)) {
				Third::libpng::png_error(png_ptr, "Read Error");
			}
			std::memcpy(data, stream.current_pointer().value, length);
			stream.forward(mbw<Size>(length));
			return;
		}

		static auto png_write_data (
			Third::libpng::png_structp png_ptr,
			Third::libpng::png_bytep   data,
			Third::libpng::size_t      length
		) -> Void {
			auto & stream = *static_cast<OByteStreamView *>(Third::libpng::png_get_io_ptr(png_ptr));
			if (stream.reserve() < mbw<Size>(length)) {
				Third::libpng::png_error(png_ptr, "Write Error");
			}
			std::memcpy(stream.current_pointer().value, data, length);
			stream.forward(mbw<Size>(length));
			return;
		}

		static auto png_output_flush (
			Third::libpng::png_structp png_ptr
		) -> Void {
			return;
		}

	};

	struct Write :
		WriteCommon {

	protected:

		static auto process_image (
			OByteStreamView &         data,
			Image::CImageView const & image
		) -> Void {
			auto png_struct = Third::libpng::png_create_write_struct(Third::libpng::PNG_LIBPNG_VER_STRING_, nullptr, nullptr, nullptr);
			Third::libpng::png_set_error_fn(png_struct, nullptr, &png_error, &png_warning);
			Third::libpng::png_set_write_fn(png_struct, &data, png_write_data, &png_output_flush);
			auto png_info = Third::libpng::png_create_info_struct(png_struct);
			Third::libpng::png_set_IHDR(png_struct, png_info, static_cast<Third::libpng::png_uint_32>(image.size().width.value), static_cast<Third::libpng::png_uint_32>(image.size().height.value), static_cast<int>(k_type_bit_count<Color>.value), Third::libpng::PNG_COLOR_TYPE_RGB_ALPHA_, Third::libpng::PNG_INTERLACE_NONE_, Third::libpng::PNG_COMPRESSION_TYPE_DEFAULT_, Third::libpng::PNG_FILTER_TYPE_DEFAULT_);
			Third::libpng::png_write_info(png_struct, png_info);
			for (auto & row : image.data()) {
				Third::libpng::png_write_row(png_struct, reinterpret_cast<Third::libpng::png_const_bytep>(row.begin().value));
			}
			Third::libpng::png_write_end(png_struct, png_info);
			Third::libpng::png_destroy_write_struct(&png_struct, &png_info);
			return;
		}

	public:

		static auto do_process_image (
			OByteStreamView &         data_,
			Image::CImageView const & image
		) -> Void {
			M_use_zps_of(data);
			return process_image(data, image);
		}

	};

	struct Read :
		WriteCommon {

	protected:

		static auto compute_image_size (
			CByteListView const & data,
			Image::ImageSize &    image_size
		) -> Void {
			auto stream = IByteStreamView{data};
			auto png_struct = Third::libpng::png_create_read_struct(Third::libpng::PNG_LIBPNG_VER_STRING_, nullptr, nullptr, nullptr);
			Third::libpng::png_set_error_fn(png_struct, nullptr, &png_error, &png_warning);
			Third::libpng::png_set_read_fn(png_struct, &stream, &png_read_data);
			auto png_info = Third::libpng::png_create_info_struct(png_struct);
			Third::libpng::png_read_info(png_struct, png_info);
			image_size = Image::ImageSize{mbw<Size>((*png_struct).width), mbw<Size>((*png_struct).height)};
			Third::libpng::png_destroy_read_struct(&png_struct, &png_info, nullptr);
			return;
		}

		// ----------------

		static auto process_image (
			IByteStreamView &         data,
			Image::VImageView const & image
		) -> Void {
			auto png_struct = Third::libpng::png_create_read_struct(Third::libpng::PNG_LIBPNG_VER_STRING_, nullptr, nullptr, nullptr);
			Third::libpng::png_set_error_fn(png_struct, nullptr, &png_error, &png_warning);
			Third::libpng::png_set_read_fn(png_struct, &data, &png_read_data);
			auto png_info = Third::libpng::png_create_info_struct(png_struct);
			Third::libpng::png_read_info(png_struct, png_info);
			assert_test(image.size() == Image::ImageSize{mbw<Size>((*png_struct).width), mbw<Size>((*png_struct).height)});
			switch ((*png_info).color_type) {
				case Third::libpng::PNG_COLOR_TYPE_PALETTE_ : {
					Third::libpng::png_set_add_alpha(png_struct, 0xFF, Third::libpng::PNG_FILLER_AFTER_);
					Third::libpng::png_set_palette_to_rgb(png_struct);
					break;
				}
				case Third::libpng::PNG_COLOR_TYPE_GRAY_ : {
					Third::libpng::png_set_add_alpha(png_struct, 0xFF, Third::libpng::PNG_FILLER_AFTER_);
					if ((*png_info).bit_depth == 1 || (*png_info).bit_depth == 2 || (*png_info).bit_depth == 4) {
						Third::libpng::png_set_expand_gray_1_2_4_to_8(png_struct);
					}
					[[fallthrough]];
				}
				case Third::libpng::PNG_COLOR_TYPE_GRAY_ALPHA_ : {
					if ((*png_info).bit_depth == 16) {
						Third::libpng::png_set_scale_16(png_struct);
					}
					Third::libpng::png_set_gray_to_rgb(png_struct);
					break;
				}
				case Third::libpng::PNG_COLOR_TYPE_RGB_ : {
					Third::libpng::png_set_add_alpha(png_struct, 0xFF, Third::libpng::PNG_FILLER_AFTER_);
					[[fallthrough]];
				}
				case Third::libpng::PNG_COLOR_TYPE_RGB_ALPHA_ : {
					if ((*png_info).bit_depth == 16) {
						Third::libpng::png_set_scale_16(png_struct);
					}
					break;
				}
				default : {
					throw ImpossibleException{};
				}
			}
			auto png_trans_alpha = Third::libpng::png_bytep{};
			auto png_num_trans = int{};
			auto png_trans_color = Third::libpng::png_color_16p{};
			if (Third::libpng::png_get_tRNS(png_struct, png_info, &png_trans_alpha, &png_num_trans, &png_trans_color) != 0) {
				Third::libpng::png_set_tRNS_to_alpha(png_struct);
			}
			auto png_background = Third::libpng::png_color_16p{};
			if (Third::libpng::png_get_bKGD(png_struct, png_info, &png_background) != 0) {
				Third::libpng::png_set_background(png_struct, png_background, Third::libpng::PNG_BACKGROUND_GAMMA_FILE_, 1, 1.0);
			}
			auto png_file_srgb_intent = int{};
			auto png_file_gamma = double{};
			if (Third::libpng::png_get_sRGB(png_struct, png_info, &png_file_srgb_intent) != 0) {
				Third::libpng::png_set_gamma(png_struct, Third::libpng::PNG_DEFAULT_sRGB_, Third::libpng::PNG_DEFAULT_sRGB_);
			} else if (Third::libpng::png_get_gAMA(png_struct, png_info, &png_file_gamma) != 0) {
				Third::libpng::png_set_gamma(png_struct, Third::libpng::PNG_DEFAULT_sRGB_, png_file_gamma);
			} else {
				Third::libpng::png_set_gamma(png_struct, Third::libpng::PNG_DEFAULT_sRGB_, 0.45455);
			}
			for (auto & row : image.data()) {
				Third::libpng::png_read_row(png_struct, reinterpret_cast<Third::libpng::png_bytep>(row.begin().value), nullptr);
			}
			Third::libpng::png_read_end(png_struct, png_info);
			Third::libpng::png_destroy_read_struct(&png_struct, &png_info, nullptr);
			return;
		}

	public:

		static auto do_compute_image_size (
			CByteListView const & data,
			Image::ImageSize &    image_size
		) -> Void {
			restruct(image_size);
			return compute_image_size(data, image_size);
		}

		// ----------------

		static auto do_process_image (
			IByteStreamView &         data_,
			Image::VImageView const & image
		) -> Void {
			M_use_zps_of(data);
			return process_image(data, image);
		}

	};

}
