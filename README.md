# Group4-Final-Project

MUHAMMAD ADAM AQIL BIN ROSLI          : 261UC260Y5
JACKSON TIOH                          : 262UC2437S
MUHAMMAD DANISH AIMAN BIN ABD HAMID   : 1231303473
SYAKIR BASILUDDIN BIN SYAMSUL BAHRAIN : 253UC2TTTN
PUTRA MOHAIFAL BIN MOHD KHAIRI        : 262UC2644X
CHOO ZHEN HAO                         : 262UC2461X




# Laptop Recommendation Program

A C++ program that reads a list of laptops from a text file and displays recommendations by category.

## Compilation
```
g++ -std=c++11 -o main.cpp
```

## Usage
1. Run the program: `./laptop_recommender`
2. Enter the name of the laptop data file when prompted.
3. Select a category from the menu (1-7). The program will display matching laptops.
4. Choose 7 to quit the program.

## Input File Format
Each line represents one laptop. Fields are comma-separated, except the first field (ID) which may end with a period and is followed by a space.

Format: `ID[.] Model,CPU,RAM,Battery,Graphics,Size`

Example:
```
1. Dell XPS,Intel i7,16GB,6-cell,NVIDIA GTX,15
2. Lenovo ThinkPad,AMD Ryzen 7,32GB,4-cell,Integrated,14
```

- ID: integer (optional trailing period)
- Model: string
- CPU: string
- RAM: string (e.g., 16GB)
- Battery: string
- Graphics: string
- Size: integer (screen size in inches)

Empty lines are ignored.
