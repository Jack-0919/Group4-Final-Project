#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

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
    std::string getGraphics() const{
        return Graphics;
    }

    std::string getModel_name() const{
        return model_name;
    }

    std::string getBattery() const{
        return Battery;
    }

    std::string getCPU() const{
        return CPU;
    }

    int getSize() const{
        return size;
    }

    int getRamAmount() const {
        std::string numeric_ram = "";
        for (char c : RAM) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                numeric_ram += c;
            }else if(!numeric_ram.empty()){
                break;
            }
        }
        return numeric_ram.empty() ? 0 : std::stoi(numeric_ram);
    }
    //-------------------/GETTERS--------------------//

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

    std::vector<Laptops> start() const{
         std::cout<<"Enter laptop list File: ";
        std::string laptop_file;
        std::cin>>laptop_file;
        std::ifstream file(laptop_file);
        if (!file.is_open()) {
            std::cerr << "Could not open file!\n";
        }

        std::vector<Laptops> catalog;
        Laptops temp_laptop;

        while (file >> temp_laptop) {
            catalog.push_back(temp_laptop);
        }
        file.close();
        return catalog;
    }
};


//---------------------LAPTOP CATEGORY GOES HERE--------------------//

void getMasterList(const std::vector<Laptops>& master){
    std::cout<<"\n---------Master List----------\n";
    for(const auto& laptop : master){
        std::cout<<laptop<<"-------------------\n";
    }
}

void getGamingList(const std::vector<Laptops>& gaming) {
    std::cout<<"\n---------GAMING LAPTOPS----------\n";
    for (const auto& laptop : gaming) {
        std::string gpu = laptop.getGraphics();
        if (gpu.find("NVIDIA") != std::string::npos ||
            gpu.find("AMD") != std::string::npos) {
            std::cout<<laptop<<"-------------------\n";
        }
    }
}

void getHIGHRAMList(const std::vector<Laptops>& ram){
    std::cout<<"\n---------HIGH RAM LAPTOPS----------\n";
    for(const auto& laptop : ram){
        if(laptop.getRamAmount() > 16){
            std::cout<<laptop<<"-------------------\n";
        }
    }
}

void getRyzen(const std::vector<Laptops>& ryzen){
    std::cout<<"\n---------Ryzen CPU LAPTOPS----------\n";
    for(const auto& laptop : ryzen){
        std::string cpu = laptop.getCPU();
        if(cpu.find("Ryzen") != std::string::npos){
            std::cout<<laptop<<"-------------------\n";
        }
    }

}

void getSize14inch(const std::vector<Laptops>& size){
    std::cout<<"\n--------- 14inch LAPTOPS----------\n";
    for(const auto& laptop : size){
        if(laptop.getSize() == 14){
            std::cout<<laptop<<"-------------------\n";
        }
    }
}

//---------------------LAPTOP CATEGORY GOES HERE--------------------//


int main() {
    Laptops Loader;
    std::vector<Laptops> master_list = Loader.start();


    getMasterList(master_list);
    getGamingList(master_list);
    getHIGHRAMList(master_list);
    getRyzen(master_list);
    getSize14inch(master_list);

    return 0;
}
