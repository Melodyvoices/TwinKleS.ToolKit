#pragma once

#include "core/utility/macro.hpp"
#include "core/utility/builtin.hpp"

#include "core/utility/exception/source_location.hpp"
#include "core/utility/exception/exception.hpp"
#include "core/utility/exception/utility.hpp"

#include "core/utility/trait/base.hpp"
#include "core/utility/trait/category.hpp"
#include "core/utility/trait/template_instance.hpp"
#include "core/utility/trait/object.hpp"
#include "core/utility/trait/builtin.hpp"
#include "core/utility/trait/range.hpp"
#include "core/utility/trait/package/type_package.hpp"
#include "core/utility/trait/package/value_package.hpp"
#include "core/utility/trait/callable.hpp"
#include "core/utility/trait/reflection/string.hpp"
#include "core/utility/trait/reflection/field.hpp"
#include "core/utility/trait/generalization.hpp"
#include "core/utility/trait/trait.hpp"

#include "core/utility/base_wrapper/base.hpp"
#include "core/utility/base_wrapper/boolean.hpp"
#include "core/utility/base_wrapper/number.hpp"
#include "core/utility/base_wrapper/character.hpp"
#include "core/utility/base_wrapper/byte.hpp"
#include "core/utility/base_wrapper/pointer.hpp"
#include "core/utility/base_wrapper/null_pointer.hpp"
#include "core/utility/base_wrapper/wrapper.hpp"

#include "core/utility/miscellaneous/allocator.hpp"

#include "core/utility/null.hpp"

#include "core/utility/container/wrapper/wrapper_view.hpp"
#include "core/utility/container/wrapper/wrapper.hpp"
#include "core/utility/container/optional/optional_view.hpp"
#include "core/utility/container/optional/optional.hpp"
#include "core/utility/container/optional/null_optional.hpp"
#include "core/utility/container/variant/variant.hpp"
#include "core/utility/container/variant/enumerable_variant.hpp"
#include "core/utility/container/any/any.hpp"
#include "core/utility/container/tuple/tuple.hpp"

#include "core/utility/range/range_wrapper.hpp"
#include "core/utility/range/number_iterator.hpp"
#include "core/utility/range/number_range.hpp"
#include "core/utility/range/algorithm.hpp"

#include "core/utility/container/list/list_view.hpp"
#include "core/utility/container/list/list.hpp"
#include "core/utility/container/map/map_view.hpp"
#include "core/utility/container/map/map.hpp"
#include "core/utility/container/array/array.hpp"
#include "core/utility/container/static_array/static_array.hpp"
#include "core/utility/container/stream/stream_method.hpp"
#include "core/utility/container/stream/stream_view.hpp"

#include "core/utility/miscellaneous/record.hpp"
#include "core/utility/miscellaneous/math.hpp"
#include "core/utility/miscellaneous/fourcc.hpp"
#include "core/utility/miscellaneous/number_variant.hpp"
#include "core/utility/miscellaneous/finalizer.hpp"

#include "core/utility/miscellaneous/byte_series/container.hpp"
#include "core/utility/miscellaneous/byte_series/utility.hpp"
#include "core/utility/miscellaneous/byte_series/stream_adapter.hpp"
#include "core/utility/miscellaneous/byte_series/stream.hpp"

#include "core/utility/miscellaneous/character_series/type.hpp"
#include "core/utility/miscellaneous/character_series/container.hpp"
#include "core/utility/miscellaneous/character_series/stream_adapter.hpp"
#include "core/utility/miscellaneous/character_series/stream.hpp"

#include "core/utility/string/basic_string_adapter.hpp"
#include "core/utility/string/basic_string_view.hpp"
#include "core/utility/string/basic_string.hpp"
#include "core/utility/string/basic_static_string.hpp"
#include "core/utility/string/string.hpp"
#include "core/utility/string/encoding.hpp"
#include "core/utility/string/format.hpp"
#include "core/utility/string/parser.hpp"

#include "core/utility/image/size.hpp"
#include "core/utility/image/color.hpp"
#include "core/utility/image/pixel.hpp"
#include "core/utility/image/image_view.hpp"
#include "core/utility/image/image.hpp"
#include "core/utility/image/regular.hpp"

#include "core/utility/data/json/value_adapter.hpp"
#include "core/utility/data/json/value.hpp"

#include "core/utility/data/xml/node.hpp"

#include "core/utility/file_system/path.hpp"
#include "core/utility/file_system/file_system.hpp"

#include "core/utility/process/process.hpp"

#include "core/utility/script/java_script/value_adapter.hpp"
#include "core/utility/script/java_script/value.hpp"
#include "core/utility/script/java_script/utility.hpp"

#include "core/utility/miscellaneous/bitset.hpp"
#include "core/utility/miscellaneous/kv_pair.hpp"
#include "core/utility/miscellaneous/dimension.hpp"
#include "core/utility/miscellaneous/padding_block.hpp"
#include "core/utility/miscellaneous/string_block.hpp"
#include "core/utility/miscellaneous/thread.hpp"

#include "core/utility/support/std.hpp"
#include "core/utility/support/fmt.hpp"
#include "core/utility/support/byte_stream.hpp"
#include "core/utility/support/character_stream.hpp"
#include "core/utility/support/string.hpp"
#include "core/utility/support/json.hpp"
#include "core/utility/support/java_script.hpp"

namespace TwinStar::Core {
}
