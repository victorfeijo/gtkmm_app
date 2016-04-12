# Bash script to create a folder to upload on Moodle

upfolder=UPLOAD_THIS_FOLDER
source='../src/elements/*.cpp ../src/view/*.cpp ../src/services/*.cpp ../src/structures/*.cpp ../main.cpp'
headers='../include/elements/*.hpp ../include/services/*.hpp ../include/structures/*.hpp ../include/view/*.hpp ../include/enumerations/*.hpp'

# remove folder and its contents if exists
[ -e $upfolder ] && rm -r ./UPLOAD_THIS_FOLDER

# create folder
mkdir $upfolder

# copy static files
cp ./static/moodle_compile.sh $upfolder/compile.sh
cp ./static/moodle_readme.txt $upfolder/README.txt


# copy headers
cp $headers -t $upfolder

if [ "$1" == "join" ]; then
  # join cpp files if parameter `join` was passed
  find $source -type f -printf '\n\n// ========== FILE: %p ========== //\n\n\n'\
      -exec cat {} \; > $upfolder/source.cpp
else
  # copy cpp files
  cp $source -t $upfolder
fi

echo "folder $upfolder created or updated."
