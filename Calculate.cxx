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


 std::cout << " ==0) :: " << tCe->GetEntries() << std::endl;
 std::cout << " ==1) :: " << tCe->GetEntries("jetpt1>=30") << std::endl;
 std::cout << " ==2) :: " << tCe->GetEntries("jetpt2>=30") << std::endl;
 std::cout << std::endl;

 std::cout << " f0) :: " << 1.* tCe->GetEntries() / tCe->GetEntries() << std::endl;
 std::cout << " f1) :: " << 1.* tCe->GetEntries("jetpt1>=30") / tCe->GetEntries() << std::endl;
 std::cout << " f2) :: " << 1.* tCe->GetEntries("jetpt2>=30") / tCe->GetEntries() << std::endl;
 std::cout << std::endl;

}