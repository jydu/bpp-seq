//
// File: test_containers.cpp
// Created by: Julien Dutheil
// Created on: Mon Nov 01 10:15 2010
//

/*
Copyright or © or Copr. Bio++ Development Team, (November 17, 2004)

This software is a computer program whose purpose is to provide classes
for numerical calculus. This file is part of the Bio++ project.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include <Bpp/Seq/Alphabet/RNA.h>
#include <Bpp/Seq/Container/VectorSiteContainer.h>
#include <Bpp/Seq/Container/CompressedVectorSiteContainer.h>
#include <Bpp/Seq/Container/SiteContainerTools.h>
#include <iostream>

using namespace bpp;
using namespace std;

int main() {
  //ProteicAlphabet* alpha = new ProteicAlphabet;
  shared_ptr<const Alphabet> alpha = AlphabetTools::RNA_ALPHABET;
  auto sites = make_unique<VectorSiteContainer>(alpha);

  auto seq1 = make_unique<Sequence>("seq1", "----AUGCCG---GCGU----UUU----G--G-CCGACGUGUUUU--", alpha);
  auto seq2 = make_unique<Sequence>("seq2", "---GAAGGCG---G-GU----UUU----GC-GACCGACG--UUUU--", alpha);
  sites->addSequence(seq1->getName(), seq1);
  sites->addSequence(seq2->getName(), seq2);
  cout << sites->getNumberOfSites() << endl;
  cout << sites->sequence("seq1").toString() << endl;
  cout << sites->sequence("seq2").toString() << endl;
  SiteContainerTools::removeGapOnlySites(*sites);
  cout << endl;
  
  cout << sites->getNumberOfSites() << endl;
  cout << sites->sequence("seq1").toString() << endl;
  cout << sites->sequence("seq2").toString() << endl;

  if (sites->getNumberOfSites() != 30)
    throw Exception("Bad removal of gap only sites");

  SiteContainerTools::removeGapSites(*sites, 0.);
  cout << endl;
  
  cout << sites->getNumberOfSites() << endl;
  cout << sites->sequence("seq1").toString() << endl;
  cout << sites->sequence("seq2").toString() << endl;
  
  if (sites->getNumberOfSites() != 24)
    throw Exception("Bad removal of gap sites");

  cout << endl;
  CompressedVectorSiteContainer cvs(*sites);

  cout << "Compressed sequence" << endl;
  
  cout << "Number of unique sites : " << cvs.getNumberOfUniqueSites() << endl;
  if (cvs.getNumberOfUniqueSites() != 6) {
    throw Exception("Bad compression of sites");
  }
  if (cvs.getSequenceNames() != sites->getSequenceNames()) {
    throw Exception("Sequence names got lost when compressing sites!");
  }
  cout << cvs.getNumberOfSites() << endl;
  cout << cvs.sequence("seq1").toString() << endl;
  cout << cvs.sequence("seq2").toString() << endl;

  return (sites->getNumberOfSites() == 24 ? 0 : 1);
}
