Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Color_Off='\033[0m'

make
echo
echo ==================TESTS=============
#ls
echo ===ls TESTS
echo -e $Color_Off ls sobre /.
echo -e $Green
./ls .
echo -e $Color_Off ls sobre mini_sist
echo -e $Green
./ls mini_sist
echo  -e $Color_Off ls sobre mini_sist/dir1
echo -e $Green
./ls mini_sist/dir1
echo  -e $Color_Off ls sobre  sobre mini_sist/dir3/dir13
echo -e $Green
./ls mini_sist/dir3/dir13
echo  -e $Color_Off ls sobre  sobre direccion invalida
echo -e $Red
./ls mini_sist-asdasd
echo  -e $Color_Off

#find
echo ===find TESTS
echo -e $Color_Off find "bus"
echo -e $Green
./find bus
echo -e $Color_Off find "x"
echo -e $Green
./find x
echo -e $Color_Off find -i "bus"
echo -e $Green
./find -i bu
echo  -e $Color_Off

#cp
echo ===CP TESTS
echo -e $Color_Off cp con un archivo que no existe 
echo cp  origen.txt  destino.txt
echo -e $Red
./cp  origen.txt  destino.txt

echo -e $Color_Off cp con un destino  que no existe 
echo cp  origen.txt  destino.txt
echo -e $Red
./cp  origen.txt  destino.txt

rm destino.txt

echo -e $Color_Off cp con argumentos correctos
echo "1 2 3 4 5 6 "> origen.txt
echo  cat en origen
echo -e $Green
cat origen.txt
echo  -e $Color_Off cp  origen.txt  destino.txt
./cp  origen.txt  destino.txt
echo  -e $Color_Off cat en destino
echo -e $Green
cat  destino.txt
rm  origen.txt  destino.txt
echo  -e $Color_Off 

#tiemout
echo === tiemout TESTS
echo sleep de 100 con timeout de 3
./timeout 3 sleep 100
echo sleep de 3 con timeout de 100
./timeout 100 sleep 3

echo
echo ==================FIN=============
echo
make clean
