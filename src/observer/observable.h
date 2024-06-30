#ifndef CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_OBSERVABLE_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_OBSERVABLE_H_

#include <list>

#include "observer.h"

class Observable {
 private:
  std::list<Observer* const> registered_observers_;

 public:
  virtual ~Observable() = default;
  void AddObserver(Observer* const observer);
  void RemoveObserver(Observer* const observer);
  void NotifyObservers();
  virtual Context* GetContext() = 0;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_OBSERVABLE_H_
