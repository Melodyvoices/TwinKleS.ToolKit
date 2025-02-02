#pragma once

#if defined M_system_windows

#include "shell/common.hpp"
#include "shell/utility/macro.hpp"
#include "shell/utility/string.hpp"
#include "shell/third/system/windows.hpp"

namespace TwinStar::Shell::Windows {

	#pragma region function

	inline auto pick_path (
		bool const & is_directory,
		bool const & is_multiply
	) -> std::vector<std::string> {
		auto state_h = HRESULT{};
		auto result = std::vector<std::string>{};
		CoInitialize(nullptr);
		auto dialog = std::add_pointer_t<IFileOpenDialog>{nullptr};
		state_h = CoCreateInstance(__uuidof(FileOpenDialog), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&dialog));
		assert_test(state_h == S_OK);
		auto option = FILEOPENDIALOGOPTIONS{};
		state_h = dialog->GetOptions(&option);
		assert_test(state_h == S_OK);
		option |= FOS_FORCEFILESYSTEM | FOS_NODEREFERENCELINKS | FOS_DONTADDTORECENT | FOS_FORCESHOWHIDDEN;
		if (is_directory) {
			option |= FOS_PICKFOLDERS;
		}
		if (is_multiply) {
			option |= FOS_ALLOWMULTISELECT;
		}
		state_h = dialog->SetOptions(option);
		assert_test(state_h == S_OK);
		state_h = dialog->Show(nullptr);
		if (state_h != HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
			assert_test(state_h == S_OK);
			auto selection_item_list = std::add_pointer_t<IShellItemArray>{nullptr};
			state_h = dialog->GetResults(&selection_item_list);
			assert_test(state_h == S_OK);
			auto count = DWORD{0};
			state_h = selection_item_list->GetCount(&count);
			assert_test(state_h == S_OK);
			result.reserve(count);
			for (auto index = DWORD{0}; index < count; ++index) {
				auto item = std::add_pointer_t<IShellItem>{nullptr};
				auto display_name = LPWSTR{nullptr};
				state_h = selection_item_list->GetItemAt(index, &item);
				assert_test(state_h == S_OK);
				state_h = item->GetDisplayName(SIGDN_FILESYSPATH, &display_name);
				assert_test(state_h == S_OK);
				auto display_name_8 = utf16_to_utf8(std::u16string_view{reinterpret_cast<char16_t const *>(display_name)});
				result.emplace_back(std::move(reinterpret_cast<std::string &>(display_name_8)));
				CoTaskMemFree(display_name);
				item->Release();
			}
			selection_item_list->Release();
		}
		dialog->Release();
		return result;
	}

	#pragma endregion

}

#endif
