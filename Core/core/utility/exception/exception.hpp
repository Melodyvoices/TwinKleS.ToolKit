#pragma once

#include "core/utility/exception/source_location.hpp"
#include "core/third/fmt.hpp"
#include <string>
#include <vector>

namespace TwinStar::Core {

	#pragma region type

	class Exception {

	protected:

		std::string              m_title;
		std::vector<std::string> m_description;
		std::source_location     m_location;

	public:

		#pragma region structor

		~Exception (
		) = default;

		// ----------------

		Exception (
		) = default;

		Exception (
			Exception const & that
		) = default;

		Exception (
			Exception && that
		) = default;

		// ----------------

		explicit Exception (
			std::string const &              title,
			std::vector<std::string> const & description,
			std::source_location const &     location = M_current_source_location
		) :
			m_title{title},
			m_description{description},
			m_location{location} {
		}

		#pragma endregion

		#pragma region operator

		auto operator = (
			Exception const & that
		) -> Exception & = default;

		auto operator = (
			Exception && that
		) -> Exception & = default;

		#pragma endregion

		#pragma region what

		auto what (
		) const -> std::string {
			auto message = std::string{};
			{
				message += "# ";
				message += thiz.m_title;
			}
			for (auto & description : thiz.m_description) {
				message += "\n";
				message += "$ ";
				message += description;
			}
			{
				message += "\n";
				message += "@ ";
				message += thiz.m_location.file_name()[0] == '\0'
					? ("?")
					: (fmt::format("{}:{} {}", parse_source_location_file_path(thiz.m_location), thiz.m_location.line(), thiz.m_location.function_name()));
			}
			return message;
		}

		#pragma endregion

	};

	#pragma endregion

}
