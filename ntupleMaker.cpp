// to compile:
//   c++ -o ntupleMaker.exe `root-config --glibs --cflags` `lhapdf-config --cppflags  --ldflags` -lm ntupleMaker.cpp
//
// to use:
//   ./ntupleMaker.exe fileLHE    outputFileRoot
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>


#include "LHEF.h"


#include "LHAPDF/LHAPDF.h"



#include "TNtuple.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"


struct ptsort: public std::binary_function<TLorentzVector, TLorentzVector, bool> {
 bool operator () (const TLorentzVector & x, const TLorentzVector & y) {
  return  (x.Perp () < y.Perp () ) ;
 }
} ;

TLorentzVector buildP (const LHEF::HEPEUP & event, int iPart) {
 TLorentzVector dummy ;
 dummy.SetPxPyPzE (
   event.PUP.at (iPart).at (0), // px
   event.PUP.at (iPart).at (1), // py
   event.PUP.at (iPart).at (2), // pz
   event.PUP.at (iPart).at (3) // E
   ) ;
 return dummy ;
}


std::vector <std::string> transform (std::string inUglyList) {
 std::vector <std::string> list_comments;
 std::string s = inUglyList;
 std::string delimiter = "#";
 size_t pos = 0;
 std::string token;
 while ((pos = s.find(delimiter)) != std::string::npos) {
  token = s.substr(0, pos);
  list_comments.push_back(token);
  s.erase(0, pos + delimiter.length());
 }
 return list_comments;
}




