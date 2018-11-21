<!---
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
-->

# Parquet GLib

This project has been donated to Apache Arrow: https://github.com/apache/arrow/tree/master/c_glib/parquet-glib

Parquet GLib is a wrapper library for Parquet C++. Parquet GLib
provides C API.

Parquet GLib supports
[GObject Introspection](https://wiki.gnome.org/Projects/GObjectIntrospection).
It means that you can create language bindings at runtime or compile
time.

For example, you can use Apache Parquet from Ruby by Parquet GLib and
[gobject-introspection gem](https://rubygems.org/gems/gobject-introspection)
with the following code:

```ruby
# Generate bindings at runtime
require "gi"
Parquet = GI.load("Parquet")

# TODO
```

## Install

You can use packages or build by yourself to install Parquet GLib. It's
recommended that you use packages.

### Package

You can install packages from https://packages.red-data-tools.org/ .
See
https://github.com/red-data-tools/packages.red-data-tools.org#readme
for details.

### How to build by users

Parquet GLib users should use released source archive to build Parquet
GLib:

```text
% wget https://github.com/red-data-tools/parquet-glib/releases/download/1.0.0/parquet-glib-1.0.0.tar.gz
% tar xf parquet-glib-1.0.0.tar.gz
% cd parquet-glib-1.0.0
```

You need to install
[Parquet C++](https://github.com/apache/parquet-cpp),
[Arrow C++](https://github.com/apache/arrow/tree/master/cpp) and
[Arrow GLib](https://github.com/apache/arrow/tree/master/c_glib)
before you install Parquet GLib. See documents about how to install
them.

You can build and install Parquet GLib after you install them:

```text
% ./configure
% make
% sudo make install
```

### How to build by developers

You need to install
[Parquet C++](https://github.com/apache/parquet-cpp),
[Arrow C++](https://github.com/apache/arrow/tree/master/cpp) and
[Arrow GLib](https://github.com/apache/arrow/tree/master/c_glib)
before you install Parquet GLib. See documents about how to install
them.

You need [GTK-Doc](https://www.gtk.org/gtk-doc/) and
[GObject Introspection](https://wiki.gnome.org/Projects/GObjectIntrospection)
to build Parquet GLib. You can install them by the followings:

On Debian GNU/Linux or Ubuntu:

```text
% sudo apt install -y -V gtk-doc-tools autoconf-archive libgirepository1.0-dev
```

On CentOS 7 or later:

```text
% sudo yum install -y gtk-doc gobject-introspection-devel
```

On macOS with [Homebrew](https://brew.sh/):

```text
% brew install -y gtk-doc gobject-introspection
```

Now, you can build Arrow GLib:

```text
% ./autogen.sh
% ./configure --enable-gtk-doc
% make
% sudo make install
```

## Usage

You can use Parquet GLib with C or other languages. If you use Parquet
GLib with C, you use C API. If you use Parquet GLib with other
languages, you use GObject Introspection based bindings.

### C

You can find API reference in the
`/usr/local/share/gtk-doc/html/parquet-glib/` directory. If you
specify `--prefix` to `configure`, the directory will be different.

TODO: Examples

### Language bindings

TODO
