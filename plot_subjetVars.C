#include <iostream>
#include "plot.h"
#include <TGraphErrors.h>
#include <TRandom3.h>

using namespace std;

void plot_subjetVars(){

 TH1::SetDefaultSumw2();
 gStyle->SetOptStat(0);

  TFile * fin = TFile::Open("hist.root");  
  TH1F * _h_R01_z_sj_15_20 = (TH1F*)fin->Get("R01_z_sj_15_20");
  _h_R01_z_sj_15_20->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_z_sj_20_25 = (TH1F*)fin->Get("R01_z_sj_20_25");
  _h_R01_z_sj_20_25->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_z_sj_25_30 = (TH1F*)fin->Get("R01_z_sj_25_30");
  _h_R01_z_sj_25_30->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_z_sj_30_40 = (TH1F*)fin->Get("R01_z_sj_30_40");
  _h_R01_z_sj_30_40->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_theta_sj_15_20 = (TH1F*)fin->Get("R01_theta_sj_15_20");
  _h_R01_theta_sj_15_20->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_theta_sj_20_25 = (TH1F*)fin->Get("R01_theta_sj_20_25");
  _h_R01_theta_sj_20_25->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_theta_sj_25_30 = (TH1F*)fin->Get("R01_theta_sj_25_30");
  _h_R01_theta_sj_25_30->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _h_R01_theta_sj_30_40 = (TH1F*)fin->Get("R01_theta_sj_30_40");
  _h_R01_theta_sj_30_40->Sumw2(); // Enable Sumw2 for this histogram
  TH1F * _hjetpT_R04 = (TH1F*)fin->Get("mult_R04");
  TH1F *_hjeteta_R06 = new TH1F("jeteta_R06","pseudorapidity", 50, -0.4, 0.4);
  cout<< "passed here "<<endl;
  
  /*
  TCanvas * Spectra04 = new TCanvas("Spectra04", " ", 500, 500);

  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();

  Spectra04->SetLogy();

  _hjeteta_R06->SetTitle(" ");
  _hjeteta_R06->SetYTitle("(#frac{1}{N_{jet}}) #frac{dN}{dp_{T}}");
  _hjeteta_R06->GetYaxis()->SetTitleOffset(1.4);
  _hjeteta_R06->GetYaxis()->SetTitleSize(0.03);
  _hjeteta_R06->GetYaxis()->SetLabelSize(0.02);
  _jeteta_R06->SetXTitle("Jet p_{T} [GeV/c]");
  _jeteta_R06->GetXaxis()->SetLabelSize(0.02);
  _hjeteta_R06->GetYaxis()->CenterTitle(true);

  _hjeteta_R06->SetMarkerStyle(29);
  _hjeteta_R06->SetMarkerColor(3);
  
  
   _jeteta_R06->SetAxisRange(10, 50, "X");

   _hjeteta_R06->jeteta_R06->Draw("hist C same");

   drawText("p+p #sqrt{s} = 200 GeV", 0.5, 0.85, 14);
   drawText("anti-k_{T} R=0.4 jet, |#eta_{jet}| < 0.6", 0.5, 0.8, 14);
   //  drawText("15 < p_{T} < 20 [GeV/c] ", 0.5, 0.75, 14);
  
   Spectra04->SaveAs("RHIC_pthat20_eta_R06.pdf", "RECREATE");

  */
  double relativeUncertainty = 0.05;


  TCanvas * csubjetR01 = new TCanvas("csubjetR01", " ", 1500, 500);
  
  makeMultiPanelCanvasWithGap(csubjetR01, 4, 2, 0.2, 0.2, 0.2, 0.2, 0.08, 0.01);
 

  // TH1F * hdummy_jetpT = (TH1F*) _h_R01_z_sj_15_20->Clone("hdummy_jetpT");
  // hdummy_jetpT->Reset();
  // hdummy_jetpT->SetAxisRange(0, 5, "Y");
  
 
  csubjetR01->cd(1);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  _h_R01_z_sj_15_20 ->SetLineStyle(1);
  _h_R01_z_sj_15_20->SetLineWidth(1);
  _h_R01_z_sj_15_20->SetTitle(" ");
  _h_R01_z_sj_15_20->SetYTitle("(1/N_{jet}) dN/dz_{sj}");
  _h_R01_z_sj_15_20->GetYaxis()->SetTitleOffset(0.8);
  _h_R01_z_sj_15_20->GetYaxis()->SetTitleSize(0.07);
  _h_R01_z_sj_15_20->GetYaxis()->SetLabelSize(0.04);
  _h_R01_z_sj_15_20->GetYaxis()->CenterTitle(true);

  _h_R01_z_sj_15_20->SetXTitle("z_{sj}");
  _h_R01_z_sj_15_20->GetXaxis()->SetTitleSize(0.07);
  _h_R01_z_sj_15_20->GetXaxis()->CenterTitle(true);
  _h_R01_z_sj_15_20->GetXaxis()->SetLabelSize(0.04);
  _h_R01_z_sj_15_20->SetMarkerSize(1.0);
  _h_R01_z_sj_15_20->SetAxisRange(0, 5.5, "Y");
  _h_R01_z_sj_15_20->SetAxisRange(0, 0.5, "X");
  //  _h_R01_z_sj_15_20->Draw("p E2 same");
  _h_R01_z_sj_15_20->Draw("hist C same");
  // Create a TGraphErrors for error bars
    int nbins15 = _h_R01_z_sj_15_20->GetNbinsX();
    double* x15 = new double[nbins15];
    double* y15 = new double[nbins15];
    double* ex15 = new double[nbins15];
    double* ey15 = new double[nbins15];
    for (int i = 1; i <= nbins15; ++i) {
        x15[i - 1] = _h_R01_z_sj_15_20->GetBinCenter(i);
        y15[i - 1] = _h_R01_z_sj_15_20->GetBinContent(i);
        ex15[i - 1] = 0.0; // Assumes uniform bin width
        ey15[i - 1] = _h_R01_z_sj_15_20->GetBinError(i);
    }
    TGraphErrors* errorGraph15 = new TGraphErrors(nbins15, x15, y15, ex15, ey15);
    errorGraph15->SetMarkerStyle(29);
    errorGraph15->SetMarkerColor(2);
    errorGraph15->Draw("p same");
    
    
  csubjetR01->cd(2);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  // cjetSpectra->cd(1)->SetLogy();
  // hdummy_jetpT->Draw();
  _h_R01_z_sj_20_25->SetTitle(" ");
  _h_R01_z_sj_20_25->SetXTitle("z_{sj}");
  _h_R01_z_sj_20_25->GetXaxis()->SetTitleSize(0.07);
  _h_R01_z_sj_20_25->GetXaxis()->CenterTitle(true);
  _h_R01_z_sj_20_25->GetXaxis()->SetLabelSize(0.04);
  _h_R01_z_sj_20_25->SetAxisRange(0, 5.5, "Y");
  _h_R01_z_sj_20_25->SetAxisRange(0, 0.5, "X");
  _h_R01_z_sj_20_25->SetMarkerSize(1.0);
  // _h_R01_z_sj_20_25->Draw("p E1 same");
  _h_R01_z_sj_20_25->Draw("hist C same");

  // Create a TGraphErrors for error bars
    int nbins20 = _h_R01_z_sj_20_25->GetNbinsX();
    double* x20 = new double[nbins20];
    double* y20 = new double[nbins20];
    double* ex20 = new double[nbins20];
    double* ey20 = new double[nbins20];
    for (int i = 1; i <= nbins20; ++i) {
        x20[i - 1] = _h_R01_z_sj_20_25->GetBinCenter(i);
        y20[i - 1] = _h_R01_z_sj_20_25->GetBinContent(i);
        ex20[i - 1] = 0.0; // Assumes uniform bin width
        ey20[i - 1] = _h_R01_z_sj_20_25->GetBinError(i);
    }
    TGraphErrors* errorGraph20 = new TGraphErrors(nbins20, x20, y20, ex20, ey20);
    errorGraph20->SetMarkerStyle(29);
    errorGraph20->SetMarkerColor(2);
    errorGraph20->Draw("p same");

  csubjetR01->cd(3);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  // cjetSpectra->cd(1)->SetLogy();
  // hdummy_jetpT->Draw();
  _h_R01_z_sj_25_30->SetMarkerStyle(29);
  _h_R01_z_sj_25_30->SetMarkerColor(2);
  _h_R01_z_sj_25_30->SetTitle(" ");
  _h_R01_z_sj_25_30->SetXTitle("z_{sj}");
  _h_R01_z_sj_25_30->GetXaxis()->SetTitleSize(0.07);
  _h_R01_z_sj_25_30->GetXaxis()->CenterTitle(true);
  _h_R01_z_sj_25_30->GetXaxis()->SetLabelSize(0.04);
  _h_R01_z_sj_25_30->SetAxisRange(0, 5.5, "Y");
  _h_R01_z_sj_25_30->SetAxisRange(0, 0.5, "X");
  _h_R01_z_sj_25_30->SetMarkerSize(1.0);
  //  _h_R01_z_sj_25_30->Draw("p E1 same");
  _h_R01_z_sj_25_30->Draw("hist C same");
// Create a TGraphErrors for error bars
    int nbins25 = _h_R01_z_sj_25_30->GetNbinsX();
    double* x25 = new double[nbins25];
    double* y25 = new double[nbins25];
    double* ex25 = new double[nbins25];
    double* ey25 = new double[nbins25];
    for (int i = 1; i <= nbins25; ++i) {
        x25[i - 1] = _h_R01_z_sj_25_30->GetBinCenter(i);
        y25[i - 1] = _h_R01_z_sj_25_30->GetBinContent(i);
        ex25[i - 1] = 0.0; // Assumes uniform bin width
        ey25[i - 1] = _h_R01_z_sj_25_30->GetBinError(i);
    }
    TGraphErrors* errorGraph25 = new TGraphErrors(nbins25, x25, y25, ex25, ey25);
    errorGraph25->SetMarkerStyle(29);
    errorGraph25->SetMarkerColor(2);
    errorGraph25->Draw("p same");

  csubjetR01->cd(4);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  _h_R01_z_sj_30_40->SetMarkerStyle(29);
  _h_R01_z_sj_30_40->SetMarkerColor(2);
  _h_R01_z_sj_30_40->SetTitle(" ");
  _h_R01_z_sj_30_40->SetXTitle("z_{sj}");
  _h_R01_z_sj_30_40->GetXaxis()->SetTitleSize(0.07);
  _h_R01_z_sj_30_40->GetXaxis()->CenterTitle(true);
  _h_R01_z_sj_30_40->GetXaxis()->SetLabelSize(0.04);
  _h_R01_z_sj_30_40->GetXaxis()->SetTitleSize(0.07);
  _h_R01_z_sj_30_40->SetAxisRange(0, 5.5, "Y");
  _h_R01_z_sj_30_40->SetAxisRange(0, 0.5, "X");
  _h_R01_z_sj_30_40->SetMarkerSize(1.0);
  //  _h_R01_z_sj_30_40->Draw("p E1 same");
  _h_R01_z_sj_30_40->Draw("hist C same");
  
   drawText("p+p #sqrt{s} = 200 GeV", 0.3, 0.8, 14);
   drawText("anti-k_{T} R=0.4 jets, |#eta_{jet}| < 0.6", 0.3, 0.7, 14);

   // Create a TGraphErrors for error bars
    int nbins30 = _h_R01_z_sj_30_40->GetNbinsX();
    double* x30 = new double[nbins30];
    double* y30 = new double[nbins30];
    double* ex30 = new double[nbins30];
    double* ey30 = new double[nbins30];
    for (int i = 1; i <= nbins30; ++i) {
        x30[i - 1] = _h_R01_z_sj_30_40->GetBinCenter(i);
        y30[i - 1] = _h_R01_z_sj_30_40->GetBinContent(i);
        ex30[i - 1] = 0.0; // Assumes uniform bin width
        ey30[i - 1] = _h_R01_z_sj_30_40->GetBinError(i);
    }
    TGraphErrors* errorGraph30 = new TGraphErrors(nbins15, x30, y30, ex30, ey30);
    errorGraph30->SetMarkerStyle(29);
    errorGraph30->SetMarkerColor(2);
    errorGraph30->Draw("p same");

  csubjetR01->cd(5);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  _h_R01_theta_sj_15_20->SetMarkerStyle(29);
  _h_R01_theta_sj_15_20->SetMarkerColor(2);
  _h_R01_theta_sj_15_20->SetMarkerSize(1.0);
  _h_R01_theta_sj_15_20->SetTitle(" ");
  _h_R01_theta_sj_15_20->SetYTitle("(1/N_{jet}) dN/d#theta_{sj}");
  _h_R01_theta_sj_15_20->SetAxisRange(0, 9.0, "Y");
  _h_R01_theta_sj_15_20->SetAxisRange(0, 0.5, "X");
  _h_R01_theta_sj_15_20->GetYaxis()->SetTitleOffset(0.8);
  _h_R01_theta_sj_15_20->GetYaxis()->SetTitleSize(0.07);
  _h_R01_theta_sj_15_20->GetYaxis()->SetLabelSize(0.04);
  _h_R01_theta_sj_15_20->GetYaxis()->CenterTitle(true);

 _h_R01_theta_sj_15_20->SetXTitle("#theta_{sj}");
 _h_R01_theta_sj_15_20->GetXaxis()->SetTitleSize(0.07);
 _h_R01_theta_sj_15_20->GetXaxis()->CenterTitle(true);
 _h_R01_theta_sj_15_20->GetXaxis()->SetLabelSize(0.04);

 _h_R01_theta_sj_15_20->Draw("hist C same");
  // Create a TGraphErrors for error bars
    int nbins15t = _h_R01_theta_sj_15_20->GetNbinsX();
    double* x15t = new double[nbins15t];
    double* y15t = new double[nbins15t];
    double* ex15t = new double[nbins15t];
    double* ey15t = new double[nbins15t];
    for (int i = 1; i <= nbins15t; ++i) {
        x15t[i - 1] = _h_R01_theta_sj_15_20->GetBinCenter(i);
        y15t[i - 1] = _h_R01_theta_sj_15_20->GetBinContent(i);
        ex15t[i - 1] = 0.0; // Assumes uniform bin width
        ey15t[i - 1] = _h_R01_theta_sj_15_20->GetBinError(i);
    }
    TGraphErrors* errorGraph15t = new TGraphErrors(nbins15t, x15t, y15t, ex15t, ey15t);
    errorGraph15t->SetMarkerStyle(29);
    errorGraph15t->SetMarkerColor(2);
    errorGraph15t->Draw("p same");

    drawText("15 < p_{T} < 20 [GeV/c]", 0.6, 0.8, 12);
    
  csubjetR01->cd(6);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  // cjetSpectra->cd(5)->SetLogy();
  // hdummy_jetpT->Draw();
  _h_R01_theta_sj_20_25->SetMarkerStyle(29);
  _h_R01_theta_sj_20_25->SetMarkerColor(2);
  _h_R01_theta_sj_20_25->SetMarkerSize(1.0);
  _h_R01_theta_sj_20_25->SetTitle(" ");
  _h_R01_theta_sj_20_25->SetXTitle("#theta_{sj}");
  _h_R01_theta_sj_20_25->GetXaxis()->SetTitleSize(0.07);
  _h_R01_theta_sj_20_25->GetXaxis()->CenterTitle(true);
  _h_R01_theta_sj_20_25->GetXaxis()->SetLabelSize(0.04);
  _h_R01_theta_sj_20_25->SetAxisRange(0, 9.0, "Y");
  _h_R01_theta_sj_20_25->SetAxisRange(0, 0.5, "X");
   _h_R01_theta_sj_20_25->Draw("hist C same");
  //  _h_R01_theta_sj_20_25->Draw("p E1 same");
   // Create a TGraphErrors for error bars
    int nbins20t = _h_R01_theta_sj_20_25->GetNbinsX();
    double* x20t = new double[nbins20t];
    double* y20t = new double[nbins20t];
    double* ex20t = new double[nbins20t];
    double* ey20t = new double[nbins20t];
    for (int i = 1; i <= nbins15t; ++i) {
        x20t[i - 1] = _h_R01_theta_sj_20_25->GetBinCenter(i);
        y20t[i - 1] = _h_R01_theta_sj_20_25->GetBinContent(i);
        ex20t[i - 1] = 0.0; // Assumes uniform bin width
        ey20t[i - 1] = _h_R01_theta_sj_20_25->GetBinError(i);
    }
    TGraphErrors* errorGraph20t = new TGraphErrors(nbins20t, x20t, y20t, ex20t, ey20t);
    errorGraph20t->SetMarkerStyle(29);
    errorGraph20t->SetMarkerColor(2);
    errorGraph20t->Draw("p same");
 drawText("20 < p_{T} < 25 [GeV/c]", 0.5, 0.8, 12);

  csubjetR01->cd(7);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  // cjetSpectra->cd(5)->SetLogy();
  // hdummy_jetpT->Draw();
  _h_R01_theta_sj_25_30->SetMarkerStyle(29);
  _h_R01_theta_sj_25_30->SetMarkerColor(2);
  _h_R01_theta_sj_25_30->SetMarkerSize(1.0);
  _h_R01_theta_sj_25_30->SetTitle(" ");
  _h_R01_theta_sj_25_30->SetXTitle("#theta_{sj}");
  _h_R01_theta_sj_25_30->GetXaxis()->SetTitleSize(0.07);
  _h_R01_theta_sj_25_30->GetXaxis()->CenterTitle(true);
  _h_R01_theta_sj_25_30->GetXaxis()->SetLabelSize(0.04);
  _h_R01_theta_sj_25_30->SetAxisRange(0, 9.0, "Y");
  _h_R01_theta_sj_25_30->SetAxisRange(0, 0.5, "X");
  // _h_R01_theta_sj_25_30->Draw("p E1 same");

  _h_R01_theta_sj_25_30->Draw("hist C same");
 // Create a TGraphErrors for error bars
    int nbins25t = _h_R01_theta_sj_25_30->GetNbinsX();
    double* x25t = new double[nbins25t];
    double* y25t = new double[nbins25t];
    double* ex25t = new double[nbins25t];
    double* ey25t = new double[nbins25t];
    for (int i = 1; i <= nbins25t; ++i) {
        x25t[i - 1] = _h_R01_theta_sj_25_30->GetBinCenter(i);
        y25t[i - 1] = _h_R01_theta_sj_25_30->GetBinContent(i);
        ex25t[i - 1] = 0.0; // Assumes uniform bin width
        ey25t[i - 1] = _h_R01_theta_sj_25_30->GetBinError(i);
    }
    TGraphErrors* errorGraph25t = new TGraphErrors(nbins25t, x25t, y25t, ex25t, ey25t);
    errorGraph25t->SetMarkerStyle(29);
    errorGraph25t->SetMarkerColor(2);
    errorGraph25t->Draw("p same");
  drawText("25 < p_{T} < 30 [GeV/c]", 0.5, 0.8, 12);

  csubjetR01->cd(8);
  gStyle->SetErrorX(0);
  gPad->SetTickx();
  gPad->SetTicky();
  _h_R01_theta_sj_30_40->SetMarkerStyle(29);
  _h_R01_theta_sj_30_40->SetMarkerColor(2);
  _h_R01_theta_sj_30_40->SetMarkerSize(1.0);
  _h_R01_theta_sj_30_40->SetTitle(" ");
  _h_R01_theta_sj_30_40->SetXTitle("#theta_{sj}");
  _h_R01_theta_sj_30_40->GetXaxis()->SetTitleSize(0.07);
  _h_R01_theta_sj_30_40->GetXaxis()->CenterTitle(true);
  _h_R01_theta_sj_30_40->GetXaxis()->SetLabelSize(0.04);
  _h_R01_theta_sj_30_40->GetXaxis()->SetTitleSize(0.07);
  _h_R01_theta_sj_30_40->SetAxisRange(0, 9.0, "Y");
  _h_R01_theta_sj_30_40->SetAxisRange(0, 0.5, "X");
  //  _h_R01_theta_sj_30_40->Draw("p E1 same");
  _h_R01_theta_sj_30_40->Draw("hist C same");
   // Create a TGraphErrors for error bars
    int nbins30t = _h_R01_theta_sj_30_40->GetNbinsX();
    double* x30t = new double[nbins30t];
    double* y30t = new double[nbins30t];
    double* ex30t = new double[nbins30t];
    double* ey30t = new double[nbins30t];
    for (int i = 1; i <= nbins30t; ++i) {
        x30t[i - 1] = _h_R01_theta_sj_30_40->GetBinCenter(i);
        y30t[i - 1] = _h_R01_theta_sj_30_40->GetBinContent(i);
        ex30t[i - 1] = 0.0; // Assumes uniform bin width
        ey30t[i - 1] = _h_R01_theta_sj_30_40->GetBinError(i);
    }
    TGraphErrors* errorGraph30t = new TGraphErrors(nbins30t, x30t, y30t, ex30t, ey30t);
    errorGraph30t->SetMarkerStyle(29);
    errorGraph30t->SetMarkerColor(2);
    errorGraph30t->Draw("p same");

   drawText("30 < p_{T} < 40 [GeV/c]", 0.5, 0.8, 12);
  
  csubjetR01->SaveAs("RHIC_subjetR04_AKT.pdf", "RECREATE");


  
}
