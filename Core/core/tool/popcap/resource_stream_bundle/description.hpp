#pragma once

#include "core/utility/utility.hpp"
#include "core/tool/popcap/resource_stream_bundle/version.hpp"
#include "core/tool/popcap/resource_stream_bundle/common.hpp"

namespace TwinStar::Core::Tool::PopCap::ResourceStreamBundle {

	template <auto version> requires (check_version(version, {}, {}))
	struct Description {

		#pragma region resource

		template <typename = None>
		struct Resource_;

		using Resource = Resource_<>;

		template <typename _> requires (check_version(version, {3}, {}))
		M_record_of_map(
			M_wrap(Resource_<_>),
			M_wrap(
				(Path) path,
				(Integer) type,
				(Map<String, String>) property,
			),
		);

		#pragma endregion

		#pragma region group

		template <typename = None>
		struct Subgroup_;

		using Subgroup = Subgroup_<>;

		template <typename _> requires (check_version(version, {3}, {}))
		M_record_of_map(
			M_wrap(Subgroup_<_>),
			M_wrap(
				(SubgroupCategory) category,
				(Map<String, Resource>) resource,
			),
		);

		// ----------------

		template <typename = None>
		struct Group_;

		using Group = Group_<>;

		template <typename _> requires (check_version(version, {3}, {}))
		M_record_of_map(
			M_wrap(Group_<_>),
			M_wrap(
				(Boolean) composite,
				(Map<String, Subgroup>) subgroup,
			),
		);

		#pragma endregion

		#pragma region package

		template <typename = None>
		struct Package_;

		using Package = Package_<>;

		template <typename _> requires (check_version(version, {3}, {}))
		M_record_of_map(
			M_wrap(Package_<_>),
			M_wrap(
				(Map<String, Group>) group,
			),
		);

		#pragma endregion

	};

}
