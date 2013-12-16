{
 TFile* fUp = new TFile ("up.root");
 TFile* fCe = new TFile ("cen.root");
 TFile* fDo = new TFile ("down.root");
 TTree* tUp = (TTree*) fUp -> Get ("ntu");
 TTree* tCe = (TTree*) fCe -> Get ("ntu");
 TTree* tDo = (TTree*) fDo -> Get ("ntu");


 std::cout << " >=0) :: " << tUp->GetEntries() << " --- " << tDo->GetEntries() << std::endl;
 std::cout << " >=1) :: " << tUp->GetEntries("jetpt1>=30") << " --- " << tDo->GetEntries("jetpt1>=30") << std::endl;
 std::cout << " >=2) :: " << tUp->GetEntries("jetpt2>=30") << " --- " << tDo->GetEntries("jetpt2>=30") << std::endl;
 std::cout << std::endl;

 double c0 = tCe->GetEntries();
 double c1 = tCe->GetEntries("jetpt1>=30");
 double c2 = tCe->GetEntries("jetpt2>=30");

 double f0 = (c0-c1)/c0;
 double f1 = (c1-c2)/c0;
 double f2 = (c2)/c0;

 double sigma0 = (tUp->GetEntries()-tDo->GetEntries() ) / (tUp->GetEntries()+tDo->GetEntries() );
 double sigma1 = fabs(tUp->GetEntries("jetpt1>=30")-tDo->GetEntries("jetpt1>=30") ) / fabs(tUp->GetEntries("jetpt1>=30")+tDo->GetEntries("jetpt1>=30") ) ;
 double sigma2 = fabs(tUp->GetEntries("jetpt2>=30")-tDo->GetEntries("jetpt2>=30") ) / fabs(tUp->GetEntries("jetpt2>=30")+tDo->GetEntries("jetpt2>=30") +1);

 std::cout << " ==0) :: " << tCe->GetEntries() << std::endl;
 std::cout << " ==1) :: " << tCe->GetEntries("jetpt1>=30") << std::endl;
 std::cout << " ==2) :: " << tCe->GetEntries("jetpt2>=30") << std::endl;
 std::cout << std::endl;

 std::cout << " f0) :: " << 1.* tCe->GetEntries() / tCe->GetEntries() << std::endl;
 std::cout << " f1) :: " << 1.* tCe->GetEntries("jetpt1>=30") / tCe->GetEntries() << std::endl;
 std::cout << " f2) :: " << 1.* tCe->GetEntries("jetpt2>=30") / tCe->GetEntries() << std::endl;
 std::cout << std::endl;

 // sigma

 std::cout << " sigma0 =" << sigma0 << std::endl;
 std::cout << " sigma1 =" << sigma1 << std::endl;
 std::cout << " sigma2 =" << sigma2 << std::endl;
 std::cout << std::endl;

 // k = exp (sigma)
 double k0 = exp(sigma0);
 double k1 = exp(sigma1);
 double k2 = exp(sigma2);

 std::cout << " k0 =" << k0 << std::endl;
 std::cout << " k1 =" << k1 << std::endl;
 std::cout << " k2 =" << k2 << std::endl;
 std::cout << std::endl;

 // theta
 double t00 = pow(k0,1./f0);
 double t01 = pow(k1,-(f1+f2)/f0);
 double t11 = pow(k1,(f1+f2)/f0);
 double t12 = pow(k2,-f2/f1);
 double t22 = k2;

 std::cout << " t00 =" << t00 << std::endl;
 std::cout << " t01 =" << t01 << std::endl;
 std::cout << " t11 =" << t11 << std::endl;
 std::cout << " t12 =" << t12 << std::endl;
 std::cout << " t22 =" << t22 << std::endl;
 std::cout << std::endl;


}