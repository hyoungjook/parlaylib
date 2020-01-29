#ifndef PARLAY_INTERNAL_SCHEDULER_PLUGINS_PARLAY_HPP_
#define PARLAY_INTERNAL_SCHEDULER_PLUGINS_PARLAY_HPP_

#include "../../scheduler.h"

namespace parlay {

// Use a "Meyer singleton" to provide thread-safe 
// initialisation and destruction of the scheduler
static fork_join_scheduler& __get_scheduler() {
  static fork_join_scheduler fj;
  return fj;
}

inline int num_workers() {
  return __get_scheduler().num_workers();
}

inline int worker_id() {
  return __get_scheduler().worker_id();
}

template <class F>
inline void parallel_for(long start, long end, F f,
			 long granularity,
			 bool conservative) {
  if (end > start)
    __get_scheduler().parfor(start, end, f, granularity, conservative);
}

template <typename Lf, typename Rf>
inline void par_do(Lf left, Rf right, bool conservative) {
  return __get_scheduler().pardo(left, right, conservative);
}

}  // namespace parlay

#endif  // PARLAY_INTERNAL_SCHEDULER_PLUGINS_PARLAY_HPP_
