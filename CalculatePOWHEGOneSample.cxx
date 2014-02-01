{
 #include <algorithm>

 TFile* f = new TFile ("fAll.root");

 TTree* t = (TTree*) f -> Get ("ntu");

 Double_t X[200];
 Double_t Y_f0[200];
 Double_t Y_f1[200];
 Double_t Y_t01[200];
 Double_t Y_t11[200];
 Double_t Y_sigma0[200];
 Double_t Y_sigma1[200];
 Double_t Y_error_0jet[200];
 Double_t Y_error_sigma_0jet[200];

 t->Draw("1 >> htemp(10,0,2)","w00","goff");  std::cout << " total Events: 0505 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp(10,0,2)","w01","goff");  std::cout << " total Events: 0510 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp(10,0,2)","w10","goff");  std::cout << " total Events: 1005 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp(10,0,2)","w11","goff");  std::cout << " total Events: 1010 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp(10,0,2)","w12","goff");  std::cout << " total Events: 1020 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp(10,0,2)","w21","goff");  std::cout << " total Events: 2010 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp(10,0,2)","w22","goff");  std::cout << " total Events: 2020 = " << htemp->Integral() << std::endl;

 int n = 100;
 for (int i=0; i<n; i++) {
  double threshold = 10+i*2;
//   double threshold = 25+i;
  X[i] = threshold;
  TString s1 = Form ("jetpt1>=%f",threshold);
  TString s2 = Form ("jetpt2>=%f",threshold);

  double c0 = 1. * t->GetEntries();
  double c1 = 1. * t->GetEntries(s1.Data());
  double c2 = 1. * t->GetEntries(s2.Data());

  double f0 = (c0-c1)/c0;
  double f1 = (c1-c2)/c0;
  double f2 = (c2)/c0;

  int xsec[100];

  TString s00 = Form ("(%s) >> htemp(10,0,2)",s1.Data());  t->Draw(s00.Data(),"w00","goff");  xsec[0] = htemp->Integral();
  TString s01 = Form ("(%s) >> htemp(10,0,2)",s1.Data());  t->Draw(s01.Data(),"w01","goff");  xsec[1] = htemp->Integral();
  TString s10 = Form ("(%s) >> htemp(10,0,2)",s1.Data());  t->Draw(s10.Data(),"w10","goff");  xsec[2] = htemp->Integral();
  TString s12 = Form ("(%s) >> htemp(10,0,2)",s1.Data());  t->Draw(s12.Data(),"w12","goff");  xsec[3] = htemp->Integral();
  TString s21 = Form ("(%s) >> htemp(10,0,2)",s1.Data());  t->Draw(s21.Data(),"w21","goff");  xsec[4] = htemp->Integral();
  TString s22 = Form ("(%s) >> htemp(10,0,2)",s1.Data());  t->Draw(s22.Data(),"w22","goff");  xsec[5] = htemp->Integral();

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



