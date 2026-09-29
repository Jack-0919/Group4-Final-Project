#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 

class Laptops {
private:
    int ID;
    std::string model_name;
    std::string CPU;
    std::string RAM;
    std::string Battery;
    std::string Graphics;
    int size;

public:
    Laptops() : ID(0), size(0) {}

    Laptops(int id, std::string m, std::string c, std::string r, std::string b, std::string g, int s) 
        : ID(id), model_name(m), CPU(c), RAM(r), Battery(b), Graphics(g), size(s) 
    {};

    friend std::ostream& operator<<(std::ostream& os, const Laptops& l) {
        os << "\nID: " << l.ID << "\nModel: " << l.model_name << "\nCPU: " << l.CPU 
           << "\nRAM: " << l.RAM << "\nBattery: " << l.Battery << "\nGraphics: " << l.Graphics 
           << "\nsize: " << l.size << "\n";
        return os;
    }

    //-------------------GETTERS--------------------//
    std::string getGraphics(){
        return Graphics;
    }

    int getRamAmount() const {
        std::string numeric_ram = "";
        for (char c : RAM) {
            if (std::isdigit(c)) {
                numeric_ram += c;
            }
        }
        return numeric_ram.empty() ? 0 : std::stoi(numeric_ram);
    }
    //-------------------GETTERS--------------------//

    friend std::istream& operator>>(std::istream& is, Laptops& l) {
        std::string line;
      
        if (std::getline(is, line)) {
            if (line.empty()) return is; 

            std::stringstream ss(line);
            std::string temp_id, temp_size;

          
            ss >> temp_id; 
            
           
            if (!temp_id.empty() && temp_id.back() == '.') {
                temp_id.pop_back();
            }
            l.ID = std::stoi(temp_id);

           
            ss.ignore(1); 

            
            std::getline(ss, l.model_name, ',');
            std::getline(ss, l.CPU, ',');
            std::getline(ss, l.RAM, ',');
            std::getline(ss, l.Battery, ',');
            std::getline(ss, l.Graphics, ',');
            
        
            std::getline(ss, temp_size); 
            l.size = std::stoi(temp_size);
        }
        return is;
    }
};

int main() {
    std::cout<<"Enter laptop list File: ";
    std::string laptop_file;
    std::cin>>laptop_file;
    std::ifstream file(laptop_file);
    if (!file.is_open()) {
        std::cerr << "Could not open file!\n";
        return 1;
    }

    std::vector<Laptops> catalog;
    Laptops temp_laptop;

    while (file >> temp_laptop) {
        catalog.push_back(temp_laptop);
    }
    
    file.close();
    for (const auto& laptop : catalog) {
        std::cout << laptop << "-------------------\n";
    }


    //CATEGORIZATION (add more if you guys want)
    std::cout<<"\nGAMING: ";
    for(auto& laptop : catalog){
        std::string gpu = laptop.getGraphics();
        if(gpu.find("NVIDIA") != std::string::npos || gpu.find("AMD") != std::string::npos ){
            std::cout<<laptop<<"\n";
        }
    }

    std::cout<<"\nHIGH RAM: ";
    for(const auto& laptop : catalog){
        if(laptop.getRamAmount() > 12){
            std::cout<<laptop<<"\n";
        }
    }


    return 0;
}
