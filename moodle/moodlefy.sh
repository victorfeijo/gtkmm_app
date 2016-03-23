# Bash script to create a folder to upload on Moodle

upfolder=UPLOAD_THIS_FOLDER

# remove folder and its contents if exists
[ -e $upfolder ] && rm -r ./UPLOAD_THIS_FOLDER

# create folder
mkdir $upfolder

# copy static files
cp ./static/moodle_compile.sh $upfolder/compile.sh
cp ./static/moodle_readme.txt $upfolder/README.txt

# copy code 
cp ../src/*.cpp -t $upfolder
cp ../include/*.hpp -t $upfolder

echo "folder $upfolder created or updated."
