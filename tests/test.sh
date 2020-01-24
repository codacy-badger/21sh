export DIR_21SH=$PWD
export ls=ls
export arg=-a
export arg2=/
export 'loop=bonjour$loop'
./21sh tests/expansion > tests/exp.21sh 2>&1
bash tests/expansion > tests/exp.bash 2>&1


mkdir testing_dotdots
mkdir -p tricky_dots/1/2/3/4/5/6/7
mkdir -p test_cdpath1/1 test_cdpath1/2 test_cdpath2/1 test_cdpath2/3
mkdir -p test_cdpath1/var
export CDPATH=$PWD/test_cdpath1:$PWD/test_cdpath2

./21sh tests/cd > tests/cd.21sh 2>&1
bash tests/cd > tests/cd.bash 2>&1

rm -rf tricky_dots
rm -rf testing_dotdots
rm -rf test_cdpath1 test_cdpath2


./21sh tests/env > tests/env.21sh 2>&1
bash tests/env > tests/env.bash 2>&1


./21sh tests/setenv > tests/setenv.21sh 2>&1
tcsh tests/setenv > tests/setenv.bash 3>&1


./21sh tests/pipe > tests/pipe.21sh 2>&1
bash tests/pipe > tests/pipe.bash 2>&1

./21sh tests/redir > tests/redir.21sh 2>&1
bash tests/redir > tests/redir.bash 2>&1

./21sh tests/quotes > tests/quotes.21sh 2>&1
bash tests/quotes > tests/quotes.bash 2>&1

./21sh tests/heredoc > tests/heredoc.21sh 2>&1
bash tests/heredoc > tests/heredoc.bash 2>&1


if [[ "$OSTYPE" == "darwin"* ]]; then
	sed -i '' -E  's/.*:.*: (.*:)/21sh: \1/g' tests/*.bash
	sed -i '' -E "s/(.+)\/$/\1/g" tests/cd.21sh #remove / at the end of line for $PWD
	sed -i '' -E "/TERMINFO=/d" tests/env.21sh tests/env.bash
	sed -i '' -E "/_=/d" tests/env.21sh tests/env.bash
	sed -i '' -E "s/21sh:(.*): command not found/env:\1: No such file or directory/g" tests/env.21sh
	sed -i '' -E "/_=|HOSTTYPE=|VENDOR=|OSTYPE=|MACHTYPE=|GROUP=|HOST=/d" tests/setenv.bash
	sed -i '' -E "/_=/d" tests/setenv.21sh
	sed -i '' -E "s/\/var\/root\/log: Permission denied/Could not open file/g" tests/pipe.bash
	sed -i '' -E "s/\/bin\/ls:/ls:/g" tests/redir.21sh
	sed -i '' -E "s/21sh: .*: Bad file descriptor/21sh: Bad file descriptor/g" tests/redir.bash
	sed -i '' -E "s/21sh: .*: No such file or directory/21sh: Could not open file/g" tests/redir.bash
else
	sed -i -E  's/.*:.*: (.*:)/21sh: \1/g' tests/*.bash
	sed -i -E "s/(.+)\/$/\1/g" tests/cd.21sh #remove / at the end of line for $PWD
	sed -i -E "/TERMINFO=/d" tests/env.21sh tests/env.bash
	sed -i -E "/_=/d" tests/env.21sh tests/env.bash
	sed -i -E "s/21sh:(.*): command not found/env:\1: No such file or directory/g" tests/env.21sh
	sed -i -E "s/‘//g" tests/env.bash
	sed -i -E "s/’//g" tests/env.bash
	sed -i -E "/_=|HOSTTYPE=|VENDOR=|OSTYPE=|MACHTYPE=|GROUP=|HOST=/d" tests/setenv.bash
	sed -i -E "/_=|HOSTTYPE=/d" tests/setenv.21sh
	sed -i -E "s/norights: Permission denied/Could not open file/g" tests/pipe.bash
	sed -i -E "s/\/bin\/ls/ls/g" tests/redir.21sh
	sed -i -E "s/21sh: .*: Bad file descriptor/21sh: Bad file descriptor/g" tests/redir.bash
	sed -i -E "s/21sh: .*: No such file or directory/21sh: Could not open file/g" tests/redir.bash
fi


mkdir -p tests/bash tests/21sh

for file in tests/*.21sh
do
	name=$(basename $(echo $file | cut -d '.' -f 1))
	csplit --silent --suppress-matched "$file" '/~~~/' '{*}'\
		--prefix "tests/21sh/$name "
done
for file in tests/*.bash
do
	name=$(basename $(echo $file | cut -d '.' -f 1))
	csplit --silent --suppress-matched "$file" '/~~~/' '{*}'\
		--prefix "tests/bash/$name "
done

for file in tests/bash/*
do
	file=`basename "$file"`
	if diff -u -U 10 "tests/21sh/$file" "tests/bash/$file"; then
		echo "$file" ✔️
	else
		echo "$file" ❌
	fi
done

rm -rf tests/*21sh tests/*bash
