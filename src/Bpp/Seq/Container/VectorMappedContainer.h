//
// File: VectorMappedContainer.h
// Created by: Laurent Guéguen (for template feature)
// Created on: mardi 28 mars 2017, à 15h 09
//

/*
   Copyright or © or Copr. CNRS, (November 17, 2004)

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

#ifndef VECTOR_MAPPED_CONTAINER_H_
#define VECTOR_MAPPED_CONTAINER_H_

#include "MappedNamedContainer.h"
#include "PositionedNamedContainer.h"
#include "VectorPositionedContainer.h"

// From the STL library:
#include <string>
#include <vector>
#include <iostream>

namespace bpp
{
/**
 * @brief The template VectorMappedContainer class.
 *
 * Objects are stored in a std::vector of shared pointers and in a
 * map of shared pointers.
 *
 * Object access is hence in \f$O(1)\f$ through indexes, and
 * \f$O(log(n))\f$ through names.
 *
 */

  template<class T>
  class VectorMappedContainer :
    virtual public PositionedNamedContainer<T>,
    virtual public MappedNamedContainer<T>,
    virtual public VectorPositionedContainer<T>
  {
  private:
    /*
     * @brief vector of the names, in same order as objects
     *
     */
    
    std::vector<std::string> vNames_;

    /*
     * @brief map <string, size_t> for the positions of the names
     *
     */
    
    std::map<std::string, size_t> mNames_;

  public:
    VectorMappedContainer() :
      MappedNamedContainer<T>(),
      VectorPositionedContainer<T>(),
      vNames_(),
      mNames_()
    {
    }


    VectorMappedContainer(const VectorMappedContainer& vsc) :
      MappedNamedContainer<T>(vsc),
      VectorPositionedContainer<T>(vsc),
      vNames_(vsc.vNames_),
      mNames_(vsc.mNames_)      
    {
    }
    

    VectorMappedContainer<T>& operator=(const VectorMappedContainer& vsc)
    {
      MappedNamedContainer<T>::operator=(vsc);
      VectorPositionedContainer<T>::operator=(vsc);
      vNames_=vsc.vNames_;
      mNames_=vsc.mNames_;
      
      return *this;
    }

  public:
    /**
     * @name The Clonable interface.
     *
     * @{
     */
    
    VectorMappedContainer<T>* clone() const
    {
      return new VectorMappedContainer(*this);
    }
    
    /** @} */

    /*
     * @brief size of the position vector
     * !! may be different than the actual number of objects
     *
     */
    
    size_t getSize() const
    {
      return VectorPositionedContainer<T>::getSize();
    }

    /*
     * @brief real number of objects
     *
     */

    size_t getNumberOfObjects() const
    {
      return VectorMappedContainer<T>::getSize();
    }

    const std::shared_ptr<T> getObject(size_t objectIndex) const
    {
      return VectorPositionedContainer<T>::getObject(objectIndex);
    }

    std::shared_ptr<T> getObject(size_t objectIndex)
    {
      return VectorPositionedContainer<T>::getObject(objectIndex);
    }
    
    /**
     * @brief Get a object.
     *
     * @param name The key of the object to retrieve.
     * @return The object associated to the given key.
     */

    std::shared_ptr<T> getObject(const std::string& name) const
    {
      return MappedNamedContainer<T>::getObject(name);
    }

    std::shared_ptr<T> getObject(const std::string& name) 
    {
      return MappedNamedContainer<T>::getObject(name);
    }
    
    bool hasObject(const std::string& name) const
    {
      return MappedNamedContainer<T>::hasObject(name);
    }

    void addObject(std::shared_ptr<T> object, size_t objectIndex, const std::string& name, bool check = false)
    {
      VectorPositionedContainer<T>::addObject(object, objectIndex, check);
      MappedNamedContainer<T>::addObject(object, name, check);
      vNames_[objectIndex]=name;
      mNames_[name]=objectIndex;
      
    }
    
    void appendObject(std::shared_ptr<T> object, const std::string& name, bool check = true)
    {
      MappedNamedContainer<T>::addObject(object,name, check);
      VectorPositionedContainer<T>::appendObject(object);
      
      vNames_.push_back(name);
      mNames_[name]=vNames_.size()-1;
    }

    std::shared_ptr<T> removeObject(size_t objectIndex)
    {
      std::shared_ptr<T> obj= VectorPositionedContainer<T>::removeObject(objectIndex);
      MappedNamedContainer<T>::removeObject(vNames_[objectIndex]);
      mNames_.erase(vNames_[objectIndex]);
      vNames_[objectIndex]="";
      return obj;
    }

    std::shared_ptr<T> removeObject(std::string& name)
    {
      std::shared_ptr<T> obj= MappedNamedContainer<T>::removeObject(name);
      size_t objectIndex=mNames_[name];
      
      VectorPositionedContainer<T>::removeObject(name);
      mNames_.erase(name);
      vNames_[objectIndex]="";
      
      return obj;
    }

    void clear()
    {
      MappedNamedContainer<T>::clear();
      VectorPositionedContainer<T>::clear();
      vNames_.clear();
      mNames_.clear();
    }
      
  };
} // end of namespace bpp.

#endif  // VECTOR_MAPPED_CONTAINER_H_
