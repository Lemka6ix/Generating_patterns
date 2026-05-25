#include "builder/ComputerBuilder.h"
#include "builder/Director.h"

int main() {
    std::cout << "BUILDER PATTERN\n";
    
    // Gaming PC
    std::cout << "\n>>> Building Gaming PC...\n";
    GamingPCBuilder gamingBuilder;
    Director gamingDirector(&gamingBuilder);
    Computer* gamingPC = gamingDirector.constructCompleteComputer();
    gamingPC->printSpecification();
    delete gamingPC;
    
    // Workstation
    std::cout << "\n>>> Building Professional Workstation...\n";
    WorkstationBuilder workstationBuilder;
    Director workstationDirector(&workstationBuilder);
    Computer* workstation = workstationDirector.constructCompleteComputer();
    workstation->printSpecification();
    delete workstation;
    
    // Server
    std::cout << "\n>>> Building Enterprise Server...\n";
    ServerBuilder serverBuilder;
    Director serverDirector(&serverBuilder);
    Computer* server = serverDirector.constructCompleteComputer();
    server->printSpecification();
    delete server;
    
    return 0;
}