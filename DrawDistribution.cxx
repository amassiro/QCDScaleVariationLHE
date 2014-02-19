#include <algorithm>

void DrawDistribution(std::string var = "jetpt1", int NBIN = 1000, int MIN = 0, int MAX = 1000, std::string varHR = ""){

 if (varHR == "") {
  varHR = var;
 }

 gStyle->SetOptStat(0);


 TFile* fCMS   = new TFile ("fAll.root");

 TTree* tCMS   =  (TTree*) fCMS   -> Get ("ntu");


 //--------------------------
 TH1F* h_e0_CMS   = new TH1F("CMS",varHR.c_str(),NBIN,MIN,MAX);

 TString toDraw;

 toDraw = Form ("%s >> CMS",var.c_str());       tCMS    -> Draw(toDraw.Data(),"","goff");


 h_e0_CMS->SetMarkerColor(kRed);
 h_e0_CMS->SetLineWidth(2);
 h_e0_CMS->SetLineColor(kRed);
 h_e0_CMS->GetXaxis()->SetTitle(varHR.c_str());
 h_e0_CMS->GetYaxis()->SetTitle("evetns");


 TLegend* leg = new TLegend(0.5,0.7,0.9,0.9);
 leg->AddEntry(h_e0_CMS,"CMS tune","lp");
 leg->SetFillColor(0);

 TCanvas* cn = new TCanvas ("cn","cn",800,600);
 h_e0_CMS->DrawNormalized();
 leg->Draw();
 cn->SetGrid();

}




