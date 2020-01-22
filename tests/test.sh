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


sed -i "" -E  "s/.*:.*: (.*:)/21sh: \1/g" tests/*.bash
sed -i "" -E "s/(.+)\/$/\1/g" tests/cd.21sh #remove / at the end of line for $PWD
diff -u tests/exp.21sh tests/exp.bash && echo "Expansions: success"
diff -u tests/cd.21sh tests/cd.bash && echo "cd: success"

