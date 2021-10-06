//
// File AlignedSequenceContainer.h
// Created by: Guillaume Deuchst
// //             Julien Dutheil
// Last modification : Friday August 22 2003
//

/*
   Copyright or © or Copr. Bio++ Development Team, (November 17, 2004)

   This software is a computer program whose purpose is to provide classes
   for sequences analysis.

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

#ifndef _ALIGNEDSEQUENCECONTAINER_H_
#define _ALIGNEDSEQUENCECONTAINER_H_

#include "../Site.h"
#include "SiteContainer.h"
#include "OrderedSequenceContainer.h"
#include "VectorSequenceContainer.h"
#include <Bpp/Exceptions.h>
#include "VectorPositionedContainer.h"

// From the STL:
#include <string>

namespace bpp
{
/**
 * @brief Aligned sequences container.
 *
 * This class inherits from the VectorSequenceContainer and add site access.
 * Sequence addition methods are re-defined to check for sequence lengths.
 * Sequence access is in \f$O(1)\f$, and site access in \f$O(n)\f$, where
 * \f$n\f$ is the number of sequences in the container.
 *
 * Sites are built on the fly when needed, otherwise they are only nullptr
 *
 * See VectorSiteContainer for an alternative implementation.
 *
 * @see VectorSequenceContainer, Sequence, Site, VectorSiteContainer
 */
class AlignedSequenceContainer :
  public virtual VectorSequenceContainer,
  public virtual SiteContainer,
  public virtual VectorPositionedContainer<Site>
{
private:
  // // Integer std::vector that contains sites's positions
  std::vector<int> positions_;

  size_t length_; // Number of sites for verifications before sequence's insertion in sequence container

public:
  /**
   * @brief Build a new empty container with the specified alphabet.
   *
   * @param alpha The alphabet to use.
   */
  AlignedSequenceContainer(const Alphabet* alpha) :
    AbstractSequenceContainer(alpha),
    VectorSequenceContainer(alpha),
    VectorPositionedContainer<Site>(),
    positions_(),
    length_(0)
  {
    reindexSites();
  }

  /**
   * @brief Copy constructor.
   *
   * @param asc The container to copy.
   */
  AlignedSequenceContainer(const AlignedSequenceContainer& asc) :
    AbstractSequenceContainer(asc),
    VectorSequenceContainer(asc),
    VectorPositionedContainer<Site>(asc),
    positions_(asc.getSitePositions()),
    length_(asc.getNumberOfSites())
  {}

  /**
   * @brief Convert any SiteContainer object into a AlignedSequenceContainer object.
   *
   * @param sc The container to copy.
   */

  AlignedSequenceContainer(const SiteContainer& sc) :
    AbstractSequenceContainer(sc),
    VectorSequenceContainer(sc),
    VectorPositionedContainer<Site>(sc.getNumberOfSites()),
    positions_(sc.getSitePositions()),
    length_(sc.getNumberOfSites())
  {}

  /**
   * @brief Try to coerce an OrderedSequenceContainer object into an AlignedSequenceContainer object.
   *
   * Sequences in osc will be considered alligned, and have the same number of sites.
   *
   * @param osc The ordered container to coerce.
   * @throw SequenceNotAlignedException If sequences in osc do not have the same length.
   */
  AlignedSequenceContainer(const OrderedSequenceContainer& osc);

  AlignedSequenceContainer& operator=(const AlignedSequenceContainer& asc);
  AlignedSequenceContainer& operator=(const SiteContainer&  sc);
  AlignedSequenceContainer& operator=(const OrderedSequenceContainer& osc);

  virtual ~AlignedSequenceContainer() {}

public:
  /**
   * @name The Clonable interface.
   *
   * @{
   */
  AlignedSequenceContainer* clone() const { return new AlignedSequenceContainer(*this); }
  /** @} */

  /**
   * @name The SiteContainer interface implementation:
   *
   * @{
   */
  const Site& getSite(size_t siteIndex) const;
  Site& getSite(size_t siteIndex);
  void  setSite(size_t siteIndex, const Site& site, bool checkPosition = true);
  std::shared_ptr<Site> deleteSite(size_t siteIndex);
  void addSite(const Site& site, bool checkPosition = true);
  void addSite(const Site& site, int position, bool checkPosition = true);
  void addSite(const Site& site, size_t siteIndex, bool checkPosition = true);
  void addSite(const Site& site, size_t siteIndex, int position, bool checkPosition = true);

  void clear();

  AlignedSequenceContainer* createEmptyContainer() const;

  /** @} */

  /**
   * @name From AlignedValuesContainer interface
   *
   * @{
   */

  void deleteSites(size_t siteIndex, size_t length);

  size_t getNumberOfSites() const { return length_; }
  Vint getSitePositions() const { return positions_; }
  void setSitePositions(Vint vPositions);

  void reindexSites();

  /** @} */

  /**
   * @name Redefinition of VectorSequenceContainer methods, to check for sequence lengths.
   *
   * @{
   */
  void setSequence(const std::string& name, const Sequence& sequence, bool checkName = true);
  void setSequence(size_t sequenceIndex, const Sequence& sequence, bool checkName = true);

  void addSequence(const Sequence& sequence, bool checkName = true);
  void addSequence(const Sequence& sequence, size_t sequenceIndex, bool checkName = true);

/** @} */

protected:
  /**
   * @brief Check sequence's size before insertion in sequence container.
   *
   * @param sequence The sequence to check.
   * @return True if sequence length = number of sites in container.
   */
  bool checkSize_(const Sequence& sequence) { return sequence.size() == length_; }
};
} // end of namespace bpp.

#endif// _ALIGNEDSEQUENCECONTAINER_H_
