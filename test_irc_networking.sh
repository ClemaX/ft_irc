#!/usr/bin/sh

# Export 'IRC=server_executable' to overwrite TARGET_IRC
# Export 'IRC_ARGS=server_args' to overwrite TARGET_IRC_ARGS
# Export 'IRC_CLIENT' and 'CLIENT_ARGS' to overwrite CLIENT

# NOTE: Don't forget the client will be runned in backgound
#	that means tty input could stop the process.
#	USE: "--no-shutdown" on ncat or "-d" on netcat.

TARGET_IRC=${IRC:-ircserv}
TARGET_IRC_ARGS=${IRC_ARGS:-}
CLIENT=${IRC_CLIENT:-ncat}
CLIENT_BASENAME=${CLIENT}
CLIENT_ARGS=${IRC_CLIENT_ARGS:---crlf --no-shutdown 127.0.0.1 6666}
CLIENT+=" ${CLIENT_ARGS[@]}"

# Colors

COLOR_ORANGE='\033[0;33m'
PURPLE_COLOR='\033[0;35m'
NO_COLOR='\033[0m'
PREFIX="${COLOR_ORANGE}[TEST NETWORKING]${NO_COLOR}" #Should be scaped

trap 'bg $TEST' `kill -l TSTP`

function background_client_exec_cmd
{
	# $1 is the target PID, others args are ignored

	# Timeout that should send a SIGTSTP went the client is on the foreground
	#	it should stop the client.
	sleep 2 && kill -TSTP $$ && echo "[Debug] kill $$" & > /dev/null 2>&1
	# NOTE: Currently i kill $$ not $1 (testing stuff)
	CHILD=$!

	echo "[Debug] jobs -rp before:"
	jobs -rp

	# Pass the client to the

	wait $1
	echo -e "$PREFIX ${PURPLE_COLOR} Foreground: ${1}${NO_COLOR}"

	# TO DO: Execute something in the client to test if the server still working
	echo "[Debug] jobs -rp after:"
	jobs -rp

	# Resume the client in the background (like it was before fg)
	TEST=$1
	bg $1
	echo -e "$PREFIX ${PURPLE_COLOR} Backgound: ${1}${NO_COLOR}"
}

# Enable job control
set -m

# TEST1: Kill a client a check if the server still operational

# Launch the server and store it pid
./$TARGET_IRC ${TARGET_IRC_ARGS[@]} &
echo -e "$PREFIX ${PURPLE_COLOR}Launching $TARGET_IRC ${TARGET_IRC_ARGS[@]} ...${NO_COLOR}"
sleep 3

# Connected 5 client to the server and store their pid
INDEX=0
while [ $INDEX -lt 5 ] ; do
	${CLIENT[@]} &
	CLIENTS_PIDS[$INDEX]=$!
	echo -e "$PREFIX ${PURPLE_COLOR}New client invoked ! (pid=${CLIENTS_PIDS[$INDEX]})${NO_COLOR}"
	sleep 1
	let INDEX++
done

# Kill 3 clients
kill -INT ${CLIENTS_PIDS[1]} ${CLIENTS_PIDS[2]} ${CLIENTS_PIDS[4]}
echo -e "$PREFIX ${PURPLE_COLOR}kill -INT ${CLIENTS_PIDS[1]} ${CLIENTS_PIDS[2]} ${CLIENTS_PIDS[4]}${NO_COLOR}"

# Test a remaining client
background_client_exec_cmd ${CLIENTS_PIDS[0]}
background_client_exec_cmd ${CLIENTS_PIDS[3]}

# Stop the server & $0's childs
wait $CHILD && killall $TARGET_IRC $CLIENT_BASENAME
