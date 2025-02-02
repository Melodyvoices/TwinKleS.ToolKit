#pragma once

#include "core/utility/container/wrapper/wrapper.hpp"
#include "core/utility/null.hpp"
#include "core/utility/miscellaneous/byte_series/container.hpp"
#include "core/utility/string/string.hpp"
#include "core/utility/data/json/value.hpp"
#include "core/utility/script/java_script/value_adapter.hpp"
#include "core/third/quickjs.hpp"

namespace TwinStar::Core::JavaScript {

	#pragma region namespace alias

	namespace quickjs = Third::quickjs;

	#pragma endregion

	#pragma region declaration

	class Runtime;

	class Context;

	class Value;

	#pragma endregion

	#pragma region type

	class ExecutionException :
		public Exception {

	public:

		explicit ExecutionException (
			Value & exception
		);

	};

	// ----------------

	using ClassFinalizer = AsGlobalFunction<Void, Runtime &, Value &>;

	using NativeFunction = AsGlobalFunction<Void, Context &, Value &, List<Value> &, Value &>;

	// ----------------

	class Runtime {

	protected:

		Pointer<quickjs::JSRuntime> m_runtime;
		Boolean                     m_is_holder;

	protected:

		#pragma region structor

		explicit Runtime (
			ZPointer<quickjs::JSRuntime> const & raw_value,
			Boolean const &                      is_holder
		) :
			m_runtime{raw_value},
			m_is_holder{is_holder} {
		}

		#pragma endregion

	public:

		#pragma region create

		static auto new_reference (
			ZPointer<quickjs::JSRuntime> const & runtime
		) -> Runtime {
			return Runtime{runtime, k_false};
		}

		static auto new_instance (
		) -> Runtime {
			return Runtime{quickjs::JS_NewRuntime(), k_true};
		}

		#pragma endregion

	public:

		#pragma region structor

		~Runtime (
		) {
			if (thiz.m_is_holder) {
				quickjs::JS_FreeRuntime(thiz._runtime());
			}
		}

		// ----------------

		Runtime (
		) = delete;

		Runtime (
			Runtime const & that
		) = delete;

		Runtime (
			Runtime && that
		) :
			m_runtime{},
			m_is_holder{} {
			thiz = as_moveable(that);
		}

		#pragma endregion

		#pragma region operator

		auto operator = (
			Runtime const & that
		) -> Runtime & = delete;

		auto operator = (
			Runtime && that
		) -> Runtime & {
			thiz.m_runtime = that.m_runtime;
			thiz.m_is_holder = that.m_is_holder;
			that.m_runtime = k_null_pointer;
			that.m_is_holder = k_false;
			return thiz;
		}

		#pragma endregion

		#pragma region raw

		auto _runtime (
		) -> ZPointer<quickjs::JSRuntime> {
			return thiz.m_runtime.value;
		}

		#pragma endregion

		#pragma region context

		auto new_context (
		) -> Context;

		#pragma endregion

		#pragma region job

		auto has_pending_job (
		) -> Boolean;

		auto execute_pending_job (
			Context & context
		) -> Void;

		#pragma endregion

		#pragma region promise

		auto disable_promise_rejection_tracker (
		) -> Void;

		auto enable_promise_rejection_tracker (
		) -> Void;

		#pragma endregion

		#pragma region module

		auto disable_module_loader (
		) -> Void;

		auto enable_module_loader (
			Optional<Path> & home
		) -> Void;

		#pragma endregion

		#pragma region class

		template <auto finalizer> requires
			CategoryConstraint<>
			&& (IsSameV<finalizer, ClassFinalizer>)
		auto register_class (
			Integer &      id,
			String const & name
		) -> Void;

		#pragma endregion

	};

	class Context {

	protected:

		Pointer<quickjs::JSContext> m_context;
		Boolean                     m_is_holder;

	protected:

		#pragma region structor

		explicit Context (
			ZPointer<quickjs::JSContext> const & raw_value,
			Boolean const &                      is_holder
		) :
			m_context{raw_value},
			m_is_holder{is_holder} {
		}

		#pragma endregion

	public:

		#pragma region create

		static auto new_reference (
			ZPointer<quickjs::JSContext> const & context
		) -> Context {
			return Context{context, k_false};
		}

		static auto new_instance (
			ZPointer<quickjs::JSRuntime> const & runtime
		) -> Context {
			return Context{quickjs::JS_NewContext(runtime), k_true};
		}

		#pragma endregion

	public:

		#pragma region structor

		~Context (
		) {
			if (thiz.m_is_holder) {
				quickjs::JS_FreeContext(thiz._context());
			}
		}

		// ----------------

		Context (
		) = delete;

		Context (
			Context const & that
		) = delete;

