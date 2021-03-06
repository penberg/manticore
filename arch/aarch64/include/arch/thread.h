#ifndef ARM64_THREAD_H
#define ARM64_THREAD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//! The TIF_NEW flag represents a task that has never been scheduled.
//! The switch_to() function takes this into account and switches the task
//! to userspace context.
#define __TIF_NEW	0
#define TIF_NEW		(1ULL << __TIF_NEW)

struct task_state {
	void *sp;
	void *pc;
	uint32_t flags;
};

struct task_state *task_state_new(void *pc, void *sp);
void task_state_delete(struct task_state *task_state);
void task_state_init(struct task_state *task_state, void *pc, void *sp);
void *task_state_stack_top(struct task_state *task_state);
void *task_state_entry_point(struct task_state *task_state);

void switch_to(struct task_state *old, struct task_state *new);
void switch_to_first(struct task_state *task_state);
void ret_to_usespace(void *pc, void *sp);


#endif
