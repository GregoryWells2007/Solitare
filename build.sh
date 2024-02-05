#!/bin/bash

# a little build script for my solitare game
# i've wanted to lean bash for a little while so i tought this was the best way
# I know there are so many better ways to do what I am doing but this doesn't need too many functions so I should be good

# how is a function laid out
# name $1 = if they are running it or asking for help on how it works [ "RUN", "USAGE" ] $2.... are the other params


# if there are no arguments just prompt the user to ask for help
if [ $# = '0' ]; then
    echo 'Use --help for help'
fi

# define the help function there are only 2 functions currently help and usage
function help_function {
    if [ $1 = "RUN" ]; then
        echo "usage ./build.sh [OPTIONS]";
        echo "Options: ";
        echo "  --help, -h                 for getting help"
        echo "  --usage, -u [COMMAND]      shows how a commans if run"
        echo "  --clean, -c                cleans the whole project"
    elif [ $1 = "USAGE" ]; then
        echo "./build.sh --help"
    else
        echo "This is a me error just ask me what $1 is doing here"
    fi
}

# just print out commands and error codes
function command_error {
    echo "command $1 failed because $2"
}

# if a command is unknown
function command_not_known {
    echo "command $1 not known"; 
    echo "run --help for commands";
}

# cleans the whole project
function clean_project {
    if [ $1 = "RUN" ]; then
        rm -rf "build/"
        mkdir "build"
    else 
        echo "./build.sh --clean";
    fi
}

# how a command is used function
function command_usage {
    if [ $1 = "RUN" ]; then
        if [ $2 = "--help" ]; then
            help_function "USAGE";
        elif [ $2 = "-h" ]; then
            help_function "USAGE";
        fi;

        if [ $2 = "--usage" ]; then
            command_usage "USAGE";
        elif [ $2 = "-u" ]; then
            command_usage "USAGE";
        fi;

        if [ $2 = "--clean" ]; then
            clean_project "USAGE";
        elif [ $2 = "-c" ]; then
            clean_project "USAGE";
        fi;

    else 
        echo "./build.sh --usage [COMMAND]";
    fi
}

# get all the inputs in an array so they are easier to work with
inputs=();
for var in $@;
do
    inputs+=($var);
done;

# loop through everything
for ((i=0; i<$#; i++));
do  
    var=${inputs[$i]};

    if [ "${var:0:2}" = "--" ]; then
        command=${var:2}
        if [ $command = "help" ]; then
            help_function "RUN";
        elif [ $command = "usage" ]; then
            i=$((i+1));

            if [ $i = $# ]; then
                command_error "--usage" "no input provided";
            else
                command_usage "RUN" ${inputs[$i]};
            fi
        elif [ $command = "clean" ]; then
            clean_project "RUN";
        else
            command_not_known $var;
        fi
    elif [ "${var:0:1}" == "-" ]; then
        command=${var:1:2};
        if [ $command = "h" ]; then
            help_function "RUN";
        elif [ $command = "u" ]; then
            i=$((i+1));

            if [ $i = $# ]; then
                command_error "-u" "no input provided";
            else
                command_usage "RUN" ${inputs[$i]};
            fi
        elif [ $command = "c" ]; then
            clean_project "RUN";
        else
            command_not_known $var;
        fi
    fi
done
