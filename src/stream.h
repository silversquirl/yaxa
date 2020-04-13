#ifndef YAXA_STREAM_H
#define YAXA_STREAM_H

struct yx_stream; 

// Returns number of characters unable to be written (len - written_chars)
typedef int (yx_stream_writefunc_t)(const char *data, size_t len, void *data);
// Returns a character or EOF
typedef int (yx_stream_nextfunc_t)(void *data);
typedef void (yx_stream_closefunc_t)(void *data);

struct yx_stream *yx_file_stream(FILE *fp);
struct yx_stream *yx_string_stream(const char *buf, size_t len);
struct yx_stream *yx_custom_stream(void *data, yx_stream_writefunc_t *write, yx_stream_nextfunc_t *next, yx_stream_closefunc_t *close);

int yx_stream_write(struct yx_stream *stream, const char *data, size_t len);
int yx_stream_next(struct yx_stream *stream);
void yx_stream_close(struct yx_stream *stream);

#endif
