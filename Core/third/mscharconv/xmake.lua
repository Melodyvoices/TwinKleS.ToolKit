-- mscharconv
-- 1.2.1 e1a23741136aeb1e08f1a8b712c9eca331f7dd32
-- https://github.com/iboB/mscharconv

target('third.mscharconv', function()
	set_group('source/third')
	set_kind('headeronly')
	add_headerfiles(
		'./include/msstl/converted/charconv.inl',
		'./include/msstl/converted/m_floating_type_traits.inl',
		'./include/msstl/converted/xbit_ops.h.inl',
		'./include/msstl/converted/xcharconv_ryu_tables.h.inl',
		'./include/msstl/converted/xcharconv_ryu.h.inl',
		'./include/msstl/converted/xcharconv.h.inl',
		'./include/msstl/charconv_fwd.hpp',
		'./include/msstl/charconv_impl.inl',
		'./include/msstl/charconv.hpp',
		'./include/msstl/util.hpp',
		{ install = false }
	)
	on_load(function(target)
		import('custom')
		custom.apply_compiler_option_basic(target)
		custom.apply_compiler_option_warning_disable(target)
	end)
end)
