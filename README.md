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

In Ruby case, you should use
[red-arrow gem](https://rubygems.org/gems/red-arrow). It's based on
gobject-introspection gem. It adds many convenient features to raw
gobject-introspection gem based bindings.

## Install

You can use packages or build by yourself to install Arrow GLib. It's
recommended that you use packages.

Note that the packages are "unofficial". "Official" packages will be
released in the future.

### Package

There are supported platforms:

  * Debian GNU/Linux Jessie
  * Ubuntu 16.04 LTS
  * Ubuntu 16.10
  * CentOS 7

You can feedback to https://github.com/kou/arrow-packages about
packages things.

#### Debian GNU/Linux jessie

You need to add the following apt-lines to
`/etc/apt/sources.list.d/groonga.list`:

```text
deb https://packages.groonga.org/debian/ jessie main
deb-src https://packages.groonga.org/debian/ jessie main
```

Then you need to run the following command lines:

```text
% sudo apt update
% sudo apt install -y --allow-unauthenticated groonga-keyring
% sudo apt update
```

Now you can install Arrow GLib packages:

```text
% sudo apt install -y libarrow-glib-dev
```

#### Ubuntu 16.04 LTS and Ubuntu 16.10

You need to add an APT repository:

```text
% sudo apt install -y software-properties-common
% sudo add-apt-repository -y ppa:groonga/ppa
% sudo apt update
```

Now you can install Arrow GLib packages:

```text
% sudo apt install -y libarrow-glib-dev
```

#### CentOS 7

You need to add a Yum repository:

```text
% sudo yum install -y https://packages.groonga.org/centos/groonga-release-1.3.0-1.noarch.rpm
```

Now you can install Arrow GLib packages:

```text
% sudo yum install -y --enablerepo=epel arrow-glib-devel
```

### How to build by users

Arrow GLib users should use released source archive to build Arrow
GLib:

```text
% wget https://dist.apache.org/repos/dist/release/arrow/arrow-0.3.0/apache-arrow-0.3.0.tar.gz
% tar xf apache-arrow-0.3.0.tar.gz
% cd apache-arrow-0.3.0
```

You need to build and install Arrow C++ before you build and install
Arrow GLib. See Arrow C++ document about how to install Arrow C++.

You can build and install Arrow GLib after you install Arrow C++:

```text
% cd c_glib
% ./configure
% make
% sudo make install
```

### How to build by developers

You need to install Arrow C++ before you install Arrow GLib. See Arrow
C++ document about how to install Arrow C++.

You need [GTK-Doc](https://www.gtk.org/gtk-doc/) and
[GObject Introspection](https://wiki.gnome.org/action/show/Projects/GObjectIntrospection)
to build Arrow GLib. You can install them by the followings:

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
% cd c_glib
% ./autogen.sh
% ./configure --enable-gtk-doc
% make
% sudo make install
```

## Usage

You can use Arrow GLib with C or other languages. If you use Arrow
GLib with C, you use C API. If you use Arrow GLib with other
languages, you use GObject Introspection based bindings.

### C

You can find API reference in the
`/usr/local/share/gtk-doc/html/arrow-glib/` directory. If you specify
`--prefix` to `configure`, the directory will be different.

You can find example codes in the `example/` directory.

### Language bindings

You can use Arrow GLib with non C languages with GObject Introspection
based bindings. Here are languages that support GObject Introspection:

  * Ruby: [red-arrow gem](https://rubygems.org/gems/red-arrow) should be used.
    * Examples: https://github.com/red-data-tools/red-arrow/tree/master/example

  * Python: [PyGObject](https://wiki.gnome.org/Projects/PyGObject) should be used. (Note that you should use PyArrow than Arrow GLib.)

  * Lua: [LGI](https://github.com/pavouk/lgi) should be used.
    * Examples: `example/lua/` directory.

  * Go: [Go-gir-generator](https://github.com/linuxdeepin/go-gir-generator) should be used.

See also
[Projects/GObjectIntrospection/Users - GNOME Wiki!](https://wiki.gnome.org/Projects/GObjectIntrospection/Users)
for other languages.
