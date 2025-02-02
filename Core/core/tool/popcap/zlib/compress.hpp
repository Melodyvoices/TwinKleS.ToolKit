#pragma once

#include "core/utility/utility.hpp"
#include "core/tool/popcap/zlib/version.hpp"
#include "core/tool/data/compression/deflate.hpp"

namespace TwinStar::Core::Tool::PopCap::ZLib {

	template <auto version> requires (check_version(version, {}))
	struct CompressCommon {

	protected:

		using MagicIdentifier = IntegerU32;

		inline static constexpr auto k_magic_identifier = MagicIdentifier{0xDEADFED4_iu32};

		// ----------------

		using IntegerOfPlatform = AsSwitch<version.variant_64.value, IntegerU64, IntegerU32>;

	};

	template <auto version> requires (check_version(version, {}))
	struct Compress :
		CompressCommon<version> {

	protected:

		using Common = CompressCommon<version>;

		using typename Common::MagicIdentifier;

		using Common::k_magic_identifier;

		using typename Common::IntegerOfPlatform;

		// ----------------

		template <typename RawValue> requires
			CategoryConstraint<IsPureInstance<RawValue>>
			&& (IsBaseWrapper<RawValue>)
		static auto exchange_unit_constant (
			OByteStreamView & data,
			RawValue const &  value
		) -> Void {
			data.write_constant(value);
			return;
		}

		static auto exchange_unit_integer_platform (
			OByteStreamView & data,
			Integer const &   value
		) -> Void {
			data.write(cbw<IntegerOfPlatform>(value));
			return;
		}

		// ----------------

		static auto compute_size_bound (
			Size const & raw_size,
			Size &       ripe_size_bound,
			Size const & window_bits,
			Size const & memory_level
		) -> Void {
			ripe_size_bound = k_none_size;
			ripe_size_bound += bs_static_size<MagicIdentifier>();
			if constexpr (check_version(version, {true})) {
				ripe_size_bound += bs_static_size<IntegerU32>();
			}
			ripe_size_bound += bs_static_size<IntegerOfPlatform>();
			auto ripe_data_size_bound = Size{};
			Data::Compression::Deflate::Compress::do_compute_size_bound(raw_size, ripe_data_size_bound, window_bits, memory_level, Data::Compression::Deflate::Wrapper::Constant::zlib());
			ripe_size_bound += ripe_data_size_bound;
			return;
		}

		// ----------------

		static auto process_whole (
			IByteStreamView &                            raw,
			OByteStreamView &                            ripe,
			Size const &                                 level,
			Size const &                                 window_bits,
			Size const &                                 memory_level,
			Data::Compression::Deflate::Strategy const & strategy
		) -> Void {
			ripe.write_constant(k_magic_identifier);
			if constexpr (check_version(version, {true})) {
				exchange_unit_constant(ripe, 0x00000000_iu32);
			}
			exchange_unit_integer_platform(ripe, cbw<Integer>(raw.reserve()));
			Data::Compression::Deflate::Compress::do_process_whole(raw, ripe, level, window_bits, memory_level, strategy, Data::Compression::Deflate::Wrapper::Constant::zlib());
			return;
		}

	public:

		static auto do_compute_size_bound (
			Size const & raw_size,
			Size &       ripe_size_bound,
			Size const & window_bits,
			Size const & memory_level
		) -> Void {
			restruct(ripe_size_bound);
			return compute_size_bound(raw_size, ripe_size_bound, window_bits, memory_level);
		}

		static auto do_process_whole (
			IByteStreamView &                            raw_,
			OByteStreamView &                            ripe_,
			Size const &                                 level,
			Size const &                                 window_bits,
			Size const &                                 memory_level,
			Data::Compression::Deflate::Strategy const & strategy
		) -> Void {
			M_use_zps_of(raw);
			M_use_zps_of(ripe);
			return process_whole(raw, ripe, level, window_bits, memory_level, strategy);
		}

	};

	template <auto version> requires (check_version(version, {}))
	struct Uncompress :
		CompressCommon<version> {

	protected:

		using Common = CompressCommon<version>;

		using typename Common::MagicIdentifier;

		using Common::k_magic_identifier;

		using typename Common::IntegerOfPlatform;

		// ----------------

		template <typename RawValue> requires
			CategoryConstraint<IsPureInstance<RawValue>>
			&& (IsBaseWrapper<RawValue>)
		static auto exchange_unit_constant (
			IByteStreamView & data,
			RawValue const &  value
		) -> Void {
			data.read_constant(value);
			return;
		}

		static auto exchange_unit_integer_platform (
			IByteStreamView & data,
			Integer &         value
		) -> Void {
			value = cbw<Integer>(data.read_of<IntegerOfPlatform>());
			return;
		}

		// ----------------

		static auto compute_size (
			CByteListView const & ripe,
			Size &                raw_size
		) -> Void {
			raw_size = k_none_size;
			auto ripe_stream = IByteStreamView{ripe};
			ripe_stream.read_constant(k_magic_identifier);
			if constexpr (check_version(version, {true})) {
				exchange_unit_constant(ripe_stream, 0x00000000_iu32);
			}
			auto raw_data_size = cbw<Size>(M_apply(M_wrap(Integer{}), M_wrap({ exchange_unit_integer_platform(ripe_stream, it); })));
			raw_size += raw_data_size;
			return;
		}

		// ----------------

		static auto process_whole (
			IByteStreamView & ripe,
			OByteStreamView & raw,
			Size const &      window_bits
		) -> Void {
			ripe.read_constant(k_magic_identifier);
			if constexpr (check_version(version, {true})) {
				exchange_unit_constant(ripe, 0x00000000_iu32);
			}
			auto raw_data_begin = raw.position();
			auto raw_data_size = cbw<Size>(M_apply(M_wrap(Integer{}), M_wrap({ exchange_unit_integer_platform(ripe, it); })));
			Data::Compression::Deflate::Uncompress::do_process_whole(ripe, raw, window_bits, Data::Compression::Deflate::Wrapper::Constant::zlib());
			assert_test(raw.position() - raw_data_begin == raw_data_size);
			return;
		}

	public:

		static auto do_compute_size (
			CByteListView const & ripe,
			Size &                raw_size
		) -> Void {
			restruct(raw_size);
			return compute_size(ripe, raw_size);
		}

		static auto do_process_whole (
			IByteStreamView & ripe_,
			OByteStreamView & raw_,
			Size const &      window_bits
		) -> Void {
			M_use_zps_of(ripe);
			M_use_zps_of(raw);
			return process_whole(ripe, raw, window_bits);
		}

	};

}
