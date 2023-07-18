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

#include <Resource.hpp>
#include <Job.hpp>

void Resource::addReserver(Resource::Reserver &reserver) {
  if (find(mReservers.begin(),
           mReservers.end(),
           &reserver)
      == mReservers.end()) {
    mReservers.push_back(&reserver);
  }
}

void Resource::addWriter(Resource::Writer &writer) {
  if (find(mWriters.begin(),
           mWriters.end(),
           &writer)
      == mWriters.end()) {
    mWriters.push_back(&writer);
  }
}

void Resource::addValidator(Resource::Validator &validator) {  
  if (find(mValidators.begin(),
           mValidators.end(),
           &validator)
      == mValidators.end()) {
    mValidators.push_back(&validator);
  }

  for (vector<Reserver *>::const_iterator reserverIt = reservers().begin() ;
       reserverIt != reservers().end() ;
       ++reserverIt) {
    Reserver &reserver = **reserverIt;

    if (find(reserver.resources().begin(),
             reserver.resources().end(),
             this)
        != reserver.resources().end()) {
      reserver.addValidator(validator);
    }
  }
}

void Resource::setStatus(Status status) {
#ifdef NDEBUG
  mStatus.store(status);
#else
  Status oldStatus = mStatus.exchange(status);
#endif

  assert((oldStatus == FREE && status == RESERVED) ||
         (oldStatus == RESERVED && status == USED) ||
         (oldStatus == RESERVED && status == FREE) ||
         (oldStatus == USED && status == FREE));
}


TimeValue Resource::deadline() const {
  TimeValue ret = TimeValue::MAX;

  // compute the minimal deadline amongst the validators
  for (vector<Validator *>::const_iterator validatorIt = validators().begin() ;
       validatorIt != validators().end() ;
       ++validatorIt) {
    Validator &validator = **validatorIt;
    TimeValue deadline = validator.deadline();

    if (deadline < ret) {
      ret = deadline;
    }
  }

  return ret;
}

void Resource::use() {
  block();

  assert(status() == RESERVED);
      
  setStatus(USED);
}

void Resource::free() {
  assert(status() == RESERVED || status() == USED);

  bool used = (status() == USED);
    
  setStatus(FREE);

  notifyValidators();
  
  unpreventReservers();
  
  mReserve.unlock();
  
  if (used) {
    unblock();
  }
}

void Resource::block() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    reserver.block();
  }

  preventReservers();
}

void Resource::unblock() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    reserver.unblock();
  }

  unpreventReservers();
}

void Resource::preventReservers() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    if (reserver.hasJob()) {
      reserver.job().preventEnqueuing();
    }
  }
}

void Resource::unpreventReservers() {
  for (vector<Resource::Reserver *>::const_iterator reserverIt = mReservers.begin() ;
       reserverIt != mReservers.end() ;
       ++reserverIt) {
    Resource::Reserver &reserver = **reserverIt;

    if (reserver.hasJob()) {
      reserver.job().unpreventEnqueuing();
    }
  }
}

void Resource::notifyValidators() {
  for (vector<Validator *>::const_iterator validatorIt = validators().begin() ;
       validatorIt != validators().end() ;
       ++validatorIt) {
    Validator &validator = **validatorIt;

    validator.free(*this);
  }
}

TimeValue Resource::Reserver::deadline() const {
  TimeValue ret = TimeValue::MAX;

  for (vector<Validator *>::const_iterator validatorIt = mValidators.begin() ;
       validatorIt != mValidators.end() ;
       ++validatorIt) {
    Validator &validator = **validatorIt;
    TimeValue deadline = validator.deadline();
    
    if (deadline < ret) {
      ret = deadline;
    }
  }

  return ret;
}

void Resource::Reserver::addResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {
    mResources.push_back(&resource);
  }
  
  mReserveGroup.add(resource.mReserve);
  
  resource.addReserver(*this);

  for (vector<Validator *>::const_iterator validatorIt = resource.validators().begin() ;
       validatorIt != resource.validators().end() ;
       ++validatorIt) {
    Validator &validator = **validatorIt;

    addValidator(validator);
  }
}

void Resource::Reserver::addObservedResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {    
    mObservedResources.push_back(&resource);    
  }
  
  mReserveGroup.add(resource.mReserve);
  mObservedReserveGroup.add(resource.mReserve);
  
  resource.addReserver(*this);
}

void Resource::Reserver::addValidator(Validator &validator) {  
  if (find(mValidators.begin(),
           mValidators.end(),
           &validator)
      == mValidators.end()) {
    mReserveGroup.add(validator.mReserve);
    mValidators.push_back(&validator);
  }
}

void Resource::Reserver::initialize() {
  mReserveGroup.initialize();
  mObservedReserveGroup.initialize();
}

