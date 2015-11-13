. $OWN/env/updenv
. env.sh
. env_afl.sh
./AFL/UDF_CORE/tools/linuxScripts/udf_core_build.sh -t opt
./sys/src/AFL/UDF_CORE/dailyBuild/UDF_CORE_Install/executeInstall.sh opt MD1 02 copyAFLandTests
/home/i809989/SAPDevelop/AFL/git/env/updenv.sh 
/home/i809989/SAPDevelop/AFL/git/gen/opt/test/gmock/UDF_CORE/test_facade  --gtest_filter=ModParCfgBusinessFacadeImplUnitTest.*
DIR_EXECUTABLE=. AFL/UDF_CORE/madness/madness 2>&1 | tee ~/tmp/logs/madness.log
INSTALL_DIR=`grep HANA_ARCHIVE $OWN/sys/wrk/opt/log/preparing.vprj.x0 | awk -F'server' '{print $1}' | awk -F'= ' '{print $2}'`
LD_LIBRARY_PATH=/home/i809989/SAPDevelop/HDB/git/gen/opt:$LD_LIBRARY_PATH /home/i809989/SAPDevelop/HDB/git/gen/opt/test/gmock/UDF_CORE/test_facade --gtest_filter=*.missingOneRegular >test.log 2>&1
PYTHONPATH=/usr/sap/hdbclient/hdbcli:/usr/sap/hdbclient /usr/sap/hdbclient/Python/bin/python2.6 
alias ls='ls --color=never'
cat /etc/issue
cat /sapremote/production2/makeresults/HANA/info/pool_paths/import_path_for_linux64_gcc47 | sed s/sapmnt/sapremote/ > $OWN/HANA_POOL/import_path
cd $INSTALL_DIR
date "+%Y%m%d.%H%M%S"
date && echo ${RANDOM}
do tags
echo $SAP_RETRIEVAL_PATH
emacs -font 10x20 &
find_data_files.py /home/i809989/SAPDevelop/AFL/git/sys/src/nutest/testscripts/UDF_CORE/UDF_DDF_RD1/misc/createProxyLocations/forecast/testBasic
git apply --3way /home/i809989/SAPDevelop/AFL/git/sys/src/.git/rebase-apply/patch
git config --global --list
git diff origin/UDF_dev..HEAD
git difftool -t emerge HEAD multimodel-2 AFL/UDF_CORE/hana_content
git difftool -y
git difftool -y HEAD~1.. AFL/UDF_CORE
git fetch ssh://i809989@hdbgerrit.wdf.sap.corp:29418/afl refs/changes/17/316417/3 && git cherry-pick FETCH_HEAD
git log --first-parent 
git mergetool --tool=kdiff3
git stash show -p stash@{0} | grep diff | cut -d' ' -f 4 | sed -e 's|^b/||' > tarbean.sh
grep --word-regexp --files-with-matches SP_SR_MERGE_CONFIG_PAR *.procedure
hdbuserstore list
hpy ~/pystudio/pystudio.py
kdiff3 ~/hana_work/RD1_02_DAVISMIC/__empty__/sap/is/ddf/udf AFL/UDF_CORE/hana_content/RD1/sap/is/ddf/udf & 
kdiff3 ~/tmp/multimodel-2/AFL AFL
lg pc procedure-callers.sh
lg testtree "find /home/i809989/SAPDevelop/AFL/git/sys/src/nutest/testscripts/UDF_CORE/UDF_DDF_RD1 -type d | sed -e 's|/home/i809989/SAPDevelop/AFL/git/sys/src/nutest/testscripts/UDF_CORE/UDF_DDF_RD1/||' | grep -v /doc$ | grep -v /docs$ | grep -v /data_input$ | grep -v /data_ref$ | toTree.py"
procedure-callers.sh
python ~/bin/walknfix.py nutest/testscripts/UDF_CORE/UDF_{CORE,DDF}_RD1
sh $OWN/env/updenv.sh
sh -f afl_user_setup.sh
ssh -Y i809989@ld2411.wdf.sap.corp
ssh -Y i809989@lts.wdf.sap.corp
vncserver -kill :1
yes | git difftool -t kdiff3 -w HEAD~1..HEAD
~/tools/bin/procedure-callers.sh
#################   TIME IMMEMORIAL   ###############
bin/startvnc 
git branch --set-upstream mm-rename UDF_dev
git names | egrep ^\(AFL\)\|\(nutest\)/
git push gerrit HEAD:refs/changes/91/345691
git push gerrit HEAD:refs/for/UDF_dev
git rebase --skip
git status --porcelain --short
head -1 --quiet $(find . -name udf_mod_met.csv )
lg pytest 'su - md1adm -c "make -f /usr/sap/MD1/home/tests/Makefile install_RD1"'
nohup emacs -font 10x20 &
nohup xterm -font 10x20 &
source env_afl.sh
ssh -Y i809989@llbpal24
ssh -Y i809989@llbpal27
ssh lroot@llbpal24
su - md1adm
sudo ./hdbinst --configfile=/home/i809989/MD1.cfg
tar tvf ~/tmp/md1adm4.tgz 
#################   STOP HERE   ###############
git rb
git mergetool -y -t emerge
git rebase --continue
git status
git log
git names
b
lg
dedup
