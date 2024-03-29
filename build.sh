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
        echo "  --delete, -d [PROJECT]     deletes the specified project"
        echo "  --build -b                 builds the whole project"; 
        echo ""
        echo "Utils: "
        echo "  --run -r                runs the project when the build is finished"
        echo "  --run-last              runs the last build that was successful"
        echo "  --test-project          tests the project with specified tests"
        echo "  --run-test -t [TEST]    runs one specified test"
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

# deletes a specified project
function delete_project {
    if [ $1 == "RUN" ]; then
        echo "PLEASE WRITE THIS FUNCTION - ME (delete_project)"
    else
        echo "./build.sh --delete [PROJECT]"
    fi
}

# builds the whole project
function build_project {
    if [ $1 == "RUN" ]; then
        cd build
        make
        cd ../
    else
        echo "./build.sh --build"
    fi
}

# runs the project
function run_project {
    if [ $1 == "RUN" ]; then
        cd build
        ./Solitare
    else
        echo "./build.sh --run"
    fi
}

#runs the last with a successful build
function run_last_build {
    if [ $1 == "RUN" ]; then
        cd build
        ./Solitare
    else
        echo "./build.sh --run-last"
    fi
}

# runs all the tests on the project
function test_project {
    if [ $1 == "RUN" ]; then
        echo "PLEASE WRITE THIS FUNCTION - ME (test_project)"
    else
        echo "./build.sh --test-project"
    fi
}

# runs the project
function run_project_test {
    if [ $1 == "RUN" ]; then
        echo "PLEASE WRITE THIS FUNCTION - ME (run_project_test)"
    else
        echo "./build.sh --run-test [PROJECT]"
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

        if [ $2 = "--delete" ]; then
            delete_project "USAGE";
        elif [ $2 = "-d" ]; then
            delete_project "USAGE";
        fi;

        if [ $2 = "--build" ]; then
            build_project "USAGE";
        elif [ $2 = "-b" ]; then
            build_project "USAGE";
        fi;



        if [ $2 = "--run" ]; then
            run_project "USAGE";
        elif [ $2 = "-r" ]; then
            run_project "USAGE";
        fi;

        if [ $2 = "--run-last" ]; then
            run_last_build "USAGE";
        fi;

        if [ $2 = "--test-project" ]; then
            test_project "USAGE";
        fi;

        if [ $2 = "--run-test" ]; then
            run_project_test "USAGE";
        elif [ $2 = "-t" ]; then
            run_project_test "USAGE";
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

built_project=false;

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
                command_error "--usage" "no command provided";
            else
                command_usage "RUN" ${inputs[$i]};
            fi
        elif [ $command = "clean" ]; then
            clean_project "RUN";
        elif [ $command = "delete" ]; then

            i=$((i+1));

            if [ $i = $# ]; then
                command_error "--delete" "no project provided (did you mean to run --clean)";
            else
                delete_project "RUN" ${inputs[$i]};
            fi
        elif [ $command = "build" ]; then
            build_project "RUN";
            built_project=true;
        elif [ $command = "run" ]; then
            if [ $built_project = false ]; then
                command_error "--run" "--build or -b not called"
            else
                run_project "RUN";
            fi
        elif [ $command = "run-last" ]; then
            run_last_build "RUN";
        elif [ $command = "test-project" ]; then
            test_project "RUN";
        elif [ $command = "run-test" ]; then
            i=$((i+1));

            if [ $i = $# ]; then
                command_error "--run-test" "no test provided (did you mean to run --test-project)";
            else
                test_project "RUN" ${inputs[$i]};
            fi
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
        elif [ $command = "d" ]; then

            i=$((i+1));

            if [ $i = $# ]; then
                command_error "-d" "no project provided (did you mean to run -c)";
            else
                delete_project "RUN" ${inputs[$i]};
            fi
        elif [ $command = "b" ]; then
            build_project "RUN";
            built_project=true;
        elif [ $command = "r" ]; then
            if [ $built_project = false ]; then
                command_error "-r" "--build or -b not called"
            else
                run_project "RUN";
            fi
        elif [ $command = "t" ]; then
            i=$((i+1));

            if [ $i = $# ]; then
                command_error "-t" "no test provided (did you mean to run --test-project)";
            else
                test_project "RUN" ${inputs[$i]};
            fi
        else
            command_not_known $var;
        fi
    fi
done
