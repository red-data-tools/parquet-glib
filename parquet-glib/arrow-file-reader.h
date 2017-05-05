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

#pragma once

#include <arrow-glib/arrow-glib.h>

G_BEGIN_DECLS

#define GPARQUET_TYPE_ARROW_FILE_READER         \
  (gparquet_arrow_file_reader_get_type())
#define GPARQUET_ARROW_FILE_READER(obj)                         \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),                            \
                              GPARQUET_TYPE_ARROW_FILE_READER,  \
                              GParquetArrowFileReader))
#define GPARQUET_ARROW_FILE_READER_CLASS(klass)                 \
  (G_TYPE_CHECK_CLASS_CAST((klass),                             \
                           GPARQUET_TYPE_ARROW_FILE_READER,     \
                           GParquetArrowFileReaderClass))
#define GPARQUET_IS_ARROW_FILE_READER(obj)                      \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),                            \
                              GPARQUET_TYPE_ARROW_FILE_READER))
#define GPARQUET_IS_ARROW_FILE_READER_CLASS(klass)              \
  (G_TYPE_CHECK_CLASS_TYPE((klass),                             \
                           GPARQUET_TYPE_ARROW_FILE_READER))
#define GPARQUET_ARROW_FILE_READER_GET_CLASS(obj)               \
  (G_TYPE_INSTANCE_GET_CLASS((obj),                             \
                             GPARQUET_TYPE_ARROW_FILE_READER,   \
                             GParquetArrowFileReaderClass))

typedef struct _GParquetArrowFileReader         GParquetArrowFileReader;
typedef struct _GParquetArrowFileReaderClass    GParquetArrowFileReaderClass;

/**
 * GParquetArrowFileReader:
 *
 * It wraps `parquet::arrow::FileReader`.
 */
struct _GParquetArrowFileReader
{
  /*< private >*/
  GObject parent_instance;
};

struct _GParquetArrowFileReaderClass
{
  GObjectClass parent_class;
};

GType gparquet_arrow_file_reader_get_type(void) G_GNUC_CONST;

GParquetArrowFileReader *gparquet_arrow_file_reader_new_arrow(GArrowSeekableInputStream *source,
                                                              GError **error);
GParquetArrowFileReader *gparquet_arrow_file_reader_new_path(const gchar *path,
                                                             GError **error);

GArrowTable *gparquet_arrow_file_reader_read_table(GParquetArrowFileReader *reader,
                                                   GError **error);

gint gparquet_arrow_file_reader_get_n_row_groups(GParquetArrowFileReader *reader);

void gparquet_arrow_file_reader_set_n_threads(GParquetArrowFileReader *reader,
                                              gint n_threads);

G_END_DECLS
