#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <sstream>
#include <string>

void txt_to_root() {
  // Open (or create) the ROOT file in “RECREATE” mode
  TFile *f = TFile::Open("SunLayers.root", "RECREATE");
  if (!f || f->IsZombie()) {
    printf("Error creating file\n");
    return;
  }

  // Create the TTree
  TTree* tree = new TTree("LayerParameters", "Parameters of each solar layer");

  // Create variables to hold the data
  Double_t InR = 0;
  Double_t OutR = 0;
  Double_t Rho = 0;
  Double_t P = 0;
  Double_t T = 0;
  tree->Branch("InnerRadius", &InR, "InnerRadius/D");
  tree->Branch("OuterRadius", &OutR, "OuterRadius/D");
  tree->Branch("Density", &Rho, "Density/D");
  tree->Branch("Pressure", &P, "Pressure/D");
  tree->Branch("Temperature", &T, "Temperature/D");

  // Fill the tree
  std::string filename = "/home/jimmyma/Software/G4SOLAR/SunInfo/SunLayers.txt";
  std::ifstream infile( filename );
  if (!infile.is_open()) {
    std::cout << "Could not open Sun info file " << filename << std::endl;
    return;
  }
  
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss >> InR >> OutR >> Rho >> P >> T;
    tree->Fill();                           // now store into the tree
  }

  tree->Write();  // writes the tree into the file

  infile.close();
  f->Close();
  delete f;

  return;
}