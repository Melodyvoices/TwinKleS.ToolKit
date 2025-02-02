// ignore_for_file: unused_import, library_prefixes

import '/common.dart';
import 'dart:ffi' as ffi;
import '/core/interface.dart' as Interface;
import '/core/symbol.dart';
import '/core/library.dart';

// ----------------

class DynamicLibrary extends Library {

  late SymbolTable        _symbol;
  late ffi.DynamicLibrary _handle;

  // ----------------

  DynamicLibrary(
    String path,
  ) {
    this._handle = ffi.DynamicLibrary.open(normalizeLibraryPath(path));
    this._symbol = SymbolTable();
    this._symbol.version = this._handle.lookup<ffi.NativeFunction<Interface.version>>(SymbolNameTable.version);
    this._symbol.execute = this._handle.lookup<ffi.NativeFunction<Interface.execute>>(SymbolNameTable.execute);
    this._symbol.prepare = this._handle.lookup<ffi.NativeFunction<Interface.prepare>>(SymbolNameTable.prepare);
  }

  // ----------------

  @override
  ffi.Pointer<Interface.String>
  version(
    ffi.Pointer<ffi.Pointer<Interface.Size>> number,
  ) {
    return this._symbol.version.asFunction<Interface.version>()(number);
  }

  @override
  ffi.Pointer<Interface.String>
  execute(
    ffi.Pointer<ffi.Pointer<Interface.Callback>> callback,
    ffi.Pointer<ffi.Pointer<Interface.String>> script,
    ffi.Pointer<ffi.Pointer<Interface.StringList>> argument,
    ffi.Pointer<ffi.Pointer<Interface.String>> result,
  ) {
    return this._symbol.execute.asFunction<Interface.execute>()(callback, script, argument, result);
  }

  @override
  ffi.Pointer<Interface.String>
  prepare(
  ) {
    return this._symbol.prepare.asFunction<Interface.prepare>()();
  }

}
