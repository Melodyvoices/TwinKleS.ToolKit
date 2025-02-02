#pragma once

#include "shell/common.hpp"
#include "shell/utility/exception.hpp"
#include "shell/utility/string.hpp"

#if defined M_system_windows
#define M_declare_native_main_function int wmain (int argc, wchar_t * argv[])
#endif
#if defined M_system_linux || defined M_system_macintosh || defined M_system_android || defined M_system_iphone
#define M_declare_native_main_function int  main (int argc, char    * argv[])
#endif

namespace TwinStar::Shell {

	#pragma region raw native string

	inline auto parse_raw_native_string (
		#if defined M_system_windows
		std::span<wchar_t const * const> const & source
		#endif
		#if defined M_system_linux || defined M_system_macintosh || defined M_system_android || defined M_system_iphone
		std::span<char const * const> const & source
		#endif
	) -> std::vector<std::string> {
		auto destination = std::vector<std::string>{};
		destination.reserve(source.size());
		for (auto & source_element : source) {
			#if defined M_system_windows
			auto source_element_8 = utf16_to_utf8(std::u16string_view{reinterpret_cast<char16_t const *>(source_element)});
			destination.emplace_back(std::move(reinterpret_cast<std::string &>(source_element_8)));
			#endif
			#if defined M_system_linux || defined M_system_macintosh || defined M_system_android || defined M_system_iphone
			destination.emplace_back(source_element);
			#endif
		}
		return destination;
	}

	#pragma endregion

}
