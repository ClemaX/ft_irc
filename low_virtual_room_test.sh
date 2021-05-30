#!/usr/bin/sh

# $1 Executable name
# $N (1 < N < +inf) executable arguments

# Lauch the executable many times, reducing the avalaible virtual memory room
#	each time. Used to stress heap related functions and check executable
#	heap error handling.

LOGGER="virt_test_logger"

function usage
{
	echo "USAGE: $0 target_exec [target_arg1 ...]"
}

function parse_args
{
	if [ -z $1 ] ; then
		usage
		exit 1
	elif [ ! -f $1 ] || [ ! -x $1 ] ; then
		echo "Cannot execute ./${1}"
		exit 1
	fi

	EXEC=$1
	shift
	ARGS=$@
}

function reset_logger
{
	local ANSWER
	read -p "You want to delete the logger: ${LOGGER} ? [y/n]" -n1 -rs ANSWER
	echo
	if [[ ${ANSWER} =~ ^[Yy]$ ]] ; then
		echo -e "rm -rf $LOGGER"
		rm $LOGGER
	fi
}

function test_virtual_room
{
	local VIRTUAL_ROOM=1000000
	while [ $VIRTUAL_ROOM -ge 100 ] ; do
		# Limit avalaible virtual memory room
		ulimit -v $VIRTUAL_ROOM
		echo "CURRENT MAX VIRTUAL ROOM: $VIRTUAL_ROOM"
		# Launch executable in background
		./${EXEC} ${ARGS} &
		# Wait a bit
		sleep 3
		# Kill it and repeat
		killall $EXEC
		let VIRTUAL_ROOM/=10
	done > $LOGGER 2>&1
}

touch $LOGGER

parse_args $@
test_virtual_room
reset_logger
