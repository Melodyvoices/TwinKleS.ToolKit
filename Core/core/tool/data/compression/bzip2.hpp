#pragma once

#include "core/utility/utility.hpp"
#include "core/third/bzip2.hpp"

namespace TwinStar::Core::Tool::Data::Compression::BZip2 {

	struct CompressCommon {

	protected:

	};

	struct Compress :
		CompressCommon {

	protected:

		static auto process_whole (
			IByteStreamView & raw,
			OByteStreamView & ripe,
			Size const &      block_size,
			Size const &      work_factor
		) -> Void {
			assert_test(Math::between(block_size, 1_sz, 9_sz));
			assert_test(Math::between(work_factor, 0_sz, 250_sz));
			auto bz_stream = Third::bzip2::bz_stream{
				.next_in = cast_pointer<char>(as_variable_pointer(raw.current_pointer())).value,
				.avail_in = static_cast<unsigned int>(raw.reserve().value),
				.total_in_lo32 = 0,
				.total_in_hi32 = 0,
				.next_out = cast_pointer<char>(ripe.current_pointer()).value,
				.avail_out = static_cast<unsigned int>(ripe.reserve().value),
				.total_out_lo32 = 0,
				.total_out_hi32 = 0,
				.state = nullptr,
				.bzalloc = nullptr,
				.bzfree = nullptr,
				.opaque = nullptr,
			};
			auto state = int{};
			state = Third::bzip2::BZ2_bzCompressInit(
				&bz_stream,
				static_cast<int>(block_size.value),
				0,
				static_cast<int>(work_factor.value)
			);
			assert_test(state == Third::bzip2::BZ_OK_);
			state = Third::bzip2::BZ2_bzCompress(
				&bz_stream,
				Third::bzip2::BZ_FINISH_
			);
			assert_test(state == Third::bzip2::BZ_STREAM_END_);
			state = Third::bzip2::BZ2_bzCompressEnd(
				&bz_stream
			);
			assert_test(state == Third::bzip2::BZ_OK_);
			assert_test(bz_stream.avail_in == 0);
			raw.forward(mbw<Size>((static_cast<uint64_t>(bz_stream.total_in_hi32) << 32) + static_cast<uint64_t>(bz_stream.total_in_lo32)));
			ripe.forward(mbw<Size>((static_cast<uint64_t>(bz_stream.total_out_hi32) << 32) + static_cast<uint64_t>(bz_stream.total_out_lo32)));
			assert_test(raw.full());
			return;
		}

	public:

		static auto do_process_whole (
			IByteStreamView & raw_,
			OByteStreamView & ripe_,
			Size const &      block_size,
			Size const &      work_factor
		) -> Void {
			M_use_zps_of(raw);
			M_use_zps_of(ripe);
			return process_whole(raw, ripe, block_size, work_factor);
		}

	};

	struct Uncompress :
		CompressCommon {

	protected:

		static auto process_whole (
			IByteStreamView & ripe,
			OByteStreamView & raw,
			Boolean const &   small
		) -> Void {
			auto bz_stream = Third::bzip2::bz_stream{
				.next_in = cast_pointer<char>(as_variable_pointer(ripe.current_pointer())).value,
				.avail_in = static_cast<unsigned int>(ripe.reserve().value),
				.total_in_lo32 = 0,
				.total_in_hi32 = 0,
				.next_out = cast_pointer<char>(raw.current_pointer()).value,
				.avail_out = static_cast<unsigned int>(raw.reserve().value),
				.total_out_lo32 = 0,
				.total_out_hi32 = 0,
				.state = nullptr,
				.bzalloc = nullptr,
				.bzfree = nullptr,
				.opaque = nullptr,
			};
			auto state = int{};
			state = Third::bzip2::BZ2_bzDecompressInit(
				&bz_stream,
				0,
				static_cast<int>(small.value)
			);
			assert_test(state == Third::bzip2::BZ_OK_);
			state = Third::bzip2::BZ2_bzDecompress(
				&bz_stream
			);
			assert_test(state == Third::bzip2::BZ_STREAM_END_);
			state = Third::bzip2::BZ2_bzDecompressEnd(
				&bz_stream
			);
			assert_test(state == Third::bzip2::BZ_OK_);
			ripe.forward(mbw<Size>((static_cast<uint64_t>(bz_stream.total_in_hi32) << 32) + static_cast<uint64_t>(bz_stream.total_in_lo32)));
			raw.forward(mbw<Size>((static_cast<uint64_t>(bz_stream.total_out_hi32) << 32) + static_cast<uint64_t>(bz_stream.total_out_lo32)));
			return;
		}

	public:

		static auto do_process_whole (
			IByteStreamView & ripe_,
			OByteStreamView & raw_,
			Boolean const &   small
		) -> Void {
			M_use_zps_of(ripe);
			M_use_zps_of(raw);
			return process_whole(ripe, raw, small);
		}

	};

}
