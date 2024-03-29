#!/bin/sh

   reset

base_dir="$PWD"

echo "Setting up environment..."
if [ $# -eq 1 ]; then
   #TODO(damonkey): check that this round hasnt yet been run.
   round_name="ROUND$1"
   echo "\tOrganising Dracs..."
   drac_sub_round_dir="$base_dir/dracula/submissions/$round_name"
   drac_comp_round_dir="$base_dir/dracula/compiled_round_$round_name"
   rm -rf $drac_sub_round_dir
   mkdir $drac_sub_round_dir
   rm -rf $drac_comp_round_dir
   mkdir $drac_comp_round_dir

   echo "\tCollecting dracs from openlearning and leaving them in $drac_sub_round_dir"
   #TODO(damonkey): make this not just grab my example..
#   cp -r $base_dir/dracula/submissions/example $drac_sub_round_dir/example

   cd $drac_sub_round_dir
   export AUTH='spots.admin.2013:aoeuidhtns'
   export PAGE='unsw/courses/COMP9024/Activities/DraculaSubmission'
   export COHORT='unsw/courses/COMP9024/Cohorts/2013Semester2'

   /usr/bin/curl -L -k -u "$AUTH" "http://$AUTH@www.openlearning.com/api/getSubmissions?activity=$PAGE&cohort=$COHORT" > submissions.zip
   unzip submissions.zip
   rm submissions.zip;
   chmod +rw `find .`

   for i in `ls`; do mv $i `echo $i | sed "s/\./_/g"`; done 
   for i in `ls`; do mv $i/`ls $i` $i/$i.tar; done
   for i in `ls`; do cd $i; tar -xvf $i.tar; cd ..; done
   cd $base_dir

   echo "\tCopying them to directory to be compiled/modified"
   cp -r $drac_sub_round_dir/* $drac_comp_round_dir/.

   echo ""
   echo "\tOrganising Hunters"
   hunt_sub_round_dir="$base_dir/hunter/submissions/$round_name"
   hunt_comp_round_dir="$base_dir/hunter/compiled_round_$round_name"
   rm -rf $hunt_sub_round_dir
   mkdir $hunt_sub_round_dir
   rm -rf $hunt_comp_round_dir
   mkdir $hunt_comp_round_dir

   echo "\tCollecting hunters from openlearning and leaving them in $hunt_sub_round_dir"
   #TODO(damonkey): make this not just grab my example..
#   cp -r $base_dir/hunter/submissions/example $hunt_sub_round_dir/example

   cd /home/cs1927/13s2.work/projectHunt
   pwd
   for i in `ls | egrep "[a-z]{3}[0-9]{2}"`; do 
      for j in `ls $i | grep -v "rename"`; do 
         cp $i/$j/submission.tar $hunt_sub_round_dir/$j.tar; 
      done ; 
   done;
   
   cd $hunt_sub_round_dir
   for i in `ls | grep "tar$"`; do
        i=`echo $i | sed "s/\.tar$//g"`;
        mkdir $i;
        mv $i.tar $i/.;
        cd $i;
        tar -xvf $i.tar;
        cd ..;
   done;

   echo "\tCopying them to directory to be compiled/modified"
   cp -r $hunt_sub_round_dir/* $hunt_comp_round_dir/.

else
   echo "\tNo round name.. quitting"
   exit
fi

echo "Environment setup"


echo "Compilation starting..."
echo "\tCompiling dracs..."
cd $drac_comp_round_dir

for file in `ls`; do
   cd $file
   #TODO(damonkey): copy in base files to each directory, overwriting
   #                the files that are labelled DO NOT EDIT
   cp $base_dir/dracula/do_not_edit/*.java . 
   sed "s/dracula/$file/g" -i `find . | grep "\.java$"`

   rm -rf *.class
   cd ..
   echo "\t\tCompiling $file..."
   echo "\t\tjavac `find . | grep ".java$" | paste -s`"
   
   javac -sourcepath . $file/DraculaRunner.java > $file.compilation_log 2>&1;
#javac `find . | grep ".java$"` | sed "s/^/\t\t\t/g";
   echo "\t\tCompilation for $file completed."
   echo "\t\tMoving it to the list of dracs.."
   cd $drac_comp_round_dir
done

echo "\tCompiling hunters..."
cd $hunt_comp_round_dir


for file in `ls`; do
   cd $file
   cp $base_dir/hunter/do_not_edit/*.c .
   cp $base_dir/hunter/do_not_edit/*.h .
   echo "\t\tCompiling $file.."
   make > $file.compilation_log 2>&1;
   gcc -o myPlayer *.o game.c -ljansson >> $file.compilation_log 2>&1
   echo "\t\tCompilation for $file completed."
   echo "\t\tMoving it to the list of hunters"
   cp myPlayer ../$file.elf
   cd $hunt_comp_round_dir
done
cd $base_dir



echo "Compilation complete."
echo "Running Games..."
if [ $# -eq 1 ]; then
   mkdir $round_name
   
   cp -r $drac_comp_round_dir/* $round_name/.
   cp $hunt_comp_round_dir/*.elf  $round_name/.
   cp $hunt_comp_round_dir/*compilation_log $round_name/.

   cd $round_name
   #add compilation logs to right place
   mkdir compilation_logs
   chmod 755 compilation_logs
   mv `ls | grep compilation_log` compilation_logs/.                
   cp `find $hunt_comp_round_dir | grep compilation_log` compilation_logs/.
   chmod 755 compilation_logs/*
   
   #create directory to log rounds
   mkdir logs;
   touch logs/who_ran_in_what.log
   chmod 755 logs/*

   #prepare the public html folder
   mkdir ~/public_html/13s2.dracula/$round_name
   chmod 755 ~/public_html/13s2.dracula/$round_name
   ln -s $base_dir/$round_name/logs ~/public_html/13s2.dracula/$round_name/logs
   ln -s $base_dir/$round_name/compilation_logs ~/public_html/13s2.dracula/$round_name/compilation_logs
   
   chmod 755 logs
   chmod 755 compilation_logs
   chmod 755 .
   chmod +x *.elf
   for (( i=0; $i<1000; i++ )); do
      ls -d | sort -R
      #TODO(damonkey): make this more evenly distributed
      #Grab the current files in the directory, decide if they are dracs or hunters
      #        then shuffle them with sort -R
      #        and grab the first one from the shuffled list
      drac="`ls | grep -v ".elf$" | grep -v "logs" | sort -R | tail -n 1`"
      hunter0="`ls | grep ".elf$" | grep -v "logs" | sort -R | tail -n 1`"
      hunter1=$hunter0
      hunter2=$hunter1
      hunter3=$hunter2            

      echo $i ": " $drac "vs" $hunter0 >> logs/who_ran_in_what.log
      echo $drac " vs " $hunter0
      log_file="logs/$i.log";
      ./../node/node ../game_runner/runGame.js \
               "$PWD/$hunter0" \
               "$PWD/$hunter1" \
               "$PWD/$hunter2" \
               "$PWD/$hunter3" \
               "timeout 90 java -ea $drac.DraculaRunner" \
                        | sed "s/^/\t/g" > $log_file
      chmod 755 $log_file
   done;
   cd ..
fi