		Context (
			Context && that
		) :
			m_context{},
			m_is_holder{} {
			thiz = as_moveable(that);
		}

		#pragma endregion

		#pragma region operator

		auto operator = (
			Context const & that
		) -> Context & = delete;

		auto operator = (
			Context && that
		) -> Context & {
			thiz.m_context = that.m_context;
			thiz.m_is_holder = that.m_is_holder;
			that.m_context = k_null_pointer;
			that.m_is_holder = k_false;
			return thiz;
		}

		#pragma endregion

		#pragma region raw

		auto _context (
		) -> ZPointer<quickjs::JSContext> {
			return thiz.m_context.value;
		}

		#pragma endregion

		#pragma region runtime

		auto runtime (
		) -> Runtime {
			return Runtime::new_reference(quickjs::JS_GetRuntime(thiz._context()));
		}

		#pragma endregion

		#pragma region value

		auto new_value (
		) -> Value;

		template <typename ValueObject> requires
			CategoryConstraint<IsValid<ValueObject>>
		auto new_value (
			ValueObject && value
		) -> Value;

		#pragma endregion

		#pragma region evaluate

		auto evaluate (
			CStringView const & script,
			String const &      name,
			Boolean const &     is_module
		) -> Value;

		#pragma endregion

		#pragma region global

		auto global_object (
		) -> Value;

		#pragma endregion

		#pragma region exception

		auto throw_exception (
			Value && value
		) -> Void;

		auto catch_exception (
		) -> Value;

		#pragma endregion

		#pragma region class

		auto get_class_proto (
			Integer const & id
		) -> Value;

		auto set_class_proto (
			Integer const & id,
			Value &&        value
		) -> Void;

		#pragma endregion

	};

	class Value {

	protected:

		Optional<ZPointer<quickjs::JSContext>> m_context;
		quickjs::JSValue                       m_value;

	protected:

		#pragma region structor

		explicit Value (
			quickjs::JSValue const & value
		) :
			m_context{},
			m_value{value} {
		}

		explicit Value (
			ZPointer<quickjs::JSContext> const & context,
			quickjs::JSValue const &             value
		) :
			m_context{},
			m_value{value} {
			thiz.m_context.set(context);
		}

		#pragma endregion

	public:

		#pragma region create

		static auto new_orphan (
			quickjs::JSValue const & value
		) -> Value {
			return Value{value};
		}

		static auto new_reference (
			ZPointer<quickjs::JSContext> const & context,
			quickjs::JSValue const &             value
		) -> Value {
			return Value{context, quickjs::JS_DupValue(context, value)};
		}

		static auto new_instance (
			ZPointer<quickjs::JSContext> const & context,
			quickjs::JSValue const &             value = quickjs::JS_UNINITIALIZED_
		) -> Value {
			return Value{context, value};
		}

		// ----------------

		static auto new_instance_of (
			ZPointer<quickjs::JSContext> const & context
		) -> Value {
			auto result = new_instance(context);
			result.set_undefined();
			return result;
		}

		template <typename That, typename ... Option> requires
			CategoryConstraint<IsValid<That> && IsValid<Option ...>>
		static auto new_instance_of (
			ZPointer<quickjs::JSContext> const & context,
			That &&                              that,
			Option && ...                        option
		) -> Value {
			auto result = new_instance(context);
			result.from(as_forward<That>(that), as_forward<Option>(option) ...);
			return result;
		}

		#pragma endregion

	public:

		#pragma region structor

		~Value (
		) {
			thiz._reset_value();
		}

		// ----------------

		Value (
		) :
			Value{quickjs::JS_UNINITIALIZED_} {
		}

		Value (
			Value const & that
		) :
			Value{} {
			thiz.m_context = that.m_context;
			thiz.m_value = !that.m_context.has() ? (as_variable(that)._value()) : (quickjs::JS_DupValue(as_variable(that)._context(), as_variable(that)._value()));
		}

		Value (
			Value && that
		) :
			Value{} {
			thiz.m_context = that.m_context;
			thiz.m_value = !that.m_context.has() ? (as_variable(that)._value()) : (that._release_value());
		}

		#pragma endregion

		#pragma region operator

		auto operator = (
			Value const & that
		) -> Value & {
			thiz._reset_value();
			thiz.m_context = that.m_context;
			thiz.m_value = !that.m_context.has() ? (as_variable(that)._value()) : (quickjs::JS_DupValue(as_variable(that)._context(), as_variable(that)._value()));
			return thiz;
		}

		auto operator = (
			Value && that
		) -> Value & {
			thiz._reset_value();
			thiz.m_context = that.m_context;
			thiz.m_value = !that.m_context.has() ? (as_variable(that)._value()) : (that._release_value());
			return thiz;
		}

