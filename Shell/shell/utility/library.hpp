#pragma once

#include "shell/common.hpp"
#include "shell/utility/exception.hpp"
#include "shell/utility/string.hpp"
#include "shell/third/system/windows.hpp"
#include "shell/third/system/posix.hpp"

namespace TwinStar::Shell::Core {

	#pragma region type

	class LibraryLoader {

	protected:

		void * m_handle;

	public:

		#pragma region structor

		~LibraryLoader (
		) {
			if (thiz.m_handle != nullptr) {
				thiz.close();
			}
		}

		// ----------------

		LibraryLoader (
		) :
			m_handle{} {
		}

		LibraryLoader (
			LibraryLoader const & that
		) = delete;

		LibraryLoader (
			LibraryLoader && that
		) = delete;

		#pragma endregion

		#pragma region operator

		auto operator = (
			LibraryLoader const & that
		) -> LibraryLoader & = delete;

		auto operator = (
			LibraryLoader && that
		) -> LibraryLoader & = delete;

		#pragma endregion

		#pragma region utility

		auto open (
			std::string_view const & path
		) -> void {
			if (thiz.m_handle != nullptr) {
				throw std::runtime_error{"library should close"s};
			}
			#if defined M_system_windows
			auto path_absolute = std::string{path} + "."s;
			auto path_absolute_16 = utf8_to_utf16(reinterpret_cast<std::u8string const &>(path_absolute));
			thiz.m_handle = static_cast<void *>(LoadLibraryW(reinterpret_cast<LPCWSTR>(path_absolute_16.data())));
			#endif
			#if defined M_system_linux || defined M_system_macintosh || defined M_system_android || defined M_system_iphone
			thiz.m_handle = dlopen(path.data(), RTLD_LAZY | RTLD_LOCAL);
			#endif
			if (thiz.m_handle == nullptr) {
				throw std::runtime_error{"library can not open : "s + path.data()};
			}
			return;
		}

		auto close (
		) -> void {
			if (thiz.m_handle == nullptr) {
				throw std::runtime_error{"library should open"s};
			}
			auto state = bool{};
			#if defined M_system_windows
			state = FreeLibrary(static_cast<HMODULE>(thiz.m_handle)) != FALSE;
			#endif
			#if defined M_system_linux || defined M_system_macintosh || defined M_system_android || defined M_system_iphone
			state = dlclose(thiz.m_handle) == 0;
			#endif
			if (state == false) {
				throw std::runtime_error{"library can not close"s};
			}
			thiz.m_handle = nullptr;
			return;
		}

		// ----------------

		template <typename Symbol>
		auto lookup (
			std::string_view const & name
		) -> Symbol {
			if (thiz.m_handle == nullptr) {
				throw std::runtime_error{"library should open"s};
			}
			auto address = std::add_pointer_t<void>{};
			#if defined M_system_windows
			address = reinterpret_cast<void *>(GetProcAddress(static_cast<HMODULE>(thiz.m_handle), name.data()));
			#endif
			#if defined M_system_linux || defined M_system_macintosh || defined M_system_android || defined M_system_iphone
			address = dlsym(thiz.m_handle, name.data());
			#endif
			if (address == nullptr) {
				throw std::runtime_error{"can not get symbol : "s + name.data()};
			}
			return reinterpret_cast<Symbol>(address);
		}

		#pragma endregion

	};

	#pragma endregion

}
