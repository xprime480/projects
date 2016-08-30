#!/bin/bash
testPackInstallerDir=$(cat $SRC/build/Optimized/imports/hana_pool | awk '{print $1 "/__installer.HDB"}')
sudo -S $testPackInstallerDir/hdbuninst --keep_user_home_dir --keep_user --sid=MD1 --batch  < $HOME/.spw
echo "Old HDB Instance uninstalled"
#sudo $testPackInstallerDir/hdbinst -nostart
##sudo $testPackInstallerDir/hdbinst -s MD1 -p md1admpw --system_user_password=manager --import_content=off --nostart -b 
sudo -S $testPackInstallerDir/hdbinst -nostart --configfile=$HOME/MD1.cfg --batch < $HOME/.spw
echo "HDB Instance installed"
exit
