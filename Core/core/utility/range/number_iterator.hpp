#pragma once

#include "core/utility/base_wrapper/wrapper.hpp"

namespace TwinStar::Core {

	#pragma region type

	template <typename TNumber> requires
		CategoryConstraint<IsPureInstance<TNumber>>
		&& (IsNumberWrapper<TNumber>)
	class NumberIterator {

	public:

		using Number = TNumber;

	protected:

		Number m_value;
		Number m_step;

	public:

		#pragma region structor

		constexpr ~NumberIterator (
		) = default;

		// ----------------

		constexpr NumberIterator (
		) = default;

		constexpr NumberIterator (
			NumberIterator const & that
		) = default;

		constexpr NumberIterator (
			NumberIterator && that
		) = default;

		// ----------------

		explicit constexpr NumberIterator (
			Number const & value,
			Number const & step
		) :
			m_value{value},
			m_step{step} {
		}

		#pragma endregion

		#pragma region operator

		constexpr auto operator = (
			NumberIterator const & that
		) -> NumberIterator & = default;

		constexpr auto operator = (
			NumberIterator && that
		) -> NumberIterator & = default;

		// ----------------

		constexpr auto operator * (
		) const -> Number const & {
			return thiz.m_value;
		}

		// ----------------

		constexpr auto operator ++ (
		) -> NumberIterator & {
			thiz.m_value += thiz.m_step;
			return thiz;
		}

		#pragma endregion

	public:

		#pragma region operator

		friend constexpr auto operator == (
			NumberIterator const & thix,
			NumberIterator const & that
		) -> bool = default;

		#pragma endregion

	};

	#pragma endregion

}
