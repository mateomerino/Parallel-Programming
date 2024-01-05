cd src

echo "Compiling filter program. Please wait..."

make filter

echo "Executing program for separe image in R-G-B channels. Please wait..."

python3 separe_img.py

echo "Enter the number of threads to use in paralel section:"

read threads

./filter $threads

python3 show_img.py
