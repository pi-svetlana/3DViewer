#include "observable.h"

#include <algorithm>

void Observable::AddObserver(Observer* const observer) {
  if ((std::find(registered_observers_.begin(), registered_observers_.end(),
                 observer) == registered_observers_.end())) {
    registered_observers_.push_back(observer);
  }
}

void Observable::RemoveObserver(Observer* const observer) {
  for (auto i = registered_observers_.begin(); i != registered_observers_.end();
       i++) {
    if (*i == observer) {
      registered_observers_.erase(i);
    }
  }
}

void Observable::NotifyObservers() {
  Context* context = GetContext();
  for (auto observer : registered_observers_) {
    observer->update(context);
  }
}