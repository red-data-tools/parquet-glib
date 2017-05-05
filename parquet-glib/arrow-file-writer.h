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

#define GPARQUET_TYPE_ARROW_FILE_WRITER         \
  (gparquet_arrow_file_writer_get_type())
#define GPARQUET_ARROW_FILE_WRITER(obj)                         \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),                            \
                              GPARQUET_TYPE_ARROW_FILE_WRITER,  \
                              GParquetArrowFileWriter))
#define GPARQUET_ARROW_FILE_WRITER_CLASS(klass)                 \
  (G_TYPE_CHECK_CLASS_CAST((klass),                             \
                           GPARQUET_TYPE_ARROW_FILE_WRITER,     \
                           GParquetArrowFileWriterClass))
#define GPARQUET_IS_ARROW_FILE_WRITER(obj)                      \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),                            \
                              GPARQUET_TYPE_ARROW_FILE_WRITER))
#define GPARQUET_IS_ARROW_FILE_WRITER_CLASS(klass)              \
  (G_TYPE_CHECK_CLASS_TYPE((klass),                             \
                           GPARQUET_TYPE_ARROW_FILE_WRITER))
#define GPARQUET_ARROW_FILE_WRITER_GET_CLASS(obj)               \
  (G_TYPE_INSTANCE_GET_CLASS((obj),                             \
                             GPARQUET_TYPE_ARROW_FILE_WRITER,   \
                             GParquetArrowFileWriterClass))

typedef struct _GParquetArrowFileWriter         GParquetArrowFileWriter;
typedef struct _GParquetArrowFileWriterClass    GParquetArrowFileWriterClass;

/**
 * GParquetArrowFileWriter:
 *
 * It wraps `parquet::arrow::FileWriter`.
 */
struct _GParquetArrowFileWriter
{
  /*< private >*/
  GObject parent_instance;
};

struct _GParquetArrowFileWriterClass
{
  GObjectClass parent_class;
};

GType gparquet_arrow_file_writer_get_type(void) G_GNUC_CONST;

GParquetArrowFileWriter *gparquet_arrow_file_writer_new_arrow(GArrowSchema *schema,
                                                              GArrowOutputStream *sink,
                                                              GError **error);
GParquetArrowFileWriter *gparquet_arrow_file_writer_new_path(GArrowSchema *schema,
                                                             const gchar *path,
                                                             GError **error);

gboolean gparquet_arrow_file_writer_write_table(GParquetArrowFileWriter *writer,
                                                GArrowTable *table,
                                                guint64 chunk_size,
                                                GError **error);

gboolean gparquet_arrow_file_writer_close(GParquetArrowFileWriter *writer,
                                          GError **error);

G_END_DECLS
