#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "t1.h"

#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h> 
#include <TLorentzVector.h>

using namespace std;


//------------------------------------------------------------------------------
// Particle Class
//
class Particle{

	public:
	Particle();
    Particle(double Pt, double Eta, double Phi, double Energy);
	double   pt, eta, phi, E, m, p[4];
	void     p4(double, double, double, double);
	void     print();
	void     setMass(double);
	double   sintheta();
};

//------------------------------------------------------------------------------

//*****************************************************************************
//                                                                             *
//    MEMBERS functions of the Particle Class                                  *
//                                                                             *
//*****************************************************************************

//
//*** Default constructor ------------------------------------------------------
//
Particle::Particle(){
	pt = eta = phi = E = m = 0.0;
	p[0] = p[1] = p[2] = p[3] = 0.0;
}

//*** Additional constructor ------------------------------------------------------
Particle::Particle (double Pt, double Eta, double Phi, double Energy){ 
	pt = Pt;
    eta = Eta;
    phi = Phi;
    E = Energy;

    p4(Pt, Eta, Phi, Energy);
    double momentum_sq = pow(p[0],2) + pow(p[1],2) + pow(p[2],2);
    setMass(sqrt(pow(E,2)-momentum_sq)); 
}

//
//*** Members  ------------------------------------------------------
//
double Particle::sintheta(){
    double theta = 2*atan(exp(-eta));
    return sin(theta);
}

void Particle::p4(double pT, double eta, double phi, double energy){
	p[0] = pT * cos(phi);
    p[1] = pT * sin(phi);
    p[2] = pT * sinh(eta);
    p[3] = energy;
}

void Particle::setMass(double mass)
{
    m = mass;
	return;
}

//
//*** Prints 4-vector ----------------------------------------------------------
//
void Particle::print(){
	std::cout << "(" << p[0] <<",\t" << p[1] <<",\t"<< p[2] <<",\t"<< p[3] << ")" << "  " <<  sintheta() << std::endl;
}


//------------------------------------------------------------------------------
// Lepton Class
//
class Lepton: public Particle{
    
    public:
        Lepton(): Particle() {}
        Lepton(double Pt, double Eta, double Phi, double Energy, int Charge);
        double  charge;
        void    setCharge(int);

};

//------------------------------------------------------------------------------

//*****************************************************************************
//                                                                             *
//    MEMBERS functions of the Lepton Class                                    *
//                                                                             *
//*****************************************************************************

//*** Additional constructor ------------------------------------------------------
Lepton::Lepton(double Pt, double Eta, double Phi, double Energy, int Charge) : Particle(Pt, Eta, Phi, Energy)
{
    setCharge(Charge);
}

//
//*** Members  ------------------------------------------------------
//                                                                   

void Lepton::setCharge(int Charge)
{
    charge = Charge;
	return;
}

//------------------------------------------------------------------------------
// Jet Class
//
class Jet: public Particle{

	public:
        Jet(): Particle() {}
        Jet(double Pt, double Eta, double Phi, double Energy, int Flavour);
        double  flavour;
        void    setFlavour(int);

};

//------------------------------------------------------------------------------

//*****************************************************************************
//                                                                             *
//    MEMBERS functions of the Jet Class                                    *
//                                                                             *
//*****************************************************************************

//*** Additional constructor ------------------------------------------------------
Jet::Jet(double Pt, double Eta, double Phi, double Energy, int Flavour) : Particle(Pt, Eta, Phi, Energy)
{
    setFlavour(Flavour);
}

//
//*** Members  ------------------------------------------------------
//

void Jet::setFlavour(int Flavour)
{
    flavour = Flavour;
	return;
}


int main() {

	/* ************* */
	/* Input Tree    */
	/* ************* */

	TFile *f      = new TFile("input.root","READ");
	TTree *t1 = (TTree*)(f->Get("t1"));

	// Read the variables from the ROOT tree branches
    t1->SetBranchAddress("nleps",&nleps);
	t1->SetBranchAddress("lepPt",&lepPt);
	t1->SetBranchAddress("lepEta",&lepEta);
	t1->SetBranchAddress("lepPhi",&lepPhi);
	t1->SetBranchAddress("lepE",&lepE);
	t1->SetBranchAddress("lepQ",&lepQ);
	
	t1->SetBranchAddress("njets",&njets);
	t1->SetBranchAddress("jetPt",&jetPt);
	t1->SetBranchAddress("jetEta",&jetEta);
	t1->SetBranchAddress("jetPhi",&jetPhi);
	t1->SetBranchAddress("jetE", &jetE);
	t1->SetBranchAddress("jetHadronFlavour",&jetHadronFlavour);

	// Total number of events in ROOT tree
	Long64_t nentries = t1->GetEntries();

	for (Long64_t jentry=0; jentry<100;jentry++)
 	{
		t1->GetEntry(jentry);
		std::cout<<" Event "<< jentry <<std::endl;

        for(int i=0; i<nleps; i++) {
            Lepton current_lepton((double)lepPt[i], (double)lepEta[i], (double)lepPhi[i], (double)lepE[i], (int)lepQ[i]);
            cout<<"Lepton #"<<i<<" Information:"<<endl;
            cout<<"    pT = "<<current_lepton.pt<<endl;
            cout<<"    eta = "<<current_lepton.eta<<endl;
            cout<<"    phi = "<<current_lepton.phi<<endl;
            cout<<"    E = "<<current_lepton.E<<endl;
            cout<<"    m = "<<current_lepton.m<<endl;
            cout<<"    hadron flavour = "<<current_lepton.charge<<endl;
            cout<<"    p4 = ";
            current_lepton.print();
            cout<<endl<<endl;
        }

        for(int i=0; i<njets; i++) {
            Jet current_jet((double)jetPt[i], (double)jetEta[i], (double)jetPhi[i], (double)jetE[i], (int)jetHadronFlavour[i]);
            cout<<"Jet #"<<i<<" Information:"<<endl;
            cout<<"    pT = "<<current_jet.pt<<endl;
            cout<<"    eta = "<<current_jet.eta<<endl;
            cout<<"    phi = "<<current_jet.phi<<endl;
            cout<<"    E = "<<current_jet.E<<endl;
            cout<<"    m = "<<current_jet.m<<endl;
            cout<<"    hadron flavour = "<<current_jet.flavour<<endl;
            cout<<"    p4 = ";
            current_jet.print();
            cout<<endl<<endl;
        }


	} // Loop over all events

  	return 0;
}
