#pragma once

#include "implement/common.hpp"
#include "implement/language.hpp"
#include "implement/forward_explorer_command.hpp"

#define M_define_exposed_forward_command(_uuid, _base, _name, _id)\
	class __declspec(uuid(_uuid)) _name##_base :\
		public _base {\
	public:\
		_name##_base (\
		) :\
			_base{ForwardExplorerCommandConfigurationTable::_id} {\
		}\
	};

#define M_define_exposed_visible_forward_command(_uuid, _base, _name, _id)\
	class __declspec(uuid(_uuid)) _name##_base :\
		public VisibleExplorerCommand<_base> {\
	public:\
		_name##_base (\
		) :\
			VisibleExplorerCommand{L###_id, ForwardExplorerCommandConfigurationTable::_id} {\
		}\
	};

namespace TwinStar::ForwarderForWindows::Exposed {

	#pragma region configuration

	namespace ForwardExplorerCommandConfigurationTable {

		inline auto const main = ForwardExplorerCommandConfiguration{
			.id = L"main",
			.type = std::nullopt,
			.rule = std::nullopt,
			.method = std::nullopt,
			.argument = LR"({})",
		};

		// ----------------

		inline auto const launch = ForwardExplorerCommandConfiguration{
			.id = L"launch",
			.type = std::nullopt,
			.rule = std::nullopt,
			.method = std::nullopt,
			.argument = LR"({})",
		};

		inline auto const js = GroupForwardExplorerCommandConfiguration{
			.id = L"js",
			.item = {
				{
					.id = L"js.execute",
					.type = false,
					.rule = std::wregex{LR"(.+(\.js)$)", std::wregex::icase},
					.method = L"js.execute",
					.argument = LR"({})",
				},
			},
			.separator = {
				1,
			},
		};

