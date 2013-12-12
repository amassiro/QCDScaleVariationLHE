{
 TFile* fUp = new TFile ("up.root");
 TFile* fDo = new TFile ("down.root");
 TTree* tUp = (TTree*) fUp -> Get ("ntu");
 TTree* tDo = (TTree*) fDo -> Get ("ntu");

 std::cout << " 0) :: " << tUp->GetEntries() << " --- " << tDo->GetEntries() << std::endl;
 std::cout << " 1) :: " << tUp->GetEntries("jetpt1>=30") << " --- " << tDo->GetEntries("jetpt1>=30") << std::endl;
 std::cout << " 2) :: " << tUp->GetEntries("jetpt2>=30") << " --- " << tDo->GetEntries("jetpt2>=30") << std::endl;


}