		#pragma endregion

		#pragma region raw

		auto _context (
		) -> ZPointer<quickjs::JSContext> {
			return thiz.m_context.get();
		}

		auto _value (
		) -> quickjs::JSValue {
			return thiz.m_value;
		}

		#pragma endregion

		#pragma region raw bind

		auto _unbind_context (
		) -> Void {
			thiz.m_context.reset();
			return;
		}

		auto _unbind_value (
		) -> Void {
			thiz.m_value = quickjs::JS_UNINITIALIZED_;
			return;
		}

		auto _unbind (
		) -> Void {
			thiz._unbind_value();
			thiz._unbind_context();
			return;
		}

		auto _rebind_value (
			quickjs::JSValue const & new_value
		) -> Void {
			if (thiz.m_context.has()) {
				quickjs::JS_FreeValue(thiz._context(), thiz._value());
			}
			thiz.m_value = new_value;
			return;
		}

		// ----------------

		auto _reset_value (
		) -> Void {
			return thiz._rebind_value(quickjs::JS_UNINITIALIZED_);
		}

		auto _release_value (
		) -> quickjs::JSValue {
			auto result = thiz.m_value;
			thiz._unbind_value();
			return result;
		}

		#pragma endregion

		#pragma region context

		auto context (
		) -> Context {
			return Context::new_reference(thiz._context());
		}

		#pragma endregion

		#pragma region value

		auto new_value (
		) -> Value {
			return thiz.new_instance(thiz._context());
		}

		template <typename ... Argument> requires
			CategoryConstraint<IsValid<Argument ...>>
		auto new_value (
			Argument && ... argument
		) -> Value {
			return thiz.new_instance_of(thiz._context(), as_forward<Argument>(argument) ...);
		}

		#pragma endregion

		#pragma region check uninitialized

		auto is_uninitialized (
		) -> Boolean {
			return mbw<Boolean>(quickjs::JS_IsUninitialized(thiz._value()));
		}

		auto set_uninitialized (
		) -> Void {
			return thiz._rebind_value(quickjs::JS_UNINITIALIZED_);
		}

		#pragma endregion

		#pragma region is

		auto is_undefined (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsUndefined(thiz._value()));
		}