		inline auto const json = GroupForwardExplorerCommandConfiguration{
			.id = L"json",
			.item = {
				{
					.id = L"json.format",
					.type = false,
					.rule = std::wregex{LR"(.+(\.json)$)", std::wregex::icase},
					.method = L"json.format",
					.argument = LR"({})",
				},
				{
					.id = L"json.format.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"json.format.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				1,
				1,
			},
		};

		inline auto const data = GroupForwardExplorerCommandConfiguration{
			.id = L"data",
			.item = {
				{
					.id = L"data.hash.md5",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.hash.md5",
					.argument = LR"({})",
				},
				{
					.id = L"data.encoding.base64.encode",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.encoding.base64.encode",
					.argument = LR"({})",
				},
				{
					.id = L"data.encoding.base64.decode",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.encoding.base64.decode",
					.argument = LR"({})",
				},
				{
					.id = L"data.encryption.xor.encrypt",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.encryption.xor.encrypt",
					.argument = LR"({})",
				},
				{
					.id = L"data.encryption.rijndael.encrypt",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.encryption.rijndael.encrypt",
					.argument = LR"({})",
				},
				{
					.id = L"data.encryption.rijndael.decrypt",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.encryption.rijndael.decrypt",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.deflate.compress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.deflate.compress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.deflate.uncompress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.deflate.uncompress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.zlib.compress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.zlib.compress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.zlib.uncompress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.zlib.uncompress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.gzip.compress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.gzip.compress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.gzip.uncompress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.gzip.uncompress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.bzip2.compress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.bzip2.compress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.bzip2.uncompress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.bzip2.uncompress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.lzma.compress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.lzma.compress",
					.argument = LR"({})",
				},
				{
					.id = L"data.compression.lzma.uncompress",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.compression.lzma.uncompress",
					.argument = LR"({})",
				},
				{
					.id = L"data.differentiation.vcdiff.encode",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.differentiation.vcdiff.encode",
					.argument = LR"({})",
				},
				{
					.id = L"data.differentiation.vcdiff.decode",
					.type = false,
					.rule = std::nullopt,
					.method = L"data.differentiation.vcdiff.decode",
					.argument = LR"({})",
				},
			},
			.separator = {
				1,
				2,
				1,
				2,
				2,
				2,
				2,
				2,
				2,
				2,
			},
		};

		inline auto const image = GroupForwardExplorerCommandConfiguration{
			.id = L"image",
			.item = {
				{
					.id = L"image.transformation.flip",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"image.transformation.flip",
					.argument = LR"({})",
				},
				{
					.id = L"image.transformation.scale",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"image.transformation.scale",
					.argument = LR"({})",
				},
				{
					.id = L"image.transformation.scale_rate",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"image.transformation.scale_rate",
					.argument = LR"({})",
				},
				{
					.id = L"image.atlas.pack",
					.type = false,
					.rule = std::wregex{LR"(.+(\.atlas)(\.json)$)", std::wregex::icase},
					.method = L"image.atlas.pack",
					.argument = LR"({})",
				},
				{
					.id = L"image.atlas.unpack",
					.type = false,
					.rule = std::wregex{LR"(.+(\.atlas)(\.json)$)", std::wregex::icase},
					.method = L"image.atlas.unpack",
					.argument = LR"({})",
				},
				{
					.id = L"image.atlas.pack_automatic",
					.type = true,
					.rule = std::wregex{LR"(.+(\.sprite)$)", std::wregex::icase},
					.method = L"image.atlas.pack_automatic",
					.argument = LR"({})",
				},
			},
			.separator = {
				1,
				2,
				2,
				1,
			},
		};

		inline auto const wwise_media = GroupForwardExplorerCommandConfiguration{
			.id = L"wwise.media",
			.item = {
				{
					.id = L"wwise.media.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.wem)$)", std::wregex::icase},
					.method = L"wwise.media.decode",
					.argument = LR"({})",
				},
				{
					.id = L"wwise.media.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"wwise.media.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				1,
				1,
			},
		};

		inline auto const wwise_sound_bank = GroupForwardExplorerCommandConfiguration{
			.id = L"wwise.sound_bank",
			.item = {
				{
					.id = L"wwise.sound_bank.encode",
					.type = true,
					.rule = std::wregex{LR"(.+(\.bnk)(\.bundle)$)", std::wregex::icase},
					.method = L"wwise.sound_bank.encode",
					.argument = LR"({})",
				},
				{
					.id = L"wwise.sound_bank.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.bnk)$)", std::wregex::icase},
					.method = L"wwise.sound_bank.decode",
					.argument = LR"({})",
				},
				{
					.id = L"wwise.sound_bank.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"wwise.sound_bank.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"wwise.sound_bank.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"wwise.sound_bank.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const marmalade_dzip = GroupForwardExplorerCommandConfiguration{
			.id = L"marmalade.dzip",
			.item = {
				{
					.id = L"marmalade.dzip.pack",
					.type = true,
					.rule = std::wregex{LR"(.+(\.dz)(\.bundle)$)", std::wregex::icase},
					.method = L"marmalade.dzip.pack",
					.argument = LR"({})",
				},
				{
					.id = L"marmalade.dzip.unpack",
					.type = false,
					.rule = std::wregex{LR"(.+(\.dz)$)", std::wregex::icase},
					.method = L"marmalade.dzip.unpack",
					.argument = LR"({})",
				},
				{
					.id = L"marmalade.dzip.pack_automatic",
					.type = true,
					.rule = std::nullopt,
					.method = L"marmalade.dzip.pack_automatic",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				1,
			},
		};

		inline auto const popcap_zlib = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.zlib",
			.item = {
				{
					.id = L"popcap.zlib.compress",
					.type = false,
					.rule = std::nullopt,
					.method = L"popcap.zlib.compress",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.zlib.uncompress",
					.type = false,
					.rule = std::nullopt,
					.method = L"popcap.zlib.uncompress",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.zlib.compress.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.zlib.compress.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.zlib.uncompress.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.zlib.uncompress.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_crypt_data = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.crypt_data",
			.item = {
				{
					.id = L"popcap.crypt_data.encrypt",
					.type = false,
					.rule = std::nullopt,
					.method = L"popcap.crypt_data.encrypt",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.crypt_data.decrypt",
					.type = false,
					.rule = std::wregex{LR"(.+(\.cdat)$)", std::wregex::icase},
					.method = L"popcap.crypt_data.decrypt",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.crypt_data.encrypt.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.crypt_data.encrypt.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.crypt_data.decrypt.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.crypt_data.decrypt.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_reflection_object_notation = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.reflection_object_notation",
			.item = {
				{
					.id = L"popcap.reflection_object_notation.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.json)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rton)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.encrypt",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rton)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.encrypt",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decrypt",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rton)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.decrypt",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.encode_then_encrypt",
					.type = false,
					.rule = std::wregex{LR"(.+(\.json)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.encode_then_encrypt",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decrypt_then_decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rton)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.decrypt_then_decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decode_lenient",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rton)$)", std::wregex::icase},
					.method = L"popcap.reflection_object_notation.decode_lenient",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.reflection_object_notation.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.reflection_object_notation.decode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.encrypt.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.reflection_object_notation.encrypt.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decrypt.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.reflection_object_notation.decrypt.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.encode_then_encrypt.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.reflection_object_notation.encode_then_encrypt.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.reflection_object_notation.decrypt_then_decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.reflection_object_notation.decrypt_then_decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
				2,
				1,
				2,
				2,
				2,
			},
		};

		inline auto const popcap_texture = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.texture",
			.item = {
				{
					.id = L"popcap.texture.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.texture.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.texture.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.ptx)$)", std::wregex::icase},
					.method = L"popcap.texture.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.texture.encode:rgba_8888_o",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.texture.encode",
					.argument = LR"({ "format": "rgba_8888_o" })",
				},
				{
					.id = L"popcap.texture.decode:rgba_8888_o",
					.type = false,
					.rule = std::wregex{LR"(.+(\.ptx)$)", std::wregex::icase},
					.method = L"popcap.texture.decode",
					.argument = LR"({ "format": "rgba_8888_o" })",
				},
				{
					.id = L"popcap.texture.encode:argb_8888",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.texture.encode",
					.argument = LR"({ "format": "argb_8888" })",
				},
				{
					.id = L"popcap.texture.decode:argb_8888",
					.type = false,
					.rule = std::wregex{LR"(.+(\.ptx)$)", std::wregex::icase},
					.method = L"popcap.texture.decode",
					.argument = LR"({ "format": "argb_8888" })",
				},
				{
					.id = L"popcap.texture.encode:rgba_pvrtc4",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.texture.encode",
					.argument = LR"({ "format": "rgba_pvrtc4" })",
				},
				{
					.id = L"popcap.texture.decode:rgba_pvrtc4",
					.type = false,
					.rule = std::wregex{LR"(.+(\.ptx)$)", std::wregex::icase},
					.method = L"popcap.texture.decode",
					.argument = LR"({ "format": "rgba_pvrtc4" })",
				},
				{
					.id = L"popcap.texture.encode:rgb_etc1_a_8",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.texture.encode",
					.argument = LR"({ "format": "rgb_etc1_a_8" })",
				},
				{
					.id = L"popcap.texture.decode:rgb_etc1_a_8",
					.type = false,
					.rule = std::wregex{LR"(.+(\.ptx)$)", std::wregex::icase},
					.method = L"popcap.texture.decode",
					.argument = LR"({ "format": "rgb_etc1_a_8" })",
				},
				{
					.id = L"popcap.texture.encode:rgb_etc1_a_palette",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.texture.encode",
					.argument = LR"({ "format": "rgb_etc1_a_palette" })",
				},
				{
					.id = L"popcap.texture.decode:rgb_etc1_a_palette",
					.type = false,
					.rule = std::wregex{LR"(.+(\.ptx)$)", std::wregex::icase},
					.method = L"popcap.texture.decode",
					.argument = LR"({ "format": "rgb_etc1_a_palette" })",
				},
			},
			.separator = {
				2,
				2,
				2,
				2,
				2,
				2,
			},
		};

		inline auto const popcap_u_texture = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.u_texture",
			.item = {
				{
					.id = L"popcap.u_texture.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.u_texture.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.u_texture.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.tex)$)", std::wregex::icase},
					.method = L"popcap.u_texture.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.u_texture.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.u_texture.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.u_texture.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.u_texture.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_sexy_texture = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.sexy_texture",
			.item = {
				{
					.id = L"popcap.sexy_texture.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.png)$)", std::wregex::icase},
					.method = L"popcap.sexy_texture.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.sexy_texture.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.tex)$)", std::wregex::icase},
					.method = L"popcap.sexy_texture.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.sexy_texture.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.sexy_texture.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.sexy_texture.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.sexy_texture.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_animation = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.animation",
			.item = {
				{
					.id = L"popcap.animation.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.pam)(\.json)$)", std::wregex::icase},
					.method = L"popcap.animation.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.pam)$)", std::wregex::icase},
					.method = L"popcap.animation.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.from",
					.type = false,
					.rule = std::wregex{LR"(.+(\.pam)(\.json)$)", std::wregex::icase},
					.method = L"popcap.animation.convert.flash.from",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.to",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pam)(\.xfl)$)", std::wregex::icase},
					.method = L"popcap.animation.convert.flash.to",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.resize",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pam)(\.xfl)$)", std::wregex::icase},
					.method = L"popcap.animation.convert.flash.resize",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.resize:1536",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pam)(\.xfl)$)", std::wregex::icase},
					.method = L"popcap.animation.convert.flash.resize",
					.argument = LR"({ "resolution": 1536 })",
				},
				{
					.id = L"popcap.animation.convert.flash.link_media",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pam)(\.xfl)$)", std::wregex::icase},
					.method = L"popcap.animation.convert.flash.link_media",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.decode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.from.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.convert.flash.from.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.to.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.convert.flash.to.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.resize.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.convert.flash.resize.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.animation.convert.flash.resize.batch:1536",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.convert.flash.resize.batch",
					.argument = LR"({ "resolution": 1536 })",
				},
				{
					.id = L"popcap.animation.convert.flash.link_media.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.animation.convert.flash.link_media.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
				2,
				1,
				2,
				2,
				2,
				1,
			},
		};

		inline auto const popcap_re_animation = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.re_animation",
			.item = {
				{
					.id = L"popcap.re_animation.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.reanim)(\.json)$)", std::wregex::icase},
					.method = L"popcap.re_animation.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.re_animation.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.reanim)(\.compiled)$)", std::wregex::icase},
					.method = L"popcap.re_animation.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.re_animation.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.re_animation.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.re_animation.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.re_animation.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_particle = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.particle",
			.item = {
				{
					.id = L"popcap.particle.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.particle)(\.json)$)", std::wregex::icase},
					.method = L"popcap.particle.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.particle.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.xml)(\.compiled)$)", std::wregex::icase},
					.method = L"popcap.particle.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.particle.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.particle.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.particle.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.particle.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_trail = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.trail",
			.item = {
				{
					.id = L"popcap.trail.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.trail)(\.json)$)", std::wregex::icase},
					.method = L"popcap.trail.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.trail.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.trail)(\.compiled)$)", std::wregex::icase},
					.method = L"popcap.trail.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.trail.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.trail.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.trail.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.trail.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_effect = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.effect",
			.item = {
				{
					.id = L"popcap.effect.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.popfx)(\.json)$)", std::wregex::icase},
					.method = L"popcap.effect.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.effect.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.popfx)$)", std::wregex::icase},
					.method = L"popcap.effect.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.effect.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.effect.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.effect.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.effect.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_character_font_widget_2 = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.character_font_widget_2",
			.item = {
				{
					.id = L"popcap.character_font_widget_2.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.cfw2)(\.json)$)", std::wregex::icase},
					.method = L"popcap.character_font_widget_2.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.character_font_widget_2.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.cfw2)$)", std::wregex::icase},
					.method = L"popcap.character_font_widget_2.decode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.character_font_widget_2.encode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.character_font_widget_2.encode.batch",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.character_font_widget_2.decode.batch",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.character_font_widget_2.decode.batch",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				2,
			},
		};

		inline auto const popcap_package = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.package",
			.item = {
				{
					.id = L"popcap.package.pack",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pak)(\.bundle)$)", std::wregex::icase},
					.method = L"popcap.package.pack",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.package.unpack",
					.type = false,
					.rule = std::wregex{LR"(.+(\.pak)$)", std::wregex::icase},
					.method = L"popcap.package.unpack",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.package.pack_automatic",
					.type = true,
					.rule = std::nullopt,
					.method = L"popcap.package.pack_automatic",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.package.encrypt",
					.type = false,
					.rule = std::wregex{LR"(.+(\.pak)$)", std::wregex::icase},
					.method = L"popcap.package.encrypt",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				1,
				1,
			},
		};

		inline auto const popcap_resource_stream_group = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.resource_stream_group",
			.item = {
				{
					.id = L"popcap.resource_stream_group.pack",
					.type = true,
					.rule = std::wregex{LR"(.+(\.rsg)(\.bundle)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_group.pack",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.resource_stream_group.unpack",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rsg)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_group.unpack",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
			},
		};

		inline auto const popcap_resource_stream_bundle = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.resource_stream_bundle",
			.item = {
				{
					.id = L"popcap.resource_stream_bundle.pack",
					.type = true,
					.rule = std::wregex{LR"(.+(\.rsb)(\.bundle)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_bundle.pack",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.resource_stream_bundle.unpack",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rsb)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_bundle.unpack",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.resource_stream_bundle.resource_convert",
					.type = true,
					.rule = std::wregex{LR"(.+(\.rsb)(\.bundle)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_bundle.resource_convert",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.resource_stream_bundle.unpack_lenient",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rsb)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_bundle.unpack_lenient",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
				1,
				1,
			},
		};

		inline auto const popcap_resource_stream_bundle_patch = GroupForwardExplorerCommandConfiguration{
			.id = L"popcap.resource_stream_bundle_patch",
			.item = {
				{
					.id = L"popcap.resource_stream_bundle_patch.encode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rsb)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_bundle_patch.encode",
					.argument = LR"({})",
				},
				{
					.id = L"popcap.resource_stream_bundle_patch.decode",
					.type = false,
					.rule = std::wregex{LR"(.+(\.rsb)$)", std::wregex::icase},
					.method = L"popcap.resource_stream_bundle_patch.decode",
					.argument = LR"({})",
				},
			},
			.separator = {
				2,
			},
		};

		inline auto const pvz2_text_table = GroupForwardExplorerCommandConfiguration{
			.id = L"pvz2.text_table",
			.item = {
				{
					.id = L"pvz2.text_table.convert",
					.type = false,
					.rule = std::wregex{LR"(.+(\.(txt|json))$)", std::wregex::icase},
					.method = L"pvz2.text_table.convert",
					.argument = LR"({})",
				},
			},
			.separator = {
				1,
			},
		};

		inline auto const pvz2_remote_android_helper = GroupForwardExplorerCommandConfiguration{
			.id = L"pvz2.remote_android_helper",
			.item = {
				{
					.id = L"pvz2.remote_android_helper.launch:pull_main_package",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "pull_main_package" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:push_main_package",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "push_main_package" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:pull_local_profile",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "pull_local_profile" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:push_local_profile",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "push_local_profile" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:pull_player_profile",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "pull_player_profile" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:push_player_profile",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "push_player_profile" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:pull_content_delivery",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "pull_content_delivery" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:push_content_delivery",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "push_content_delivery" })",
				},
				{
					.id = L"pvz2.remote_android_helper.launch:clear_snapshot",
					.type = true,
					.rule = std::wregex{LR"(.+(\.pvz2_remote_android_helper_project)$)", std::wregex::icase},
					.method = L"pvz2.remote_android_helper.launch",
					.argument = LR"({ "action": "clear_snapshot" })",
				},
			},
			.separator = {
				2,
				2,
				2,
				2,
				1,
			},
		};

	}

	#pragma endregion

	#pragma region type

	M_define_exposed_forward_command("9992EC48-22A5-86FA-EA42-72DA1A53F23D", ForwardExplorerCommand, Main, main);

	// ----------------

	M_define_exposed_forward_command("A918A8A8-1436-43C5-99C1-9420D0D56D40", ForwardExplorerCommand, Launch, launch);

	M_define_exposed_visible_forward_command("314F8A42-AC6F-4192-8F9A-D2DF1C9F0546", GroupForwardExplorerCommand, JS, js);

	M_define_exposed_visible_forward_command("D60FB9DD-7677-4742-A2BC-C9049E268CBA", GroupForwardExplorerCommand, JSON, json);

	M_define_exposed_visible_forward_command("1DAED04B-CD51-45DA-91E4-F15DC831C7D5", GroupForwardExplorerCommand, Data, data);

	M_define_exposed_visible_forward_command("2BEEB70E-8211-4DB4-B6BF-8D6FDAB791BF", GroupForwardExplorerCommand, Image, image);

	M_define_exposed_visible_forward_command("C9A257AC-8048-4257-85AD-CE68CACD7922", GroupForwardExplorerCommand, WwiseMedia, wwise_media);

	M_define_exposed_visible_forward_command("8B32AE59-795E-4F2D-B3B8-A4558CF9488F", GroupForwardExplorerCommand, WwiseSoundBank, wwise_sound_bank);

	M_define_exposed_visible_forward_command("164D100A-5228-429D-A926-EFF742D00E9D", GroupForwardExplorerCommand, MarmaladeDZip, marmalade_dzip);

	M_define_exposed_visible_forward_command("5F334CE4-29A4-4B0F-A696-10EB3D773666", GroupForwardExplorerCommand, PopCapZLib, popcap_zlib);

	M_define_exposed_visible_forward_command("DFA54DDD-44E6-57BF-D063-9043B169A4ED", GroupForwardExplorerCommand, PopCapCryptData, popcap_crypt_data);

	M_define_exposed_visible_forward_command("A7121460-0260-4E4A-829F-D21A7E649B50", GroupForwardExplorerCommand, PopCapReflectionObjectNotation, popcap_reflection_object_notation);

	M_define_exposed_visible_forward_command("654DB9CD-DA07-4942-96A5-57F948C6A44C", GroupForwardExplorerCommand, PopCapTexture, popcap_texture);

	M_define_exposed_visible_forward_command("5E774A16-C9AA-8096-DFFC-71EB187033E6", GroupForwardExplorerCommand, PopCapUTexture, popcap_u_texture);

	M_define_exposed_visible_forward_command("F4410002-C25F-BF2B-6D68-1434FAC08314", GroupForwardExplorerCommand, PopCapSexyTexture, popcap_sexy_texture);

	M_define_exposed_visible_forward_command("D3EBD69C-CB8B-452D-BFC7-7C06519BDA68", GroupForwardExplorerCommand, PopCapAnimation, popcap_animation);

	M_define_exposed_visible_forward_command("E2D6187D-7E0E-4089-82F2-768A6EE7D4D1", GroupForwardExplorerCommand, PopCapReAnimation, popcap_re_animation);

	M_define_exposed_visible_forward_command("0DD08DF0-3B5D-5273-99AA-1A3766355ED1", GroupForwardExplorerCommand, PopCapParticle, popcap_particle);

	M_define_exposed_visible_forward_command("8532B3AF-4E59-149E-A324-BABC012C38F2", GroupForwardExplorerCommand, PopCapTrail, popcap_trail);

	M_define_exposed_visible_forward_command("A29DEC4C-30C3-1C40-63C2-AD34D4F828AF", GroupForwardExplorerCommand, PopCapEffect, popcap_effect);

	M_define_exposed_visible_forward_command("3AB6C4D5-C386-E654-C646-54D42FF58065", GroupForwardExplorerCommand, PopCapCharacterFontWidget2, popcap_character_font_widget_2);

	M_define_exposed_visible_forward_command("64DBC2C3-402F-42AA-B8BF-B43B3280F813", GroupForwardExplorerCommand, PopCapPackage, popcap_package);

	M_define_exposed_visible_forward_command("95E74A50-81DC-48BA-A24B-E0AD30C75139", GroupForwardExplorerCommand, PopCapResourceStreamGroup, popcap_resource_stream_group);

	M_define_exposed_visible_forward_command("BCF8438E-67D1-4B7B-8649-78C46FAB4CFE", GroupForwardExplorerCommand, PopCapResourceStreamBundle, popcap_resource_stream_bundle);

	M_define_exposed_visible_forward_command("C83A33D4-B96D-4002-9D76-4DB88AF589C0", GroupForwardExplorerCommand, PopCapResourceStreamBundlePatch, popcap_resource_stream_bundle_patch);

	M_define_exposed_visible_forward_command("3F961602-866A-4305-8031-42597990C6AB", GroupForwardExplorerCommand, PvZ2TextTable, pvz2_text_table);

	M_define_exposed_visible_forward_command("CD04E4D3-2224-14FC-C9DD-66D746408D62", GroupForwardExplorerCommand, PvZ2RemoteAndroidHelper, pvz2_remote_android_helper);

	#pragma endregion

}
