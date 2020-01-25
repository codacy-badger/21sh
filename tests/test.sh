#!/bin/bash

#this script needs GNU csplit to work on macOS, run
#brew install coreutils
#to install it

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [[ "$OSTYPE" == "darwin"* ]]; then
	CSPLIT=gcsplit
else
	CSPLIT=csplit
fi

export DIR_21SH=$PWD
export ls=ls
export arg=-a
export arg2=/
export "loop=bonjour\$loop"
./21sh $DIR/expansion > $DIR/exp.21sh 2>&1
bash $DIR/expansion > $DIR/exp.bash 2>&1


mkdir testing_dotdots
mkdir -p tricky_dots/1/2/3/4/5/6/7
mkdir -p test_cdpath1/1 test_cdpath1/2 test_cdpath2/1 test_cdpath2/3
mkdir -p test_cdpath1/var
export CDPATH=$PWD/test_cdpath1:$PWD/test_cdpath2

./21sh $DIR/cd > $DIR/cd.21sh 2>&1
bash $DIR/cd > $DIR/cd.bash 2>&1

rm -rf tricky_dots
rm -rf testing_dotdots
rm -rf test_cdpath1 test_cdpath2


./21sh $DIR/env > $DIR/env.21sh 2>&1
bash $DIR/env > $DIR/env.bash 2>&1


./21sh $DIR/setenv > $DIR/setenv.21sh 2>&1
tcsh $DIR/setenv > $DIR/setenv.bash 3>&1


./21sh $DIR/pipe > $DIR/pipe.21sh 2>&1
bash $DIR/pipe > $DIR/pipe.bash 2>&1

./21sh $DIR/redir > $DIR/redir.21sh 2>&1
bash $DIR/redir > $DIR/redir.bash 2>&1

./21sh $DIR/quotes > $DIR/quotes.21sh 2>&1
bash $DIR/quotes > $DIR/quotes.bash 2>&1

./21sh $DIR/heredoc > $DIR/heredoc.21sh 2>&1
bash $DIR/heredoc > $DIR/heredoc.bash 2>&1


if [[ "$OSTYPE" == "darwin"* ]]; then
	sed -i '' -E  's/.*:.*: (.*:)/21sh: \1/g' $DIR/*.bash
	sed -i '' -E "s/(.+)\/$/\1/g" $DIR/cd.21sh #remove / at the end of line for $PWD
	sed -i '' -E "/TERMINFO=/d" $DIR/env.21sh $DIR/env.bash
	sed -i '' -E "/_=/d" $DIR/env.21sh $DIR/env.bash
	sed -i '' -E "s/21sh:(.*): command not found/env:\1: No such file or directory/g" $DIR/env.21sh
	sed -i '' -E "/_=|HOSTTYPE=|VENDOR=|OSTYPE=|MACHTYPE=|GROUP=|HOST=/d" $DIR/setenv.bash
	sed -i '' -E "/_=/d" $DIR/setenv.21sh
	sed -i '' -E "s/norights: Permission denied/Could not open file/g" $DIR/pipe.bash
	sed -i '' -E "s/21sh: .*: Bad file descriptor/21sh: Bad file descriptor/g" $DIR/redir.bash
	sed -i '' -E "s/21sh: .*: No such file or directory/21sh: Could not open file/g" $DIR/redir.bash
else
	sed -i -E  's/.*:.*: (.*:)/21sh: \1/g' $DIR/*.bash
	sed -i -E "s/(.+)\/$/\1/g" $DIR/cd.21sh #remove / at the end of line for $PWD
	sed -i -E "/TERMINFO=/d" $DIR/env.21sh $DIR/env.bash
	sed -i -E "/_=/d" $DIR/env.21sh $DIR/env.bash
	sed -i -E "s/21sh:(.*): command not found/env:\1: No such file or directory/g" $DIR/env.21sh
	sed -i -E "s/‘//g" $DIR/env.bash
	sed -i -E "s/’//g" $DIR/env.bash
	sed -i -E "/_=|HOSTTYPE=|VENDOR=|OSTYPE=|MACHTYPE=|GROUP=|HOST=/d" $DIR/setenv.bash
	sed -i -E "/_=|HOSTTYPE=/d" $DIR/setenv.21sh
	sed -i -E "s/norights: Permission denied/Could not open file/g" $DIR/pipe.bash
	sed -i -E "s/21sh: .*: Bad file descriptor/21sh: Bad file descriptor/g" $DIR/redir.bash
	sed -i -E "s/21sh: .*: No such file or directory/21sh: Could not open file/g" $DIR/redir.bash
fi


mkdir -p $DIR/bash $DIR/21sh

for file in $DIR/*.21sh
do
	name="$(basename "$(echo "$file" | cut -d '.' -f 1)")"
	$CSPLIT --silent --suppress-matched "$file" '/~~~/' '{*}'\
		--prefix "$DIR/21sh/$name "
done
for file in $DIR/*.bash
do
	name="$(basename "$(echo "$file" | cut -d '.' -f 1)")"
	$CSPLIT --silent --suppress-matched "$file" '/~~~/' '{*}'\
		--prefix "$DIR/bash/$name "
done

for file in $DIR/bash/*
do
	file="$(basename "$file")"
	if diff -u -U 10 "$DIR/21sh/$file" "$DIR/bash/$file"; then
		echo "$file" ✅
	else
		echo "$file" ❌
	fi
done

rm -rf $DIR/*21sh $DIR/*bash
