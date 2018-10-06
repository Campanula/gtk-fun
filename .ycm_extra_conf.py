from distutils.sysconfig import get_python_inc
import os
import subprocess
import ycm_core

DIR_OF_THIS_SCRIPT = os.path.abspath(os.path.dirname(__file__))
DIR_OF_THIRD_PARTY = os.path.join(DIR_OF_THIS_SCRIPT, 'third_party')
SOURCE_EXTENSIONS = ['.cpp', '.cxx', '.cc', '.c', '.m', '.mm']

flags = [
    '-Wall -Wextra -Werror -Wno-long-long -Wno-variadic-macros',
    '-fexceptions',
    '-DNDEBUG',
    '-x', 'c',
    '-std=c11',
    '-I cpp/ycm',
    '-I cpp/ycm/ClangCompleter',
    '-isystem cpp/pybind11',
    '-isystem cpp/BoostParts',
    '-isystem {}'.format(get_python_inc()),
    '-isystem cpp/llvm/include',
    '-isystem cpp/llvm/tools/clang/include',
    '-isystem cpp/ycm/tests/gmock/gtest',
    '-isystem cpp/ycm/tests/gmock/gtest/include',
    '-isystem cpp/ycm/tests/gmock',
    '-isystem cpp/ycm/tests/gmock/include',
    '-isystem cpp/ycm/benchmarks/benchmark/include',

    '-I/usr/include/gtk-3.0',
    '-I/usr/include/pango-1.0',
    '-I/usr/include/glib-2.0',
    '-I/usr/include/fribidi',
    '-I/usr/include/cairo',
    '-I/usr/include/pixman-1',
    '-I/usr/include/freetype2',
    '-I/usr/include/libpng16',
    '-I/usr/include/harfbuzz',
    '-I/usr/include/uuid',
    '-I/usr/include/gdk-pixbuf-2.0',
    '-I/usr/include/gio-unix-2.0',
    '-I/usr/include/libmount',
    '-I/usr/include/blkid',
    '-I/usr/include/libdrm',
    '-I/usr/include/atk-1.0',
    '-I/usr/include/at-spi2-atk/2.0',
    '-I/usr/include/at-spi-2.0',
    '-I/usr/include/dbus-1.0',
    '-I/usr/lib/glib-2.0/include',
    '-I/usr/lib/libffi-3.2.1/include',
    '-I/usr/lib/dbus-1.0/include',
    '-pthread',
    '-lgtk-3',
    '-lgdk-3',
    '-lpangocairo-1.0',
    '-lpango-1.0',
    '-latk-1.0',
    '-lcairo-gobject',
    '-lcairo',
    '-lgdk_pixbuf-2.0',
    '-lgio-2.0',
    '-lgobject-2.0',
    '-lglib-2.0',
]

# You can get CMake to generate this file for you by adding:
#   set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
# to your CMakeLists.txt file.
compilation_database_folder = ''

if os.path.exists(compilation_database_folder):
    database = ycm_core.CompilationDatabase(compilation_database_folder)
else:
    database = None


def is_header_file(filename):
    extension = os.path.splitext(filename)[1]
    return extension in ['.h', '.hxx', '.hpp', '.hh']


def find_src(filename):
    if is_header_file(filename):
        basename = os.path.splitext(filename)[0]
        for extension in SOURCE_EXTENSIONS:
            replacement_file = basename + extension
            if os.path.exists(replacement_file):
                return replacement_file
    return filename


def Settings(**kwargs):
    if kwargs['language'] == 'cfamily':
        # If the file is a header, try to find the corresponding source file and
        # retrieve its flags from the compilation database if using one. This is
        # necessary since compilation databases don't have entries for header files.
        # In addition, use this source file as the translation unit. This makes it
        # possible to jump from a declaration in the header file to its definition
        # in the corresponding source file.
        filename = find_src(kwargs['filename'])

        if not database:
            return {
                'flags': flags,
                'include_paths_relative_to_dir': DIR_OF_THIS_SCRIPT,
                'override_filename': filename
            }

        compilation_info = database.GetCompilationInfoForFile(filename)
        if not compilation_info.compiler_flags_:
            return {}

        # Bear in mind that compilation_info.compiler_flags_ does NOT return a
        # python list, but a "list-like" StringVec object.
        final_flags = list(compilation_info.compiler_flags_)

        # NOTE: This is just for YouCompleteMe; it's highly likely that your project
        # does NOT need to remove the stdlib flag. DO NOT USE THIS IN YOUR
        # ycm_extra_conf IF YOU'RE NOT 100% SURE YOU NEED IT.
        try:
            final_flags.remove('-stdlib=libc++')
        except ValueError:
            pass

        return {
            'flags': final_flags,
            'include_paths_relative_to_dir': compilation_info.compiler_working_dir_,
            'override_filename': filename
        }
    return {}


def GetStandardLibraryIndexInSysPath(sys_path):
    for path in sys_path:
        if os.path.isfile(os.path.join(path, 'os.py')):
            return sys_path.index(path)
    raise RuntimeError('Could not find standard library path in Python path.')


def PythonSysPath(**kwargs):
    sys_path = kwargs['sys_path']
    if not os.path.exists(DIR_OF_THIRD_PARTY):
        return sys_path
    for folder in os.listdir(DIR_OF_THIRD_PARTY):
        if folder == 'python-future':
            folder = os.path.join(folder, 'src')
            sys_path.insert(
                GetStandardLibraryIndexInSysPath(sys_path) + 1,
                os.path.realpath(os.path.join(DIR_OF_THIRD_PARTY, folder))
            )
            continue

        if folder == 'cregex':
            interpreter_path = kwargs['interpreter_path']
            major_version = subprocess.check_output([
                interpreter_path, '-c', 'import sys; print( sys.version_info[ 0 ] )'
            ]).rstrip().decode('utf8')
            folder = os.path.join(folder, 'regex_{}'.format(major_version))

        sys_path.insert(0, os.path.realpath(os.path.join(DIR_OF_THIRD_PARTY, folder)))
    return sys_path
