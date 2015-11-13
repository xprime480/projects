me=`basename $0`

TARGET=/home/$USER/SAPDevelop/AFL/git

print_msg()
{
  echo "$me: $1"
}

update_import_path()
{
  print_msg "Updating import path..."

  mkdir -p $TARGET/HANA_POOL || exit 1
  
  sed s/sapmnt/sapremote/g /sapremote/production2/makeresults/HANA/info/pool_paths/import_path_for_linux64_gcc47 > $TARGET/HANA_POOL/import_path

  if [[ $? -ne 0 ]]; then
     print_msg "Failed to update import path"
     exit 1
  fi
}

detect_location()
{
  if [[ $HOST =~ ^llbpal ]]; then
      LOCATION="PAL"
      print_msg "Using settings for Palo Alto"
  else
      print_msg "Using generic location settings"
  fi

}

update_iuser_file()
{
    print_msg "Updating $TARGET/.iuser"

    echo "export GCC_VERSION=47" >> $TARGET/.iuser
    echo "export VMAKE_PARALLEL_WORKER=24" >> $TARGET/.iuser
    echo "export PS1='\[\033]0;$USER@$HOST:\$(__git_ps1 \" %s\") \w\007\033[38m\]\u@\h:\[\033[02;34m\]\w\[\033[01;31m\]\$(__git_ps1 \" (%s)\")\[\033[30m\]>\[\033[00m\] '" >>  $TARGET/.iuser
    echo "echo -en \"\033]0;$USER@$HOST\007\"" >>  $TARGET/.iuser
    echo "export GREP_OPTIONS='--color=auto'" >> $TARGET/.iuser

    if [[ $LOCATION == "PAL" ]]; then
	update_import_path
	echo "export IMPORT_PATH_FILE=$TARGET/HANA_POOL/import_path" >>  $TARGET/.iuser
	echo "export TOOLS_ROOT_CACHE=1" >> $TARGET/.iuser
	echo "export WDF_RSYNC_COMPRESSION_HOST=lu241511.dhcp.wdf.sap.corp" >> $TARGET/.iuser
	echo "export WDF_RSYNC_REMOTE_MOUNTPOINT=sapremote" >> $TARGET/.iuser
    else
	echo "export IMPORT_PATH_FILE=/sapmnt/production2/makeresults/HANA/info/pool_paths/import_path_for_linux64_gcc47" >>  $TARGET/.iuser
    fi
}

generate_afl_env_script()
{
    print_msg "Generating $TARGET/afl_env.sh"
    echo "cd $TARGET" > $TARGET/afl_env.sh
#echo "rm -f $TARGET/.iprofile $TARGET/.irelease" >> $TARGET/afl_env.sh
#echo "source $TARGET/.iuser" >> $TARGET/afl_env.sh
#echo "perl /SAPDevelop/buildtools/dev/bin/createhdbprofile.pl" >> $TARGET/afl_env.sh
    echo "source $TARGET/.iprofile" >> $TARGET/afl_env.sh
    echo "cd sys/src" >> $TARGET/afl_env.sh
    echo "bash" >> $TARGET/afl_env.sh

    print_msg "Setting permissions for $TARGET/afl_env.sh"
    chmod 744 $TARGET/afl_env.sh || exit 1
}

print_msg "Setting up AFL Make environment for $USER"

perl /SAPDevelop/buildtools/dev/bin/hdbenvinit.pl -avoidtoolcopy -branch UDF_dev -component AFL -gitrepo afl -basepath $TARGET || exit 1

detect_location

update_iuser_file

generate_afl_env_script

if [[ $LOCATION == "PAL" ]]; then
    print_msg "Updating $TARGET/.extvars"
    echo "APPS_ROOT=/sapremote/depot/apps" >> $TARGET/.extvars
fi

## Eclipse-related settings
WORKSPACE=/home/$USER/afl_workspace
print_msg "Set default workspace to $WORKSPACE"
# 1. This file is used to set the default workspace in gen-project.sh"
echo "$WORKSPACE" > $TARGET/.project.workspace

# 2. Ensure this directory exists, gen-project.sh needs it.
mkdir -p $WORKSPACE/.metadata/.plugins/org.eclipse.core.runtime/.settings/org.eclipse.cdt.ui.prefs || exit 1

