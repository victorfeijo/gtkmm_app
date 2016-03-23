Alunos: José Victor Feijó (14100842) e Matteus Legat (14100861)

O trabalho foi feito utilizando a bibilioteca gtkmm 3.0, pois acreditamos que é 
melhor para o conceito de orientação a objetos também para manutenção e futuras
atualizações no software que estamos desenvolvendo na disciplina.

O comando para compilar a aplicação deve ser o seguinte:
g++ *.cpp -o app.o `pkg-config gtkmm-3.0 --cflags --libs` -std=c++11

Para compilar e rodar a aplicação, existe também a opção de rodar o arquivo 
chamado "compile.sh", utilizando o comando "bash compile.sh run". Caso queira
apenas compilar, utilize somente "bash COMPILE.sh". Ao rodar o script, o 
programa compilado é salvo como app.o.

Em caso de algum problema com biblioteca, é recomendado certificar-se de que a
biblioteca gtkmm-dev está instalada. No ubuntu, é possível instalá-la com o 
comando:
sudo apt-get install libgtkmm-3.0-dev

