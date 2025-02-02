#pragma once

#include "core/common.hpp"
#include "core/utility/macro.hpp"
#include "core/utility/builtin.hpp"
#include "core/utility/exception/exception.hpp"
#include "core/utility/exception/utility.hpp"
#include <type_traits>
#include <concepts>
#include <tuple>

namespace TwinStar::Core::Trait {

	#pragma region constraint comment

	inline constexpr auto NoneConstraint = true;

	inline constexpr auto AutoConstraint = true;

	inline constexpr auto CustomConstraint = true;

	// ----------------

	template <auto condition = true>
	concept CategoryConstraint =
		CustomConstraint
		&& (condition)
		;

	#pragma endregion

	#pragma region utility

	template <typename>
	inline constexpr auto k_static_assert_fail = bool{false};

	// ----------------

	template <typename It> requires
		AutoConstraint
	inline constexpr auto declare (
	) -> It {
		throw ImpossibleException{};
	}

	#pragma endregion

}
