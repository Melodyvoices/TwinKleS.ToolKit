#pragma once

#include "core/utility/trait/package/value_package.hpp"
#include "core/utility/trait/callable.hpp"

namespace TwinStar::Core::Trait::Generalization {

	#pragma region utility

	template <typename ... Package, typename Executor> requires
		CategoryConstraint<IsPureInstance<Package ...> && IsPureInstance<Executor>>
		&& ((IsTypePackage<Package> || IsValuePackage<Package>) && ...)
		&& ((Package::size == AsSwitch<sizeof...(Package) == 0_szz, TypePackage<TypePackage<>>, TypePackage<Package ...>>::template Element<1_ixz>::size) && ...)
		&& (IsGenericCallable<Executor>)
	inline constexpr auto each (
		Executor const & executor
	) -> Void {
		auto iterate = [&] <auto element_index> (
			ValuePackage<element_index>
		) {
			executor(
				ValuePackage<element_index>{},
				[] <typename CurrentPackage> (CurrentPackage) {
					if constexpr (IsTypePackage<CurrentPackage>) {
						return TypePackage<typename CurrentPackage::template Element<element_index>>{};
					} else {
						return ValuePackage<CurrentPackage::template element<element_index>>{};
					}
				}(Package{}) ...
			);
		};
		[&] <auto ... element_index> (
			ValuePackage<element_index ...>
		) {
				(iterate(ValuePackage<element_index>{}), ...);
			}(AsValuePackageOfIndex<AsSwitch<sizeof...(Package) == 0_szz, TypePackage<TypePackage<>>, TypePackage<Package ...>>::template Element<1_ixz>::size>{});
		return;
	}

	template <typename ... Package, typename Executor, typename ... Argument> requires
		CategoryConstraint<IsPureInstance<Package ...> && IsPureInstance<Executor> && IsValid<Argument ...>>
		&& ((IsTypePackage<Package> || IsValuePackage<Package>) && ...)
		&& ((Package::size == (sizeof...(Argument))) && ...)
		&& (IsGenericCallable<Executor>)
	inline constexpr auto each_with (
		Executor const & executor,
		Argument && ...  argument
	) -> Void {
		auto iterate = [&] <auto element_index, typename CurrentArgument> (
			ValuePackage<element_index>,
			CurrentArgument && current_argument
		) {
			executor(
				ValuePackage<element_index>{},
				[] <typename CurrentPackage> (CurrentPackage) {
					if constexpr (IsTypePackage<CurrentPackage>) {
						return TypePackage<typename CurrentPackage::template Element<element_index>>{};
					} else {
						return ValuePackage<CurrentPackage::template element<element_index>>{};
					}
				}(Package{}) ...,
				as_forward<CurrentArgument>(current_argument)
			);
		};
		[&] <auto ... element_index> (
			ValuePackage<element_index ...>
		) {
				(iterate(ValuePackage<element_index>{}, as_forward<Argument>(argument)), ...);
			}(AsValuePackageOfIndex<sizeof...(Argument)>{});
		return;
	}

	// ----------------

	template <typename Package, typename Condition, typename Executor> requires
		CategoryConstraint<IsPureInstance<Package> && IsPureInstance<Condition> && IsPureInstance<Executor>>
		&& (IsValuePackage<Package>)
		&& (IsGenericCallable<Executor>)
	inline constexpr auto match (
		Condition const & condition,
		Executor const &  executor
	) -> Void {
		auto has_case = false;
		each<Package>(
			[&] <auto index, auto element> (ValuePackage<index>, ValuePackage<element>) {
				if (element == condition) {
					executor(ValuePackage<index>{}, ValuePackage<element>{});
					has_case = true;
				}
			}
		);
		assert_test(has_case);
		return;
	}

	#pragma endregion

}
