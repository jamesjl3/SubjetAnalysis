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
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh" 
#include "fastjet/contrib/ModifiedMassDropTagger.hh"
using namespace fastjet;

// ROOT, for histogramming. 
#include "TH1.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"


int main(int argc, char* argv[]) {

  // Number of events.
  int nEvent = 10000000;

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
    
  JetDefinition jetDefAKT_R005( antikt_algorithm, radius[0]);
  JetDefinition jetDefAKT_R01( antikt_algorithm, radius[1]);
  JetDefinition jetDefAKT_R02( antikt_algorithm, radius[2]);
  JetDefinition jetDefAKT_R04( antikt_algorithm, radius[3]);
  JetDefinition jetDefAKT_R06( antikt_algorithm, radius[4]);


  //! create a new ROOT histogram for jet transverse momentum pT


  TFile* outFile = new TFile("hist.root", "RECREATE");
  outFile->cd();

  //  std::// cout << "created hist.root! yay!" << std::endl;
    
  // Book histogram.
  TH1F *_h_event_mult= new TH1F("mult","total multiplicity for event", 60, 0, 60);
  
  TH1F *_hmult_R005= new TH1F("mult_R005","total number of constituents inside R=0.05 jets", 30, 0, 30);
  TH1F *_hmult_R005_pT_lt_5GeV= new TH1F("mult_R005_pT_lt_5GeV","total number of constituents inside R=0.05 jets with p_{T} < 5.0", 30, 0, 30);
  
  TH1F *_hmult_R01= new TH1F("mult_R01","total number of constituents inside R=0.1 jets", 30, 0, 30);
  TH1F *_hmult_R01_pT_lt_5GeV= new TH1F("mult_R01_pT_lt_5GeV","total number of constituents inside R=0.1 jets with p_{T} < 5.0", 30, 0, 30);


  TH1F *_h_R01_z_sj_15_20= new TH1F("R01_z_sj_15_20","z_sj in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R01_theta_sj_15_20= new TH1F("R01_theta_sj_15_20","theta_sj in subjets 1 & 2", 10, 0, 0.5);
  
  TH1F *_h_R01_z_sj_20_25= new TH1F("R01_z_sj_20_25","z_sj in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R01_theta_sj_20_25= new TH1F("R01_theta_sj_20_25","theta_sj in subjets 1 & 2", 10, 0, 0.5);

  
  TH1F *_h_R01_z_sj_25_30= new TH1F("R01_z_sj_25_30","z_sj in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R01_theta_sj_25_30= new TH1F("R01_theta_sj_25_30","theta_sj in subjets 1 & 2", 10, 0, 0.5);

  
  TH1F *_h_R01_z_sj_30_40= new TH1F("R01_z_sj_30_40","z_sj in subjets 1 & 2", 10, 0, 0.5);
  TH1F *_h_R01_theta_sj_30_40= new TH1F("R01_theta_sj_30_40","theta_sj in subjets 1 & 2", 10, 0, 0.5);

  
  TH1F *_hmult_R02= new TH1F("mult_R02","total number of constituents inside R=0.2 jets", 30, 0, 30);
  
  TH1F *_hmult_R04= new TH1F("mult_R04","total number of constituents inside R=0.4 jets", 30, 0, 30);
  
  TH1F *_hmult_R04_pT_lt_5GeV= new TH1F("mult_R04_pT_lt_5GeV","total number of constituents inside R=0.4 jets with p_{T} < 5.0", 30, 0, 30);

  TH1F *_hmult_R04_pT_15_20GeV= new TH1F("mult_R04_pT_15_20GeV","total number of constituents inside R=0.4 jets with 15< p_{T} < 20", 30, 0, 30);

  TH1F *_hmult_R04_pT_20_25GeV= new TH1F("mult_R04_pT_20_25GeV","total number of constituents inside R=0.4 jets with 20 < p_{T} < 25", 30, 0, 30);

  TH1F *_hmult_R04_pT_25_30GeV= new TH1F("mult_R04_pT_25_30GeV","total number of constituents inside R=0.4 jets with 25 < p_{T} < 30", 30, 0, 30);

  TH1F *_hmult_R04_pT_30_40GeV= new TH1F("mult_R04_pT_30_40GeV","total number of constituents inside R=0.4 jets with 30 < p_{T} < 40", 30, 0, 30);

  TH1F *_hmult_R06= new TH1F("mult_R06","total number of constituents inside R=0.6 jets", 30, 0, 30);

  TH1F *_hjetpT_R005 = new TH1F("jetpT_R005","jet transverse momentum for R=0.05 jets", 100, 0, 100);
  TH1F *_hjetpT_R01 = new TH1F("jetpT_R01","jet transverse momentum for R=0.1 jets", 100, 0, 100);
  TH1F *_hjetpT_R02 = new TH1F("jetpT_R02","jet transverse momentum for R=0.2 jets", 100, 0, 100);
  TH1F *_hjetpT_R04 = new TH1F("jetpT_R04","jet transverse momentum 15 to 20 for R=0.4 jets", 100, 0, 100);
  //  TH1F *_hjetpT_R04_20_25 = new TH1F("jetpT_R04_20_25","jet transverse momentum 20 to 25 for R=0.4 jets", 100, 0, 100);
  //  TH1F *_hjetpT_R04_25_30 = new TH1F("jetpT_R04_25_30","jet transverse momentum 25 to 30 for R=0.4 jets", 100, 0, 100);
  //    TH1F *_hjetpT_R04_30_40 = new TH1F("jetpT_R04_30_40","jet transverse momentum 30 to 40 for R=0.4 jets", 100, 0, 100);
  TH1F *_hjetpT_R06 = new TH1F("jetpT_R06","jet transverse momentum for R=0.6 jets", 100, 0, 100);

  TH1F *_hjeteta_R005 = new TH1F("jeteta_R005", "jet pseudorapidity for R=0.05 jets", 50,-0.95, 0.95);
  TH1F *_hjeteta_R01 = new TH1F("jeteta_R01"," jet pseudorapidity for R=0.1 jets", 50, -0.9, 0.9);
  TH1F *_hjeteta_R02 = new TH1F("jeteta_R02","jet pseudorapidity for R=0.2 jets", 50, -0.8, 0.8);
  TH1F *_hjeteta_R04 = new TH1F("jeteta_R04","jet pseudorapidity for R=0.4 jets", 50, -0.6, 0.6);
  //  TH1F *_hjeteta_R04_20_25 = new TH1F("jeteta_R04_20_25","jet pseudorapidity for R=0.4 jets", 50, -0.6, 0.6);
  //   TH1F *_hjeteta_R04_25_30 = new TH1F("jeteta_R04_25_30","jet pseudorapidity for R=0.4 jets", 50, -0.6, 0.6);
  //   TH1F *_hjeteta_R04_30_40 = new TH1F("jeteta_R04_30_40","jet pseudorapidity for R=0.4 jets", 50, -0.6, 0.6);
  TH1F *_hjeteta_R06 = new TH1F("jeteta_R06","jet pseudorapidity for R=0.6 jets", 50, -0.4, 0.4);
  
					    
  // Begin event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    if (!pythia.next()) continue;

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
   
    // Run Fastjet anti-kT algorithm and sort jets in pT order. R=0.05
    ClusterSequence clustSeq_R005( particles, jetDefAKT_R005 );
    vector<PseudoJet> sortedJets_R005 = sorted_by_pt( clustSeq_R005.inclusive_jets() );
    // Rjet = 0.005 Begin

    //! create a loop to run over the jets -
    for (int j = 0; j < sortedJets_R005.size(); ++j) {
      PseudoJet jet = sortedJets_R005.at(j);
      if(fabs(jet.eta()) > 0.95)
	continue;
      if(jet.pt()  > 5){
	// cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
	_hjetpT_R005->Fill(jet.perp());
	pseudorapidity = jet.eta();
	_hjeteta_R005->Fill(pseudorapidity);	
	_hmult_R005->Fill(jet.constituents().size());
      } else {
	_hmult_R005_pT_lt_5GeV->Fill(jet.constituents().size());
      }
      
    }//! jet loop
    // Rjet = 0.005 End

    // Rjet = 0.1 Begin

    // Run Fastjet anti-kT algorithm and sort jets in pT order.vR = 0.1
    ClusterSequence clustSeq_R01( particles, jetDefAKT_R01 );
    vector<PseudoJet> sortedJets_R01 = sorted_by_pt( clustSeq_R01.inclusive_jets() );
    
    //! create a loop to run over the jets -
    for (int j = 0; j < sortedJets_R01.size(); ++j) {
      PseudoJet jet = sortedJets_R01.at(j);
      if(fabs(jet.eta()) > 0.9)
	continue;
      if(jet.pt() > 5){
	// cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
	_hjetpT_R01->Fill(jet.perp());
	pseudorapidity = jet.eta();
	_hjeteta_R01->Fill(pseudorapidity);	
	_hmult_R01->Fill(jet.constituents().size());
      } else {
	_hmult_R01_pT_lt_5GeV->Fill(jet.constituents().size());
      }
      
    }//! jet loop
    // Rjet = 0.1 End


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


	//! get subjets 15 to 20 pT
	_h_R01_z_sj_15_20->Fill(z_sj);
	_h_R01_theta_sj_15_20->Fill(theta_sj);

	  
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


	//! get subjets 20 to 25 pT
	_h_R01_z_sj_20_25->Fill(z_sj);
	_h_R01_theta_sj_20_25->Fill(theta_sj);
	  
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


	//! get subjets
        theta_sj = sj1.delta_R(sj2);
	z_sj = sj2.pt()/(sj2.pt()+sj1.pt());
      
	_h_R01_z_sj_25_30->Fill(z_sj);
	_h_R01_theta_sj_25_30->Fill(theta_sj);
		
	
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


	//! get subjets
	_h_R01_z_sj_30_40->Fill(z_sj);
	_h_R01_theta_sj_30_40->Fill(theta_sj);
		
	
      } else {
	_hmult_R04_pT_30_40GeV->Fill(jet.constituents().size());
      }
      
    }//! jet loop
    // Rjet = 0.4 End

    
    // Rjet = 0.6 Begin
    // Run Fastjet anti-kT algorithm and sort jets in pT order.
    ClusterSequence clustSeq_R06( particles, jetDefAKT_R06 );
    vector<PseudoJet> sortedJets_R06 = sorted_by_pt( clustSeq_R06.inclusive_jets() );
    
    //! create a loop to run over the jets -
    for (int j = 0; j < sortedJets_R06.size(); ++j) {
      PseudoJet jet = sortedJets_R06.at(j);
      if(fabs(jet.eta()) > 0.4)
	continue;
      if(jet.pt() < 5)
	continue;
      // cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
      _hjetpT_R06->Fill(jet.perp());
      pseudorapidity = jet.eta();
      _hjeteta_R06->Fill(pseudorapidity);

      _hmult_R06->Fill(jet.constituents().size());
      
    }//! jet loop

    //! R=0.2 JETS

    // Run Fastjet anti-kT algorithm and sort jets in pT order.
    ClusterSequence clustSeq_R02( particles, jetDefAKT_R02 );
    vector<PseudoJet> sortedJets_R02 = sorted_by_pt( clustSeq_R02.inclusive_jets() );
    
    //! create a loop to run over the jets -
    for (int j = 0; j < sortedJets_R02.size(); ++j) {

      PseudoJet jet = sortedJets_R02.at(j);
      if(fabs(jet.eta()) > 0.8)
	continue;
      if(jet.pt() < 5)
	continue;
      // cout<<"sorted jets at "<<j<<" the pT = "<<jet.pt()<<endl;
      _hjetpT_R02->Fill(jet.perp());
      pseudorapidity = jet.eta();
      _hjeteta_R02->Fill(pseudorapidity);

      _hmult_R02->Fill(jet.constituents().size());
      
    }//! jet loop
    
	 
    // cout<<" passed here :) "<<endl;

    //filled nEvent in histogram
    _h_event_mult->Fill( mult);
    
    //   std::// cout << "iZ = " << nEvent << std::endl;
    
  }//! event loop ends for pT

  
  // End of event loop. Statistics. Histograms. Done.
  pythia.stat();

  // Show histogram. Can close it
  // mult->Draw();
  //  std::// cout << "\nDouble click on the histogram window to quit.\n";
  // gPad->WaitPrimitive();

  // Normalize 15-20 hists

  _h_R01_z_sj_15_20->Scale(1./_h_R01_z_sj_15_20->Integral());
  _h_R01_theta_sj_15_20->Scale(1./_h_R01_theta_sj_15_20->Integral());

  _h_R01_z_sj_15_20->Scale(1./0.05);
  _h_R01_theta_sj_15_20->Scale(1./0.05);

  // Normalize 20-25 hists


  _h_R01_z_sj_20_25->Scale(1./_h_R01_z_sj_20_25->Integral());
  _h_R01_theta_sj_20_25->Scale(1./_h_R01_theta_sj_20_25->Integral());

  _h_R01_z_sj_20_25->Scale(1./0.05);
  _h_R01_theta_sj_20_25->Scale(1./0.05);

 // Normalize 25-30 hists
  _h_R01_z_sj_25_30->Scale(1./_h_R01_z_sj_25_30->Integral());
  _h_R01_theta_sj_25_30->Scale(1./_h_R01_theta_sj_25_30->Integral());

  _h_R01_z_sj_25_30->Scale(1./0.05);
  _h_R01_theta_sj_25_30->Scale(1./0.05);
  
 // Normalize 30-40 hists
  
   _h_R01_z_sj_30_40->Scale(1./_h_R01_z_sj_30_40->Integral());
  _h_R01_theta_sj_30_40->Scale(1./_h_R01_theta_sj_30_40->Integral());

  _h_R01_z_sj_30_40->Scale(1./0.05);
  _h_R01_theta_sj_30_40->Scale(1./0.05);
     
  // Save histogram on file and close file
  outFile->Write();
  outFile->Close();
  
  // Done.
  return 0;
}


