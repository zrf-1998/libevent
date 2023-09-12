#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include "event2/event.h"

void *start_routine(void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    pthread_detach(pthread_self());

    sleep(5);

    // event_base_loopexit(base, NULL);
    // event_base_loopbreak(base);

    return NULL;
}

int main(int argc, char **argv)
{
	struct event_base *base;
	enum event_method_feature f;
    pthread_t tid;

	base = event_base_new();
	if (!base) {
		puts("Couldn't get an event_base!");
	} else {
		printf("Using Libevent with backend method %s.",
			event_base_get_method(base));
		f = event_base_get_features(base);
		if ((f & EV_FEATURE_ET))
			printf("  Edge-triggered events are supported.");
		if ((f & EV_FEATURE_O1))
			printf("  O(1) event notification is supported.");
		if ((f & EV_FEATURE_FDS))
			printf("  All FD types are supported.");
		puts("");
	}

    event_base_priority_init(base, 4);
    printf("this event base support %d priorities\n", 
                            event_base_get_npriorities(base));    

    pthread_create(&tid, NULL, start_routine, base);
    event_base_loop(base, EVLOOP_NO_EXIT_ON_EMPTY);

    event_base_free(base);
	return 0;
}