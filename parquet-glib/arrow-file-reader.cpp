/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <arrow-glib/arrow-glib.hpp>

#include <parquet-glib/arrow-file-reader.hpp>

G_BEGIN_DECLS

/**
 * SECTION: arrow-file-reader
 * @short_description: Arrow file reader class
 * @include: parquet-glib/parquet-glib.h
 *
 * #GParquetArrowFileReader is a class for reading Apache Parquet data
 * from file and returns them as Apache Arrow data.
 */

typedef struct GParquetArrowFileReaderPrivate_ {
  parquet::arrow::FileReader *arrow_file_reader;
} GParquetArrowFileReaderPrivate;

enum {
  PROP_0,
  PROP_ARROW_FILE_READER
};

G_DEFINE_TYPE_WITH_PRIVATE(GParquetArrowFileReader,
                           gparquet_arrow_file_reader,
                           G_TYPE_OBJECT)

#define GPARQUET_ARROW_FILE_READER_GET_PRIVATE(obj)             \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                           \
                               GPARQUET_TYPE_ARROW_FILE_READER, \
                               GParquetArrowFileReaderPrivate))

static void
gparquet_arrow_file_reader_finalize(GObject *object)
{
  auto priv = GPARQUET_ARROW_FILE_READER_GET_PRIVATE(object);

  delete priv->arrow_file_reader;

  G_OBJECT_CLASS(gparquet_arrow_file_reader_parent_class)->finalize(object);
}

static void
gparquet_arrow_file_reader_set_property(GObject *object,
                                        guint prop_id,
                                        const GValue *value,
                                        GParamSpec *pspec)
{
  auto priv = GPARQUET_ARROW_FILE_READER_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_ARROW_FILE_READER:
    priv->arrow_file_reader =
      static_cast<parquet::arrow::FileReader *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gparquet_arrow_file_reader_get_property(GObject *object,
                                        guint prop_id,
                                        GValue *value,
                                        GParamSpec *pspec)
{
  switch (prop_id) {
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gparquet_arrow_file_reader_init(GParquetArrowFileReader *object)
{
}

static void
gparquet_arrow_file_reader_class_init(GParquetArrowFileReaderClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gparquet_arrow_file_reader_finalize;
  gobject_class->set_property = gparquet_arrow_file_reader_set_property;
  gobject_class->get_property = gparquet_arrow_file_reader_get_property;

  spec = g_param_spec_pointer("arrow-file-reader",
                              "ArrowFileReader",
                              "The raw std::shared<parquet::arrow::FileReader> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_ARROW_FILE_READER, spec);
}

/**
 * gparquet_arrow_file_reader_new_arrow:
 * @source: Arrow source to be read.
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Returns: (nullable): A newly created #GParquetArrowFileReader.
 *
 * Since: 1.0.0
 */
GParquetArrowFileReader *
gparquet_arrow_file_reader_new_arrow(GArrowSeekableInputStream *source,
                                     GError **error)
{
  auto arrow_random_access_file =
    garrow_seekable_input_stream_get_raw(source);
  auto arrow_memory_pool = arrow::default_memory_pool();
  std::unique_ptr<parquet::arrow::FileReader> parquet_arrow_file_reader;
  auto status = parquet::arrow::OpenFile(arrow_random_access_file,
                                         arrow_memory_pool,
                                         &parquet_arrow_file_reader);
  if (garrow_error_check(error, status, "[arrow][file-reader][new-arrow]")) {
    return gparquet_arrow_file_reader_new_raw(parquet_arrow_file_reader.release());
  } else {
    return NULL;
  }
}

/**
 * gparquet_arrow_file_reader_new_path:
 * @path: Path to be read.
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Returns: (nullable): A newly created #GParquetArrowFileReader.
 *
 * Since: 1.0.0
 */
GParquetArrowFileReader *
gparquet_arrow_file_reader_new_path(const gchar *path,
                                    GError **error)
{
  std::shared_ptr<arrow::io::MemoryMappedFile> arrow_memory_mapped_file;
  auto status = arrow::io::MemoryMappedFile::Open(path,
                                                  ::arrow::io::FileMode::READ,
                                                  &arrow_memory_mapped_file);
  if (!garrow_error_check(error, status, "[arrow][file-reader][new-path]")) {
    return NULL;
  }

  std::shared_ptr<arrow::io::RandomAccessFile> arrow_random_access_file =
    arrow_memory_mapped_file;
  auto arrow_memory_pool = arrow::default_memory_pool();
  std::unique_ptr<parquet::arrow::FileReader> parquet_arrow_file_reader;
  status = parquet::arrow::OpenFile(arrow_random_access_file,
                                    arrow_memory_pool,
                                    &parquet_arrow_file_reader);
  if (garrow_error_check(error, status, "[arrow][file-reader][new-path]")) {
    return gparquet_arrow_file_reader_new_raw(parquet_arrow_file_reader.release());
  } else {
    return NULL;
  }
}

/**
 * gparquet_arrow_file_reader_read_table:
 * @reader: A #GParquetArrowFileReader.
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Returns: (transfer full) (nullable): A read #GArrowTable.
 *
 * Since: 1.0.0
 */
GArrowTable *
gparquet_arrow_file_reader_read_table(GParquetArrowFileReader *reader,
                                      GError **error)
{
  auto parquet_arrow_file_reader = gparquet_arrow_file_reader_get_raw(reader);
  std::shared_ptr<arrow::Table> arrow_table;
  auto status = parquet_arrow_file_reader->ReadTable(&arrow_table);
  if (garrow_error_check(error, status, "[arrow][file-reader][read-table]")) {
    return garrow_table_new_raw(&arrow_table);
  } else {
    return NULL;
  }
}

/**
 * gparquet_arrow_file_reader_get_n_row_groups:
 * @reader: A #GParquetArrowFileReader.
 *
 * Returns: The number of row groups.
 *
 * Since: 1.0.0
 */
gint
gparquet_arrow_file_reader_get_n_row_groups(GParquetArrowFileReader *reader)
{
  auto parquet_arrow_file_reader = gparquet_arrow_file_reader_get_raw(reader);
  return parquet_arrow_file_reader->num_row_groups();
}

/**
 * gparquet_arrow_file_reader_set_n_threads:
 * @reader: A #GParquetArrowFileReader.
 * @n_threads: The max number of threads to read.
 *
 * Since: 1.0.0
 */
void
gparquet_arrow_file_reader_set_n_threads(GParquetArrowFileReader *reader,
                                         gint n_threads)
{
  auto parquet_arrow_file_reader = gparquet_arrow_file_reader_get_raw(reader);
  parquet_arrow_file_reader->set_num_threads(n_threads);
}

G_END_DECLS

GParquetArrowFileReader *
gparquet_arrow_file_reader_new_raw(parquet::arrow::FileReader *parquet_arrow_file_reader)
{
  auto arrow_file_reader =
    GPARQUET_ARROW_FILE_READER(g_object_new(GPARQUET_TYPE_ARROW_FILE_READER,
                                            "arrow-file-reader", parquet_arrow_file_reader,
                                            NULL));
  return arrow_file_reader;
}

parquet::arrow::FileReader *
gparquet_arrow_file_reader_get_raw(GParquetArrowFileReader *arrow_file_reader)
{
  auto priv = GPARQUET_ARROW_FILE_READER_GET_PRIVATE(arrow_file_reader);
  return priv->arrow_file_reader;
}
