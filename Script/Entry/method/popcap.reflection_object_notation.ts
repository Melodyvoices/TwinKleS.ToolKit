namespace TwinStar.Script.Entry.method.popcap.reflection_object_notation {

	// ------------------------------------------------

	// encode *
	// decode *
	// encrypt *
	// decrypt *
	// encode_then_encrypt *
	// decrypt_then_decode *
	// decode_lenient

	type Configuration = {
		version_number: Executor.Argument<bigint, false>;
		version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
		key: Executor.Argument<string, false>;
		encode_buffer_size: Executor.Argument<string, false>;
	};

	export function _injector(
		configuration: Configuration,
	) {
		g_executor_method.push(
			Executor.method_of({
				id: 'popcap.reflection_object_notation.encode',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					value_file: Executor.Argument<string, false>;
					data_file: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
					buffer_size: Executor.Argument<string, false>;
				}) {
					let value_file: string;
					let data_file: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					let buffer_size: bigint;
					{
						value_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file'),
							a.value_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						data_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file'),
							a.data_file,
							(value) => (value),
							() => (value_file.replace(/((\.json))?$/i, '.rton')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
						buffer_size = Executor.request_argument(
							Executor.query_argument_name(this.id, 'buffer_size'),
							a.buffer_size,
							(value) => (parse_size_string(value)),
							null,
							(initial) => (Console.size(null, null, initial)),
						);
					}
					CoreX.Tool.PopCap.ReflectionObjectNotation.encode_fs(data_file, value_file, true, true, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 }, buffer_size);
					return [`${data_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					value_file: undefined!,
					data_file: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
					buffer_size: configuration.encode_buffer_size,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.json)$/i]]),
				input_forwarder: 'value_file',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decode',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					data_file: Executor.Argument<string, false>;
					value_file: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
				}) {
					let data_file: string;
					let value_file: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					{
						data_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file'),
							a.data_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						value_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file'),
							a.value_file,
							(value) => (value),
							() => (data_file.replace(/((\.rton))?$/i, '.json')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
					}
					CoreX.Tool.PopCap.ReflectionObjectNotation.decode_fs(data_file, value_file, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 });
					return [`${value_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					data_file: undefined!,
					value_file: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.rton)$/i]]),
				input_forwarder: 'data_file',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.encrypt',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					plain_file: Executor.Argument<string, false>;
					cipher_file: Executor.Argument<string, true>;
					key: Executor.Argument<string, false>;
				}) {
					let plain_file: string;
					let cipher_file: string;
					let key: string;
					{
						plain_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'plain_file'),
							a.plain_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						cipher_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'cipher_file'),
							a.cipher_file,
							(value) => (value),
							() => (plain_file.replace(/((\.rton))?$/i, '.cipher.rton')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
					}
					CoreX.Tool.PopCap.ReflectionObjectNotation.encrypt_fs(plain_file, cipher_file, key);
					return [`${cipher_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					plain_file: undefined!,
					cipher_file: '?default',
					key: configuration.key,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.rton)$/i]]),
				input_forwarder: 'plain_file',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decrypt',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					cipher_file: Executor.Argument<string, false>;
					plain_file: Executor.Argument<string, true>;
					key: Executor.Argument<string, false>;
				}) {
					let cipher_file: string;
					let plain_file: string;
					let key: string;
					{
						cipher_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'cipher_file'),
							a.cipher_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						plain_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'plain_file'),
							a.plain_file,
							(value) => (value),
							() => (cipher_file.replace(/((\.rton))?$/i, '.plain.rton')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
					}
					CoreX.Tool.PopCap.ReflectionObjectNotation.decrypt_fs(cipher_file, plain_file, key);
					return [`${plain_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					cipher_file: undefined!,
					plain_file: '?default',
					key: configuration.key,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.rton)$/i]]),
				input_forwarder: 'cipher_file',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.encode_then_encrypt',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					value_file: Executor.Argument<string, false>;
					data_file: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
					key: Executor.Argument<string, false>;
					buffer_size: Executor.Argument<string, false>;
				}) {
					let value_file: string;
					let data_file: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					let key: string;
					let buffer_size: bigint;
					{
						value_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file'),
							a.value_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						data_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file'),
							a.data_file,
							(value) => (value),
							() => (value_file.replace(/((\.json))?$/i, '.rton')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
						buffer_size = Executor.request_argument(
							Executor.query_argument_name(this.id, 'buffer_size'),
							a.buffer_size,
							(value) => (parse_size_string(value)),
							null,
							(initial) => (Console.size(null, null, initial)),
						);
					}
					CoreX.Tool.PopCap.ReflectionObjectNotation.encode_then_encrypt_fs(data_file, value_file, true, true, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 }, key, buffer_size);
					return [`${data_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					value_file: undefined!,
					data_file: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
					key: configuration.key,
					buffer_size: configuration.encode_buffer_size,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.json)$/i]]),
				input_forwarder: 'value_file',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decrypt_then_decode',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					data_file: Executor.Argument<string, false>;
					value_file: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
					key: Executor.Argument<string, false>;
				}) {
					let data_file: string;
					let value_file: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					let key: string;
					{
						data_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file'),
							a.data_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						value_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file'),
							a.value_file,
							(value) => (value),
							() => (data_file.replace(/((\.rton))?$/i, '.json')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
					}
					CoreX.Tool.PopCap.ReflectionObjectNotation.decrypt_then_decode_fs(data_file, value_file, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 }, key);
					return [`${value_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					data_file: undefined!,
					value_file: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
					key: configuration.key,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.rton)$/i]]),
				input_forwarder: 'data_file',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decode_lenient',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					data_file: Executor.Argument<string, false>;
					value_file: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
				}) {
					let data_file: string;
					let value_file: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					{
						data_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file'),
							a.data_file,
							(value) => (value),
							null,
							(initial) => (Console.path('file', ['in'], null, null, initial)),
						);
						value_file = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file'),
							a.value_file,
							(value) => (value),
							() => (data_file.replace(/((\.rton))?$/i, '.json')),
							(initial) => (Console.path('file', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
					}
					Support.PopCap.ReflectionObjectNotation.DecodeLenient.process_whole_fs(data_file, value_file, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 });
					return [`${value_file}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					data_file: undefined!,
					value_file: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
				},
				input_filter: Entry.file_system_path_test_generator([['file', /.+(\.rton)$/i]]),
				input_forwarder: 'data_file',
			}),
		);
		g_executor_method_of_batch.push(
			Executor.method_of({
				id: 'popcap.reflection_object_notation.encode.batch',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					value_file_directory: Executor.Argument<string, false>;
					data_file_directory: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
					buffer_size: Executor.Argument<string, false>;
				}) {
					let value_file_directory: string;
					let data_file_directory: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					let buffer_size: bigint;
					{
						value_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file_directory'),
							a.value_file_directory,
							(value) => (value),
							null,
							(initial) => (Console.path('directory', ['in'], null, null, initial)),
						);
						data_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file_directory'),
							a.data_file_directory,
							(value) => (value),
							() => (value_file_directory.replace(/$/i, '.encode')),
							(initial) => (Console.path('directory', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
						buffer_size = Executor.request_argument(
							Executor.query_argument_name(this.id, 'buffer_size'),
							a.buffer_size,
							(value) => (parse_size_string(value)),
							null,
							(initial) => (Console.size(null, null, initial)),
						);
					}
					let data_buffer = Core.ByteArray.allocate(Core.Size.value(buffer_size));
					simple_batch_execute(
						value_file_directory,
						['file', /.+(\.json)$/i],
						(item) => {
							let value_file = `${value_file_directory}/${item}`;
							let data_file = `${data_file_directory}/${item.slice(0, -5)}.rton`;
							CoreX.Tool.PopCap.ReflectionObjectNotation.encode_fs(data_file, value_file, true, true, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 }, data_buffer.view());
						},
					);
					return [`${data_file_directory}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					value_file_directory: undefined!,
					data_file_directory: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
					buffer_size: configuration.encode_buffer_size,
				},
				input_filter: Entry.file_system_path_test_generator([['directory', null]]),
				input_forwarder: 'value_file_directory',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decode.batch',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					data_file_directory: Executor.Argument<string, false>;
					value_file_directory: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
				}) {
					let data_file_directory: string;
					let value_file_directory: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					{
						data_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file_directory'),
							a.data_file_directory,
							(value) => (value),
							null,
							(initial) => (Console.path('directory', ['in'], null, null, initial)),
						);
						value_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file_directory'),
							a.value_file_directory,
							(value) => (value),
							() => (data_file_directory.replace(/$/i, '.decode')),
							(initial) => (Console.path('directory', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
					}
					simple_batch_execute(
						data_file_directory,
						['file', /.+(\.rton)$/i],
						(item) => {
							let data_file = `${data_file_directory}/${item}`;
							let value_file = `${value_file_directory}/${item.slice(0, -5)}.json`;
							CoreX.Tool.PopCap.ReflectionObjectNotation.decode_fs(data_file, value_file, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 });
						},
					);
					return [`${value_file_directory}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					data_file_directory: undefined!,
					value_file_directory: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
				},
				input_filter: Entry.file_system_path_test_generator([['directory', null]]),
				input_forwarder: 'data_file_directory',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.encrypt.batch',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					plain_file_directory: Executor.Argument<string, false>;
					cipher_file_directory: Executor.Argument<string, true>;
					key: Executor.Argument<string, false>;
				}) {
					let plain_file_directory: string;
					let cipher_file_directory: string;
					let key: string;
					{
						plain_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'plain_file_directory'),
							a.plain_file_directory,
							(value) => (value),
							null,
							(initial) => (Console.path('directory', ['in'], null, null, initial)),
						);
						cipher_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'cipher_file_directory'),
							a.cipher_file_directory,
							(value) => (value),
							() => (plain_file_directory.replace(/$/i, '.encrypt')),
							(initial) => (Console.path('directory', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
					}
					simple_batch_execute(
						plain_file_directory,
						['file', /.+(\.rton)$/i],
						(item) => {
							let plain_file = `${plain_file_directory}/${item}`;
							let cipher_file = `${cipher_file_directory}/${item}`;
							CoreX.Tool.PopCap.ReflectionObjectNotation.encrypt_fs(plain_file, cipher_file, key);
						},
					);
					return [`${cipher_file_directory}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					plain_file_directory: undefined!,
					cipher_file_directory: '?default',
					key: configuration.key,
				},
				input_filter: Entry.file_system_path_test_generator([['directory', null]]),
				input_forwarder: 'plain_file_directory',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decrypt.batch',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					cipher_file_directory: Executor.Argument<string, false>;
					plain_file_directory: Executor.Argument<string, true>;
					key: Executor.Argument<string, false>;
				}) {
					let cipher_file_directory: string;
					let plain_file_directory: string;
					let key: string;
					{
						cipher_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'cipher_file_directory'),
							a.cipher_file_directory,
							(value) => (value),
							null,
							(initial) => (Console.path('directory', ['in'], null, null, initial)),
						);
						plain_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'plain_file_directory'),
							a.plain_file_directory,
							(value) => (value),
							() => (cipher_file_directory.replace(/$/i, '.decrypt')),
							(initial) => (Console.path('directory', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
					}
					simple_batch_execute(
						cipher_file_directory,
						['file', /.+(\.rton)$/i],
						(item) => {
							let cipher_file = `${cipher_file_directory}/${item}`;
							let plain_file = `${plain_file_directory}/${item}`;
							CoreX.Tool.PopCap.ReflectionObjectNotation.decrypt_fs(cipher_file, plain_file, key);
						},
					);
					return [`${plain_file_directory}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					cipher_file_directory: undefined!,
					plain_file_directory: '?default',
					key: configuration.key,
				},
				input_filter: Entry.file_system_path_test_generator([['directory', null]]),
				input_forwarder: 'cipher_file_directory',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.encode_then_encrypt.batch',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					value_file_directory: Executor.Argument<string, false>;
					data_file_directory: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
					key: Executor.Argument<string, false>;
					buffer_size: Executor.Argument<string, false>;
				}) {
					let value_file_directory: string;
					let data_file_directory: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					let key: string;
					let buffer_size: bigint;
					{
						value_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file_directory'),
							a.value_file_directory,
							(value) => (value),
							null,
							(initial) => (Console.path('directory', ['in'], null, null, initial)),
						);
						data_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file_directory'),
							a.data_file_directory,
							(value) => (value),
							() => (value_file_directory.replace(/$/i, '.encode_then_encrypt')),
							(initial) => (Console.path('directory', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
						buffer_size = Executor.request_argument(
							Executor.query_argument_name(this.id, 'buffer_size'),
							a.buffer_size,
							(value) => (parse_size_string(value)),
							null,
							(initial) => (Console.size(null, null, initial)),
						);
					}
					let data_buffer = Core.ByteArray.allocate(Core.Size.value(buffer_size));
					simple_batch_execute(
						value_file_directory,
						['file', /.+(\.json)$/i],
						(item) => {
							let value_file = `${value_file_directory}/${item}`;
							let data_file = `${data_file_directory}/${item.slice(0, -5)}.rton`;
							CoreX.Tool.PopCap.ReflectionObjectNotation.encode_then_encrypt_fs(data_file, value_file, true, true, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 }, key, data_buffer.view());
						},
					);
					return [`${data_file_directory}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					value_file_directory: undefined!,
					data_file_directory: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
					key: configuration.key,
					buffer_size: configuration.encode_buffer_size,
				},
				input_filter: Entry.file_system_path_test_generator([['directory', null]]),
				input_forwarder: 'value_file_directory',
			}),
			Executor.method_of({
				id: 'popcap.reflection_object_notation.decrypt_then_decode.batch',
				name(
				) {
					return Executor.query_method_name(this.id);
				},
				worker(a: Entry.CommonArgument & {
					data_file_directory: Executor.Argument<string, false>;
					value_file_directory: Executor.Argument<string, true>;
					version_number: Executor.Argument<bigint, false>;
					version_native_string_encoding_use_utf8: Executor.Argument<boolean, false>;
					key: Executor.Argument<string, false>;
				}) {
					let data_file_directory: string;
					let value_file_directory: string;
					let version_number: bigint;
					let version_native_string_encoding_use_utf8: boolean;
					let key: string;
					{
						data_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'data_file_directory'),
							a.data_file_directory,
							(value) => (value),
							null,
							(initial) => (Console.path('directory', ['in'], null, null, initial)),
						);
						value_file_directory = Executor.request_argument(
							Executor.query_argument_name(this.id, 'value_file_directory'),
							a.value_file_directory,
							(value) => (value),
							() => (data_file_directory.replace(/$/i, '.decrypt_then_decode')),
							(initial) => (Console.path('directory', ['out', a.path_tactic_if_out_exist], null, null, initial)),
						);
						version_number = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_number'),
							a.version_number,
							(value) => (value),
							null,
							(initial) => (Console.option(Console.option_integer(CoreX.Tool.PopCap.ReflectionObjectNotation.VersionNumberE), null, null, initial)),
						);
						version_native_string_encoding_use_utf8 = Executor.request_argument(
							Executor.query_argument_name(this.id, 'version_native_string_encoding_use_utf8'),
							a.version_native_string_encoding_use_utf8,
							(value) => (value),
							null,
							(initial) => (Console.confirmation(null, null, initial)),
						);
						key = Executor.request_argument(
							Executor.query_argument_name(this.id, 'key'),
							a.key,
							(value) => (value),
							null,
							(initial) => (Console.string(null, null, initial)),
						);
					}
					simple_batch_execute(
						data_file_directory,
						['file', /.+(\.rton)$/i],
						(item) => {
							let data_file = `${data_file_directory}/${item}`;
							let value_file = `${value_file_directory}/${item.slice(0, -5)}.json`;
							CoreX.Tool.PopCap.ReflectionObjectNotation.decrypt_then_decode_fs(data_file, value_file, { number: version_number as any, native_string_encoding_use_utf8: version_native_string_encoding_use_utf8 }, key);
						},
					);
					return [`${value_file_directory}`];
				},
				default_argument: {
					...Entry.k_common_argument,
					data_file_directory: undefined!,
					value_file_directory: '?default',
					version_number: configuration.version_number,
					version_native_string_encoding_use_utf8: configuration.version_native_string_encoding_use_utf8,
					key: configuration.key,
				},
				input_filter: Entry.file_system_path_test_generator([['directory', null]]),
				input_forwarder: 'data_file_directory',
			}),
		);
	}

	// ------------------------------------------------

}

({
	injector: TwinStar.Script.Entry.method.popcap.reflection_object_notation._injector,
});