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

/*****************************************************************************/
/* Global Variables */
/*****************************************************************************/

GError *err = NULL;

/*****************************************************************************/
/* Utility Functions */
/*****************************************************************************/

gchar *stripPunctuation(gchar *str)
{
	/* Implement Here! */
	return str;
}

/*****************************************************************************/
/* Functions */
/*****************************************************************************/

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

GSequence *getFilteredWordSequence(gchar **words)
{
    GSequence *sequence;
    gchar **ptr;

    sequence = g_sequence_new(g_free);

    for (ptr = words; *ptr; ++ptr) {
    	gchar *new_word;
    	//DEBUG_PRINT("word in : [%s]\n", *ptr);

    	// Filter 0 size
    	if (g_utf8_strlen(*ptr, -1) == 0) {
    		continue;
    	}
    	// Strip punctuations
    	new_word = stripPunctuation(*ptr);

    	// Add to sequence
        g_sequence_append(sequence, g_strdup(new_word));

        DEBUG_PRINT("word out: [%s]\n", new_word);
    }

    return sequence;
}

void process(gchar *file_name)
{
	GString *content;
	gchar **words;
	GSequence *filtered_words;

	DEBUG_PRINT("File Name: %s\n", file_name);

	// Read file content
	content = getContent(file_name);
	//DEBUG_PRINT("%s", content->str);

	// Split content to words
	words = g_strsplit(content->str, " ", 0);

	// Filter words
	filtered_words = getFilteredWordSequence(words);
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
