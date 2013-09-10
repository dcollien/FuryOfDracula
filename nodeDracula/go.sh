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
   cp -r $base_dir/dracula/submissions/example $drac_sub_round_dir/example   

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
   cp -r $base_dir/hunter/submissions/example $hunt_sub_round_dir/example
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

   sed "s/dracula/$file/g" -i *.java

   rm -rf *.class
   echo "\t\tCompiling $file..." 
   for f in `find . | grep *.java`; do
      javac "$f" | sed "s/^/\t\t\t/g";
   done
   echo "\t\tCompilation for $file completed."
   cd $drac_comp_round_dir 
done
cd ../..

echo "\tCompiling hunters..."
cd $hunt_comp_round_dir

for file in `ls`; do
   cd $file
   echo "\t\tCompiling $file.."
   make clean | sed "s/^/\t\t\t/g"
   make all | sed "s/^/\t\t\t/g"
   echo "\t\tCompilation for $file completed."
   echo "\t\tMoving it to the list of hunters"
   cp myPlayer ../hunter_$file.elf
   cd $hunt_comp_round_dir
done
cd $base_dir
   


echo "Compilation complete."
echo "Running Games..."
if [ $# -eq 1 ]; then
   mkdir $round_name
   cp -r $drac_comp_round_dir/* $round_name/.
   cp $hunt_comp_round_dir/*.elf  $round_name/.   

   cd $round_name
   drac="example"
   hunter0="hunter_example.elf"
   hunter1="hunter_example.elf"
   hunter2="hunter_example.elf"
   hunter3="hunter_example.elf"
   nodejs ../game_runner/runGame.js \
            "$hunter0" \
            "$hunter1" \
            "$hunter2" \
            "$hunter3" \
            "java -ea $drac.DraculaRunner" \
                     | sed "s/^/\t/g"
   cd ..
fi
