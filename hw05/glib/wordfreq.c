#include <glib.h>
#include <glib/gstdio.h>
#include <glib/gprintf.h>
#include <glib/gstring.h>
#include <gio/gio.h>

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT	g_printf
#else
#define DEBUG_PRINT(...)
#endif

GError *err = NULL;


GString *getContent(gchar *file_name)
{
	GFileInputStream *file_stream;
	GDataInputStream *data_stream;
	GFile *file;
	gchar *line;

	GString *content;
	content = g_string_new("");

	// File processing code
	// Reference: https://github.com/chergert/fuzzy/blob/master/main.c

	file = g_file_new_for_path(file_name);
	file_stream = g_file_read(file, NULL, NULL);
	data_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));
	while ((line = g_data_input_stream_read_line(data_stream, NULL, NULL, NULL))) {
		content = g_string_append(content, line);
	}

	g_clear_object(&data_stream);
	g_clear_object(&file_stream);
	g_clear_object(&file);

	return content;
}

void process(gchar *file_name)
{
	GString *content;

	DEBUG_PRINT("File Name: %s\n", file_name);

	content = getContent(file_name);
	DEBUG_PRINT("%s", content->str);
}

int main(gint argc, gchar *argv[])
{
	// Without this line, there comes weird error in runtime!
	// Reference: http://ubuntuforums.org/showthread.php?t=1642100
	gtk_init(&argc, &argv);

    if (argc == 1) {
    	process((gchar *)"./input.txt");
    }
    else if (argc == 2) {
    	process(argv[1]);
    }
    else {
    	fprintf(stderr, "Error: invalid input\n");
    	fprintf(stderr, "Usage:\n");
    	fprintf(stderr, "\t%s\n\t%s INPUT_FILE\n", argv[0], argv[0]);
    }

    return 0;
}
