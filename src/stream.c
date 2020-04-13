#include "stream.h"

struct yx_stream {
	void *data;

	yx_stream_writefunc_t *write;
	yx_stream_nextfunc_t *next;
	yx_stream_closefunc_t *close;
};

// File stream {{{
static int _file_write(const char *data, size_t len, void *fp) {
	return len - fwrite(data, 1, len, fp);
}

static int _file_next(void *fp) {
	return fgetc(fp);
}

static void _file_close(void *fp) {
	fclose(fp);
}

struct yx_stream *yx_file_stream(FILE *fp) {
	return yx_custom_stream(fp, _file_write, _file_next, _file_close);
}
// }}}

// String stream {{{
struct _string_stream {
	char *buf, *ptr;
	size_t len;
};

static int _string_write(const char *data, size_t len, void *data) {
	while (len > 0 && stream->ptr < stream->buf + stream->len) {
		*stream->ptr++ = data++;
		len--;
	}
	return len;
}

static int _string_next(void *data) {
	struct _string_stream *stream;
	if (stream->ptr >= stream->buf + stream->len) return EOF;
	return *stream->ptr++;
}

struct yx_stream *yx_string_istream(const char *buf, size_t len) {
	struct _string_stream *stream = malloc(sizeof *stream);
	if (!stream) return NULL;
	return yx_custom_stream(stream, NULL, _string_next, free);
}

struct yx_stream *yx_string_ostream(const char *buf, size_t len) {
	struct _string_stream *stream = malloc(sizeof *stream);
	if (!stream) return NULL;
	return yx_custom_stream(stream, _string_write, NULL, free);
}
// }}}

struct yx_stream *yx_custom_stream(void *data, char (*next)(void *data), void (*close)(void *data)) {
	yx_stream *stream = malloc(sizeof *stream);
	if (!stream) return NULL;

	stream->data = data;
	stream->next = next;
	stream->close = close;

	return stream;
}

int yx_stream_write(struct yx_stream *stream, const char *data, size_t len) {
	if (stream->write) return stream->write(data, len, stream->data);
	return len;
}

int yx_stream_next(struct yx_stream *stream) {
	if (stream->next) return stream->next(stream->data);
	return EOF;
}

void yx_stream_close(struct yx_stream *stream) {
	if (stream->close) stream->close(stream->data);
	free(stream);
}
