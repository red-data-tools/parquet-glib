# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CLEANFILES =

EXTRA_DIST =

AM_CPPFLAGS =					\
	-I$(top_builddir)			\
	-I$(top_srcdir)

AM_CFLAGS =					\
	$(GLIB_CFLAGS)				\
	$(PARQUET_CFLAGS)			\
	$(GARROW_CFLAGS)			\
	$(GPARQUET_CFLAGS)

lib_LTLIBRARIES =				\
	libparquet-glib.la

libparquet_glib_la_CXXFLAGS =			\
	$(GLIB_CFLAGS)				\
	$(PARQUET_CFLAGS)			\
	$(GARROW_CFLAGS)			\
	$(GPARQUET_CXXFLAGS)

libparquet_glib_la_LDFLAGS =			\
	-version-info $(LT_VERSION_INFO)	\
	-no-undefined

libparquet_glib_la_LIBADD =			\
	$(GLIB_LIBS)				\
	$(PARQUET_LIBS)				\
	$(GARROW_LIBS)

libparquet_glib_la_headers =			\
	arrow-file-reader.h			\
	arrow-file-writer.h			\
	parquet-glib.h

libparquet_glib_la_sources =			\
	arrow-file-reader.cpp			\
	arrow-file-writer.cpp			\
	$(libparquet_glib_la_headers)

libparquet_glib_la_cpp_headers =		\
	arrow-file-reader.hpp			\
	arrow-file-writer.hpp			\
	parquet-glib.hpp

libparquet_glib_la_SOURCES =			\
	$(libparquet_glib_la_sources)		\
	$(libparquet_glib_la_cpp_headers)

parquet_glib_includedir = $(includedir)/parquet-glib
parquet_glib_include_HEADERS =			\
	$(libparquet_glib_la_headers)		\
	$(libparquet_glib_la_cpp_headers)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA =				\
	parquet-glib.pc

# GObject Introspection
if HAVE_INTROSPECTION
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS =
INTROSPECTION_COMPILER_ARGS =

Parquet-1.0.gir: libparquet-glib.la
Parquet_1_0_gir_PACKAGES =			\
	gobject-2.0				\
	arrow-glib
Parquet_1_0_gir_EXPORT_PACKAGES = parquet
Parquet_1_0_gir_INCLUDES =			\
	GObject-2.0				\
	Arrow-1.0
Parquet_1_0_gir_CFLAGS =			\
	$(AM_CPPFLAGS)
Parquet_1_0_gir_LIBS = libparquet-glib.la
Parquet_1_0_gir_FILES = $(libparquet_glib_la_sources)
Parquet_1_0_gir_SCANNERFLAGS =			\
	--warn-all				\
	--identifier-prefix=GParquet		\
	--symbol-prefix=gparquet
INTROSPECTION_GIRS += Parquet-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES +=					\
	$(gir_DATA)				\
	$(typelib_DATA)
endif
