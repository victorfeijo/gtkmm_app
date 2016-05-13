# Bash script to create a folder to upload on Moodle

upfolder=UPLOAD_THIS_FOLDER
source='../src/elements/*.cpp ../src/view/*.cpp ../src/services/*.cpp ../src/structures/*.cpp ../main.cpp'
headers='../include/elements/*.hpp ../include/services/*.hpp ../include/structures/*.hpp ../include/view/*.hpp ../include/enumerations/*.hpp'
alert="// AVISO: COMO O LIMITE DE ARQUIVOS FOI EXCEDIDO, TODOS OS ARQUIVOS .CPP FORAM\n// UNIDOS EM UM ÚNICO CPP, E PARA FACILITAR A AVALIAÇÃO, TAMBÉM FOI ENVIADO UM\n// ARQUIVO .ZIP COM TODOS OS ARQUIVOS SEPARADOS."

# remove folder and its contents if exists
[ -e $upfolder ] && rm -r ./UPLOAD_THIS_FOLDER

# create folder
mkdir $upfolder

# copy static files
cp ./static/compile.sh $upfolder/
cp ./static/README.txt $upfolder/
cp ../test.obj $upfolder/
cp ../cube.obj $upfolder/


# copy headers
cp $headers -t $upfolder

# if parameter `join` was passed:
if [ "$1" == "join" ]; then
  echo -e $alert > $upfolder/source.cpp
  # join cpp files:
  find $source -type f -printf '\n\n// ========== FILE: %p ========== //\n\n\n' -exec cat {} \; >> $upfolder/source.cpp
  # join files in zip:
  mkdir zip/
  cp $source $headers ../test.obj ../cube.obj ./static/README.txt ./static/compile.sh -t zip
  zip -r $upfolder/code.zip zip/ >> /dev/null
  rm -r zip/
else
  # copy cpp files
  cp $source -t $upfolder
fi

echo "folder $upfolder created or updated."
