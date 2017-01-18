#include <stdio.h>
#include <math.h>
#include <alsa/asoundlib.h>

#include "util.h"
#include "buffer.h"

#define VOL_ICON_HIGH "\uE050"
#define VOL_ICON_MEDIUM "\uE04D"
#define VOL_ICON_LOW "\uE04E"
#define VOL_ICON_MUTE "\uE04F"

void
vol (buffer_t *buf) {
	long current = 0, min, max;
	long double percent = NAN;
	char *icon;

	snd_mixer_t *mp;
	snd_mixer_selem_id_t *id;
	snd_mixer_elem_t *elem;


	snd_mixer_selem_id_malloc(&id);

	snd_mixer_selem_id_set_index(id, 0);
	snd_mixer_selem_id_set_name(id, "Master");

	if (snd_mixer_open(&mp, 0) == 0) {
		if (snd_mixer_attach(mp, "default") != 0) {
			goto EXIT;
		}

		if (snd_mixer_selem_register(mp, NULL, NULL) != 0) {
			goto EXIT;
		}

		if (snd_mixer_load(mp) != 0) {
			goto EXIT;
		}
		
		if ((elem = snd_mixer_find_selem(mp, id)) == NULL) {
			goto EXIT;
		}

		snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

		// average channel volumes lol
		int i;
		long v;
		for (i = 0; ; i++) {
			if (snd_mixer_selem_has_playback_channel(elem, i) == 0) {
				break;
			}
			if (snd_mixer_selem_get_playback_volume(elem, i, &v)) {
				goto EXIT;
			}
			current += v;
		}
		current /= i;

		percent = round(((double)(current - min) / (max - min)) * 100);
	} else {
		fprintf(stderr, "could not open mixer\n");
	}
EXIT:
	snd_mixer_selem_id_free(id);
	snd_mixer_close(mp);

	// which icon
	if (percent >= 75) {
		icon = VOL_ICON_HIGH;

	} else if (percent < 75 && percent > 25) {
		icon = VOL_ICON_MEDIUM;

	} else if (percent <= 25 && percent > 0) {
		icon = VOL_ICON_LOW;

	} else {
		icon = VOL_ICON_MUTE;
	}

	buffer_printf(buf, " %s %02.0Lf%% ", icon, percent);

}