void fillNtuple (std::string fileNameLHE,  TNtuple & ntuple) {
 std::ifstream ifs (fileNameLHE.c_str ()) ;
 LHEF::Reader reader (ifs) ;

 long ieve = 0 ;
 long selected = 0 ;
 double jetsNum = 0. ;

 std::cout << " reading " << fileNameLHE << std::endl;

 // loop over events
 while ( reader.readEvent () ) {
  ieve++;
  if (ieve % 10000 == 0) std::cout << "event " << ieve << "\n" ;

  //----                mu      mu    weight
  std::map < std::pair<float, float>, float > weights;
  std::vector <std::string> comments_LHE = transform (reader.eventComments);

  //----                    0 is somethig I don't care:     rwgt            1           3  0.404994932416933         54217137   634096161           0
  for (unsigned int iComm = 1; iComm < comments_LHE.size(); iComm++) {
  /// #new weight,renfact,facfact,pdf1,pdf2 32.2346904790193 1.00000000000000 1.00000000000000 11000 11000 lha
   std::stringstream line( comments_LHE.at(iComm) );
   std::string dummy;
   line >> dummy; // new weight,renfact,facfact,pdf1,pdf2
   line >> dummy;
   float dummy_float_weight;
   line >> dummy_float_weight; // 32.2346904790193
   float dummy_float_mu1;
   line >> dummy_float_mu1; // 1.00000000000000
   float dummy_float_mu2;
   line >> dummy_float_mu2; // 1.00000000000000
   std::pair <float, float> mumu(dummy_float_mu1,dummy_float_mu2);
   weights[mumu] = dummy_float_weight;
  }


  TLorentzVector Higgs;
  int iPartHiggs = -1;
  float mH = 0;

  std::vector<int> finalJets ;
  std::vector<TLorentzVector> v_f_quarks ;
  std::vector<TLorentzVector> v_f_leptons ;
  std::vector<TLorentzVector> v_f_neutrinos ;

  // loop over particles in the event
  // and fill the variables of leptons and quarks
  for (int iPart = 0 ; iPart < reader.hepeup.IDUP.size (); ++iPart) {

   // look for the Higgs
   if (abs (reader.hepeup.IDUP.at (iPart)) == 25) {
    iPartHiggs = iPart;
    Higgs.SetPxPyPzE  (
      reader.hepeup.PUP.at (iPart).at (0), // px
      reader.hepeup.PUP.at (iPart).at (1), // py
      reader.hepeup.PUP.at (iPart).at (2), // pz
      reader.hepeup.PUP.at (iPart).at (3) // E
      );
    mH = Higgs.M();
   }

   // outgoing particles
   if (reader.hepeup.ISTUP.at (iPart) == 1) {
    // quarks
    if (abs (reader.hepeup.IDUP.at (iPart)) < 7) {
     finalJets.push_back (iPart) ;
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_f_quarks.push_back (dummy) ;
    } // quarks
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 11 || abs (reader.hepeup.IDUP.at (iPart)) == 13 || abs (reader.hepeup.IDUP.at (iPart)) == 15) {  // e = 11,   mu = 13,   tau = 15
     TLorentzVector dummy (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_f_leptons.push_back (dummy) ;
    }
    else if (abs (reader.hepeup.IDUP.at (iPart)) == 12 || abs (reader.hepeup.IDUP.at (iPart)) == 14 || abs (reader.hepeup.IDUP.at (iPart)) == 16) { // ve = 12,   vmu = 14,   vtau = 16
     TLorentzVector dummy
       (
       reader.hepeup.PUP.at (iPart).at (0), // px
       reader.hepeup.PUP.at (iPart).at (1), // py
       reader.hepeup.PUP.at (iPart).at (2), // pz
       reader.hepeup.PUP.at (iPart).at (3) // E
       ) ;
     v_f_neutrinos.push_back (dummy) ;
    }
   } // outgoing particles
  } // loop over particles in the event

  if (v_f_leptons.size () != 2) {
   std::cout << " what !?!?!?! Not 2 leptons? Are you kidding?" << std::endl;
   continue;
  }


  // sorting in pt
  sort (v_f_quarks.rbegin (), v_f_quarks.rend (), ptsort ()) ;
  sort (v_f_leptons.rbegin (), v_f_leptons.rend (), ptsort ()) ;

  TLorentzVector diLepton = v_f_leptons.at (0) + v_f_leptons.at (1) ;
  TLorentzVector missingEnergy = v_f_neutrinos.at (0) + v_f_neutrinos.at (1) ;

  TLorentzVector dilepton_plus_dineutrinos = v_f_leptons.at (0) + v_f_leptons.at (1) + v_f_neutrinos.at (0) + v_f_neutrinos.at (1) ;

  // the sum pf the two quarks

  float jetpt1 = -99;
  if (v_f_quarks.size()>0) jetpt1 = v_f_quarks.at (0).Pt ();
  float jetpt2 = -99;
  if (v_f_quarks.size()>1) jetpt2 = v_f_quarks.at (1).Pt ();

  ntuple.Fill (
    jetpt1,
    jetpt2,
//     v_f_leptons.at (0).Pt (),
//     v_f_leptons.at (1).Pt ()
    weights[std::pair<float, float>(0.5, 0.5)],
    weights[std::pair<float, float>(1.0, 0.5)],
    weights[std::pair<float, float>(0.5, 1.0)],
    weights[std::pair<float, float>(1.0, 2.0)],
    weights[std::pair<float, float>(2.0, 1.0)],
    weights[std::pair<float, float>(2.0, 2.0)]
    ) ;

 } // loop over events

}



int main (int argc, char **argv) { 
 // Open a stream connected to an event file:
 if (argc < 3) exit (1) ;

 std::cout << " Input  LHE  =" << argv[1] << std::endl;
 std::cout << " Output ROOT =" << argv[2] << std::endl;

 
 const int SUBSET = 0 ;
 const std::string NAME = "cteq6ll" ; //"cteq6l1"

 LHAPDF::initPDFSet (NAME, LHAPDF::LHPDF, SUBSET) ;
 const int NUMBER = LHAPDF::numberPDF () ;

 LHAPDF::initPDF (0) ;


//  TNtuple ntu ("ntu", "ntu", "jetpt1:jetpt2:pt1:pt2");
 TNtuple ntu ("ntu", "ntu", "jetpt1:jetpt2:w00:w10:w01:w12:w21:w22");
 fillNtuple (argv[1], ntu) ;

 TFile output (argv[2], "recreate") ;
 output.cd() ;
 ntu.Write();
 output.Close();

}



