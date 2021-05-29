#!/usr/bin/sh

# This global vars can be exported for test launcher script
ENTRY_POINT="src/irc/commands"
TEST_DIR="tests"
TEST_DEFINITION_FILE="0"
TEST_ANSWER_FILE="1"

# Colors

COLOR_RED='\033[0;31m'
NO_COLOR='\033[0m'

function build_test_files
{
	# $1 The dirrectory where the commands definion is located
	# $2 to $+inf are ignored

	for cmds in ${1}/*/*.cpp ; do
		local BASENAME=`basename ${cmds%.*}`
		local DIR_TEST_NAME=${TEST_DIR}/${BASENAME@L}
		mkdir -p $DIR_TEST_NAME
		touch ${DIR_TEST_NAME}/{$TEST_DEFINITION_FILE,$TEST_ANSWER_FILE}
	done
}

function help_or_reset
{
	# if $1 == "reset" user can rm $TEST_DIR
	# if $1 != "reset" help is displayed

	if [ "${1}" != "reset" ] && [ "${1}" != "-reset" ] \
	&& [ "${1}" != "--reset" ] ; then # TO DO: Can do better this if
		echo "USAGE: ${0} [ reset | -reset | --reset ]" # TO DO: Color this
	elif [ -d $TEST_DIR ] ; then
		local ANSWER
		read -p "Do you want to delete $TEST_DIR ? [y/n]" -n1 -rs ANSWER
		echo
		if [[ $ANSWER =~ ^[Yy]$ ]] ; then
			echo -e "${COLOR_RED}rm -rf ${TEST_DIR}${NO_COLOR}"
			rm -rf ${TEST_DIR}
		fi
	else
		echo "Nothing to reset."
	fi
	exit 0
}

function is_this_test_needed
{
	# $1 must be a function name using this format: <gen_><command><_test>
	# Return 0 if the command is implemented
	# If not return 1

	local TESTNAME=${1:4}
	CURR_COMMAND=${TESTNAME%_*}

	if [ -d ${TEST_DIR}/${CURR_COMMAND} ] ; then
		return 0
	fi
	return 1
}

# Unitary tests

function gen_admin_test # Check if admin command exist, then call
{
	is_this_test_needed ${FUNCNAME[0]}
	if [ $? != 0 ] ; then
		return 0
	fi

	local DEST=${TEST_DIR}/${CURR_COMMAND}/${TEST_DEFINITION_FILE}

	cat <<- EOF > ${DEST}
		this
		is
		a
		test
	EOF

}

function gen_invite_test # Check if invite command exist, then call
{
	is_this_test_needed ${FUNCNAME[0]}
	if [ $? != 0 ] ; then
		return 0
	fi

	local DEST=${TEST_DIR}/${CURR_COMMAND}/${TEST_DEFINITION_FILE}

	cat <<- EOF > ${DEST}
		this
		is
		a
		another
		test
		that
		show
		if
		i
		though
		well
	EOF
}

function init_test_files
{
	# Just a readable solution to init each test

	gen_admin_test
	gen_invite_test
}

if [ $# -gt 0 ] ; then
	help_or_reset ${1}
fi

# Just copy paste each test function body and overide heredocs

build_test_files $ENTRY_POINT
init_test_files