		auto is_null (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsNull(thiz._value()));
		}

		auto is_boolean (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsBool(thiz._value()));
		}

		auto is_bigint (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsBigInt(thiz._context(), thiz._value()));
		}

		auto is_number (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsNumber(thiz._value()));
		}

		auto is_string (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsString(thiz._value()));
		}

		auto is_object (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsObject(thiz._value()));
		}

		// ----------------

		auto is_exception (
		) -> Boolean {
			assert_test(thiz.m_context);
			return mbw<Boolean>(quickjs::JS_IsException(thiz._value()));
		}

		#pragma endregion

		#pragma region get

		auto get_undefined (
		) -> Void {
			assert_test(thiz.is_undefined());
			return;
		}

		auto get_null (
		) -> Null {
			assert_test(thiz.is_null());
			return k_null;
		}

		auto get_boolean (
		) -> Boolean {
			assert_test(thiz.is_boolean());
			auto raw_value = quickjs::JS_ToBool(thiz._context(), thiz._value());
			return mbw<Boolean>(raw_value);
		}

		auto get_bigint (
		) -> Integer {
			assert_test(thiz.is_bigint());
			auto raw_value = int64_t{};
			quickjs::JS_ToBigInt64(thiz._context(), &raw_value, thiz._value());
			return mbw<Integer>(raw_value);
		}

		auto get_number (
		) -> Floater {
			assert_test(thiz.is_number());
			auto raw_value = double{};
			quickjs::JS_ToFloat64(thiz._context(), &raw_value, thiz._value());
			return mbw<Floater>(raw_value);
		}

		auto get_string (
		) -> String {
			assert_test(thiz.is_string());
			auto raw_length = size_t{};
			auto raw_value = quickjs::JS_ToCStringLen(thiz._context(), &raw_length, thiz._value());
			auto value = make_string(raw_value, raw_length);
			quickjs::JS_FreeCString(thiz._context(), raw_value);
			return value;
		}

		// ----------------

		auto get_object_of_array_buffer (
		) -> VByteListView {
			auto size = size_t{};
			auto data = quickjs::JS_GetArrayBuffer(thiz._context(), &size, thiz._value());
			assert_test(data);
			return VByteListView{cast_pointer<Byte>(make_pointer(data)), mbw<Size>(size)};
		}

		#pragma endregion

		#pragma region set

		auto set_undefined (
		) -> Void {
			return thiz._rebind_value(quickjs::JS_UNDEFINED_);
		}

		auto set_null (
			Null const & value
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NULL_);
		}

		auto set_boolean (
			Boolean const & value
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewBool(thiz._context(), static_cast<int>(value.value)));
		}

		auto set_bigint (
			Integer const & value
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewBigInt64(thiz._context(), value.value));
		}

		auto set_number (
			Floater const & value
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewFloat64(thiz._context(), value.value));
		}

		auto set_string (
			String const & value
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewStringLen(thiz._context(), cast_pointer<char>(value.begin()).value, value.size().value));
		}

		// TODO : sv remove
		auto set_string (
			CStringView const & value
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewStringLen(thiz._context(), cast_pointer<char>(value.begin()).value, value.size().value));
		}

		// ----------------

		auto set_object_of_object (
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewObject(thiz._context()));
		}

		auto set_object_of_array (
		) -> Void {
			return thiz._rebind_value(quickjs::JS_NewArray(thiz._context()));
		}

		auto set_object_of_array_buffer (
			CByteListView const & data
		) -> Void {
			return thiz._rebind_value(
				quickjs::JS_NewArrayBufferCopy(
					thiz._context(),
					cast_pointer<uint8_t>(data.begin()).value,
					data.size().value
				)
			);
		}

		auto set_object_of_array_buffer (
			VByteListView const & data,
			Boolean const &       is_holder
		) -> Void {
			return thiz._rebind_value(
				quickjs::JS_NewArrayBuffer(
					thiz._context(),
					cast_pointer<uint8_t>(data.begin()).value,
					data.size().value,
					!is_holder
					? nullptr
					: [] (quickjs::JSRuntime * rt, void * opaque, void * ptr) -> void {
						delete[] static_cast<uint8_t *>(ptr);
						return;
					},
					nullptr,
					false
				)
			);
		}

		template <auto function> requires
			CategoryConstraint<>
			&& (IsSameV<function, NativeFunction>)
		auto set_object_of_native_function (
			String const &  name,
			Boolean const & is_constructor
		) -> Void;

		#pragma endregion

		#pragma region object proto

		auto get_object_proto (
		) -> Value {
			assert_test(thiz.is_object());
			return thiz.new_instance(thiz._context(), quickjs::JS_GetPrototype(thiz._context(), thiz._value()));
		}

		auto set_object_proto (
			Value && value
		) -> Void {
			assert_test(thiz.is_object());
			quickjs::JS_SetPrototype(thiz._context(), thiz._value(), value._release_value());
			return;
		}

		#pragma endregion

		#pragma region object class name

		auto get_object_class_name (
		) -> String {
			assert_test(thiz.is_object());
			return thiz.get_object_proto().get_object_property("constructor"_sv).get_object_property("name"_sv).get_string();
		}

		// ----------------

		auto is_object_of_class (
			String const & name
		) -> Boolean {
			return thiz.is_object() && thiz.get_object_class_name() == name;
		}

		// TODO : sv remove
		auto is_object_of_class (
			CStringView const & name
		) -> Boolean {
			return thiz.is_object() && thiz.get_object_class_name() == name;
		}

		// ----------------

		auto is_object_of_object (
		) -> Boolean {
			return thiz.is_object_of_class("Object"_sv);
		}

		auto is_object_of_array (
		) -> Boolean {
			return thiz.is_object_of_class("Array"_sv);
		}

		#pragma endregion

		#pragma region object property

		auto define_object_property (
			String const & name,
			Value &&       value
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_DefinePropertyValue(thiz._context(), thiz._value(), atom, value._release_value(), quickjs::JS_PROP_C_W_E_);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		auto define_object_property (
			Size const & index,
			Value &&     value
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomUInt32(thiz._context(), static_cast<uint32_t>(index.value));
			auto result = quickjs::JS_DefinePropertyValue(thiz._context(), thiz._value(), atom, value._release_value(), quickjs::JS_PROP_C_W_E_);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		// ----------------

		auto define_object_property (
			String const & name,
			Value &&       getter,
			Value &&       setter
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_DefinePropertyGetSet(thiz._context(), thiz._value(), atom, getter._release_value(), setter._release_value(), quickjs::JS_PROP_C_W_E_);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		auto define_object_property (
			Size const & index,
			Value &&     getter,
			Value &&     setter
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomUInt32(thiz._context(), static_cast<uint32_t>(index.value));
			auto result = quickjs::JS_DefinePropertyGetSet(thiz._context(), thiz._value(), atom, getter._release_value(), setter._release_value(), quickjs::JS_PROP_C_W_E_);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		// ----------------

		auto delete_object_property (
			String const & name
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_DeleteProperty(thiz._context(), thiz._value(), atom, quickjs::JS_PROP_THROW_);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		auto delete_object_property (
			Size const & index
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomUInt32(thiz._context(), static_cast<uint32_t>(index.value));
			auto result = quickjs::JS_DeleteProperty(thiz._context(), thiz._value(), atom, quickjs::JS_PROP_THROW_);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		// ----------------

		auto has_object_property (
			String const & name
		) -> Boolean {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_HasProperty(thiz._context(), thiz._value(), atom);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			return mbw<Boolean>(result == 1);
		}

		auto has_object_property (
			Size const & index
		) -> Boolean {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomUInt32(thiz._context(), static_cast<uint32_t>(index.value));
			auto result = quickjs::JS_HasProperty(thiz._context(), thiz._value(), atom);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			return mbw<Boolean>(result == 1);
		}

		// ----------------

		// TODO : sv remove
		auto get_object_property (
			CStringView const & name
		) -> Value {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_GetProperty(thiz._context(), thiz._value(), atom);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			return thiz.new_instance(thiz._context(), result);
		}

		auto get_object_property (
			String const & name
		) -> Value {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_GetProperty(thiz._context(), thiz._value(), atom);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			return thiz.new_instance(thiz._context(), result);
		}

		auto get_object_property (
			Size const & index
		) -> Value {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomUInt32(thiz._context(), static_cast<uint32_t>(index.value));
			auto result = quickjs::JS_GetProperty(thiz._context(), thiz._value(), atom);
			quickjs::JS_FreeAtom(thiz._context(), atom);
			return thiz.new_instance(thiz._context(), result);
		}

		// ----------------

		// TODO : sv remove
		auto set_object_property (
			CStringView const & name,
			Value &&            value
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_SetProperty(thiz._context(), thiz._value(), atom, value._release_value());
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		auto set_object_property (
			String const & name,
			Value &&       value
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomLen(thiz._context(), cast_pointer<char>(name.begin()).value, name.size().value);
			auto result = quickjs::JS_SetProperty(thiz._context(), thiz._value(), atom, value._release_value());
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		auto set_object_property (
			Size const & index,
			Value &&     value
		) -> Void {
			assert_test(thiz.is_object());
			auto atom = quickjs::JS_NewAtomUInt32(thiz._context(), static_cast<uint32_t>(index.value));
			auto result = quickjs::JS_SetProperty(thiz._context(), thiz._value(), atom, value._release_value());
			quickjs::JS_FreeAtom(thiz._context(), atom);
			assert_test(result != -1);
			assert_test(result == 1);
			return;
		}

		#pragma endregion

		#pragma region object own property

		auto collect_object_own_property (
		) -> Map<String, Value> {
			assert_test(thiz.is_object());
			auto property_enum = ZPointer<quickjs::JSPropertyEnum>{};
			auto property_count = uint32_t{};
			quickjs::JS_GetOwnPropertyNames(thiz._context(), &property_enum, &property_count, thiz._value(), quickjs::JS_GPN_STRING_MASK_);
			auto result = Map<String, Value>{mbw<Size>(property_count)};
			for (auto & element : make_range_n(make_pointer(property_enum), mbw<Size>(property_count))) {
				auto name = quickjs::JS_AtomToCString(thiz._context(), element.atom);
				result.append(make_string(name), thiz.new_instance(thiz._context(), quickjs::JS_GetProperty(thiz._context(), thiz._value(), element.atom)));
				quickjs::JS_FreeCString(thiz._context(), name);
			}
			quickjs::js_free_prop_enum(thiz._context(), property_enum, property_count);
			return result;
		}

		// ----------------

		auto collect_object_own_property_of_object (
		) -> Map<String, Value> {
			assert_test(thiz.is_object_of_object());
			auto map = thiz.collect_object_own_property();
			return map;
		}

		auto collect_object_own_property_of_array (
		) -> List<Value> {
			assert_test(thiz.is_object_of_array());
			auto map = thiz.collect_object_own_property();
			auto list = List<Value>{};
			auto length = cbw<Size>(map["length"_sv].to_of<Floater>());
			list.allocate_full(length);
			for (auto & index : SizeRange{length}) {
				assert_test(cbw<Size>(map.at(index).key.to_of<Integer>()) == index);
				list[index] = as_moveable(map.at(index).value);
			}
			return list;
		}

		#pragma endregion

		#pragma region function call

		auto call (
			List<Value> const & argument
		) -> Value {
			assert_test(thiz.is_object());
			auto argument_value = Array<quickjs::JSValue>{};
			argument_value.assign(
				argument,
				[] (auto & element) -> auto {
					return as_variable(element)._value();
				}
			);
			auto result = thiz.new_instance(thiz._context(), quickjs::JS_Call(thiz._context(), thiz._value(), quickjs::JS_UNDEFINED_, static_cast<int>(argument.size().value), argument_value.begin().value));
			if (result.is_exception()) {
				throw ExecutionException{as_lvalue(thiz.context().catch_exception())};
			}
			return result;
		}

		auto call_method (
			String const &      name,
			List<Value> const & argument
		) -> Value {
			assert_test(thiz.is_object());
			auto function = thiz.get_object_property(name);
			auto argument_value = Array<quickjs::JSValue>{};
			argument_value.assign(
				argument,
				[] (auto & element) -> auto {
					return as_variable(element)._value();
				}
			);
			auto result = thiz.new_instance(thiz._context(), quickjs::JS_Call(thiz._context(), function._value(), thiz._value(), static_cast<int>(argument.size().value), argument_value.begin().value));
			if (result.is_exception()) {
				throw ExecutionException{as_lvalue(thiz.context().catch_exception())};
			}
			return result;
		}

		#pragma endregion

		#pragma region from & to by adapter

		template <typename That, typename ... Option> requires
			CategoryConstraint<IsValid<That> && IsValid<Option ...>>
		auto from (
			That &&       that,
			Option && ... option
		) -> Void {
			assert_test(thiz.m_context);
			thiz.set_uninitialized();
			ValueAdapter<AsPure<That>>::from(thiz, as_forward<That>(that), as_forward<Option>(option) ...);
			return;
		}

		template <typename That, typename ... Option> requires
			CategoryConstraint<IsValid<That> && IsValid<Option ...>>
		auto to (
			That &&       that,
			Option && ... option
		) -> That && {
			assert_test(thiz.m_context);
			ValueAdapter<AsPure<That>>::to(thiz, as_forward<That>(that), as_forward<Option>(option) ...);
			return as_forward<That>(that);
		}

		// ----------------

		template <typename That, typename ... Option> requires
			CategoryConstraint<IsPureInstance<That> && IsValid<Option ...>>
		auto to_of (
			Option && ... option
		) -> That {
			auto that = That{};
			thiz.to(that, as_forward<Option>(option) ...);
			return that;
		}

		#pragma endregion

	};

	#pragma endregion

	#pragma region detail

	namespace Detail {

		inline auto custom_promise_rejection_tracker (
			quickjs::JSContext * ctx,
			quickjs::JSValue     promise,
			quickjs::JSValue     reason,
			quickjs::BOOL        is_handled,
			void *               opaque
		) -> void {
			// TODO
			return;
		}

		// ----------------

		inline auto custom_module_loader (
			quickjs::JSContext * ctx,
			char const *         module_name,
			void *               opaque
		) -> quickjs::JSModuleDef * {
			auto path = Path{};
			if (module_name[0] == '~') {
				auto & home = *static_cast<Optional<Path> *>(opaque);
				if (!home.has()) {
					quickjs::JS_ThrowReferenceError(ctx, "could not load module '%s': home path not set", module_name);
					return nullptr;
				}
				if (module_name[1] != '/') {
					quickjs::JS_ThrowReferenceError(ctx, "could not load module '%s': path invalid", module_name);
					return nullptr;
				}
				path = home.get() / Path{make_string(module_name + 2)};
			} else {
				path = Path{make_string(module_name)};
			}
			if (!FileSystem::exist_file(path)) {
				quickjs::JS_ThrowReferenceError(ctx, "could not load module '%s': file not found", module_name);
				return nullptr;
			}
			auto data = FileSystem::read_file(path);
			data.expand(1_sz);
			data.last() = k_null_byte;
			auto value = quickjs::JS_Eval(
				ctx,
				cast_pointer<char>(data.begin()).value,
				data.size().value - 1,
				module_name,
				quickjs::JS_EVAL_FLAG_STRICT_ | quickjs::JS_EVAL_TYPE_MODULE_ | quickjs::JS_EVAL_FLAG_COMPILE_ONLY_
			);
			if (quickjs::JS_IsException(value)) {
				return nullptr;
			}
			auto definition = static_cast<quickjs::JSModuleDef *>(JS_VALUE_GET_PTR(value));
			quickjs::JS_FreeValue(ctx, value);
			auto meta = quickjs::JS_GetImportMeta(ctx, definition);
			if (quickjs::JS_IsException(meta)) {
				quickjs::JS_ThrowReferenceError(ctx, "could not load module '%s': could not meta", module_name);
				return nullptr;
			}
			auto meta_name_atom = quickjs::JS_NewAtomLen(ctx, "name", std::strlen("name"));
			quickjs::JS_DefinePropertyValue(ctx, meta, meta_name_atom, quickjs::JS_NewStringLen(ctx, module_name, std::strlen(module_name)), quickjs::JS_PROP_C_W_E_);
			quickjs::JS_FreeAtom(ctx, meta_name_atom);
			quickjs::JS_FreeValue(ctx, meta);
			return definition;
		}

		// ----------------

		template <auto finalizer> requires
			CategoryConstraint<>
			&& (IsSameV<finalizer, ClassFinalizer>)
		inline auto proxy_class_finalizer (
			quickjs::JSRuntime * rt,
			quickjs::JSValue     obj
		) -> void {
			auto runtime = Runtime::new_reference(rt);
			auto object = Value::new_orphan(obj);
			finalizer(runtime, object);
			return;
		}

		// ----------------

		template <auto function> requires
			CategoryConstraint<>
			&& (IsSameV<function, NativeFunction>)
		inline auto proxy_native_function (
			quickjs::JSContext * ctx,
			quickjs::JSValue     this_val,
			int                  argc,
			quickjs::JSValue *   argv
		) -> quickjs::JSValue {
			auto result_value = quickjs::JSValue{};
			#if defined M_build_release
			try {
			#endif
				auto context = Context::new_reference(ctx);
				auto object = Value::new_reference(ctx, this_val);
				auto argument = List<Value>{};
				argument.allocate_full(mbw<Size>(argc));
				for (auto index = 0; index < argc; ++index) {
					argument[mbw<Size>(index)] = Value::new_reference(ctx, argv[index]);
				}
				auto result = Value::new_instance(ctx);
				function(context, object, argument, result);
				result_value = result._release_value();
			#if defined M_build_release
			} catch (...) {
				auto exception = parse_current_exception();
				auto message_std = exception.what();
				auto message = make_string_view(message_std);
				auto context_wrapper = Context::new_reference(ctx);
				context_wrapper.throw_exception(
					context_wrapper.evaluate(
						R"((message) => {
							let error = new Error();
							error.name = 'NativeError';
							error.message = message;
							error.stack = error.stack.substring(error.stack.indexOf('\n') + 1);
							return error;
						})"_sv,
						"<unnamed>"_s,
						k_false
					).call(
						make_list<Value>(
							Value::new_instance_of(ctx, message)
						)
					)
				);
				result_value = quickjs::JS_EXCEPTION_;
			}
			#endif
			return result_value;
		}

	}

	#pragma endregion

	#pragma region type method implement

	inline ExecutionException::ExecutionException (
		Value & exception
	) :
		Exception{"JavaScript.Execution", {}, std::source_location{}} {
		auto exception_message = exception.context().evaluate(
			R"((error) => {
				function split_error_stack(
					string,
				) {
					let list;
					if (string === undefined) {
						list = [`@ ?`];
					} else {
						list = string.split('\n').slice(0, -1).map((e) => {
							let result;
							let regexp_result = /    at (.*) \((.*)\)/.exec(e);
							if (regexp_result !== null) {
								result = `@ ${regexp_result[2] === 'native' ? ('<native>:?') : (regexp_result[2])} ${regexp_result[1]}`;
							} else {
								result = '@ ?';
							}
							return result;
						});
					}
					return list;
				}
				function parse_error_message(
					error,
				) {
					let title = '';
					let description = [];
					if (error instanceof Error) {
						if (error.name === 'NativeError') {
							title = `${error.name}`;
							description.push(...error.message.split('\n'));
						} else {
							title = `${error.name}: ${error.message}`;
						}
						description.push(...split_error_stack(error.stack));
					} else {
						title = `${error}`;
					}
					return [title, description];
				}
				let message = parse_error_message(error);
				return [message[0], ...message[1]];
			})"_sv,
			"<unnamed>"_s,
			k_false
		).call(
			make_list<Value>(
				exception
			)
		);
		thiz.m_description.emplace_back(mss(catenate_string<String>(exception_message.to_of<List<String>>(), '\n'_c)));
	}

	// ----------------

	inline auto Runtime::new_context (
	) -> Context {
		return Context::new_instance(thiz._runtime());
	}

	// ----------------

	inline auto Runtime::has_pending_job (
	) -> Boolean {
		return mbw<Boolean>(quickjs::JS_IsJobPending(thiz._runtime()));
	}

	inline auto Runtime::execute_pending_job (
		Context & context
	) -> Void {
		auto context_pointer = ZPointer<quickjs::JSContext>{};
		auto count = quickjs::JS_ExecutePendingJob(thiz._runtime(), &context_pointer);
		assert_test(count != 0);
		context = Context::new_reference(context_pointer);
		if (count < 0) {
			throw ExecutionException{as_lvalue(Value::new_instance(context_pointer, quickjs::JS_GetException(context_pointer)))};
		}
		return;
	}

	// ----------------

	inline auto Runtime::disable_promise_rejection_tracker (
	) -> Void {
		quickjs::JS_SetHostPromiseRejectionTracker(
			thiz._runtime(),
			nullptr,
			nullptr
		);
		return;
	}

	inline auto Runtime::enable_promise_rejection_tracker (
	) -> Void {
		quickjs::JS_SetHostPromiseRejectionTracker(
			thiz._runtime(),
			&Detail::custom_promise_rejection_tracker,
			nullptr
		);
		return;
	}

	// ----------------

	inline auto Runtime::disable_module_loader (
	) -> Void {
		quickjs::JS_SetModuleLoaderFunc(
			thiz._runtime(),
			nullptr,
			nullptr,
			nullptr
		);
		return;
	}

	inline auto Runtime::enable_module_loader (
		Optional<Path> & home
	) -> Void {
		quickjs::JS_SetModuleLoaderFunc(
			thiz._runtime(),
			nullptr,
			&Detail::custom_module_loader,
			&home
		);
		return;
	}

	// ----------------

	template <auto finalizer> requires
		CategoryConstraint<>
		&& (IsSameV<finalizer, ClassFinalizer>)
	inline auto Runtime::register_class (
		Integer &      id,
		String const & name
	) -> Void {
		auto name_null_terminated = make_null_terminated_string(name);
		auto definition = quickjs::JSClassDef{
			.class_name = cast_pointer<char>(name_null_terminated.begin()).value,
			.finalizer = &Detail::proxy_class_finalizer<finalizer>,
			.gc_mark = nullptr,
			.call = nullptr,
			.exotic = nullptr,
		};
		auto id_value = static_cast<quickjs::JSClassID>(id.value);
		quickjs::JS_NewClassID(&id_value);
		id.value = static_cast<ZInteger>(id_value);
		auto result = quickjs::JS_NewClass(thiz._runtime(), id_value, &definition);
		assert_test(result == 0);
		return;
	}

	// ----------------

	inline auto Context::new_value (
	) -> Value {
		return Value::new_instance_of(thiz._context());
	}

	template <typename ValueObject> requires
		CategoryConstraint<IsValid<ValueObject>>
	inline auto Context::new_value (
		ValueObject && value
	) -> Value {
		return Value::new_instance_of(thiz._context(), as_forward<ValueObject>(value));
	}

	// ----------------

	inline auto Context::evaluate (
		CStringView const & script,
		String const &      name,
		Boolean const &     is_module
	) -> Value {
		auto result = quickjs::JS_Eval(
			thiz._context(),
			cast_pointer<char>(make_null_terminated_string(script).begin()).value,
			script.size().value,
			cast_pointer<char>(make_null_terminated_string(name).begin()).value,
			quickjs::JS_EVAL_FLAG_STRICT_ | (!is_module ? (quickjs::JS_EVAL_TYPE_GLOBAL_) : (quickjs::JS_EVAL_TYPE_MODULE_))
		);
		if (quickjs::JS_IsException(result)) {
			throw ExecutionException{as_lvalue(Value::new_instance(thiz._context(), quickjs::JS_GetException(thiz._context())))};
		}
		return Value::new_instance(thiz._context(), result);
	}

	// ----------------

	inline auto Context::global_object (
	) -> Value {
		return Value::new_instance(thiz._context(), quickjs::JS_GetGlobalObject(thiz._context()));
	}

	// ----------------

	inline auto Context::throw_exception (
		Value && value
	) -> Void {
		quickjs::JS_Throw(thiz._context(), value._release_value());
		return;
	}

	inline auto Context::catch_exception (
	) -> Value {
		return Value::new_instance(thiz._context(), quickjs::JS_GetException(thiz._context()));
	}

	// ----------------

	inline auto Context::get_class_proto (
		Integer const & id
	) -> Value {
		return Value::new_instance(thiz._context(), quickjs::JS_GetClassProto(thiz._context(), static_cast<quickjs::JSClassID>(id.value)));
	}

	inline auto Context::set_class_proto (
		Integer const & id,
		Value &&        value
	) -> Void {
		quickjs::JS_SetClassProto(thiz._context(), static_cast<quickjs::JSClassID>(id.value), value._release_value());
		return;
	}

	// ----------------

	template <auto function> requires
		CategoryConstraint<>
		&& (IsSameV<function, NativeFunction>)
	inline auto Value::set_object_of_native_function (
		String const &  name,
		Boolean const & is_constructor
	) -> Void {
		return thiz._rebind_value(
			quickjs::JS_NewCFunction2(
				thiz._context(),
				&Detail::proxy_native_function<function>,
				cast_pointer<char>(make_null_terminated_string(name).begin()).value,
				0,
				!is_constructor ? (quickjs::JS_CFUNC_generic_) : (quickjs::JS_CFUNC_constructor_),
				0
			)
		);
	}

	#pragma endregion

}
