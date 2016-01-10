#!/bin/sh

DELAY=1

# Icons:
PLAYING="\\\\uE037"
PAUSED="\\\\uE034"

STOPPED="\\\\uE047"

VOL_MED="\uE04D"
VOL_LOW="\uE04E"
VOL_MUTE="\uE04F"
VOL_HIGH="\uE050"

# E162
# E068
CPU="\uE30D"

MEM="\uE322"

CLOCK="\uE192"
################

# BUG: at ~0% progress bar displays full
mpdstatus() {
	v=$(mpc -f "[[%artist%] - %title%]|[%file%]" | awk '
		NR == 1 {
			current = $0
		}
		NR == 2 {
			gsub(/[\[(\])]/, "")

			state = $1
			progress = $4
		}
		END {
			if (NR == 1) {
				print "'$STOPPED'"
				exit
			}

			if (state == "playing")
				state = "'$PLAYING'"
			else if (state == "paused") 
				state = "'$PAUSED'"

			if (progress == "0%")
				progress = "1%"

			"SIZE=16 CHAR1=\"—\" CHAR2=\"—\" SEP=\"\x02\" START=\"\x03\" END=\"\x02\" mkb "progress | getline
			progress = $0
			print state, current, progress
		}
	')
	printf %b "$v"
}

vol() {
	v=$(pa-volume | tr -d '%')
	sym=

	if [ $v -eq 0 ]
	then
		sym=$VOL_MUTE

	elif [ $v -lt 30 ]
	then
		sym=$VOL_LOW

	elif [ $v -lt 60 ]
	then
		sym=$VOL_MED

	else
		sym=$VOL_HIGH

	fi

	printf %b "$sym $v%"
}

# cpu usage adapted from
# https://bbs.archlinux.org/viewtopic.php?pid=874333#p874333 and
# http://stackoverflow.com/a/23376195
#previdle=0
#prevtotal=0
cpu() {
	#read id user nice system idle iowait irq softirq steal rest < /proc/stat

	#previdle=$((idle + iowait))
	#prevnonidle=$((user + nice + system + irq + softirq + steal))

	#prevtotal=$((previdle + prevnonidle))

	#sleep 1

	read id user nice system idle iowait irq softirq steal rest < /proc/stat

	idle=$((idle + iowait))
	nonidle=$((user + nice + system + irq + softirq + steal))

	total=$((idle + nonidle))

	if [ "$previdle" -a "$prevtotal" ]
	then
		totald=$((total - prevtotal))
		idled=$((idle - previdle))

		v=$(echo "scale=8;($totald - $idled) / $totald * 100" | bc -qs ) #| sed 's/\..*$//')
	fi

	previdle=$idle
	prevtotal=$total

	#echo $v >&2
	#echo $previdle $prevtotal >&2

	#if [ "$previdle" -a "$prevtotal" ]
	#then
		#v=$(( 
		#	100 * (
		#		(total - prevtotal) - (idle - previdle)
		#	) /
		#	(total - prevtotal)
		#))
		#v="$(echo "scale=8;((($total - $prevtotal) - ($idle - $previdle)) / ($total - $prevtotal)) * 100" | bc -q)"
		#echo $total $idle $previdle $prevtotal >&2
		#echo "scale=8;(($total - $prevtotal) - ($idle - $previdle)) / ($total - $prevtotal) * 100" >&2
	#else
	#	v=0
	#fi


	#previdle=$idle
	#prevtotal=$total

	#echo $idle $total >&2

	#export previdle=$idle prevtotal=$total

	printf %b "$CPU" 
	printf " %02d%%" $v 2> /dev/null
}

cpu > /dev/null

# adapted from procps-ng proc/sysinfo.c:715..717
# proc/sysinfo.c:715:  mem_used = kb_main_total - kb_main_free - kb_main_cached - kb_main_buffers;
# proc/sysinfo.c:716:  if (mem_used < 0)
# proc/sysinfo.c:717:    mem_used = kb_main_total - kb_main_free;
# Note: this value is what free(1) prints
mem() {
	v="$(awk '
		/^MemTotal:/ { total = $2 }
		/^MemFree:/  { free = $2 }
		/^Cached:/   { cached = $2 }
		/^Buffers:/  { buffers = $2 }
		END {
			used = total - free - cached - buffers
			if (used < 0)
				used = total - free
			print (used / total) * 100
		}
	' < /proc/meminfo | sed 's/\..*$//')"

	#printf %b "\uF15B $v%"
	printf %b "$MEM $v%"

}

clock() {
	printf %b "$CLOCK $(date +"%a %d %b %R")"
}

while true
do
	xsetroot -name "$(printf %b "\x02")$(mpdstatus) $(vol)  $(mem)  $(cpu)  $(clock)"
	sleep $DELAY
done
