#include <algorithm>

void DrawDistributionAMCATNLOPOWHEG(std::string var = "jetpt1", int NBIN = 1000, int MIN = 0, int MAX = 1000, std::string varHR = ""){

 if (varHR == "") {
  varHR = var;
 }

 gStyle->SetOptStat(0);


 TFile* fCMS_amcatnlo   = new TFile ("fAll_amcatnlo.root");
 TTree* tCMS_amcatnlo   =  (TTree*) fCMS_amcatnlo   -> Get ("ntu");

 TFile* fCMS_powheg   = new TFile ("fAll_powheg.root");
 TTree* tCMS_powheg   =  (TTree*) fCMS_powheg   -> Get ("ntu");

 //--------------------------
 TH1F* h_e0_CMS_amcatnlo   = new TH1F("CMS_amcatnlo",varHR.c_str(),NBIN,MIN,MAX);
 TH1F* h_e0_CMS_powheg   = new TH1F("CMS_powheg",varHR.c_str(),NBIN,MIN,MAX);

 TString toDraw;

 toDraw = Form ("%s >> CMS_amcatnlo",var.c_str());       tCMS_amcatnlo    -> Draw(toDraw.Data(),"w11","goff");
 toDraw = Form ("%s >> CMS_powheg",var.c_str());         tCMS_powheg      -> Draw(toDraw.Data(),"w11","goff");


 h_e0_CMS_amcatnlo->SetMarkerColor(kRed);
 h_e0_CMS_amcatnlo->SetLineWidth(2);
 h_e0_CMS_amcatnlo->SetLineColor(kRed);
 h_e0_CMS_amcatnlo->GetXaxis()->SetTitle(varHR.c_str());
 h_e0_CMS_amcatnlo->GetYaxis()->SetTitle("events");

 h_e0_CMS_powheg->SetMarkerColor(kBlue);
 h_e0_CMS_powheg->SetLineWidth(2);
 h_e0_CMS_powheg->SetLineColor(kBlue);
 h_e0_CMS_powheg->GetXaxis()->SetTitle(varHR.c_str());
 h_e0_CMS_powheg->GetYaxis()->SetTitle("events");

 TLegend* leg = new TLegend(0.5,0.7,0.9,0.9);
 leg->AddEntry(h_e0_CMS_amcatnlo,"CMS aMC@NLO","lp");
 leg->AddEntry(h_e0_CMS_powheg,"CMS POWHEG","lp");
 leg->SetFillColor(0);

 TCanvas* cn = new TCanvas ("cn","cn",800,600);
 h_e0_CMS_amcatnlo->DrawClone();
 h_e0_CMS_powheg->DrawClone("same");
 leg->Draw();
 cn->SetGrid();

 TCanvas* cn_norm = new TCanvas ("cn_norm","cn_norm",800,600);
 h_e0_CMS_amcatnlo->GetYaxis()->SetTitle("a.u.");
 h_e0_CMS_amcatnlo->DrawNormalized();
 h_e0_CMS_powheg->DrawNormalized("same");
 leg->Draw();
 cn_norm->SetGrid();


}




