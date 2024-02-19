//
// File: ProbabilisticSequence.cpp
//

/*
  Copyright or Â© or Copr. Bio++ Development Team, (November 17, 2004)
  
  This software is a computer program whose purpose is to provide classes
  for sequences analysis.
  
  This software is governed by the CeCILL license under French law and
  abiding by the rules of distribution of free software. You can use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".
  
  As a counterpart to the access to the source code and rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty and the software's author, the holder of the
  economic rights, and the successive licensors have only limited
  liability.
  
  In this respect, the user's attention is drawn to the risks associated
  with loading, using, modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean that it is complicated to manipulate, and that also
  therefore means that it is reserved for developers and experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and, more generally, to use and operate it in the
  same conditions as regards security.
  
  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.
*/

#include "ProbabilisticSequence.h" // class's header file

using namespace bpp;

// From the STL:
#include <iostream>

using namespace std;

/******************************************************************************/

void ProbabilisticSequence::setToSizeR(size_t newSize)
{
  // Size verification
  size_t seqSize = size();
  if (newSize == seqSize)
    return;

  if (newSize < seqSize)
  {
    deleteElements(newSize,seqSize-newSize);
    return;
  }

  // Add gaps up to specified size
  auto gap = std::vector<double>(alphabet().getSize(),0);
  
  for (size_t i=0; i< (size_t)(newSize-seqSize);i++)
    addElement(gap);
}

/******************************************************************************/

void ProbabilisticSequence::setToSizeL(size_t newSize)
{
  // Size verification
  size_t seqSize = size();
  if (newSize == seqSize)
    return;

  if (newSize < seqSize)
  {
    deleteElements(0,seqSize-newSize);
    return;
  }

  // Add gaps up to specified size
  auto gap = std::vector<double>(alphabet().getSize(),0);
  
  for (size_t i=0; i< (size_t)(newSize-seqSize);i++)
    addElement(0,gap);
}

