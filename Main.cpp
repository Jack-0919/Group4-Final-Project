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

//These are getters
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


//Laptop category

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

void getWorkstationCreatorList(const std::vector<Laptops>& workstation){
    std::cout<<"\n---------WORKSTATION / CREATOR LAPTOPS----------\n";

    for(const auto& laptop : workstation){

        std::string cpu = laptop.getCPU();

        bool highRAM = laptop.getRamAmount() >= 32;

        bool premiumCPU = (
            cpu.find("Xeon") != std::string::npos ||
            cpu.find("i9") != std::string::npos ||
            cpu.find("Ryzen") != std::string::npos &&cpu.find("9") != std::string::npos
        );

        if(highRAM || premiumCPU){
            std::cout << laptop << "-------------------\n";
        }
    }
}

void getUltraportableList(const std::vector<Laptops>& inventory) {
    std::cout << "\n---------ULTRAPORTABLE / ULTRABOOK LAPTOPS----------\n";
    std::cout << "Innovation Note: These models represent the ultimate 'Spin-off' of mobility, \n";
    std::cout << "maximizing untethered work with highly miniaturized hardware.\n";
    
    for(const auto& laptop : inventory) {
        if(laptop.getSize() <= 14) {
            std::cout << laptop << "-------------------\n";
        }
    }
}

void getBudgetChromebookList(const std::vector<Laptops>& inventory) {
    std::cout << "\n---------BUDGET / CHROMEBOOK LAPTOPS----------\n";
    std::cout << "Rule: Lightweight OS OR RAM under 8GB\n";

    for (const auto& laptop : inventory) {
        bool lowRAM = laptop.getRamAmount() < 8;

        if (lowRAM) {
            std::cout << laptop << "-------------------\n";
        }
    }
}
//recommendation UI

void recommendationUI(const std::vector<Laptops>& inventory) { 

    int choice;

    std::cout << "\n\n========================================\n";
    std::cout << "       LAPTOP RECOMMENDATION UI\n";
    std::cout << "========================================\n";

    std::cout << "\nWhat type of laptop are you looking for?\n";
    std::cout << "1. Gaming Laptop\n";
    std::cout << "2. High RAM Laptop\n";
    std::cout << "3. Ryzen CPU Laptop\n";
    std::cout << "4. Workstation / Creator Laptop\n";
    std::cout << "5. Ultraportable Laptop\n";
    std::cout << "6. Budget / Chromebook Laptop\n";
    std::cout << "7. Quit the program";


    while(true){
        std::cout << "\nEnter your choice(number 1-7): ";
        std::cin >> choice;

        if(choice == 1){
            getGamingList(inventory);
        }
        else if(choice == 2){
            getHIGHRAMList(inventory);
        }
        else if(choice == 3){
            getRyzen(inventory);
        }
        else if(choice == 4){
            getWorkstationCreatorList(inventory);
        }
        else if(choice == 5){
            getUltraportableList(inventory);
        }
        else if(choice == 6){
            getBudgetChromebookList(inventory);
        }
        else if(choice == 7){
            std::cout<<"Goodbye!";
            break;
        }
        else{
            std::cout<<"Invalid Choice!";
        }

    }
}


int main() {
    Laptops Loader; 
    std::vector<Laptops> master_list = Loader.start(); 
    recommendationUI(master_list);      
    return 0; 
}
