#include <glib.h>
#include <glib/gstdio.h>
#include <glib/gprintf.h>
#include <glib/gstring.h>
#include <gio/gio.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT	g_printf
#else
#define DEBUG_PRINT(...)
#endif

/*****************************************************************************/
/* Global Variables */
/*****************************************************************************/

GError *err = NULL;

typedef struct pair {
	gchar *str;
	gint num;
} pair_t;

/*****************************************************************************/
/* Utility Functions */
/*****************************************************************************/

GString *stripPunctuationAndLower(gchar *input)
{
	GString *output;
	gint i, len, start, end;

	output = g_string_new("");
	len = g_utf8_strlen(input, -1);
	start = 0;
	end = len - 1;

	// Strip: remove leading and trailing punctuations not inner ones.

	// From the beginning
	if (g_ascii_ispunct(input[0])) {
		for (i = 1; i < len; ++i) {
			if (!g_ascii_ispunct(input[i])) {
				break;
			}
		}
		start = i;
	}

	// From the end
	if (g_ascii_ispunct(input[len - 1])) {
		for (i = len - 1; i >= 0; --i) {
			if (!g_ascii_ispunct(input[i])) {
				break;
			}
		}
		end = i;
	}

	for (i = start; i <= end; ++i) {
		g_string_append_c(output, input[i]);
	}
	g_string_append(output, "\0");

	return output;
}

pair_t *new_struct_pair(gchar *str, gint num)
{
	pair_t *new_pair;

	new_pair = g_malloc(sizeof(pair_t));
	if (new_pair == NULL) {
		fprintf(stderr, "Error: failed to allocate memory\n");
		return NULL;
	}

	new_pair->str = g_strdup(str);
	new_pair->num = num;

	return new_pair;
}

void free_struct_pair(pair_t *data)
{
	g_free(data->str);
	g_free(data);
}

static gint compare_struct_pair(gconstpointer a, gconstpointer b, gpointer data)
{
	// Reference: http://web.mit.edu/barnowl/src/glib/glib-2.16.3/tests/sequence-test.c
	pair_t *p1, *p2;
	gint n1, n2;
	p1 = (pair_t *)a;
	p2 = (pair_t *)b;
	n1 = p1->num;
	n2 = p2->num;
	if (n1 == n2) {
		return 0;
	}
	else if (n1 > n2) {
		return 1;
	}
	else if (n1 < n2) {
		return -1;
	}
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
		gchar *lowered = g_utf8_strdown(line, g_utf8_strlen(line, -1));
		content = g_string_append(content, lowered);
		content = g_string_append_c(content, ' ');	// delimiter for line
		g_free(lowered);
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
    // when g_sequence_free(), all internal data will be freed by g_free()

    for (ptr = words; *ptr; ++ptr) {
    	GString *new_word;
    	//DEBUG_PRINT("word in : [%s]\n", *ptr);

    	// Filter 0 size
    	if (g_utf8_strlen(*ptr, -1) == 0) {
    		continue;
    	}
    	// Strip punctuations
    	new_word = stripPunctuationAndLower(*ptr);

    	// Add to sequence
        g_sequence_append(sequence, g_strdup(new_word->str));
        //DEBUG_PRINT("word out: [%s]\n", new_word->str);

        g_string_free(new_word, TRUE);
    }

    return sequence;
}

GSequence *getFrequencySequence(GSequence *word_sequence)
{
	GSequence *sequence;
	GSequenceIter *iter, *iter2;
	pair_t *pair;
	gchar *word, *word2;

	sequence = g_sequence_new(free_struct_pair);

	// GSequence iteration
	// Reference: https://lists.connman.net/pipermail/connman/2013-June/014534.html

	iter = g_sequence_get_begin_iter(word_sequence);
	while (g_sequence_iter_is_end(iter) == FALSE) {
		gboolean found = 0;
		word = g_sequence_get(iter);
		//DEBUG_PRINT("word: [%s]\n", word);

		// check word list
		iter2 = g_sequence_get_begin_iter(sequence);
		while (g_sequence_iter_is_end(iter2) == FALSE) {
			pair = g_sequence_get(iter2);
			word2 = pair->str;
			//DEBUG_PRINT("word2: [%s]\n", word2);
			// if word found, break
			if (g_strcmp0(word, word2) == 0) {
				found = 1;
				break;
			}
			iter2 = g_sequence_iter_next(iter2);
		}

		if (found) {	// if found, increase frequency
			//DEBUG_PRINT("found\n");
			++(pair->num);
		}
		else { // if not found, add word
			//DEBUG_PRINT("not found, added [%s]\n", word);
			pair = new_struct_pair(word, 1);
			g_sequence_append(sequence, pair);
		}

		iter = g_sequence_iter_next(iter);
	}

	g_sequence_sort(sequence, compare_struct_pair, NULL);

	// test code
#ifdef DEBUG
	iter = g_sequence_get_begin_iter(sequence);
	while (g_sequence_iter_is_end(iter) == FALSE) {
		pair = g_sequence_get(iter);
		printf("word: [%s] / num: [%d]\n", pair->str, pair->num);
		iter = g_sequence_iter_next(iter);
	}
#endif

	return sequence;
}

void printFrequencySequence(GSequence *sequence)
{
	GSequenceIter *iter;
	pair_t *pair;

	iter = g_sequence_get_begin_iter(sequence);
	while (g_sequence_iter_is_end(iter) == FALSE) {
		pair = g_sequence_get(iter);
		printf("word: [%s] / num: [%d]\n", pair->str, pair->num);
		iter = g_sequence_iter_next(iter);
	}
}

void process(gchar *file_name)
{
	GString *content;
	gchar **words;
	GSequence *word_sequence;
	GSequence *freq_sequence;

	DEBUG_PRINT("File Name: %s\n", file_name);

	// Read file content
	content = getContent(file_name);
	//DEBUG_PRINT("%s", content->str);
	DEBUG_PRINT("Get content completed.\n");

	// Split content to words
	words = g_strsplit(content->str, " ", 0);
	DEBUG_PRINT("Split content completed.\n");

	// Filter words and store to sequence
	word_sequence = getFilteredWordSequence(words);
	DEBUG_PRINT("Filter word completed.\n");

	// Create sorted frequency sequence from word sequence
	freq_sequence = getFrequencySequence(word_sequence);
	DEBUG_PRINT("Calculate freq completed.\n");

	// Print it!
	printFrequencySequence(freq_sequence);

	// Free resources
	g_sequence_free(freq_sequence);
	g_sequence_free(word_sequence);
	g_strfreev(words);
	g_string_free(content, TRUE);
}

/*****************************************************************************/
/* Main */
/*****************************************************************************/

gint main(gint argc, gchar *argv[])
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
