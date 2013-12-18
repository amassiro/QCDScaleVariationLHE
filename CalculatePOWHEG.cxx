{
 #include <algorithm>

 TFile* f0505 = new TFile ("f0505.root");
 TFile* f0510 = new TFile ("f0510.root");
 TFile* f1005 = new TFile ("f1005.root");
 TFile* f1010 = new TFile ("f1010.root");
 TFile* f1020 = new TFile ("f1020.root");
 TFile* f2010 = new TFile ("f2010.root");
 TFile* f2020 = new TFile ("f2020.root");

 TTree* t0505 = (TTree*) f0505 -> Get ("ntu");
 TTree* t0510 = (TTree*) f0510 -> Get ("ntu");
 TTree* t1005 = (TTree*) f1005 -> Get ("ntu");
 TTree* t1010 = (TTree*) f1010 -> Get ("ntu");
 TTree* t1020 = (TTree*) f1020 -> Get ("ntu");
 TTree* t2010 = (TTree*) f2010 -> Get ("ntu");
 TTree* t2020 = (TTree*) f2020 -> Get ("ntu");

 Double_t X[200];
 Double_t Y_f0[200];
 Double_t Y_f1[200];
 Double_t Y_t01[200];
 Double_t Y_t11[200];
 Double_t Y_sigma0[200];
 Double_t Y_sigma1[200];
 Double_t Y_error_0jet[200];
 Double_t Y_error_sigma_0jet[200];

 int n = 100;
 for (int i=0; i<n; i++) {
  double threshold = 25+i;
  X[i] = threshold;
  TString s1 = Form ("jetpt1>=%f",threshold);
  TString s2 = Form ("jetpt2>=%f",threshold);

  double c0 = 1. * t1010->GetEntries();
  double c1 = 1. * t1010->GetEntries(s1.Data());
  double c2 = 1. * t1010->GetEntries(s2.Data());

  double f0 = (c0-c1)/c0;
  double f1 = (c1-c2)/c0;
  double f2 = (c2)/c0;

  int xsec[100];

  xsec[0] = t0505->GetEntries(s1.Data());
  xsec[1] = t0510->GetEntries(s1.Data());
  xsec[2] = t1005->GetEntries(s1.Data());
  xsec[3] = t1020->GetEntries(s1.Data());
  xsec[4] = t2010->GetEntries(s1.Data());
  xsec[5] = t2020->GetEntries(s1.Data());

  int min = *std::min_element(xsec,xsec+6);
  int max = *std::max_element(xsec,xsec+6);

  double sigma0 = 0.;
  double sigma1 = 1.* abs(max-min) / c1;
  double sigma2 = 0.;

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

  std::cout << " thr = " << threshold << " :: t01 = " << t01 << " t11 = " << t11 << " :: k0 = " << k0 << " k1 = " << k1 << " :: sigma0 = " << sigma0 << " sigma1 = " << sigma1 << " = (" << max << " - " << min << " ) / " << c1 << std::endl;
  Y_t01[i] = t01;
  Y_t11[i] = t11;
  Y_error_0jet[i] = 1. - Y_t01[i];
  Y_sigma0[i] = sigma0;
  Y_sigma1[i] = sigma1;
  Y_f0[i] = f0;
  Y_f1[i] = f1;
  Y_error_sigma_0jet[i] = sigma1*c1/(c0-c1);
 }

 //--------------------------
 TGraph* g_esigma0 = new TGraph(n,X,Y_error_sigma_0jet);

 TCanvas* cesigma0 = new TCanvas ("cesigma0","cesigma0",800,600);
 g_esigma0->SetMarkerSize(1);
 g_esigma0->SetMarkerStyle(20);
 g_esigma0->SetMarkerColor(kRed);
 g_esigma0->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_esigma0->Draw("apl");


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

 //--------------------------
 TGraph* g_f0 = new TGraph(n,X,Y_f0);
 TGraph* g_f1 = new TGraph(n,X,Y_f1);

 TCanvas* cf0 = new TCanvas ("cf0","cf0",800,600);
 g_f0->SetMarkerSize(1);
 g_f0->SetMarkerStyle(20);
 g_f0->SetMarkerColor(kRed);
 g_f0->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_f0->Draw("apl");

 TCanvas* cf1 = new TCanvas ("cf1","cf1",800,600);
 g_f1->SetMarkerSize(1);
 g_f1->SetMarkerStyle(20);
 g_f1->SetMarkerColor(kRed);
 g_f1->Draw("apl");

}