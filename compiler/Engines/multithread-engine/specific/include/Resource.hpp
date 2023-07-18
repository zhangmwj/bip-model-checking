/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

#ifndef _BIP_Engine_Resource_HPP_
#define _BIP_Engine_Resource_HPP_

#include "FastMutex.hpp"
#include "Interval.hpp"
#include "TimeValue.hpp"

class Job;

class Resource {
 public:
  class Accessor;
  class Writer;
  class Validator;

  enum Status { FREE, RESERVED, USED };

  // constructors
  Resource() : mStatus(FREE), mTime(TimeValue::MIN) { }

  // destructor
  virtual ~Resource() { }

  // getters/setters
  Status status() const { return mStatus.load(); }
  void setStatus(Status status);
  TimeValue deadline() const;
  TimeValue time() const { return mTime; }
  
  // operations
  void use();
  void free();

  class Reserver {
   public:
    Reserver() : mJob(NULL) { }
    Reserver(Job &job) : mJob(&job) { }
    virtual ~Reserver() { }

    const vector<Resource *> &resources() const { return mResources; }
    const vector<Resource *> &observedResources() const { return mObservedResources; }
    Job &job() { return *mJob; }
    bool hasJob() const { return mJob != NULL; }
    bool isValid() const;
    TimeValue deadline() const;
    
    void addResource(Resource &resource);
    void addObservedResource(Resource &resource);
    void initialize();
    
    bool tryToReserve(const TimeValue &time);
    virtual void uponReservation(const TimeValue &time) { }
    void free();

    void start();
    void end();
      
    //protected:
    void addValidator(Validator &validator);
    
    void block() { mBlocker.block(); }
    void unblock() { mBlocker.unblock(); }
    
    vector<Resource *> mResources;
    vector<Resource *> mObservedResources;
    vector<Validator *> mValidators;
    
    FastBlockableMutex mBlocker;
    FastMutexGroup mReserveGroup;
    FastMutexGroup mObservedReserveGroup;
    Job *mJob;

    friend class Validator;
    friend class Resource;
  };

  class Writer {
   public:
    Writer() { }
    virtual ~Writer() { }
    
    const vector<Resource *> &resources() const { return mResources; }

    void addResource(Resource &resource);
    
    void free();
    
    void start();
    void end();
  
   protected:
    vector<Resource *> mResources;
    FastMutexGroup mReserveGroup;
  };

  class Validator {
   public:
    Validator();
    virtual ~Validator() { }

    const vector<Resource *> &resources() const { return mResources; }
    void addResource(Resource &resource);

    bool isValid() const;
    TimeValue deadline() const;
    void setIsValid(bool valid);
    void setValid(const TimeValue &deadline);
    TimeValue time() const { return mTime; }
    
    virtual void reset(const vector<Resource *> &resources) = 0;
    virtual void free(Resource &resource) = 0;
    
    //protected:
    void setTime(const TimeValue &time) { assert(time >= mTime); assert(time <= deadline()); mTime = time; }
    
    vector<Resource *> mResources;
    GroupableFastMutex mReserve;

    atomic<bool> mIsValid;
    AtomicTimeValue mDeadline;
    AtomicTimeValue mTime;

    friend class Reserver;
  };

 protected:
  // getters
  const vector<Reserver *> &reservers() const { return mReservers; }
  const vector<Writer *> &writers() const { return mWriters; }
  const vector<Validator *> &validators() const { return mValidators; }

  // setters
  void addReserver(Reserver &reserver);
  void addWriter(Writer &writer);
  void addValidator(Validator &validator);
  void setTime(const TimeValue &time) { assert(time >= mTime); assert(time <= deadline()); mTime = time; }
  
  // operations
  void block();
  void unblock();

  void preventReservers();
  void unpreventReservers();

  void notifyValidators();
  
  // attributes
  GroupableFastMutex mReserve;
  atomic<Status> mStatus;

  // references
  vector<Reserver *> mReservers;
  vector<Writer *> mWriters;
  vector<Validator *> mValidators;
  AtomicTimeValue mTime;
};

#endif
