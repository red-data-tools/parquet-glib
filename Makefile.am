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

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS =					\
	parquet-glib				\
	doc

EXTRA_DIST =					\
	LICENSE.txt				\
	NOTICE.txt				\
	README.md

parquet_glib_docdir = ${datarootdir}/doc/parquet-glib
parquet_glib_doc_DATA =				\
	README.md

tag:
	git tag -a -m '$(VERSION) has been released!!!' $(VERSION)
	git push --tags

GITHUB_RELEASE_VERSION = 0.7.2
github-release:
	wget https://github.com/aktau/github-release/releases/download/v$(GITHUB_RELEASE_VERSION)/linux-amd64-github-release.tar.bz2
	tar xvf linux-amd64-github-release.tar.bz2
	mv bin/linux/amd64/github-release ./
	rm -rf bin/

archive = $(PACKAGE)-$(VERSION).tar.gz
release: github-release $(archive)
	@[ -n "$${GITHUB_TOKEN}" ] || \
	  (echo "GITHUB_TOKEN environment variable isn't set"; false)
	./github-release upload \
	  --user red-data-tools \
	  --repo parquet-glib \
	  --tag $(VERSION) \
	  --name $(archive) \
	  --file $(archive)
