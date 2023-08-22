// 
// 
// 
// 

// 

// 
// 
//(setq initial-scratch-message "")

// Pythia include and namespace.
#include "Pythia8/Pythia.h"
using namespace Pythia8;


// FastJet include and namespace.
//#include "fastjet/PseudoJet.hh"
#include <iostream>
#include <fastjet/PseudoJet.hh>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh" // In external code, this should be fastjet/contrib/SoftDrop.hh

using namespace fastjet;

// ROOT, for histogramming. 
#include "TH1.h"
#include "TH2.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"


std::ostream& operator<<(std::ostream& os, const fastjet::PseudoJet& pj) {
    os << "PseudoJet (pt: " << pj.pt() << ", eta: " << pj.eta() << ", phi: " << pj.phi() << ")";
    return os;
}

int main(int argc, char* argv[]) {

  // Number of events.
  int nEvent = 1000000;

  // Create the ROOT application environment.
  // TApplication theApp("hist", &argc, argv);

  // Set up Pythia generation of Z + jet; Z -> hadrons; m_Z restricted.
  Pythia pythia;
  Event& event = pythia.event;
  pythia.readString("Beams:eCM = 200.");
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 15.");
  pythia.init();

  // Detector size, anti-kT radius, and modified mass-drop tagger z.
  double etaMax = 1.;
  double radius[5] = {0.05, 0.1, 0.2, 0.4, 0.6}; // jet radius
  double pseudorapidity = -999; // pseudorapidity
  double theta_sj = -1; // delta radius (value describes an unachievable value)
  double z_sj = -1; // delta radius (value describes an unachievable value)
  

  // Set up FastJet jet finders and modified mass-drop tagger.
  JetDefinition jetDefAKT_R01( antikt_algorithm, radius[1]);
  JetDefinition jetDefAKT_R04( antikt_algorithm, radius[3]);
  JetDefinition jetDefCA(cambridge_algorithm, radius[3]);

  //! create a new ROOT histogram for jet transverse momentum pT


  TFile* outFile = new TFile("hist6.root", "RECREATE");
  outFile->cd();

  //  std::// cout << "created hist.root! yay!" << std::endl;
    
  // Book histogram.
  TH1F *_h_R04_z_sj_15_20= new TH1F("R04_z_sj_15_20","z_sj", 10, 0, 0.5);
  TH1F *_h_R04_theta_sj_15_20= new TH1F("R04_theta_sj_15_20","theta_sj", 10, 0, 0.5);
  
  TH1F *_h_R04_z_sj_20_25= new TH1F("R04_z_sj_20_25","z_sj", 10, 0, 0.5);
  TH1F *_h_R04_theta_sj_20_25= new TH1F("R04_theta_sj_20_25","theta_sj", 10, 0, 0.5);

  
  TH1F *_h_R04_z_sj_25_30= new TH1F("R04_z_sj_25_30","z_sj", 10, 0, 0.5);
  TH1F *_h_R04_theta_sj_25_30= new TH1F("R04_theta_sj_25_30","theta_sj", 10, 0, 0.5);

  
  TH1F *_h_R04_z_sj_30_40= new TH1F("R04_z_sj_30_40","z_sj", 10, 0, 0.5);
  TH1F *_h_R04_theta_sj_30_40= new TH1F("R04_theta_sj_30_40","theta_sj", 10, 0, 0.5);

  TH1F *_h_R04_z_g_15_20= new TH1F("R04_z_g_15_20","z_g in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R04_theta_g_15_20= new TH1F("R04_theta_g_15_20","theta_g in subjets 1 & 2", 10, 0, 0.5);
 
  TH1F *_h_R04_z_g_20_25= new TH1F("R04_z_g_20_25","z_g in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R04_theta_g_20_25= new TH1F("R04_theta_g_20_25","theta_g in subjets 1 & 2", 10, 0, 0.5);

  
  TH1F *_h_R04_z_g_25_30= new TH1F("R04_z_g_25_30","z_g in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R04_theta_g_25_30= new TH1F("R04_theta_g_25_30","theta_g in subjets 1 & 2", 10, 0, 0.5);

  
  TH1F *_h_R04_z_g_30_40= new TH1F("R04_z_g_30_40","z_g in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R04_theta_g_30_40= new TH1F("R04_theta_g_30_40","theta_g in subjets 1 & 2", 10, 0, 0.5);

  
  TH1F *_hmult_R04= new TH1F("mult_R04","total number of constituents inside R=0.4 jets", 10, 0, 0.5);
  
   //softDrop multiplicity hists
  TH1F *_hmult_R04_pT_15_20GeV= new TH1F("g_R04_pT_15_20GeV","total number of constituents inside R=0.4 jets with 15< p_{T} < 20", 30, 0, 30);

  TH1F *_hmult_R04_pT_20_25GeV= new TH1F("g_R04_pT_20_25GeV","total number of constituents inside R=0.4 jets with 20 < p_{T} < 25", 30, 0, 30);

  TH1F *_hmult_R04_pT_25_30GeV= new TH1F("g_R04_pT_25_30GeV","total number of constituents inside R=0.4 jets with 25 < p_{T} < 30", 30, 0, 30);

  TH1F *_hmult_R04_pT_30_40GeV= new TH1F("g_R04_pT_30_40GeV","total number of constituents inside R=0.4 jets with 30 < p_{T} < 40", 30, 0, 30);
				    

  TH1F *_hjetpT_R04 = new TH1F("jetpT_R04","jet transverse momentum for R=0.4 jets", 100, 0, 100);
  TH1F *_hjeteta_R04 = new TH1F("jeteta_R04","jet pseudorapidity for R=0.4 jets", 50, -0.6, 0.6);

  TH2D * correlation_theta_15_20 = new TH2D("correlation_theta_15_20", "Correlation Plot 15 < p_{T} < 20 [GeV/c]; R_{g}; #theta_{sj}", 20, 0, 0.5, 20, 0, 0.5);
  TH2D *correlation_theta_20_25 = new TH2D("correlation_theta_20_25", "Correlation Plot 20 < p_{T} < 25 [GeV/c]; R_{g}; #theta_{sj}", 20, 0, 0.5, 20, 0, 0.5);
  TH2D *correlation_theta_25_30 = new TH2D("correlation_theta_25_30", "Correlation Plot 25 < p_{T} < 30 [GeV/c]; R_{g}; #theta_{sj}", 20, 0, 0.5, 20, 0, 0.5);
  TH2D *correlation_theta_30_40 = new TH2D("correlation_theta_30_40", "Correlation Plot 30 < p_{T} < 40 [GeV/c]; R_{g}; #theta_{sj}", 20, 0, 0.5, 20, 0, 0.5);

  TH2D *correlation_z_15_20 = new TH2D("correlation_z_15_20", "Correlation Plot; z_{g}; z_{sj}", 20, 0, 0.5, 20, 0, 0.5);
  TH2D *correlation_z_20_25 = new TH2D("correlation_z_20_25", "Correlation Plot; z_{g}; z_{sj}", 20, 0, 0.5, 20, 0, 0.5);
  TH2D *correlation_z_25_30 = new TH2D("correlation_z_25_30", "Correlation Plot; z_{g}; z_{sj}", 20, 0, 0.5, 20, 0, 0.5);
  TH2D *correlation_z_30_40 = new TH2D("correlation_z_30_40", "Correlation Plot; z_{g}; z_{sj}", 20, 0, 0.5, 20, 0, 0.5);   
  
  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (!pythia.next()) continue;

    void read_event(vector<PseudoJet> &event);
    // ostream & operator=(ostream &, const PseudoJet &);
    // Store final visible central particle four-momenta as start
    // configuration. Also find last copy 0f Z0, i.e. right before decay.
    vector<PseudoJet> particles;
    int iZ = 0;
    int mult = 0;
    for (int i = 0; i < event.size(); ++i) {
      if (event[i].isFinal() && event[i].isVisible() && abs(event[i].eta()) < etaMax){
	particles.push_back(PseudoJet( event[i].px(), event[i].py(), event[i].pz(), event[i].e() ) );
	if(event[i].charge() != 0)
	  mult++; //! mult++ = mult + 1;
	
	
      }
      if (event[i].id() == 23) iZ = i;
    }//! particle loop inside the event
    
    // Rjet = 0.4 Begin

    // Run Fastjet anti-kT algorithm and sort jets in pT order.
    ClusterSequence clustSeq_R04( particles, jetDefAKT_R04 );
    vector<PseudoJet> sortedJets_R04 = sorted_by_pt( clustSeq_R04.inclusive_jets() );
    
    //! create a loop to run over the jets -
    for (int j = 0; j < sortedJets_R04.size(); ++j) {
      PseudoJet jet = sortedJets_R04.at(j);
      if(fabs(jet.eta()) > 0.6)
	continue;
      
      ClusterSequence clustSeq_R01_con(jet.constituents() , jetDefAKT_R01 );
      vector<PseudoJet> sortedJets_R01_con = sorted_by_pt( clustSeq_R01_con.inclusive_jets() );

      if (sortedJets_R01_con.size() < 2)
	continue;
      PseudoJet sj1 = sortedJets_R01_con.at(0);
      PseudoJet sj2 = sortedJets_R01_con.at(1);

      theta_sj = sj1.delta_R(sj2);
      z_sj = sj2.pt()/(sj2.pt()+sj1.pt());
      
      // 15 to 20
      if (jet.pt() > 15 and jet.pt() < 20 ){
	// cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
	_hjetpT_R04->Fill(jet.perp());
	pseudorapidity = jet.eta();
	_hjeteta_R04->Fill(pseudorapidity);	
	_hmult_R04->Fill(jet.constituents().size());

	ClusterSequence clustSeqCA(jet.constituents(), jetDefCA);
	vector<PseudoJet> cambridgeJets = sorted_by_pt(clustSeqCA.inclusive_jets());
    
	// SoftDrop parameters
	double z_cut = 0.20;
	double beta = 0.0;
	contrib::SoftDrop sd(beta, z_cut);
	//! get subjets 15 to 20 pT
	
	_h_R04_z_sj_15_20->Fill(z_sj);
	_h_R04_theta_sj_15_20->Fill(theta_sj);

            PseudoJet sd_jet = sd(jet);
            if (sd_jet == 0)
	      continue;
                // SoftDrop was successful, analyze the resulting sd_jet
                // cout << endl;
		// cout << "original    jet: " << cambridgeJet << endl;
		// cout << "SoftDropped jet: " << sd_jet << endl;
	    cout << "jet pT: " << sd_jet.perp() << endl;
	    cout << "  delta_R between subjets: " << sd_jet.structure_of<contrib::SoftDrop>().delta_R() << endl;
	    cout << "  symmetry measure(z):     " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;
	    cout << " theta_sj: " << theta_sj << endl;
	    cout << " z_sj: " << z_sj << endl;
		// cout << "  mass drop(mu):           " << sd_jet.structure_of<contrib::SoftDrop>().mu() << endl;

		// Fill histograms with delta_R and symmetry measure z
            double delta_R_subjets = sd_jet.structure_of<contrib::SoftDrop>().delta_R();
            double z_subjets = sd_jet.structure_of<contrib::SoftDrop>().symmetry();

            _h_R04_z_g_15_20->Fill(z_subjets);
            _h_R04_theta_g_15_20->Fill(delta_R_subjets);

	    correlation_theta_15_20->Fill(delta_R_subjets, theta_sj);
	    correlation_z_15_20->Fill(z_subjets, z_sj);
	    
                // SoftDrop failed, handle the case as needed
                // e.g., skip this jet or perform alternative analysis
	      
      } else {
	_hmult_R04_pT_15_20GeV->Fill(jet.constituents().size());
      }
 
      // 20 to 25 pT

      if (jet.pt() > 20 and jet.pt() < 25 ){
	// cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
	_hjetpT_R04->Fill(jet.perp());
	pseudorapidity = jet.eta();
	_hjeteta_R04->Fill(pseudorapidity);	
	_hmult_R04->Fill(jet.constituents().size());
	
	ClusterSequence clustSeqCA(jet.constituents(), jetDefCA);
	vector<PseudoJet> cambridgeJets = sorted_by_pt(clustSeqCA.inclusive_jets());

	// SoftDrop parameters
	double z_cut = 0.20;
	double beta = 0.0;
	contrib::SoftDrop sd(beta, z_cut);
	//! get subjets 20 to 25 pT
	_h_R04_z_sj_20_25->Fill(z_sj);
	_h_R04_theta_sj_20_25->Fill(theta_sj);

            // Apply SoftDrop to the jet
           PseudoJet sd_jet = sd(jet);
            if (sd_jet == 0)
	      continue;
	 cout << "jet pT: " << sd_jet.perp() << endl;
	    cout << "  delta_R between subjets: " << sd_jet.structure_of<contrib::SoftDrop>().delta_R() << endl;
	    cout << "  symmetry measure(z):     " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;
	    cout << " theta_sj: " << theta_sj << endl;
	    cout << " z_sj: " << z_sj << endl;
		// Fill histograms with delta_R and symmetry measure z
            double delta_R_subjets = sd_jet.structure_of<contrib::SoftDrop>().delta_R();
            double z_subjets = sd_jet.structure_of<contrib::SoftDrop>().symmetry();

            _h_R04_z_g_20_25->Fill(z_subjets);
            _h_R04_theta_g_20_25->Fill(delta_R_subjets);

	    correlation_theta_20_25->Fill(delta_R_subjets, theta_sj);
	    correlation_z_20_25->Fill(z_subjets, z_sj);
	    
                // SoftDrop failed, handle the case as needed
                // e.g., skip this jet or perform alternative analysis
      } else {
	_hmult_R04_pT_20_25GeV->Fill(jet.constituents().size());
      }
        
      // 25 to 30 pT

      if (jet.pt() > 25 and jet.pt() < 30 ){
	// cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
	_hjetpT_R04->Fill(jet.perp());
	pseudorapidity = jet.eta();
	_hjeteta_R04->Fill(pseudorapidity);	
	_hmult_R04->Fill(jet.constituents().size());
	
	ClusterSequence clustSeqCA(jet.constituents(), jetDefCA);
	vector<PseudoJet> cambridgeJets = sorted_by_pt(clustSeqCA.inclusive_jets());


	// SoftDrop parameters
	double z_cut = 0.20;
	double beta = 0.0;
	contrib::SoftDrop sd(beta, z_cut);
	//! get subjets
      
	_h_R04_z_sj_25_30->Fill(z_sj);
	_h_R04_theta_sj_25_30->Fill(theta_sj);
	
	PseudoJet sd_jet = sd(jet);
	if (sd_jet == 0)
	  continue;
	
	cout << "jet pT: " << sd_jet.perp() << endl;
	cout << "  delta_R between subjets: " << sd_jet.structure_of<contrib::SoftDrop>().delta_R() << endl;
	cout << "  symmetry measure(z):     " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;
	cout << " theta_sj: " << theta_sj << endl;
	cout << " z_sj: " << z_sj << endl;
	  // Fill histograms with delta_R and symmetry measure z
	  double delta_R_subjets = sd_jet.structure_of<contrib::SoftDrop>().delta_R();
	  double z_subjets = sd_jet.structure_of<contrib::SoftDrop>().symmetry();
	  
	  _h_R04_z_g_25_30->Fill(z_subjets);
	  _h_R04_theta_g_25_30->Fill(delta_R_subjets);

	  correlation_theta_25_30->Fill(delta_R_subjets, theta_sj);
	  correlation_z_25_30->Fill(z_subjets, z_sj);
	    
	  // SoftDrop failed, handle the case as needed
	  // e.g., skip this jet or perform alternative analysis
	
      } else {
	_hmult_R04_pT_25_30GeV->Fill(jet.constituents().size());
      }

      // 30 to 40 pT

      if (jet.pt() > 30 and jet.pt() < 40 ){
	// cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
	_hjetpT_R04->Fill(jet.perp());
	pseudorapidity = jet.eta();
	_hjeteta_R04->Fill(pseudorapidity);	
	_hmult_R04->Fill(jet.constituents().size());

	ClusterSequence clustSeqCA(jet.constituents(), jetDefCA);
	vector<PseudoJet> cambridgeJets = sorted_by_pt(clustSeqCA.inclusive_jets());

	// SoftDrop parameters
	double z_cut = 0.20;
	double beta = 0.0;
	contrib::SoftDrop sd(beta, z_cut);
	//! get subjets
	_h_R04_z_sj_30_40->Fill(z_sj);
	_h_R04_theta_sj_30_40->Fill(theta_sj);
	
            // Apply SoftDrop to the jet
	PseudoJet sd_jet = sd(jet);
	if (sd_jet == 0)
	  continue;
	cout << "jet pT: " << sd_jet.perp() << endl;
	cout << "  delta_R between subjets: " << sd_jet.structure_of<contrib::SoftDrop>().delta_R() << endl;
	cout << "  symmetry measure(z):     " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;
	cout << " theta_sj: " << theta_sj << endl;
	cout << " z_sj: " << z_sj << endl;
	double delta_R_subjets = sd_jet.structure_of<contrib::SoftDrop>().delta_R();
	double z_subjets = sd_jet.structure_of<contrib::SoftDrop>().symmetry();

	_h_R04_z_g_30_40->Fill(z_subjets);
	_h_R04_theta_g_30_40->Fill(delta_R_subjets);

	correlation_theta_30_40->Fill(delta_R_subjets, theta_sj);
	correlation_z_30_40->Fill(z_subjets, z_sj);
	    
                // SoftDrop failed, handle the case as needed
                // e.g., skip this jet or perform alternative analysis
      } else {
	_hmult_R04_pT_30_40GeV->Fill(jet.constituents().size());
      }
    
    //! jet loop
    // Rjet = 0.4 End

    //filled nEvent in histogram
    _hmult_R04->Fill( mult);
    
    //   std::// cout << "iZ = " << nEvent << std::endl;
    
  }//! event loop ends for pT

  
  // End of event loop. Statistics. Histograms. Done.
    pythia.stat();
  }
  // Show histogram. Can close it
  // mult->Draw();
  //  std::// cout << "\nDouble click on the histogram window to quit.\n";
  // gPad->WaitPrimitive();

  // Normalize 15-20 hists

  _h_R04_z_sj_15_20->Scale(1./_h_R04_z_sj_15_20->Integral());
  _h_R04_theta_sj_15_20->Scale(1./_h_R04_theta_sj_15_20->Integral());

  _h_R04_z_sj_15_20->Scale(1./0.05);
  _h_R04_theta_sj_15_20->Scale(1./0.05);

  // Normalize 20-25 hists


  _h_R04_z_sj_20_25->Scale(1./_h_R04_z_sj_20_25->Integral());
  _h_R04_theta_sj_20_25->Scale(1./_h_R04_theta_sj_20_25->Integral());

  _h_R04_z_sj_20_25->Scale(1./0.05);
  _h_R04_theta_sj_20_25->Scale(1./0.05);

 // Normalize 25-30 hists
  _h_R04_z_sj_25_30->Scale(1./_h_R04_z_sj_25_30->Integral());
  _h_R04_theta_sj_25_30->Scale(1./_h_R04_theta_sj_25_30->Integral());

  _h_R04_z_sj_25_30->Scale(1./0.05);
  _h_R04_theta_sj_25_30->Scale(1./0.05);
  
 // Normalize 30-40 hists
  
  _h_R04_z_sj_30_40->Scale(1./_h_R04_z_sj_30_40->Integral());
  _h_R04_theta_sj_30_40->Scale(1./_h_R04_theta_sj_30_40->Integral());

  _h_R04_z_sj_30_40->Scale(1./0.05);
  _h_R04_theta_sj_30_40->Scale(1./0.05);
  //SoftDrop Normalization
  // Normalize 15-20 hists

  _h_R04_z_g_15_20->Scale(1./_h_R04_z_g_15_20->Integral());
  _h_R04_theta_g_15_20->Scale(1./_h_R04_theta_g_15_20->Integral());

  _h_R04_z_g_15_20->Scale(1./0.05);
  _h_R04_theta_g_15_20->Scale(1./0.05);

  // Normalize 20-25 hists


  _h_R04_z_g_20_25->Scale(1./_h_R04_z_g_20_25->Integral());
  _h_R04_theta_g_20_25->Scale(1./_h_R04_theta_g_20_25->Integral());

  _h_R04_z_g_20_25->Scale(1./0.05);
  _h_R04_theta_g_20_25->Scale(1./0.05);

 // Normalize 25-30 hists
  _h_R04_z_g_25_30->Scale(1./_h_R04_z_g_25_30->Integral());
  _h_R04_theta_g_25_30->Scale(1./_h_R04_theta_g_25_30->Integral());

  _h_R04_z_g_25_30->Scale(1./0.05);
  _h_R04_theta_g_25_30->Scale(1./0.05);
  
 // Normalize 30-40 hists
  
  _h_R04_z_g_30_40->Scale(1./_h_R04_z_g_30_40->Integral());
  _h_R04_theta_g_30_40->Scale(1./_h_R04_theta_g_30_40->Integral());

  _h_R04_z_g_30_40->Scale(1./0.05);
  _h_R04_theta_g_30_40->Scale(1./0.05);
     
  // Save histogram on file and close file
  outFile->Write();
  outFile->Close();
  
  // Done.
  return 0;
  
}

