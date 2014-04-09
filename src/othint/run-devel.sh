#!/bin/sh
if [ "$TERM" == "xterm" ] || [ "$TERM" == "konsole" ] || ["$TERM" == "aterm" ]; then
  $TERM -e ./othint --complete-shell
elif ["$TERM" == "gnome-terminal "]; then
	$TERM -x ./othint --complete-shell
else
	if hash xterm 2>/dev/null; then
		xterm -e ./othint --complete-shell
	elif hash gnome-terminal 2>/dev/null; then
		gnome-terminal -x ./othint --complete-shell
	elif hash konsole 2>/dev/null; then
		konsole -e ./othint --complete-shell
	elif hash aterm 2>/dev/null; then
		aterm -e ./othint --complete-shell  # aterm has bad unicode support
	else
		./othint --complete-shell
	fi
fi
