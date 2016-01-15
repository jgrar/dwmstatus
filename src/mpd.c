#include "buffer.h"
#include "util.h"

#include <mpd/client.h>

#ifndef MPD_HOST
# define MPD_HOST "localhost"
#endif

#ifndef MPD_PORT
# define MPD_PORT 6600
#endif

#define PROGRESS_SIZE 16
#define PROGRESS_START " \x03"
#define PROGRESS_END "\x02 "
#define PROGRESS_S1 "—"
#define PROGRESS_S2 PROGRESS_S1
#define PROGRESS_SEP "\x01"

#define MPD_ICON_PLAY "\uE037"
#define MPD_ICON_PAUSE "\uE034"
#define MPD_ICON_STOP "\uE047"

void
mpd_status (buffer_t *buf) {

	struct mpd_connection *conn = mpd_connection_new(MPD_HOST, MPD_PORT, 1000);

	if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
		fprintf(stderr, "could not connect to mpd host: %s\n",
			mpd_connection_get_error_message(conn));
		// TODO: write some error indicator to the status buffer
		goto END3;
	}

	struct mpd_status *status = mpd_run_status(conn);

	if (!status) {
		fprintf(stderr, "could not get mpd status: %s\n",
			mpd_status_get_error(status));
		goto END2;
	}

	struct mpd_song *song = mpd_run_current_song(conn);

	if (!song) {
		fprintf(stderr, "error fetching song\n");
		goto END2;
	}

	enum mpd_state state = mpd_status_get_state(status);

	if (state == MPD_STATE_STOP) {
		buffer_printf(buf, " %s ", MPD_ICON_STOP);
		goto END;
	} else if (state == MPD_STATE_PAUSE) {
		buffer_printf(buf, " %s ", MPD_ICON_PAUSE);
	} else if (state != MPD_STATE_UNKNOWN) {
		buffer_printf(buf, " %s ", MPD_ICON_PLAY);
	} else {
		fprintf(stderr, "don't like this mpd status");
		goto END;
	}

	//TODO: fallback to filename
	const char *artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
	const char *title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);

	buffer_printf(buf, " %s - %s ", artist, title);

	unsigned elapsed = mpd_status_get_elapsed_time(status);
	unsigned total = mpd_status_get_total_time(status);

	size_t percent = ((double)elapsed / total) * 100;

	progress(buf, PROGRESS_SIZE, percent,
		PROGRESS_START, PROGRESS_END,
		PROGRESS_S1, PROGRESS_S2, PROGRESS_SEP
	);

END:
	mpd_song_free(song);
END2:
	mpd_status_free(status);
END3:
	mpd_connection_free(conn);
}
