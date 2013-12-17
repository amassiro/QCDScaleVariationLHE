{
 TFile* fUp = new TFile ("up.root");
 TFile* fCe = new TFile ("cen.root");
 TFile* fDo = new TFile ("down.root");
 TTree* tUp = (TTree*) fUp -> Get ("ntu");
 TTree* tCe = (TTree*) fCe -> Get ("ntu");
 TTree* tDo = (TTree*) fDo -> Get ("ntu");

 Double_t X[200];
 Double_t Y_t01[200];
 Double_t Y_t11[200];
 Double_t Y_sigma0[200];
 Double_t Y_sigma1[200];
 Double_t Y_error_0jet[200];

 int n = 100;
 for (int i=0; i<n; i++) {
  double threshold = 20+i;
  X[i] = threshold;
  TString s1 = Form ("jetpt1>=%f",threshold);
  TString s2 = Form ("jetpt2>=%f",threshold);

  double c0 = tCe->GetEntries();
  double c1 = tCe->GetEntries(s1.Data());
  double c2 = tCe->GetEntries(s2.Data());

  double f0 = (c0-c1)/c0;
  double f1 = (c1-c2)/c0;
  double f2 = (c2)/c0;

  double sigma0 = (tUp->GetEntries()-tDo->GetEntries() ) / (tUp->GetEntries()+tDo->GetEntries() );
  double sigma1 = fabs(tUp->GetEntries(s1.Data())-tDo->GetEntries(s1.Data()) ) / fabs(tUp->GetEntries(s1.Data())+tDo->GetEntries(s1.Data()) ) ;
  double sigma2 = fabs(tUp->GetEntries(s2.Data())-tDo->GetEntries(s2.Data()) ) / fabs(tUp->GetEntries(s2.Data())+tDo->GetEntries(s2.Data()) +1);

 // k = exp (sigma)
  double k0 = exp(sigma0);
  double k1 = exp(sigma1);
  double k2 = exp(sigma2);

 // theta
  double t00 = pow(k0,1./f0);
  double t01 = pow(k1,-(f1+f2)/f0);
  double t11 = pow(k1,(f1+f2)/f0);
  double t12 = pow(k2,-f2/f1);
  double t22 = k2;

  std::cout << " thr = " << threshold << " :: t01 = " << t01 << " t11 = " << t11 << " :: k0 = " << k0 << " k1 = " << k1 << " :: sigma0 = " << sigma0 << " sigma1 = " << sigma1 << std::endl;
  Y_t01[i] = t01;
  Y_t11[i] = t11;
  Y_error_0jet[i] = 1. - Y_t01[i];
  Y_sigma0[i] = sigma0;
  Y_sigma1[i] = sigma1;
 }

 //--------------------------
 TGraph* g_e0 = new TGraph(n,X,Y_error_0jet);

 TCanvas* ce0 = new TCanvas ("ce0","ce0",800,600);
 g_e0->SetMarkerSize(1);
 g_e0->SetMarkerStyle(20);
 g_e0->SetMarkerColor(kRed);
 g_e0->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_e0->Draw("apl");

 //--------------------------
 TGraph* g_t01 = new TGraph(n,X,Y_t01);
 TGraph* g_t11 = new TGraph(n,X,Y_t11);

 TCanvas* c01 = new TCanvas ("c01","c01",800,600);
 g_t01->SetMarkerSize(1);
 g_t01->SetMarkerStyle(20);
 g_t01->SetMarkerColor(kRed);
 g_t01->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_t01->Draw("apl");

 TCanvas* c11 = new TCanvas ("c11","c11",800,600);
 g_t11->SetMarkerSize(1);
 g_t11->SetMarkerStyle(20);
 g_t11->SetMarkerColor(kRed);
 g_t11->Draw("apl");

 //--------------------------
 TGraph* g_sigma0 = new TGraph(n,X,Y_sigma0);
 TGraph* g_sigma1 = new TGraph(n,X,Y_sigma1);

 TCanvas* csigma0 = new TCanvas ("csigma0","csigma0",800,600);
 g_sigma0->SetMarkerSize(1);
 g_sigma0->SetMarkerStyle(20);
 g_sigma0->SetMarkerColor(kRed);
 g_sigma0->Draw("apl");

 TCanvas* csigma1 = new TCanvas ("csigma1","csigma1",800,600);
 g_sigma1->SetMarkerSize(1);
 g_sigma1->SetMarkerStyle(20);
 g_sigma1->SetMarkerColor(kRed);
 g_sigma1->Draw("apl");


}