bool Resource::Reserver::tryToReserve(const TimeValue &time) {  
  bool success = mReserveGroup.tryToLock();

  if (success) {
    // check if all resources are not outdated
    for (vector<Resource *>::const_iterator resourceIt = mResources.begin() ;
         resourceIt != mResources.end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      if (time < resource.time()) {
        success = false;
        break;
      }
    }
    
    // check if all resources are valid w.r.t. validators
    for (vector<Validator *>::const_iterator validatorIt = mValidators.begin() ;
         validatorIt != mValidators.end() ;
         ++validatorIt) {
      Validator &validator = **validatorIt;

      if (time < validator.time() ||
          time > validator.deadline() ) {
        success = false;
        break;
      }
    }

    if (!success) {
      // unreserve resources
      mReserveGroup.unlock();
    }
    else {
      // set resource time
      for (vector<Resource *>::const_iterator resourceIt = mResources.begin() ;
           resourceIt != mResources.end() ;
           ++resourceIt) {
        Resource &resource = **resourceIt;

        resource.setTime(time);
      }

      // set resource time
      for (vector<Validator *>::const_iterator validatorIt = mValidators.begin() ;
           validatorIt != mValidators.end() ;
           ++validatorIt) {
        Validator &validator = **validatorIt;

        validator.setTime(time);
      }
      
      // reserve specific action
      uponReservation(time);
    
      // let observed resources
      mObservedReserveGroup.unlock();
    
      // prevent other reservers from enqueuing 
      for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
        Resource &resource = **resourceIt;

        resource.preventReservers();
      }

      // update status of modified resources (FREE->RESERVED)
      for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
           resourceIt != resources().end() ;
           ++resourceIt) {
        Resource &resource = **resourceIt;

        assert(resource.status() == FREE);

        resource.setStatus(RESERVED);
      }

      // reset all impacted validators
      for (vector<Validator *>::const_iterator validatorIt = mValidators.begin() ;
           validatorIt != mValidators.end() ;
           ++validatorIt) {
        Validator &validator = **validatorIt;

        assert(time <= validator.mDeadline);
      
        validator.reset(resources());
      }
    }
  }

  return success;
}

void Resource::Reserver::free() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    resource.free();
  }
}

void Resource::Reserver::start() {
  mBlocker.lock();
}

void Resource::Reserver::end() {
  mBlocker.unlock();
}

void Resource::Writer::addResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {
    mResources.push_back(&resource);
  }
  
  mReserveGroup.add(resource.mReserve);

  resource.addWriter(*this);
}

void Resource::Writer::free() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;

    assert(resource.status() == RESERVED);

    resource.free();
  }
}

void Resource::Writer::start() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;
    
    resource.use();
  }
}

void Resource::Writer::end() {
  for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
       resourceIt != resources().end() ;
       ++resourceIt) {
    Resource &resource = **resourceIt;
    
    assert(resource.status() == USED);

    resource.free();
  }
}

Resource::Validator::Validator() :
  mIsValid(true),
  mDeadline(TimeValue::MAX),
  mTime(TimeValue::MIN) {
}

void Resource::Validator::addResource(Resource &resource) {
  if (find(mResources.begin(),
           mResources.end(),
           &resource)
      == mResources.end()) {
    mResources.push_back(&resource);
  }

  resource.addValidator(*this);
}

bool Resource::Validator::isValid() const {
  bool ret = false;
  
  if (!mReserve.isLocked()) {
    if (mIsValid.load()) {
      ret = true;
    }
  }

  return ret;
}

TimeValue Resource::Validator::deadline() const {
  // /!\ WARNING: thread-safety imposes to read mValidity before
  // checking isValid!
  bool isValidBeforeRead = isValid();

  TimeValue deadline = mDeadline;
  
  bool isValidAfterRead = isValid();

  if (isValidBeforeRead && isValidAfterRead) {    
    return deadline;
  }
  else {
    return TimeValue::MAX;
  }
}

void Resource::Validator::setIsValid(bool valid) {
  bool oldIsValid = mIsValid.exchange(valid);

  if (!oldIsValid && valid) {
    assert(mReserve.isLocked());
    
    mReserve.unlock();

    for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      resource.unpreventReservers();
    }
  }
  else if (oldIsValid && !valid) {
    assert(mReserve.isLocked());
    
    for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      resource.preventReservers();
    }
  }
}

void Resource::Validator::setValid(const TimeValue &deadline) {  
  bool oldIsValid = mIsValid.exchange(true);

  if (!oldIsValid) {
    assert(mReserve.isLocked());
    
    // set validity interval
    TimeValue oldDeadline = mDeadline;
    mDeadline = deadline;
    
    mReserve.unlock();

    for (vector<Resource *>::const_iterator resourceIt = resources().begin() ;
         resourceIt != resources().end() ;
         ++resourceIt) {
      Resource &resource = **resourceIt;

      resource.unpreventReservers();

      if (deadline != oldDeadline) {
        // restart reservers with the new validity
        for (vector<Reserver *>::const_iterator reserverIt = resource.reservers().begin() ;
             reserverIt != resource.reservers().end() ;
             ++reserverIt) {
          Reserver &reserver = **reserverIt;

          if (reserver.hasJob()) {            
            reserver.job().restart();
          }
        }
      }
    }
  }
}
