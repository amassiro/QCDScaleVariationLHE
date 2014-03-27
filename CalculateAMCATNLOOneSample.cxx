{
 #include <algorithm>

 TFile* f = new TFile ("fAll_amcatnlo.root");

 TTree* t = (TTree*) f -> Get ("ntu");

 Double_t X[200];
 Double_t Y_f0[200];
 Double_t Y_f1[200];
 Double_t Y_t00[200];
 Double_t Y_t01[200];
 Double_t Y_t11[200];
 Double_t Y_sigma0[200];
 Double_t Y_sigma1[200];
 Double_t Y_error_0jet[200];
 Double_t Y_error_sigma_0jet[200];
 TH1F htemp("htemp","htemp",10,0,2);

 t->Draw("1 >> htemp","w00","goff");  std::cout << " total Events: 0505 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp","w01","goff");  std::cout << " total Events: 0510 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp","w10","goff");  std::cout << " total Events: 1005 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp","w11","goff");  std::cout << " total Events: 1010 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp","w12","goff");  std::cout << " total Events: 1020 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp","w21","goff");  std::cout << " total Events: 2010 = " << htemp->Integral() << std::endl;
 t->Draw("1 >> htemp","w22","goff");  std::cout << " total Events: 2020 = " << htemp->Integral() << std::endl;

 int n = 50;
 for (int i=0; i<n; i++) {
  std::cout << " i = " << i << std::endl;
  double threshold = 10+i*2;
//   double threshold = 25+i;
  X[i] = threshold;
  TString s0 = Form ("1");
  TString s1 = Form ("jetpt1>=%f",threshold);
  TString s2 = Form ("jetpt2>=%f",threshold);

  double c0 = 1.;
  double c1 = 1.;
  double c2 = 1.;

  TString sc0 = Form ("w11");                   t->Draw("1 >> htemp",sc0.Data(),"goff");  c0 = htemp->Integral();
  TString sc1 = Form ("(%s) * w11",s1.Data());  t->Draw("1 >> htemp",sc1.Data(),"goff");  c1 = htemp->Integral();
  TString sc2 = Form ("(%s) * w11",s2.Data());  t->Draw("1 >> htemp",sc2.Data(),"goff");  c2 = htemp->Integral();

  double f0 = (c0-c1)/c0;
  double f1 = (c1-c2)/c0;
  double f2 = (c2)/c0;

  //---- >= 0 jets
  float xsec_0[100];

  TString s00 = Form ("(%s) * w00",s0.Data());  t->Draw("1 >> htemp",s00.Data(),"goff");  xsec_0[0] = htemp->Integral();
  TString s01 = Form ("(%s) * w01",s0.Data());  t->Draw("1 >> htemp",s01.Data(),"goff");  xsec_0[1] = htemp->Integral();
  TString s10 = Form ("(%s) * w10",s0.Data());  t->Draw("1 >> htemp",s10.Data(),"goff");  xsec_0[2] = htemp->Integral();
  TString s12 = Form ("(%s) * w12",s0.Data());  t->Draw("1 >> htemp",s12.Data(),"goff");  xsec_0[3] = htemp->Integral();
  TString s21 = Form ("(%s) * w21",s0.Data());  t->Draw("1 >> htemp",s21.Data(),"goff");  xsec_0[4] = htemp->Integral();
  TString s22 = Form ("(%s) * w22",s0.Data());  t->Draw("1 >> htemp",s22.Data(),"goff");  xsec_0[5] = htemp->Integral();

  TString s11 = Form ("(%s) * w11",s0.Data());  t->Draw("1 >> htemp",s11.Data(),"goff");  xsec_0[6] = htemp->Integral();

  float min_0 = *std::min_element(xsec_0,xsec_0+7);
  float max_0 = *std::max_element(xsec_0,xsec_0+7);

  //---- >= 1 jets

  float xsec_1[100];

  s00 = Form ("(%s) * w00",s1.Data());  t->Draw("1 >> htemp",s00.Data(),"goff");  xsec_1[0] = htemp->Integral();
  s01 = Form ("(%s) * w01",s1.Data());  t->Draw("1 >> htemp",s01.Data(),"goff");  xsec_1[1] = htemp->Integral();
  s10 = Form ("(%s) * w10",s1.Data());  t->Draw("1 >> htemp",s10.Data(),"goff");  xsec_1[2] = htemp->Integral();
  s12 = Form ("(%s) * w12",s1.Data());  t->Draw("1 >> htemp",s12.Data(),"goff");  xsec_1[3] = htemp->Integral();
  s21 = Form ("(%s) * w21",s1.Data());  t->Draw("1 >> htemp",s21.Data(),"goff");  xsec_1[4] = htemp->Integral();
  s22 = Form ("(%s) * w22",s1.Data());  t->Draw("1 >> htemp",s22.Data(),"goff");  xsec_1[5] = htemp->Integral();

  s11 = Form ("(%s) * w11",s1.Data());  t->Draw("1 >> htemp",s11.Data(),"goff");  xsec_1[6] = htemp->Integral();


  float min_1 = *std::min_element(xsec_1,xsec_1+7);
  float max_1 = *std::max_element(xsec_1,xsec_1+7);



  double sigma0 = 1.* abs(max_0-min_0) / c0;
  double sigma1 = 1.* abs(max_1-min_1) / c1;
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

  std::cout << " thr = " << threshold << " c0:c1:c2 = (" << c0 << ":" << c1 << ":" << c2 << ")  :: t01 = " << t01 << " t11 = " << t11 ;
  std::cout << " :: f0 = " << f0 << " :: k0 = " << k0 << " k1 = " << k1 << " :: sigma0 = " << sigma0 << " sigma1 = " << sigma1 << " = (" << max_1 << " - " << min_1 << " ) / " << c1 << std::endl;
  Y_t00[i] = t00;
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
 gPad->SetGrid();


 //--------------------------
 TGraph* g_e0 = new TGraph(n,X,Y_error_0jet);

 TCanvas* ce0 = new TCanvas ("ce0","ce0",800,600);
 g_e0->SetMarkerSize(1);
 g_e0->SetMarkerStyle(20);
 g_e0->SetMarkerColor(kRed);
 g_e0->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_e0->Draw("apl");
 gPad->SetGrid();

 //--------------------------
 TGraph* g_t00 = new TGraph(n,X,Y_t00); g_t00->SetName("QCDScale");    g_t00->SetTitle("QCDScale in 0 jet bin");
 TGraph* g_t01 = new TGraph(n,X,Y_t01); g_t01->SetName("QCDScale1in"); g_t01->SetTitle("QCDScale1in in 0 jet bin");
 TGraph* g_t11 = new TGraph(n,X,Y_t11);

 TCanvas* c00 = new TCanvas ("c00","c00 QCDscale",800,600);
 g_t00->SetMarkerSize(1);
 g_t00->SetMarkerStyle(20);
 g_t00->SetMarkerColor(kRed);
 g_t00->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_t00->Draw("apl");
 gPad->SetGrid();

 TCanvas* c01 = new TCanvas ("c01","c01 QCDscale1in",800,600);
 g_t01->SetMarkerSize(1);
 g_t01->SetMarkerStyle(20);
 g_t01->SetMarkerColor(kRed);
 g_t01->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_t01->Draw("apl");
 gPad->SetGrid();

 TCanvas* c11 = new TCanvas ("c11","c11",800,600);
 g_t11->SetMarkerSize(1);
 g_t11->SetMarkerStyle(20);
 g_t11->SetMarkerColor(kRed);
 g_t11->Draw("apl");
 gPad->SetGrid();

 //--------------------------
 TGraph* g_sigma0 = new TGraph(n,X,Y_sigma0);
 TGraph* g_sigma1 = new TGraph(n,X,Y_sigma1);

 TCanvas* csigma0 = new TCanvas ("csigma0","csigma0",800,600);
 g_sigma0->SetTitle("#sigma_{#geq0}");
 g_sigma0->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_sigma0->SetMarkerSize(1);
 g_sigma0->SetMarkerStyle(20);
 g_sigma0->SetMarkerColor(kRed);
 g_sigma0->Draw("apl");
 gPad->SetGrid();

 TCanvas* csigma1 = new TCanvas ("csigma1","csigma1",800,600);
 g_sigma1->SetTitle("#sigma_{#geq1}");
 g_sigma1->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_sigma1->SetMarkerSize(1);
 g_sigma1->SetMarkerStyle(20);
 g_sigma1->SetMarkerColor(kRed);
 g_sigma1->Draw("apl");
 gPad->SetGrid();

 //--------------------------
 TGraph* g_f0 = new TGraph(n,X,Y_f0);
 TGraph* g_f1 = new TGraph(n,X,Y_f1);

 TCanvas* cf0 = new TCanvas ("cf0","cf0",800,600);
 g_f0->SetTitle("f_{0}");
 g_f0->SetMarkerSize(1);
 g_f0->SetMarkerStyle(20);
 g_f0->SetMarkerColor(kRed);
 g_f0->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_f0->Draw("apl");
 gPad->SetGrid();

 TCanvas* cf1 = new TCanvas ("cf1","cf1",800,600);
 g_f1->SetTitle("f_{1}");
 g_f1->GetXaxis()->SetTitle("jet p_{T} threshold [GeV]");
 g_f1->SetMarkerSize(1);
 g_f1->SetMarkerStyle(20);
 g_f1->SetMarkerColor(kRed);
 g_f1->Draw("apl");
 gPad->SetGrid();

}



